/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2016-04-21
 * Description : Qt Multimedia based video thumbnailer 
 *
 * Copyright (C) 2016 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#include "loadvideothumb_p.h"

// Qt includes

#include <QApplication>
#include <QImage>
#include <QDebug>

VideoThumbnailer::VideoThumbnailer(QObject* const parent)
    : QObject(parent),
      d(new Private)
{
    d->player = new QMediaPlayer(this);
    d->probe  = new QVideoProbe(this);

    connect(d->player, SIGNAL(error(QMediaPlayer::Error)),
            this, SLOT(slotHandlePlayerError()));

    connect(d->player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(slotMediaStatusChanged(QMediaPlayer::MediaStatus)));

    connect(d->probe, SIGNAL(videoFrameProbed(QVideoFrame)),
            this, SLOT(slotProcessframe(QVideoFrame)));
}

VideoThumbnailer::~VideoThumbnailer()
{
    delete d;
}

bool VideoThumbnailer::getThumbnail(const QString& file)
{
    if (!d->probe->setSource(d->player))
    {
        qDebug() << "Video monitoring is not available.";
        return false;
    }

    d->media = QMediaContent(QUrl::fromLocalFile(file));
    d->player->setMedia(d->media);

    return true;
}

void VideoThumbnailer::slotMediaStatusChanged(QMediaPlayer::MediaStatus state)
{
    if (d->player->currentMedia() != d->media)
        return;

    switch (state)
    {
        case QMediaPlayer::LoadedMedia:
        {
            if (!d->player->isSeekable())
            {
                qDebug() << "Video seek is not available for " << d->fileName();
                emit signalVideoThumbDone();
            }

            qDebug() << "Video duration for " << d->fileName() << "is " << d->player->duration() << " seconds";

            d->position = (qint64)(d->player->duration() * 0.2);

            d->player->setPosition(d->position);    // Seek to 20% of the media to take a thumb.
            d->player->pause();

            qDebug() << "Trying to get thumbnail from " << d->fileName() << " at position " << d->position;
            break;
        }
        case QMediaPlayer::InvalidMedia:
        {
            qDebug() << "Video cannot be decoded for " << d->fileName();
            emit signalVideoThumbDone(); 
        }
        default:
            break;
    }
}

void VideoThumbnailer::slotHandlePlayerError()
{
    qDebug() << "Problem while video data extraction from " << d->fileName();
    qDebug() << "Error : " << d->player->errorString();

    emit signalVideoThumbDone();
}

void VideoThumbnailer::slotProcessframe(QVideoFrame frm)
{
    if (d->player->mediaStatus() != QMediaPlayer::BufferedMedia)
        return;

    if (d->player->position() != d->position)
        return;

    qDebug() << "Video frame extraction from " << d->fileName()
             << " at position " << d->position;

    if (!frm.isValid())
    {
        qDebug() << "Error : Video frame is not valid.";
        emit signalVideoThumbDone();
    }

    QImage img = d->imageFromVideoFrame(frm);

    if (!img.isNull())
    {
        img.save(QString::fromUtf8("%1-thumb.png").arg(d->fileName()), "PNG");
        qDebug() << "Video frame extracted with size " << img.size();
    }
    else
    {
        qDebug() << "Video frame format is not supported: " << frm;
        qDebug() << "Video frame is not extracted.";
    }

    emit signalVideoThumbDone();
}

// --------------------------------------------------------------------------

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        qDebug() << "loadvideothumb - Load video file to extract thumbnail";
        qDebug() << "Usage: <videofile>";
        return -1;
    }

    QApplication app(argc, argv);
    VideoThumbnailer* const vthumb = new VideoThumbnailer(&app);

    QObject::connect(vthumb, SIGNAL(signalVideoThumbDone()),
                     &app, SLOT(quit()));

    if (!vthumb->getThumbnail(QString::fromUtf8(argv[1])))
        return -1;

    return app.exec();
}