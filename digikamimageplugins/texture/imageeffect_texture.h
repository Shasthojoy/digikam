/* ============================================================
 * File  : imageeffect_texture.h
 * Author: Gilles Caulier <caulier dot gilles at free.fr>
 * Date  : 2005-03-10
 * Description : a digiKam image editor plugin for apply 
 *               texture on image.
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

#ifndef IMAGEEFFECT_TEXTURE_H
#define IMAGEEFFECT_TEXTURE_H

// Qt include.

#include <qimage.h>

// KDE include.

#include <kdialogbase.h>

class QPushButton;
class QTimer;
class QComboBox;

class KIntNumInput;

class Texture;

namespace Digikam
{
class ImagePreviewWidget;
}

namespace DigikamTextureImagesPlugin
{

class ImageEffect_Texture : public KDialogBase
{
    Q_OBJECT

public:

    ImageEffect_Texture(QWidget* parent);
    ~ImageEffect_Texture();

protected:

    void closeEvent(QCloseEvent *e);
    
private:

    enum TextureTypes 
    {
    PaperTexture=0,
    Paper2Texture,
    FabricTexture,
    BurlapTexture,
    BricksTexture,
    Bricks2Texture,
    CanvasTexture,
    MarbleTexture,
    Marble2Texture,
    BlueJeanTexture,
    CellWoodTexture,
    MetalWireTexture,
    ModernTexture,
    WallTexture,
    MossTexture,
    StoneTexture
    };

    enum RunningMode
    {
    NoneRendering=0,
    PreviewRendering,
    FinalRendering
    };
    
    int           m_currentRenderingMode;

    QWidget      *m_parent;
    
    QTimer       *m_timer;
    
    QPushButton  *m_helpButton;
    
    QComboBox    *m_textureType;

    KIntNumInput *m_blendGain;
    
    Texture      *m_textureFilter;
    
    Digikam::ImagePreviewWidget *m_imagePreviewWidget;
    
private:
    
    void abortPreview(void);
    void customEvent(QCustomEvent *event);
    QString makeTextureImage(int texture);
        
private slots:

    void slotHelp();
    void slotEffect();
    void slotOk();
    void slotCancel();
    void slotUser1();
    void slotTimer();   
};

}  // NameSpace DigikamTextureImagesPlugin

#endif /* IMAGEEFFECT_TEXTURE_H */
