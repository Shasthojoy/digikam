/* ============================================================
 * Authors: Renchi Raju <renchi@pooh.tam.uiuc.edu>
 *          Gilles Caulier <caulier dot gilles at gmail dot com> 
 * Date   : 2004-02-14
 * Description : image data interface for image plugins
 *
 * Copyright 2004-2005 by Renchi Raju, Gilles Caulier
 * Copyright 2006-2007 by Gilles Caulier
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

// Qt includes.

#include <qwidget.h>
#include <qsize.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qpainter.h>

// Local includes.

#include "ddebug.h"
#include "exposurecontainer.h"
#include "iccsettingscontainer.h"
#include "icctransform.h"
#include "dimginterface.h"
#include "bcgmodifier.h"
#include "dmetadata.h"
#include "imageiface.h"

namespace Digikam
{

class ImageIfacePriv
{
public:

    ImageIfacePriv()
    {
        usePreviewSelection = false;
        previewWidth        = 0;
        previewHeight       = 0;
    }

    bool    usePreviewSelection;

    int     originalWidth;
    int     originalHeight;
    int     originalBytesDepth;

    int     constrainWidth;
    int     constrainHeight;

    int     previewWidth;
    int     previewHeight;

    QPixmap qcheck;
    QPixmap qpix;
    QBitmap qmask;
    
    DImg    previewImage;
    DImg    targetPreviewImage;
};

ImageIface::ImageIface(int w, int h)
{
    d = new ImageIfacePriv;

    d->constrainWidth  = w;
    d->constrainHeight = h;

    d->originalWidth      = DImgInterface::instance()->origWidth();
    d->originalHeight     = DImgInterface::instance()->origHeight();
    d->originalBytesDepth = DImgInterface::instance()->bytesDepth();

    d->qpix.setMask(d->qmask);
    d->qcheck.resize(8, 8);

    QPainter p;
    p.begin(&d->qcheck);
    p.fillRect(0, 0, 4, 4, QColor(144,144,144));
    p.fillRect(4, 4, 4, 4, QColor(144,144,144));
    p.fillRect(0, 4, 4, 4, QColor(100,100,100));
    p.fillRect(4, 0, 4, 4, QColor(100,100,100));
    p.end();
}

ImageIface::~ImageIface()
{
    delete d;
}

void ImageIface::setPreviewType(bool useSelect)
{
    d->usePreviewSelection = useSelect; 
}

bool ImageIface::previewType()
{
    return d->usePreviewSelection;
}

DColor ImageIface::getColorInfoFromOriginalImage(QPoint point)
{
    if ( !DImgInterface::instance()->getImage() || point.x() > originalWidth() || point.y() > originalHeight() )
    {
        DWarning() << k_funcinfo << "Coordinate out of range or no image data available!" << endl;
        return DColor();
    }

    return DImgInterface::instance()->getImg()->getPixelColor(point.x(), point.y());
}

DColor ImageIface::getColorInfoFromPreviewImage(QPoint point)
{
    if ( d->previewImage.isNull() || point.x() > previewWidth() || point.y() > previewHeight() )
    {
        DWarning() << k_funcinfo << "Coordinate out of range or no image data available!" << endl;
        return DColor();
    }

    return d->previewImage.getPixelColor(point.x(), point.y());
}

DColor ImageIface::getColorInfoFromTargetPreviewImage(QPoint point)
{
    if ( d->targetPreviewImage.isNull() || point.x() > previewWidth() || point.y() > previewHeight() )
    {
        DWarning() << k_funcinfo << "Coordinate out of range or no image data available!" << endl;
        return DColor::DColor();
    }

    return d->targetPreviewImage.getPixelColor(point.x(), point.y());
}

uchar* ImageIface::setPreviewImageSize(int w, int h)
{
    d->previewImage.reset();
    d->targetPreviewImage.reset();

    d->constrainWidth  = w;
    d->constrainHeight = h;

    return (getPreviewImage());
}

uchar* ImageIface::getPreviewImage()
{
    if (d->previewImage.isNull())
    {
        DImg *im = 0;

        if (!d->usePreviewSelection)
            im = DImgInterface::instance()->getImg();
        else 
        {
            int    x, y, w, h;
            bool   s    = DImgInterface::instance()->sixteenBit();
            bool   a    = DImgInterface::instance()->hasAlpha();
            uchar *data = DImgInterface::instance()->getImageSelection();
            DImgInterface::instance()->getSelectedArea(x, y, w, h);
            im = new DImg(w, h, s, a, data, true); 
            delete [] data;
        }

        if (!im || im->isNull())
            return 0;

        QSize sz(im->width(), im->height());
        sz.scale(d->constrainWidth, d->constrainHeight, QSize::ScaleMin);

        d->previewImage  = im->smoothScale(sz.width(), sz.height());
        d->previewWidth  = d->previewImage.width();
        d->previewHeight = d->previewImage.height();

        // only create another copy if needed, in putPreviewImage
        d->targetPreviewImage = d->previewImage;

        d->qmask.resize(d->previewWidth, d->previewHeight);
        d->qpix.resize(d->previewWidth, d->previewHeight);
    }

    DImg previewData = d->previewImage.copyImageData();
    return previewData.stripImageData();
}

uchar* ImageIface::getOriginalImage()
{
    DImg *im = DImgInterface::instance()->getImg();

    if (!im || im->isNull())
        return 0;

    DImg origData = im->copyImageData();
    return origData.stripImageData();
}

DImg* ImageIface::getOriginalImg()
{
    return DImgInterface::instance()->getImg();
}

uchar* ImageIface::getImageSelection()
{
    return DImgInterface::instance()->getImageSelection();
}

void ImageIface::putPreviewImage(uchar* data)
{
    if (!data)
        return;

    if (d->targetPreviewImage == d->previewImage)
    {
        d->targetPreviewImage = DImg(d->previewImage.width(), d->previewImage.height(),
                                     d->previewImage.sixteenBit(), d->previewImage.hasAlpha(), data);
    }
    else
    {
        d->targetPreviewImage.putImageData(data);
    }
}

void ImageIface::putOriginalImage(const QString &caller, uchar* data, int w, int h)
{
    if (!data)
        return;

    DImgInterface::instance()->putImage(caller, data, w, h);
}

void ImageIface::setEmbeddedICCToOriginalImage( QString profilePath)
{
    DImgInterface::instance()->setEmbeddedICCToOriginalImage( profilePath );
}

void ImageIface::putImageSelection(const QString &caller, uchar* data)
{
    if (!data)
        return;

    DImgInterface::instance()->putImageSelection(caller, data);
}

int ImageIface::previewWidth()
{
    return d->previewWidth;
}

int ImageIface::previewHeight()
{
    return d->previewHeight;
}

bool ImageIface::previewSixteenBit()
{
    return originalSixteenBit();
}

bool ImageIface::previewHasAlpha()
{
    return originalHasAlpha();
}

int ImageIface::originalWidth()
{
    return DImgInterface::instance()->origWidth();
}

int ImageIface::originalHeight()
{
    return DImgInterface::instance()->origHeight();
}

bool ImageIface::originalSixteenBit()
{
    return DImgInterface::instance()->sixteenBit();
}

bool ImageIface::originalHasAlpha()
{
    return DImgInterface::instance()->hasAlpha();
}

int ImageIface::selectedWidth()
{
    int x, y, w, h;
    DImgInterface::instance()->getSelectedArea(x, y, w, h);
    return w;
}

int ImageIface::selectedHeight()
{
    int x, y, w, h;
    DImgInterface::instance()->getSelectedArea(x, y, w, h);
    return h;
}

int ImageIface::selectedXOrg()
{
    int x, y, w, h;
    DImgInterface::instance()->getSelectedArea(x, y, w, h);
    return x;
}

int ImageIface::selectedYOrg()
{
    int x, y, w, h;
    DImgInterface::instance()->getSelectedArea(x, y, w, h);
    return y;
}

void ImageIface::setPreviewBCG(double brightness, double contrast, double gamma)
{
    DImg preview = d->targetPreviewImage.copyImageData();
    BCGModifier cmod;
    cmod.setGamma(gamma);
    cmod.setBrightness(brightness);
    cmod.setContrast(contrast);
    cmod.applyBCG(preview);
    putPreviewImage(preview.bits());
}

void ImageIface::setOriginalBCG(double brightness, double contrast, double gamma)
{
    DImgInterface::instance()->setBCG(brightness, contrast, gamma);    
}

void ImageIface::convertOriginalColorDepth(int depth)
{
    DImgInterface::instance()->convertDepth(depth);
}

QPixmap ImageIface::convertToPixmap(DImg& img)
{
    return DImgInterface::instance()->convertToPixmap(img);
}

QByteArray ImageIface::getEmbeddedICCFromOriginalImage()
{
    return DImgInterface::instance()->getEmbeddedICC();
}

QByteArray ImageIface::getExifFromOriginalImage()
{
    return DImgInterface::instance()->getExif();
}

QByteArray ImageIface::getIptcFromOriginalImage()
{
    return DImgInterface::instance()->getIptc();
}

PhotoInfoContainer ImageIface::getPhotographInformations() const
{
    DMetadata meta;
    meta.setExif(DImgInterface::instance()->getExif());
    meta.setIptc(DImgInterface::instance()->getIptc());
    return meta.getPhotographInformations();
}

void ImageIface::paint(QPaintDevice* device, int x, int y, int w, int h,
                       bool underExposure, bool overExposure)
{
    if ( !d->targetPreviewImage.isNull() )
    {
        if (d->targetPreviewImage.hasAlpha())
        {
            QPainter p(&d->qpix);
            p.drawTiledPixmap(0, 0, d->qpix.width(), d->qpix.height(), d->qcheck);
            p.end();
        }
        
        QPixmap pixImage;
        ICCSettingsContainer *iccSettings = DImgInterface::instance()->getICCSettings();

        if (iccSettings)
        {
            IccTransform monitorICCtrans;
            monitorICCtrans.setProfiles(iccSettings->workspaceSetting, iccSettings->monitorSetting);

            if (iccSettings->enableCMSetting && iccSettings->managedViewSetting)
            {
                pixImage = d->targetPreviewImage.convertToPixmap(&monitorICCtrans);
            }
            else
            {
                pixImage = d->targetPreviewImage.convertToPixmap();
            }
        }
        else
        {
            pixImage = d->targetPreviewImage.convertToPixmap();
        }
        
        bitBlt(&d->qpix, 0, 0, &pixImage, 0, 0, w, h, Qt::CopyROP, false);

        // Show the Over/Under exposure pixels indicators 
    
        if (underExposure || overExposure)
        {
            ExposureSettingsContainer expoSettings;
            expoSettings.underExposureIndicator = underExposure;
            expoSettings.overExposureIndicator  = overExposure;
            expoSettings.underExposureColor     = DImgInterface::instance()->underExposureColor();
            expoSettings.overExposureColor      = DImgInterface::instance()->overExposureColor();

            QImage pureColorMask = d->targetPreviewImage.pureColorMask(&expoSettings);
            QPixmap pixMask(pureColorMask); 
            bitBlt(&d->qpix, 0, 0, &pixMask, 0, 0, w, h, Qt::CopyROP, false);
        }
    }

    bitBlt(device, x, y, &d->qpix, 0, 0, -1, -1, Qt::CopyROP, false);
}

}   // namespace Digikam

