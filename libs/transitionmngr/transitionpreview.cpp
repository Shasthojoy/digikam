/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2017-06-04
 * Description : A label to show transition preview
 *
 * Copyright (C) 2017 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#include "transitionpreview.h"

// Qt includes

#include <QTimer>
#include <QImage>
#include <QPixmap>

// Local includes

#include "vidslidetask.h"
#include "digikam_debug.h"

namespace Digikam
{

class TransitionPreview::Private
{
public:

    Private()
    {
        mngr          = 0;
        curTransition = TransitionMngr::None;
        previewSize   = QSize(256, 192);
    }

    QTimer                    timer;
    TransitionMngr*           mngr;
    TransitionMngr::TransType curTransition;
    QSize                     previewSize;
};

TransitionPreview::TransitionPreview(QWidget* const parent)
    : QLabel(parent),
      d(new Private)
{
    setFixedSize(d->previewSize);
    setContentsMargins(QMargins());
    setScaledContents(false);
    setOpenExternalLinks(false);
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));

    d->mngr = new TransitionMngr;
    d->mngr->setOutputSize(d->previewSize);

    connect(&d->timer, SIGNAL(timeout()),
            this, SLOT(slotProgressTransition()));
}

TransitionPreview::~TransitionPreview()
{
    delete d;
}

void TransitionPreview::setImagesList(const QList<QUrl>& images)
{
    if (!images.isEmpty())
    {
        d->mngr->setInImage(VidSlideTask::makeFramedImage(images[0].toLocalFile(), d->previewSize));

        if (images.count() > 1)
        {
            d->mngr->setOutImage(VidSlideTask::makeFramedImage(images[1].toLocalFile(), d->previewSize));
        }
        else
        {
            QImage blank(d->previewSize, QImage::Format_ARGB32);
            blank.fill(0);
            d->mngr->setOutImage(blank);
        }
    }
}

void TransitionPreview::startPreview(TransitionMngr::TransType eff)
{
    d->curTransition = eff;
    d->mngr->setTransition(eff);
    d->timer.start(100);
}

void TransitionPreview::slotProgressTransition()
{
    int tmout  = -1;
    QImage img = d->mngr->currentframe(tmout);
    setPixmap(QPixmap::fromImage(img));

    if (tmout == -1)
        startPreview(d->curTransition);
}

void TransitionPreview::stopPreview()
{
    d->timer.stop();
}

} // namespace Digikam