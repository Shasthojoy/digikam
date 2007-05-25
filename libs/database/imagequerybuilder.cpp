/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2007-03-22
 * Description : Building complex database SQL queries from search descriptions
 *
 * Copyright (C) 2005 by Renchi Raju <renchi@pooh.tam.uiuc.edu>
 * Copyright (C) 2007 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * ============================================================ */


// Qt includes.

#include <qfile.h>
#include <qdatastream.h>
#include <qtextstream.h>
#include <qregexp.h>
#include <qdir.h>
#include <qvariant.h>
#include <qmap.h>

// KDE includes.

#include <kglobal.h>
#include <klocale.h>
#include <kcalendarsystem.h>
#include <kinstance.h>
#include <kmimetype.h>

// Local includes.

#include "albumdb.h"
#include "databaseaccess.h"
#include "databasebackend.h"
#include "ddebug.h"
#include "imagequerybuilder.h"

namespace Digikam
{

ImageQueryBuilder::ImageQueryBuilder()
{
    // build a lookup table for month names
    const KCalendarSystem* cal = KGlobal::locale()->calendar();
    for (int i=1; i<=12; ++i)
    {
        m_shortMonths[i-1] = cal->monthName(i, 2000, true).lower();
        m_longMonths[i-1]  = cal->monthName(i, 2000, false).lower();
    }
}

QString ImageQueryBuilder::buildQuery(const KURL& url) const
{
    int  count = url.queryItem("count").toInt();
    if (count <= 0)
        return QString();

    QMap<int, RuleType> rulesMap;

    for (int i=1; i<=count; i++)
    {
        RuleType rule;

        QString key = url.queryItem(QString::number(i) + ".key").lower();
        QString op  = url.queryItem(QString::number(i) + ".op").lower();

        if (key == "album")
        {
            rule.key = ALBUM;
        }
        else if (key == "albumname")
        {
            rule.key = ALBUMNAME;
        }
        else if (key == "albumcaption")
        {
            rule.key = ALBUMCAPTION;
        }
        else if (key == "albumcollection")
        {
            rule.key = ALBUMCOLLECTION;
        }
        else if (key == "imagename")
        {
            rule.key = IMAGENAME;
        }
        else if (key == "imagecaption")
        {
            rule.key = IMAGECAPTION;
        }
        else if (key == "imagedate")
        {
            rule.key = IMAGEDATE;
        }
        else if (key == "tag")
        {
            rule.key = TAG;
        }
        else if (key == "tagname")
        {
            rule.key = TAGNAME;
        }
        else if (key == "keyword")
        {
            rule.key = KEYWORD;
        }
        else if (key == "rating")
        {
            rule.key = RATING;
        }
        else
        {
            DWarning() << "Unknown rule type: " << key << " passed to kioslave"
                        << endl;
            continue;
        }

        if (op == "eq")
            rule.op = EQ;
        else if (op == "ne")
            rule.op = NE;
        else if (op == "lt")
            rule.op = LT;
        else if (op == "lte")
            rule.op = LTE;
        else if (op == "gt")
            rule.op = GT;
        else if (op == "gte")
            rule.op = GTE;
        else if (op == "like")
            rule.op = LIKE;
        else if (op == "nlike")
            rule.op = NLIKE;
        else
        {
            DWarning() << "Unknown op type: " << op << " passed to kioslave"
                        << endl;
            continue;
        }

        rule.val = url.queryItem(QString::number(i) + ".val");

        rulesMap.insert(i, rule);
    }

    QString sqlQuery;

    QStringList strList = QStringList::split(" ", url.path());
    for ( QStringList::Iterator it = strList.begin(); it != strList.end(); ++it )
    {
        bool ok;
        int  num = (*it).toInt(&ok);
        if (ok)
        {
            RuleType rule = rulesMap[num];
            if (rule.key == KEYWORD)
            {
                bool exact;
                QString possDate = possibleDate(rule.val, exact);
                if (!possDate.isEmpty())
                {
                    rule.key = IMAGEDATE;
                    rule.val = possDate;
                    if (exact)
                    {
                        rule.op = EQ;
                    }
                    else
                    {
                        rule.op = LIKE;
                    }

                    sqlQuery += subQuery(rule.key, rule.op, rule.val);
                }
                else
                {
                    QValueList<SKey> todo;
                    todo.append( ALBUMNAME );
                    todo.append( IMAGENAME );
                    todo.append( TAGNAME );
                    todo.append( ALBUMCAPTION );
                    todo.append( ALBUMCOLLECTION );
                    todo.append( IMAGECAPTION );
                    todo.append( RATING );

                    sqlQuery += '(';
                    QValueListIterator<SKey> it;
                    it = todo.begin();
                    while ( it != todo.end() )
                    {
                        sqlQuery += subQuery(*it, rule.op, rule.val);
                        ++it;
                        if ( it != todo.end() )
                            sqlQuery += " OR ";
                    }
                    sqlQuery += ')';
                }
            }
            else
            {
                sqlQuery += subQuery(rule.key, rule.op, rule.val);
            }
        }
        else
        {
            sqlQuery += ' ' + *it + ' ';
        }
    }

    return sqlQuery;
}

QString ImageQueryBuilder::subQuery(enum ImageQueryBuilder::SKey key,
                                    enum ImageQueryBuilder::SOperator op,
                                    const QString& val) const
{
    QString query;
    QString escapedVal;
    {
        DatabaseAccess access;
        escapedVal = access.backend()->escapeString(val);
    }

    switch (key)
    {
        case(ALBUM):
        {
            query = " (Images.dirid $$##$$ $$@@$$) ";
            break;
        }
        case(ALBUMNAME):
        {
            query = " (Images.dirid IN "
                    "  (SELECT id FROM Albums WHERE url $$##$$ $$@@$$)) ";
            break;
        }
        case(ALBUMCAPTION):
        {
            query = " (Images.dirid IN "
                    "  (SELECT id FROM Albums WHERE caption $$##$$ $$@@$$)) ";
            break;
        }
        case(ALBUMCOLLECTION):
        {
            query = " (Images.dirid IN "
                    "  (SELECT id FROM Albums WHERE collection $$##$$ $$@@$$)) ";
            break;
        }
        case(TAG):
        {
            if (op == EQ)
                query = " (Images.id IN "
                        "   (SELECT imageid FROM ImageTags "
                        "    WHERE tagid = $$@@$$)) ";
            else if (op == NE)
                query = " (Images.id NOT IN "
                        "   (SELECT imageid FROM ImageTags "
                        "    WHERE tagid = $$@@$$)) ";
            else if (op == LIKE) 
                query = " (Images.id IN "
                        "   (SELECT ImageTags.imageid FROM ImageTags JOIN TagsTree on ImageTags.tagid = TagsTree.id "
                        "    WHERE TagsTree.pid = $$@@$$ or ImageTags.tagid = $$@@$$ )) ";
            else // op == NLIKE
                query = " (Images.id NOT IN "
                        "   (SELECT ImageTags.imageid FROM ImageTags JOIN TagsTree on ImageTags.tagid = TagsTree.id "
                        "    WHERE TagsTree.pid = $$@@$$ or ImageTags.tagid = $$@@$$ )) ";

    //         query = " (Images.id IN "
    //                 "   (SELECT imageid FROM ImageTags "
    //                 "    WHERE tagid $$##$$ $$@@$$)) ";

            query.replace("$$@@$$", QString::fromLatin1("'") + escapedVal
                        + QString::fromLatin1("'"));

            break;
        }
        case(TAGNAME):
        {
            query = " (Images.id IN "
                    "  (SELECT imageid FROM ImageTags "
                    "   WHERE tagid IN "
                    "   (SELECT id FROM Tags WHERE name $$##$$ $$@@$$))) ";
            break;
        }
        case(IMAGENAME):
        {
            query = " (Images.name $$##$$ $$@@$$) ";
            break;
        }
        case(IMAGECAPTION):
        {
            query = " (Images.caption $$##$$ $$@@$$) ";
            break;
        }
        case(IMAGEDATE):
        {
            query = " (Images.datetime $$##$$ $$@@$$) ";
            break;
        }
        case (KEYWORD):
        {
            DWarning() << "KEYWORD Detected which is not possible" << endl;
            break;
        }
        case(RATING):
        {
            query = " (ImageProperties.value $$##$$ $$@@$$ and ImageProperties.property='Rating') ";
            break;
        }
    }

    if (key != TAG)
    {
        switch (op)
        {
            case(EQ):
            {
                query.replace("$$##$$", "=");
                query.replace("$$@@$$", QString::fromLatin1("'") + escapedVal
                            + QString::fromLatin1("'"));
                break;
            }
            case(NE):
            {
                query.replace("$$##$$", "<>");
                query.replace("$$@@$$", QString::fromLatin1("'") + escapedVal
                            + QString::fromLatin1("'"));
                break;
            }
            case(LT):
            {
                query.replace("$$##$$", "<");
                query.replace("$$@@$$", QString::fromLatin1("'") + escapedVal
                            + QString::fromLatin1("'"));
                break;
            }
            case(GT):
            {
                query.replace("$$##$$", ">");
                query.replace("$$@@$$", QString::fromLatin1("'") + escapedVal
                            + QString::fromLatin1("'"));
                break;
            }
            case(LTE):
            {
                query.replace("$$##$$", "<=");
                query.replace("$$@@$$", QString::fromLatin1("'") + escapedVal
                            + QString::fromLatin1("'"));
                break;
            }
            case(GTE):
            {
                query.replace("$$##$$", ">=");
                query.replace("$$@@$$", QString::fromLatin1("'") + escapedVal
                            + QString::fromLatin1("'"));
                break;
            }
            case(LIKE):
            {
                query.replace("$$##$$", "LIKE");
                query.replace("$$@@$$", QString::fromLatin1("'%") + escapedVal
                            + QString::fromLatin1("%'"));
                break;
            }
            case(NLIKE):
            {
                query.replace("$$##$$", "NOT LIKE");
                query.replace("$$@@$$", QString::fromLatin1("'%") + escapedVal
                            + QString::fromLatin1("%'"));
                break;
            }
        }
    }

    // special case for imagedate. If the key is imagedate and the operator is EQ,
    // we need to split it into two rules
    if (key == IMAGEDATE && op == EQ)
    {
        QDate date = QDate::fromString(val, Qt::ISODate);
        if (!date.isValid())
            return query;

        query = QString(" (Images.datetime > '%1' AND Images.datetime < '%2') ")
                .arg(date.addDays(-1).toString(Qt::ISODate))
                .arg(date.addDays( 1).toString(Qt::ISODate));
    }

    return query;
}

QString ImageQueryBuilder::possibleDate(const QString& str, bool& exact) const
{
    QDate date = QDate::fromString(str, Qt::ISODate);
    if (date.isValid())
    {
        exact = true;
        return date.toString(Qt::ISODate);
    }

    exact = false;

    bool ok;
    int num = str.toInt(&ok);
    if (ok)
    {
        // ok. its an int, does it look like a year?
        if (1970 <= num && num <= QDate::currentDate().year())
        {
            // very sure its a year
            return QString("%1-%-%").arg(num);
        }
    }
    else
    {
        // hmm... not a year. is it a particular month?
        for (int i=1; i<=12; i++)
        {
            if (str.lower() == m_shortMonths[i-1] ||
                str.lower() == m_longMonths[i-1])
            {
                QString monGlob;
                monGlob.sprintf("%.2d", i);
                monGlob = "%-" + monGlob + "-%";
                return monGlob;
            }
        }
    }

    return QString();
}


}


