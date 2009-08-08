/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2005-11-24
 * Description : Color management setup tab.
 *
 * Copyright (C) 2005-2007 by F.J. Cruz <fj.cruz@supercable.es>
 * Copyright (C) 2005-2009 by Gilles Caulier <caulier dot gilles at gmail dot com> 
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
 *
 * ============================================================ */

#ifndef SETUPICC_H
#define SETUPICC_H

// Qt includes

#include <QScrollArea>
#include <QMap>
#include <QDir>

// KDE includes

#include <kurl.h>

// Local includes

#include "digikam_export.h"

class KPageDialog;

namespace Digikam
{

class IccProfile;
class SetupICCPriv;

class SetupICC : public QScrollArea
{
    Q_OBJECT

public:

    SetupICC(QWidget* parent = 0, KPageDialog* dialog = 0);
    ~SetupICC();

    void applySettings();

    static bool iccRepositoryIsValid();

private:

    void readSettings(bool restore=false);
    void fillCombos(bool report);
    void setWidgetsEnabled(bool enabled);
    void profileInfo(const QString&);
    void parseProfiles(const QList<IccProfile>& profiles);
    static QList<IccProfile> scanDirectories(const QStringList& paths);
    static void scanDirectory(const QString& path, const QStringList& filter, QList<IccProfile> *profiles);

private Q_SLOTS:

    void slotToggledEnabled();
    void slotToggledManagedView();
    void processLcmsUrl(const QString&);
    void slotUrlChanged();
    void slotClickedIn();
    void slotClickedWork();
    void slotClickedMonitor();
    void slotClickedProof();

private:

    SetupICCPriv* const d;
};

}  // namespace Digikam

#endif // SETUPICC_H 
