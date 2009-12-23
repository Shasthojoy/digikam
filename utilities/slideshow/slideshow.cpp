/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2005-04-21
 * Description : slide show tool using preview of pictures.
 *
 * Copyright (C) 2005-2008 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2004 by Enrico Ros <eros.kde@email.it>                  *
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

#define MAXSTRINGLEN 80

#include "slideshow.moc"

// Qt includes

#include <QColor>
#include <QCursor>
#include <QDesktopWidget>
#include <QEvent>
#include <QFont>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QWheelEvent>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusReply>

// KDE includes

#include <kapplication.h>
#include <kdeversion.h>
#include <kdialog.h>
#include <kglobalsettings.h>
#include <kiconloader.h>
#include <klocale.h>
#include <kstandarddirs.h>
#include <kdebug.h>

// Local includes

#include "dimg.h"
#include "globals.h"
#include "previewloadthread.h"
#include "toolbar.h"

namespace Digikam
{

class SlideShowPriv
{
public:

    SlideShowPriv()
    {
        previewThread     = 0;
        mouseMoveTimer    = 0;
        timer             = 0;
        toolBar           = 0;
        fileIndex         = -1;
        endOfShow         = false;
        pause             = false;
        screenSaverCookie = -1;

        // Pre-computed star polygon for a 15x15 pixmap.
        starPolygon << QPoint(0,  6);
        starPolygon << QPoint(5,  5);
        starPolygon << QPoint(7,  0);
        starPolygon << QPoint(9,  5);
        starPolygon << QPoint(14, 6);
        starPolygon << QPoint(10, 9);
        starPolygon << QPoint(11, 14);
        starPolygon << QPoint(7,  11);
        starPolygon << QPoint(3,  14);
        starPolygon << QPoint(4,  9);
    }

    bool               endOfShow;
    bool               pause;

    int                deskX;
    int                deskY;
    int                deskWidth;
    int                deskHeight;
    int                fileIndex;
    int                screenSaverCookie;

    QTimer*            mouseMoveTimer;  // To hide cursor when not moved.
    QTimer*            timer;

    QPixmap            pixmap;
    QPixmap            selPixmap;      // Selected rating star.
    QPixmap            regPixmap;      // Regular rating star.

    QPolygon           starPolygon;

    DImg               preview;

    KUrl               currentImage;

    PreviewLoadThread* previewThread;
    PreviewLoadThread* previewPreloadThread;

    ToolBar*           toolBar;

    SlideShowSettings  settings;
};

SlideShow::SlideShow(const SlideShowSettings& settings)
         : QWidget(0, Qt::FramelessWindowHint), d(new SlideShowPriv)
{
    d->settings = settings;

    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setWindowState( windowState() | Qt::WindowFullScreen );

    setWindowTitle( KDialog::makeStandardCaption(i18n("Slideshow")) );
    setContextMenuPolicy( Qt::PreventContextMenu );

    // ---------------------------------------------------------------

    QRect deskRect = KGlobalSettings::desktopGeometry(this);
    d->deskX       = deskRect.x();
    d->deskY       = deskRect.y();
    d->deskWidth   = deskRect.width();
    d->deskHeight  = deskRect.height();

    move(d->deskX, d->deskY);
    resize(d->deskWidth, d->deskHeight);

    QPalette palette;
    palette.setColor(backgroundRole(), Qt::black);
    setPalette(palette);
    setupRatingPixmap(d->settings.ratingColor);

    // ---------------------------------------------------------------

    d->toolBar = new ToolBar(this);
    d->toolBar->hide();
    if (!d->settings.loop)
        d->toolBar->setEnabledPrev(false);

    connect(d->toolBar, SIGNAL(signalPause()),
            this, SLOT(slotPause()));

    connect(d->toolBar, SIGNAL(signalPlay()),
            this, SLOT(slotPlay()));

    connect(d->toolBar, SIGNAL(signalNext()),
            this, SLOT(slotNext()));

    connect(d->toolBar, SIGNAL(signalPrev()),
            this, SLOT(slotPrev()));

    connect(d->toolBar, SIGNAL(signalClose()),
            this, SLOT(slotClose()));

    // ---------------------------------------------------------------

    d->previewThread        = new PreviewLoadThread();
    d->previewPreloadThread = new PreviewLoadThread();
    d->timer                = new QTimer(this);
    d->mouseMoveTimer       = new QTimer(this);

    d->previewThread->setDisplayingWidget(this);
    d->previewPreloadThread->setDisplayingWidget(this);
    connect(d->previewThread, SIGNAL(signalImageLoaded(const LoadingDescription &, const DImg &)),
            this, SLOT(slotGotImagePreview(const LoadingDescription &, const DImg&)));

    connect(d->mouseMoveTimer, SIGNAL(timeout()),
            this, SLOT(slotMouseMoveTimeOut()));

    connect(d->timer, SIGNAL(timeout()),
            this, SLOT(slotTimeOut()));

    d->timer->setSingleShot(true);
    d->timer->start(10);

    // ---------------------------------------------------------------

    inhibitScreenSaver();

    setMouseTracking(true);
    slotMouseMoveTimeOut();
}

SlideShow::~SlideShow()
{
    allowScreenSaver();

    d->timer->stop();
    d->mouseMoveTimer->stop();

    delete d->timer;
    delete d->mouseMoveTimer;
    delete d->previewThread;
    delete d->previewPreloadThread;
    delete d;
}

void SlideShow::setCurrent(const KUrl& url)
{
    int index = d->settings.fileList.indexOf(url);
    if (index != -1)
    {
        d->currentImage = url;
        d->fileIndex    = index-1;
    }
}

void SlideShow::setupRatingPixmap(const QColor& ratingColor)
{
    QColor color = ratingColor;
    if (!color.isValid())
        color = palette().color(QPalette::Active, QPalette::HighlightedText);

    d->regPixmap = QPixmap(15, 15);
    d->regPixmap.fill(Qt::transparent);
    d->selPixmap = QPixmap(15, 15);
    d->selPixmap.fill(Qt::transparent);

    QPainter p1(&d->regPixmap);
    p1.setRenderHint(QPainter::Antialiasing, true);
    p1.setBrush(palette().color(QPalette::Active, QPalette::Background));
    p1.setPen(palette().color(QPalette::Active, QPalette::Foreground));
    p1.drawPolygon(d->starPolygon, Qt::WindingFill);
    p1.end();

    QPainter p2(&d->selPixmap);
    p2.setRenderHint(QPainter::Antialiasing, true);
    p2.setBrush(color);
    p2.setPen(palette().color(QPalette::Active, QPalette::Foreground));
    p2.drawPolygon(d->starPolygon, Qt::WindingFill);
    p2.end();
}

void SlideShow::slotTimeOut()
{
    loadNextImage();
}

void SlideShow::loadNextImage()
{
    d->fileIndex++;
    int num = d->settings.fileList.count();

    if (d->fileIndex >= num)
    {
        if (d->settings.loop)
        {
            d->fileIndex = 0;
        }
    }

    if (!d->settings.loop)
    {
        d->toolBar->setEnabledPrev(d->fileIndex > 0);
        d->toolBar->setEnabledNext(d->fileIndex < num-1);
    }

    if (d->fileIndex < num)
    {
        d->currentImage = d->settings.fileList[d->fileIndex];
        d->previewThread->load(d->currentImage.toLocalFile(),
                               qMax(d->deskWidth, d->deskHeight), d->settings.exifRotate);
    }
    else
    {
        d->currentImage = KUrl();
        d->preview = DImg();
        updatePixmap();
        update();
    }
}

void SlideShow::loadPrevImage()
{
    d->fileIndex--;
    int num = d->settings.fileList.count();

    if (d->fileIndex < 0)
    {
        if (d->settings.loop)
        {
            d->fileIndex = num-1;
        }
    }

    if (!d->settings.loop)
    {
        d->toolBar->setEnabledPrev(d->fileIndex > 0);
        d->toolBar->setEnabledNext(d->fileIndex < num-1);
    }

    if (d->fileIndex >= 0 && d->fileIndex < num)
    {
        d->currentImage = d->settings.fileList[d->fileIndex];
        d->previewThread->load(d->currentImage.toLocalFile(),
                               qMax(d->deskWidth, d->deskHeight), d->settings.exifRotate);
    }
    else
    {
        d->currentImage = KUrl();
        d->preview = DImg();
        updatePixmap();
        update();
    }
}

void SlideShow::slotGotImagePreview(const LoadingDescription& desc, const DImg& preview)
{
    if (desc.filePath != d->currentImage.toLocalFile() || desc.isThumbnail())
        return;

    d->preview = preview;

    updatePixmap();
    update();

    if (!d->endOfShow)
    {
        if (!d->pause)
        {
            d->timer->setSingleShot(true);
            d->timer->start(d->settings.delay);
        }
        preloadNextImage();
    }
}

void SlideShow::preloadNextImage()
{
    int index = d->fileIndex + 1;
    int num   = d->settings.fileList.count();

    if (index >= num)
    {
        if (d->settings.loop)
        {
            index = 0;
        }
    }

    if (index < num)
    {
        d->previewPreloadThread->load(d->settings.fileList[index].toLocalFile(),
                                      qMax(d->deskWidth, d->deskHeight), d->settings.exifRotate);
    }
}

void SlideShow::updatePixmap()
{
    d->pixmap = QPixmap(size());
    d->pixmap.fill(Qt::black);
    QPainter p(&(d->pixmap));

    if (!d->currentImage.toLocalFile().isEmpty())
    {
        if (!d->preview.isNull())
        {
            // Preview extraction is complete... Draw the image.

            QPixmap pix(d->preview.smoothScale(width(), height(), Qt::KeepAspectRatio).convertToPixmap());
            p.drawPixmap((width()-pix.width())/2,
                         (height()-pix.height())/2, pix,
                         0, 0, pix.width(), pix.height());

            QString str;
            PhotoInfoContainer photoInfo = d->settings.pictInfoMap[d->currentImage].photoInfo;
            int offset = 0;

            // Display Rating.
            int rating = d->settings.pictInfoMap[d->currentImage].rating;

            if (d->settings.printRating && rating > 0)
            {
                int x = 0;
                for (int i = 0; i < rating; ++i)
                {
                    p.drawPixmap(10+x, height()-offset-d->selPixmap.height(), d->selPixmap);
                    x += d->selPixmap.width();
                }

                for (int i = rating; i < RatingMax; ++i)
                {
                    p.drawPixmap(10+x, height()-offset-d->regPixmap.height(), d->regPixmap);
                    x += d->regPixmap.width();
                }
            }

            // Display Comments.

            if (d->settings.printComment)
            {
                str = d->settings.pictInfoMap[d->currentImage].comment;
                printComments(p, offset, str);
            }

            // Display Make and Model.

            if (d->settings.printMakeModel)
            {
                str.clear();

                if (!photoInfo.make.isEmpty())
                    str = photoInfo.make;

                if (!photoInfo.model.isEmpty())
                {
                    if (!photoInfo.make.isEmpty())
                        str += QString(" / ");

                    str += photoInfo.model;
                }

                printInfoText(p, offset, str);
            }

            // Display Exposure and Sensitivity.

            if (d->settings.printExpoSensitivity)
            {
                str.clear();

                if (!photoInfo.exposureTime.isEmpty())
                    str = photoInfo.exposureTime;

                if (!photoInfo.sensitivity.isEmpty())
                {
                    if (!photoInfo.exposureTime.isEmpty())
                        str += QString(" / ");

                    str += i18n("%1 ISO",photoInfo.sensitivity);
                }

                printInfoText(p, offset, str);
            }

            // Display Aperture and Focal.

            if (d->settings.printApertureFocal)
            {
                str.clear();

                if (!photoInfo.aperture.isEmpty())
                    str = photoInfo.aperture;

                if (photoInfo.focalLength35mm.isEmpty())
                {
                    if (!photoInfo.focalLength.isEmpty())
                    {
                        if (!photoInfo.aperture.isEmpty())
                            str += QString(" / ");

                        str += photoInfo.focalLength;
                    }
                }
                else
                {
                    if (!photoInfo.aperture.isEmpty())
                            str += QString(" / ");

                    if (!photoInfo.focalLength.isEmpty())
                        str += QString("%1 (35mm: %2)").arg(photoInfo.focalLength).arg(photoInfo.focalLength35mm);
                    else
                        str += QString("35mm: %1)").arg(photoInfo.focalLength35mm);
                }

                printInfoText(p, offset, str);
            }

            // Display Creation Date.

            if (d->settings.printDate)
            {
                if (photoInfo.dateTime.isValid())
                {
                    str = KGlobal::locale()->formatDateTime(photoInfo.dateTime, KLocale::ShortDate, true);
                    printInfoText(p, offset, str);
                }
            }

            // Display image File Name.

            if (d->settings.printName)
            {
                str = QString("%1 (%2/%3)").arg(d->currentImage.fileName())
                                           .arg(QString::number(d->fileIndex + 1))
                                           .arg(QString::number(d->settings.fileList.count()));

                printInfoText(p, offset, str);
            }
        }
        else
        {
            // ...or preview extraction is failed.

            p.setPen(Qt::white);
            p.drawText(0, 0, d->pixmap.width(), d->pixmap.height(),
                       Qt::AlignCenter|Qt::TextWordWrap,
                       i18n("Cannot display image\n\"%1\"",
                       d->currentImage.fileName()));
        }
    }
    else
    {
        // End of Slide Show.

        QPixmap logo = QPixmap(KStandardDirs::locate("data", "digikam/data/logo-digikam.png"))
                               .scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        QFont fn(font());
        fn.setPointSize(fn.pointSize()+10);
        fn.setBold(true);

        p.setFont(fn);
        p.setPen(Qt::white);
        p.drawPixmap(50, 100, logo);
        p.drawText(60 + logo.width(), 100 + logo.height()/3,   i18n("Slideshow Completed."));
        p.drawText(60 + logo.width(), 100 + 2*logo.height()/3, i18n("Click To Exit..."));

        d->endOfShow = true;
        d->toolBar->setEnabledPlay(false);
        d->toolBar->setEnabledNext(false);
        d->toolBar->setEnabledPrev(false);
    }
}

void SlideShow::printInfoText(QPainter& p, int& offset, const QString& str)
{
    if (!str.isEmpty())
    {
        offset += 20;
        p.setPen(Qt::black);
        for (int x=9; x<=11; ++x)
            for (int y=offset+1; y>=offset-1; --y)
                p.drawText(x, height()-y, str);

        p.setPen(Qt::white);
        p.drawText(10, height()-offset, str);
    }
}

void SlideShow::printComments(QPainter& p, int& offset, const QString& comments)
{
    QStringList commentsByLines;

    uint commentsIndex = 0;     // Comments QString index

    while (commentsIndex < (uint)comments.length())
    {
        QString newLine;
        bool breakLine = false; // End Of Line found
        uint currIndex;         // Comments QString current index

        // Check minimal lines dimension

        uint commentsLinesLengthLocal = MAXSTRINGLEN;

        for (currIndex = commentsIndex ;
             currIndex < (uint)comments.length() && !breakLine ; ++currIndex )
        {
            if ( comments[currIndex] == QChar('\n') || comments[currIndex].isSpace() )
                breakLine = true;
        }

        if (commentsLinesLengthLocal <= (currIndex - commentsIndex))
            commentsLinesLengthLocal = (currIndex - commentsIndex);

        breakLine = false;

        for (currIndex = commentsIndex ;
             currIndex <= commentsIndex + commentsLinesLengthLocal &&
             currIndex < (uint)comments.length() && !breakLine ;
             ++currIndex )
            {
                breakLine = (comments[currIndex] == QChar('\n')) ? true : false;

                if (breakLine)
                    newLine.append(QString(" "));
                else
                    newLine.append(comments[currIndex]);
            }

            commentsIndex = currIndex; // The line is ended

        if (commentsIndex != (uint)comments.length())
        {
            while (!newLine.endsWith(' '))
            {
                newLine.truncate(newLine.length() - 1);
                --commentsIndex;
            }
        }

        commentsByLines.prepend(newLine.trimmed());
    }

    for (int i = 0 ; i < (int)commentsByLines.count() ; ++i )
    {
        printInfoText(p, offset, commentsByLines[i]);
    }
}

void SlideShow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0, 0, d->pixmap,
                 0, 0, d->pixmap.width(), d->pixmap.height());
    p.end();
}

void SlideShow::slotPause()
{
    d->timer->stop();
    d->pause = true;

    if (d->toolBar->isHidden())
    {
        int w = d->toolBar->width();
        d->toolBar->move(d->deskWidth-w-1,0);
        d->toolBar->show();
    }
}

void SlideShow::slotPlay()
{
    d->toolBar->hide();
    d->pause = false;
    slotTimeOut();
}

void SlideShow::slotPrev()
{
    loadPrevImage();
}

void SlideShow::slotNext()
{
    loadNextImage();
}

void SlideShow::slotClose()
{
    close();
}

void SlideShow::wheelEvent(QWheelEvent * e)
{
    if (e->delta() < 0)
    {
        d->timer->stop();
        d->pause = true;
        d->toolBar->setPaused(true);
        slotNext();
    }

    if (e->delta() > 0 && d->fileIndex-1 >= 0)
    {
        d->timer->stop();
        d->pause = true;
        d->toolBar->setPaused(true);
        slotPrev();
    }
}

void SlideShow::mousePressEvent(QMouseEvent *e)
{
    if (d->endOfShow)
        close();

    if (e->button() == Qt::LeftButton)
    {
        d->timer->stop();
        d->pause = true;
        d->toolBar->setPaused(true);
        slotNext();
    }
    else if (e->button() == Qt::RightButton && d->fileIndex-1 >= 0)
    {
        d->timer->stop();
        d->pause = true;
        d->toolBar->setPaused(true);
        slotPrev();
    }
}

void SlideShow::keyPressEvent(QKeyEvent *event)
{
    if (!event)
        return;

    d->toolBar->keyPressEvent(event);
}

static void makeCornerRectangles(const QRect& desktopRect, const QSize& size,
                                 QRect *topLeft, QRect *topRight, QRect *bottomLeft, QRect *bottomRight,
                                 QRect *topLeftLarger, QRect *topRightLarger, QRect *bottomLeftLarger, QRect *bottomRightLarger)
{
    QRect sizeRect(QPoint(0,0), size);
    *topLeft = sizeRect; *topRight = sizeRect; *bottomLeft = sizeRect; *bottomRight = sizeRect;

    topLeft->moveTo(desktopRect.x(), desktopRect.y());
    topRight->moveTo(desktopRect.x() + desktopRect.width() - sizeRect.width() - 1, topLeft->y());
    bottomLeft->moveTo(topLeft->x(), desktopRect.y() + desktopRect.height() - sizeRect.height() - 1);
    bottomRight->moveTo(topRight->x(), bottomLeft->y());

    const int marginX = 25, marginY = 10;
    *topLeftLarger     = topLeft->adjusted(0, 0, marginX, marginY);
    *topRightLarger    = topRight->adjusted(-marginX, 0, 0, marginY);
    *bottomLeftLarger  = bottomLeft->adjusted(0, -marginY, marginX, 0);
    *bottomRightLarger = bottomRight->adjusted(-marginX, -marginY, 0, 0);
}

void SlideShow::mouseMoveEvent(QMouseEvent *e)
{
    setCursor(QCursor(Qt::ArrowCursor));
    d->mouseMoveTimer->setSingleShot(true);
    d->mouseMoveTimer->start(1000);

    if (!d->toolBar->canHide())
        return;

    QPoint pos(e->pos());

    QRect sizeRect(QPoint(0,0), d->toolBar->size());
    QRect topLeft, topRight, bottomLeft, bottomRight;
    QRect topLeftLarger, topRightLarger, bottomLeftLarger, bottomRightLarger;
    makeCornerRectangles(QRect(d->deskY, d->deskY, d->deskWidth, d->deskHeight), d->toolBar->size(),
                         &topLeft, &topRight, &bottomLeft, &bottomRight,
                         &topLeftLarger, &topRightLarger, &bottomLeftLarger, &bottomRightLarger);

    if (topLeftLarger.contains(pos))
    {
        d->toolBar->move(topLeft.topLeft());
        d->toolBar->show();
    }
    else if (topRightLarger.contains(pos))
    {
        d->toolBar->move(topRight.topLeft());
        d->toolBar->show();
    }
    else if (bottomLeftLarger.contains(pos))
    {
        d->toolBar->move(bottomLeft.topLeft());
        d->toolBar->show();
    }
    else if (bottomRightLarger.contains(pos))
    {
        d->toolBar->move(bottomRight.topLeft());
        d->toolBar->show();
    }
    else
    {
        if (!d->toolBar->isHidden())
            d->toolBar->hide();
    }
}

void SlideShow::slotMouseMoveTimeOut()
{
    QPoint pos(QCursor::pos());

    QRect sizeRect(QPoint(0,0), d->toolBar->size());
    QRect topLeft, topRight, bottomLeft, bottomRight;
    QRect topLeftLarger, topRightLarger, bottomLeftLarger, bottomRightLarger;
    makeCornerRectangles(QRect(d->deskY, d->deskY, d->deskWidth, d->deskHeight), d->toolBar->size(),
                         &topLeft, &topRight, &bottomLeft, &bottomRight,
                         &topLeftLarger, &topRightLarger, &bottomLeftLarger, &bottomRightLarger);

    if (topLeftLarger.contains(pos) || topRightLarger.contains(pos)
        || bottomLeftLarger.contains(pos) || bottomRightLarger.contains(pos))
        return;

    setCursor(QCursor(Qt::BlankCursor));
}

// from Okular's presentation widget
void SlideShow::inhibitScreenSaver()
{
    QDBusMessage message = QDBusMessage::createMethodCall( "org.freedesktop.ScreenSaver", "/ScreenSaver",
                                                           "org.freedesktop.ScreenSaver", "Inhibit" );
    message << QString( "digiKam" );
    message << i18nc( "Reason for inhibiting the screensaver activation, when the presentation mode is active", "Giving a presentation" );

    QDBusReply<uint> reply = QDBusConnection::sessionBus().call( message );
    if ( reply.isValid() )
        d->screenSaverCookie = reply.value();
}

void SlideShow::allowScreenSaver()
{
    if ( d->screenSaverCookie != -1 )
    {
        QDBusMessage message = QDBusMessage::createMethodCall( "org.freedesktop.ScreenSaver", "/ScreenSaver",
                                                               "org.freedesktop.ScreenSaver", "UnInhibit" );
        message << (uint)d->screenSaverCookie;
        QDBusConnection::sessionBus().send( message );
    }
}


}  // namespace Digikam
