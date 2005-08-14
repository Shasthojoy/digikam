/* ============================================================
 * File  : imageeffect_border.cpp
 * Author: Gilles Caulier <caulier dot gilles at free.fr>
 * Date  : 2005-01-20
 * Description : a Digikam image plugin for add a border  
 *               around an image.
 * 
 * Copyright 2005 by Gilles Caulier
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
 
#include <qlabel.h>
#include <qwhatsthis.h>
#include <qlayout.h>
#include <qcombobox.h>

// KDE includes.

#include <klocale.h>
#include <kaboutdata.h>
#include <kiconloader.h>
#include <kapplication.h>
#include <kstandarddirs.h>
#include <kconfig.h>
#include <knuminput.h>
#include <kcolorbutton.h>

// Digikam includes.

#include <digikamheaders.h>

// Local includes.

#include "version.h"
#include "border.h"
#include "imageeffect_border.h"

namespace DigikamBorderImagesPlugin
{

ImageEffect_Border::ImageEffect_Border(QWidget* parent)
                  : ImageGuideDialog(parent, i18n("Add Border Around Photograph"), "border", 
                                     false, false, false)
{
    // No need Abort button action.
    showButton(User1, false); 
    
    QString whatsThis;
    
    KAboutData* about = new KAboutData("digikamimageplugins",
                                       I18N_NOOP("Add Border"), 
                                       digikamimageplugins_version,
                                       I18N_NOOP("A digiKam image plugin to add a border around an image."),
                                       KAboutData::License_GPL,
                                       "(c) 2005, Gilles Caulier", 
                                       0,
                                       "http://extragear.kde.org/apps/digikamimageplugins");
                                       
    about->addAuthor("Gilles Caulier", I18N_NOOP("Author and maintainer"),
                     "caulier dot gilles at free.fr");

    setAboutData(about);
    
    // -------------------------------------------------------------
    
    QWidget *gboxSettings = new QWidget(plainPage());
    QGridLayout* gridSettings = new QGridLayout( gboxSettings, 5, 2, marginHint(), spacingHint());
                                                  
    QLabel *label1 = new QLabel(i18n("Type:"), gboxSettings);
    
    m_borderType = new QComboBox( false, gboxSettings );
    m_borderType->insertItem( i18n("Solid") );
    // Niepce is Real name. This is the first guy in the world to have built a camera.
    m_borderType->insertItem( "Niepce" );     
    m_borderType->insertItem( i18n("Beveled") );
    m_borderType->insertItem( i18n("Decorative Pine") );
    m_borderType->insertItem( i18n("Decorative Wood") );
    m_borderType->insertItem( i18n("Decorative Paper") );
    m_borderType->insertItem( i18n("Decorative Parque") );
    m_borderType->insertItem( i18n("Decorative Ice") );
    m_borderType->insertItem( i18n("Decorative Leaf") );
    m_borderType->insertItem( i18n("Decorative Marble") );
    m_borderType->insertItem( i18n("Decorative Rain") );
    m_borderType->insertItem( i18n("Decorative Craters") );
    m_borderType->insertItem( i18n("Decorative Dried") );
    m_borderType->insertItem( i18n("Decorative Pink") );
    m_borderType->insertItem( i18n("Decorative Stone") );
    m_borderType->insertItem( i18n("Decorative Chalk") );
    m_borderType->insertItem( i18n("Decorative Granite") );
    m_borderType->insertItem( i18n("Decorative Rock") );
    m_borderType->insertItem( i18n("Decorative Wall") );
    QWhatsThis::add( m_borderType, i18n("<p>Select here the border type to add around the image."));
    
    gridSettings->addMultiCellWidget(label1, 0, 0, 0, 2);
    gridSettings->addMultiCellWidget(m_borderType, 1, 1, 0, 2);
    
    QLabel *label2 = new QLabel(i18n("Width:"), gboxSettings);
    m_borderWidth = new KIntNumInput(gboxSettings);
    QWhatsThis::add( m_borderWidth, i18n("<p>Set here the border width in pixels to add around the image."));
    gridSettings->addMultiCellWidget(label2, 2, 2, 0, 2);
    gridSettings->addMultiCellWidget(m_borderWidth, 3, 3, 0, 2);
            
    m_labelForeground = new QLabel(gboxSettings);
    m_firstColorButton = new KColorButton( QColor::QColor( 192, 192, 192 ), gboxSettings );
    m_labelBackground = new QLabel(gboxSettings);
    m_secondColorButton = new KColorButton( QColor::QColor( 128, 128, 128 ), gboxSettings );
    gridSettings->addMultiCellWidget(m_labelForeground, 4, 4, 0, 0);
    gridSettings->addMultiCellWidget(m_firstColorButton, 4, 4, 1, 2);
    gridSettings->addMultiCellWidget(m_labelBackground, 5, 5, 0, 0);
    gridSettings->addMultiCellWidget(m_secondColorButton, 5, 5, 1, 2);    

    setUserAreaWidget(gboxSettings);
    
    // -------------------------------------------------------------

    Digikam::ImageIface iface(0, 0);
    int w = iface.originalWidth();
    int h = iface.originalHeight();
    
    if (w > h) 
       m_borderWidth->setRange(1, h/2, 1, true);       
    else 
       m_borderWidth->setRange(1, w/2, 1, true);

    readSettings();
            
    // -------------------------------------------------------------
    
    connect(m_borderType, SIGNAL(activated(int)),
            this, SLOT(slotBorderTypeChanged(int)));
            
    connect(m_borderWidth, SIGNAL(valueChanged(int)),
            this, SLOT(slotTimer()));            

    connect(m_firstColorButton, SIGNAL(changed(const QColor &)),
            this, SLOT(slotColorForegroundChanged(const QColor &)));            

    connect(m_secondColorButton, SIGNAL(changed(const QColor &)),
            this, SLOT(slotColorBackgroundChanged(const QColor &))); 
}

ImageEffect_Border::~ImageEffect_Border()
{
    writeSettings();
}

void ImageEffect_Border::readSettings(void)
{
    KConfig *config = kapp->config();
    config->setGroup("Add Border Tool Settings");
    
    m_borderType->setCurrentItem( config->readNumEntry("Border Type", Border::SolidBorder) );
    m_borderWidth->setValue( config->readNumEntry("Border Width", 100) );
    
    QColor *black = new QColor( 0, 0, 0 );
    QColor *white = new QColor( 255, 255, 255 );
    QColor *gray1 = new QColor( 192, 192, 192 );
    QColor *gray2 = new QColor( 128, 128, 128 );
    
    m_solidColor = config->readColorEntry("Solid Color", black);
    m_niepceBorderColor = config->readColorEntry("Niepce Border Color", white);
    m_niepceLineColor = config->readColorEntry("Niepce Line Color", black);
    m_bevelUpperLeftColor = config->readColorEntry("Bevel Upper Left Color", gray1);
    m_bevelLowerRightColor = config->readColorEntry("Bevel Lower Right Color", gray2);
    m_decorativeFirstColor = config->readColorEntry("Decorative First Color", black);; 
    m_decorativeSecondColor = config->readColorEntry("Decorative Second Color", black);
    
    delete black;
    delete white;
    delete gray1;
    delete gray2;
              
    slotBorderTypeChanged(m_borderType->currentItem());
}
    
void ImageEffect_Border::writeSettings(void)
{
    KConfig *config = kapp->config();
    config->setGroup("Add Border Tool Settings");
    
    config->writeEntry( "Border Type", m_borderType->currentItem() );
    config->writeEntry( "Border Width", m_borderWidth->value() );
    
    config->writeEntry( "Solid Color", m_solidColor );
    config->writeEntry( "Niepce Border Color", m_niepceBorderColor );
    config->writeEntry( "Niepce Line Color", m_niepceLineColor );
    config->writeEntry( "Bevel Upper Left Color", m_bevelUpperLeftColor );
    config->writeEntry( "Bevel Lower Right Color", m_bevelLowerRightColor );
    config->writeEntry( "Decorative First Color", m_decorativeFirstColor );
    config->writeEntry( "Decorative Second Color", m_decorativeSecondColor );
    
    config->sync();
}

void ImageEffect_Border::renderingFinished()
{
    m_borderType->setEnabled(true);
    m_borderWidth->setEnabled(true);
    m_firstColorButton->setEnabled(true);
    m_secondColorButton->setEnabled(true);
}

void ImageEffect_Border::resetValues()
{
    m_borderType->blockSignals(true);
    m_borderWidth->blockSignals(true);
    m_firstColorButton->blockSignals(true);
    m_secondColorButton->blockSignals(true);
        
    m_borderType->setCurrentItem(Border::SolidBorder); 
    m_borderWidth->setValue(100);
    m_solidColor = QColor::QColor( 0, 0, 0 );

    m_borderType->blockSignals(false);
    m_borderWidth->blockSignals(false);
    m_firstColorButton->blockSignals(false);
    m_secondColorButton->blockSignals(false);
    slotBorderTypeChanged(Border::SolidBorder);
} 

void ImageEffect_Border::slotColorForegroundChanged(const QColor &color)
{
    switch (m_borderType->currentItem())
       {
       case Border::SolidBorder:
          m_solidColor = color;
          break;
       
       case Border::NiepceBorder:
          m_niepceBorderColor = color;
          break;

       case Border::BeveledBorder:
          m_bevelUpperLeftColor = color;
          break;
          
       case Border::PineBorder:
       case Border::WoodBorder: 
       case Border::PaperBorder: 
       case Border::ParqueBorder: 
       case Border::IceBorder:
       case Border::LeafBorder: 
       case Border::MarbleBorder:
       case Border::RainBorder:
       case Border::CratersBorder:
       case Border::DriedBorder:
       case Border::PinkBorder:
       case Border::StoneBorder:
       case Border::ChalkBorder:
       case Border::GraniteBorder:
       case Border::RockBorder:
       case Border::WallBorder:
          m_decorativeFirstColor = color;
          break;
       }
       
    slotEffect();       
}

void ImageEffect_Border::slotColorBackgroundChanged(const QColor &color)
{
    switch (m_borderType->currentItem())
       {
       case Border::SolidBorder:
          m_solidColor = color;
          break;
       
       case Border::NiepceBorder:
          m_niepceLineColor = color;
          break;

       case Border::BeveledBorder:
          m_bevelLowerRightColor = color;
          break;

       case Border::PineBorder:
       case Border::WoodBorder: 
       case Border::PaperBorder: 
       case Border::ParqueBorder: 
       case Border::IceBorder:
       case Border::LeafBorder: 
       case Border::MarbleBorder:
       case Border::RainBorder:
       case Border::CratersBorder:
       case Border::DriedBorder:
       case Border::PinkBorder:
       case Border::StoneBorder:
       case Border::ChalkBorder:
       case Border::GraniteBorder:
       case Border::RockBorder:
       case Border::WallBorder:
          m_decorativeSecondColor = color;
          break;          
       }
       
    slotEffect();       
}

void ImageEffect_Border::slotBorderTypeChanged(int borderType)
{
    m_labelForeground->setText(i18n("First:"));
    m_labelBackground->setText(i18n("Second:"));
    QWhatsThis::add( m_firstColorButton, i18n("<p>Set here the foreground color of the border."));
    QWhatsThis::add( m_secondColorButton, i18n("<p>Set here the Background color of the border."));
    m_firstColorButton->setEnabled(true);
    m_secondColorButton->setEnabled(true);
    m_labelForeground->setEnabled(true);
    m_labelBackground->setEnabled(true);
    m_borderWidth->setEnabled(true);
          
    switch (borderType)
       {
       case Border::SolidBorder:
          m_firstColorButton->setColor( m_solidColor );
          m_secondColorButton->setEnabled(false);
          m_labelBackground->setEnabled(false);
          break;
       
       case Border::NiepceBorder:
          QWhatsThis::add( m_firstColorButton, i18n("<p>Set here the color of the main border."));
          QWhatsThis::add( m_secondColorButton, i18n("<p>Set here the color of the line."));
          m_firstColorButton->setColor( m_niepceBorderColor );
          m_secondColorButton->setColor( m_niepceLineColor );
          break;

       case Border::BeveledBorder:
          QWhatsThis::add( m_firstColorButton, i18n("<p>Set here the color of the upper left area."));
          QWhatsThis::add( m_secondColorButton, i18n("<p>Set here the color of the lower right area."));
          m_firstColorButton->setColor( m_bevelUpperLeftColor );
          m_secondColorButton->setColor( m_bevelLowerRightColor );
          break;

       case Border::PineBorder:
       case Border::WoodBorder: 
       case Border::PaperBorder: 
       case Border::ParqueBorder: 
       case Border::IceBorder:
       case Border::LeafBorder: 
       case Border::MarbleBorder:
       case Border::RainBorder:
       case Border::CratersBorder:
       case Border::DriedBorder:
       case Border::PinkBorder:
       case Border::StoneBorder:
       case Border::ChalkBorder:
       case Border::GraniteBorder:
       case Border::RockBorder:
       case Border::WallBorder:
          QWhatsThis::add( m_firstColorButton, i18n("<p>Set here the color of the first line."));
          QWhatsThis::add( m_secondColorButton, i18n("<p>Set here the color of the second line."));
          m_firstColorButton->setColor( m_decorativeFirstColor );
          m_secondColorButton->setColor( m_decorativeSecondColor );
          break;
       }

    slotEffect();
}

void ImageEffect_Border::prepareEffect()
{
    m_borderType->setEnabled(false);
    m_borderWidth->setEnabled(false);
    m_firstColorButton->setEnabled(false);
    m_secondColorButton->setEnabled(false);

    Digikam::ImageIface* iface = m_imagePreviewWidget->imageIface();
    int orgWidth = iface->originalWidth();
    int orgHeight = iface->originalHeight();
    int w = iface->previewWidth();
    int h = iface->previewHeight();
    QImage orgImage(w, h, 32);
    uint *data = iface->getPreviewData();
    memcpy( orgImage.bits(), data, orgImage.numBytes() );

    int borderType  = m_borderType->currentItem();
    float ratio     = (float)w/(float)iface->originalWidth();
    int borderWidth = (int)((float)m_borderWidth->value()*ratio);        
    QString border = getBorderPath( m_borderType->currentItem() );
    
    m_threadedFilter = dynamic_cast<Digikam::ThreadedFilter *>(
                       new Border(&orgImage, this, orgWidth, orgHeight,
                                  border, borderType, borderWidth, 
                                  (int)(20.0*ratio), (int)(20.0*ratio), 3, 
                                  m_solidColor, m_niepceBorderColor,
                                  m_niepceLineColor, m_bevelUpperLeftColor,
                                  m_bevelLowerRightColor, m_decorativeFirstColor,
                                  m_decorativeSecondColor));
    delete [] data;
}

void ImageEffect_Border::prepareFinal()
{
    m_borderType->setEnabled(false);
    m_borderWidth->setEnabled(false);
    m_firstColorButton->setEnabled(false);
    m_secondColorButton->setEnabled(false);
    
    int borderType = m_borderType->currentItem();
    int borderWidth = m_borderWidth->value();  
    QString border = getBorderPath( m_borderType->currentItem() );
    
    Digikam::ImageIface iface(0, 0);
    int orgWidth = iface.originalWidth();
    int orgHeight = iface.originalHeight();
    QImage orgImage(orgWidth, orgHeight, 32);
    uint *data = iface.getOriginalData();
    memcpy( orgImage.bits(), data, orgImage.numBytes() );
    
    m_threadedFilter = dynamic_cast<Digikam::ThreadedFilter *>(
                       new Border(&orgImage, this, orgWidth, orgHeight,
                                  border, borderType, borderWidth, 15, 15, 10,
                                  m_solidColor, m_niepceBorderColor,
                                  m_niepceLineColor, m_bevelUpperLeftColor,
                                  m_bevelLowerRightColor, m_decorativeFirstColor,
                                  m_decorativeSecondColor));
    delete [] data;       
}

void ImageEffect_Border::putPreviewData(void)
{
    Digikam::ImageIface* iface = m_imagePreviewWidget->imageIface();

    int w = iface->previewWidth();
    int h = iface->previewHeight();
    QImage tmp = m_threadedFilter->getTargetImage();
    tmp = tmp.smoothScale(w, h, QImage::ScaleMin);
    QImage imDest( w, h, 32 );
    imDest.fill(m_imagePreviewWidget->colorGroup().background().rgb());
    bitBlt( &imDest, (w-tmp.width())/2, (h-tmp.height())/2, &tmp, 0, 0, tmp.width(), tmp.height());
    iface->putPreviewData((uint*)(imDest.smoothScale(w, h)).bits());
    
    m_imagePreviewWidget->updatePreview();    
}

void ImageEffect_Border::putFinalData(void)
{
    Digikam::ImageIface iface(0, 0);    

    QImage img = m_threadedFilter->getTargetImage();
    iface.putOriginalData(i18n("Add Border"), 
                         (uint*)img.bits(), img.width(), img.height());
}

QString ImageEffect_Border::getBorderPath(int border)
{
    QString pattern;
    
    switch (border)
       {
       case Border::PineBorder:
          pattern = "pine-pattern";
          break;
          
       case Border::WoodBorder: 
          pattern = "wood-pattern";
          break;
       
       case Border::PaperBorder: 
          pattern = "paper-pattern";
          break;
       
       case Border::ParqueBorder: 
          pattern = "parque-pattern";
          break;
       
       case Border::IceBorder:
          pattern = "ice-pattern";
          break;
       
       case Border::LeafBorder: 
          pattern = "leaf-pattern";
          break;

       case Border::MarbleBorder:
          pattern = "marble-pattern";
          break;
       
       case Border::RainBorder:
          pattern = "rain-pattern";
          break;
       
       case Border::CratersBorder:
          pattern = "craters-pattern";
          break;
       
       case Border::DriedBorder:
          pattern = "dried-pattern";
          break;
       
       case Border::PinkBorder:
          pattern = "pink-pattern";
          break;
       
       case Border::StoneBorder:
          pattern = "stone-pattern";
          break;
       
       case Border::ChalkBorder:
          pattern = "chalk-pattern";
          break;
       
       case Border::GraniteBorder:
          pattern = "granit-pattern";
          break;

       case Border::RockBorder:
          pattern = "rock-pattern";
          break;
       
       case Border::WallBorder:
          pattern = "wall-pattern";
          break;
       
       default:
          return(QString::null);
       }
    
    KGlobal::dirs()->addResourceType(pattern.ascii(), KGlobal::dirs()->kde_default("data") +
                                     "digikamimageplugins/data");
    return (KGlobal::dirs()->findResourceDir(pattern.ascii(), pattern + ".png") + pattern + ".png" );
}

}  // NameSpace DigikamBorderImagesPlugin

#include "imageeffect_border.moc"
