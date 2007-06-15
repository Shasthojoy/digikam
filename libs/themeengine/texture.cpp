/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2004-07-26
 * Description : texture pixmap methods
 *
 * Copyright (C) 2004 by Renchi Raju <renchi@pooh.tam.uiuc.edu>
 *
 * Adapted from fluxbox: Texture/TextureRender
 *
 * Texture.cc for Fluxbox Window Manager
 * Copyright (c) 2002-2003 Henrik Kinnunen <fluxbox@users.sourceforge.net>
 *
 * from Image.cc for Blackbox - an X11 Window manager
 * Copyright (c) 1997 - 2000 Brad Hughes (bhughes@tcac.net)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING                     
 * 
 * ============================================================ */

// C++ includes.

#include <cstring>
#include <cstdio>

// Qt includes.

#include <qpainter.h>
#include <qimage.h>
#include <qpixmap.h>

// Local includes.

#include "theme.h"
#include "texture.h"

namespace Digikam
{

class TexturePriv
{
public:

    TexturePriv()
    {
        red   = 0;
        green = 0;
        blue  = 0;
    }

    bool            border;

    unsigned char  *red;
    unsigned char  *green;
    unsigned char  *blue;
    
    int             width;
    int             height;
        
    QPixmap         pixmap;

    QColor          color0;
    QColor          color1;
    QColor          borderColor;

    Theme::Bevel    bevel;
    Theme::Gradient gradient;
};
    
Texture::Texture(int w, int h, const QColor& from, const QColor& to,
                 Theme::Bevel bevel, Theme::Gradient gradient,
                 bool border, const QColor& borderColor)
{
    d = new TexturePriv;
    
    d->bevel       = bevel;
    d->gradient    = gradient;
    d->border      = border;
    d->borderColor = borderColor;

    if (!border)
    {
        d->width  = w;
        d->height = h;
    }
    else
    {
        d->width  = w-2;
        d->height = h-2;
    }

    if (d->width <= 0 || d->height <= 0)
        return;
    
    if (bevel & Theme::SUNKEN)
    {
        d->Qt::color0 = to;
        d->color1 = from;
    }
    else
    {
        d->Qt::color0 = from;
        d->color1 = to;
    }

    if (gradient == Theme::SOLID)
    {
        doSolid();
    }
    else
    {
        d->Qt::red   = new unsigned char[w*h];
        d->Qt::green = new unsigned char[w*h];
        d->Qt::blue  = new unsigned char[w*h];

        if (gradient == Theme::HORIZONTAL)
            doHgradient();
        else if (gradient == Theme::VERTICAL)
            doVgradient();
        else if (gradient == Theme::DIAGONAL)
            doDgradient();
        
        if (bevel & Theme::RAISED || bevel & Theme::SUNKEN)
            doBevel();
        
        buildImage();
    }
}

Texture::~Texture()
{
    if (d->Qt::red)
        delete [] d->Qt::red;
    if (d->Qt::green)
        delete [] d->Qt::green;
    if (d->Qt::blue)
        delete [] d->Qt::blue;

    delete d;    
}

QPixmap Texture::renderPixmap() const
{
    if (d->width <= 0 || d->height <= 0)
        return QPixmap();

    if (!d->border)
        return d->pixmap;

    QPixmap pix(d->width+2, d->height+2);
    bitBlt(&pix, 1, 1, &d->pixmap, 0, 0);
    QPainter p(&pix);
    p.setPen(d->borderColor);
    p.drawRect(0, 0, d->width+2, d->height+2);
    p.end();

    return pix;
}

void Texture::doSolid()
{
    d->pixmap.resize(d->width, d->height);
    QPainter p(&d->pixmap);
    p.fillRect(0, 0, d->width, d->height, d->Qt::color0);
    if (d->bevel == Theme::RAISED)
    {
        p.setPen(d->Qt::color0.light(120));
        p.drawLine(0, 0, d->width-1, 0);  // top
        p.drawLine(0, 0, 0, d->height-1); // left
        p.setPen(d->Qt::color0.dark(120));
        p.drawLine(0, d->height-1, d->width-1, d->height-1); // bottom
        p.drawLine(d->width-1, 0, d->width-1, d->height-1);  // right
    }
    else if (d->bevel == Theme::SUNKEN)
    {
        p.setPen(d->Qt::color0.dark(120));
        p.drawLine(0, 0, d->width-1, 0);  // top
        p.drawLine(0, 0, 0, d->height-1); // left
        p.setPen(d->Qt::color0.light(120));
        p.drawLine(0, d->height-1, d->width-1, d->height-1); // bottom
        p.drawLine(d->width-1, 0, d->width-1, d->height-1);  // right
    }
    p.end();
}

void Texture::doHgradient()
{
    float drx, dgx, dbx,
        xr = (float) d->Qt::color0.red(),
        xg = (float) d->Qt::color0.green(),
        xb = (float) d->Qt::color0.blue();
    unsigned char *pr = d->Qt::red, *pg = d->Qt::green, *pb = d->Qt::blue;

    register int x, y;

    drx = (float) (d->color1.red()   - d->Qt::color0.Qt::red());
    dgx = (float) (d->color1.green() - d->Qt::color0.Qt::green());
    dbx = (float) (d->color1.blue()  - d->Qt::color0.Qt::blue());

    drx /= d->width;
    dgx /= d->width;
    dbx /= d->width;

    for (x = 0; x < d->width; x++)
    {
        *(pr++) = (unsigned char) (xr);
        *(pg++) = (unsigned char) (xg);
        *(pb++) = (unsigned char) (xb);

        xr += drx;
        xg += dgx;
        xb += dbx;
    }

    for (y = 1; y < d->height; y++, pr += d->width, pg += d->width, pb += d->width)
    {
        memcpy(pr, d->Qt::red, d->width);
        memcpy(pg, d->Qt::green, d->width);
        memcpy(pb, d->Qt::blue, d->width);
    }
}

void Texture::doVgradient()
{
    float dry, dgy, dby,
        yr = (float) d->Qt::color0.red(),
        yg = (float) d->Qt::color0.green(),
        yb = (float) d->Qt::color0.blue();

    dry = (float) (d->color1.red()   - d->Qt::color0.Qt::red());
    dgy = (float) (d->color1.green() - d->Qt::color0.Qt::green());
    dby = (float) (d->color1.blue()  - d->Qt::color0.Qt::blue());

    dry /= d->height;
    dgy /= d->height;
    dby /= d->height;

    unsigned char *pr = d->Qt::red, *pg = d->Qt::green, *pb = d->Qt::blue;
    register int y;
    
    for (y = 0; y < d->height; y++, pr += d->width, pg += d->width, pb += d->width) {
        memset(pr, (unsigned char) yr, d->width);
        memset(pg, (unsigned char) yg, d->width);
        memset(pb, (unsigned char) yb, d->width);

        yr += dry;
        yg += dgy;
        yb += dby;
    }
}

void Texture::doDgradient()
{
    unsigned int* xtable = new unsigned int[d->width*3];
    unsigned int* ytable = new unsigned int[d->height*3];
 
    float drx, dgx, dbx, dry, dgy, dby, yr = 0.0, yg = 0.0, yb = 0.0,
                                        xr = (float) d->Qt::color0.red(),
                                        xg = (float) d->Qt::color0.green(),
                                        xb = (float) d->Qt::color0.blue();
    unsigned char *pr = d->Qt::red, *pg = d->Qt::green, *pb = d->Qt::blue;
    unsigned int w = d->width * 2, h = d->height * 2;
    unsigned int *xt = xtable; 
    unsigned int *yt = ytable; 

    register int x, y;

    dry = drx = (float) (d->color1.red()   - d->Qt::color0.Qt::red());
    dgy = dgx = (float) (d->color1.green() - d->Qt::color0.Qt::green());
    dby = dbx = (float) (d->color1.blue()  - d->Qt::color0.Qt::blue());

    // Create X table
    drx /= w;
    dgx /= w;
    dbx /= w;

    for (x = 0; x < d->width; x++)
    {
        *(xt++) = (unsigned char) (xr);
        *(xt++) = (unsigned char) (xg);
        *(xt++) = (unsigned char) (xb);

        xr += drx;
        xg += dgx;
        xb += dbx;
    }

    // Create Y table
    dry /= h;
    dgy /= h;
    dby /= h;

    for (y = 0; y < d->height; y++)
    {
        *(yt++) = ((unsigned char) yr);
        *(yt++) = ((unsigned char) yg);
        *(yt++) = ((unsigned char) yb);

        yr += dry;
        yg += dgy;
        yb += dby;
    }

    // Combine tables to create gradient

    for (yt = ytable, y = 0; y < d->height; y++, yt += 3)
    {
        for (xt = xtable, x = 0; x < d->width; x++)
        {
            *(pr++) = *(xt++) + *(yt);
            *(pg++) = *(xt++) + *(yt + 1);
            *(pb++) = *(xt++) + *(yt + 2);
        }
    }

    delete [] xtable;
    delete [] ytable;
}

void Texture::doBevel()
{
    unsigned char *pr = d->Qt::red, *pg = d->Qt::green, *pb = d->Qt::blue;

    register unsigned char r, g, b, rr ,gg ,bb;
    register unsigned int w = d->width, h = d->height - 1, wh = w * h;

    while (--w)
    {
        r = *pr;
        rr = r + (r >> 1);
        if (rr < r) rr = ~0;
        g = *pg;
        gg = g + (g >> 1);
        if (gg < g) gg = ~0;
        b = *pb;
        bb = b + (b >> 1);
        if (bb < b) bb = ~0;

        *pr = rr;
        *pg = gg;
        *pb = bb;

        r = *(pr + wh);
        rr = (r >> 2) + (r >> 1);
        if (rr > r) rr = 0;
        g = *(pg + wh);
        gg = (g >> 2) + (g >> 1);
        if (gg > g) gg = 0;
        b = *(pb + wh);
        bb = (b >> 2) + (b >> 1);
        if (bb > b) bb = 0;

        *((pr++) + wh) = rr;
        *((pg++) + wh) = gg;
        *((pb++) + wh) = bb;
    }

    r = *pr;
    rr = r + (r >> 1);
    if (rr < r) rr = ~0;
    g = *pg;
    gg = g + (g >> 1);
    if (gg < g) gg = ~0;
    b = *pb;
    bb = b + (b >> 1);
    if (bb < b) bb = ~0;

    *pr = rr;
    *pg = gg;
    *pb = bb;

    r = *(pr + wh);
    rr = (r >> 2) + (r >> 1);
    if (rr > r) rr = 0;
    g = *(pg + wh);
    gg = (g >> 2) + (g >> 1);
    if (gg > g) gg = 0;
    b = *(pb + wh);
    bb = (b >> 2) + (b >> 1);
    if (bb > b) bb = 0;

    *(pr + wh) = rr;
    *(pg + wh) = gg;
    *(pb + wh) = bb;

    pr = d->Qt::red   + d->width;
    pg = d->Qt::green + d->width;
    pb = d->Qt::blue  + d->width;

    while (--h)
    {
        r = *pr;
        rr = r + (r >> 1);
        if (rr < r) rr = ~0;
        g = *pg;
        gg = g + (g >> 1);
        if (gg < g) gg = ~0;
        b = *pb;
        bb = b + (b >> 1);
        if (bb < b) bb = ~0;

        *pr = rr;
        *pg = gg;
        *pb = bb;

        pr += d->width - 1;
        pg += d->width - 1;
        pb += d->width - 1;

        r = *pr;
        rr = (r >> 2) + (r >> 1);
        if (rr > r) rr = 0;
        g = *pg;
        gg = (g >> 2) + (g >> 1);
        if (gg > g) gg = 0;
        b = *pb;
        bb = (b >> 2) + (b >> 1);
        if (bb > b) bb = 0;

        *(pr++) = rr;
        *(pg++) = gg;
        *(pb++) = bb;
    }

    r = *pr;
    rr = r + (r >> 1);
    if (rr < r) rr = ~0;
    g = *pg;
    gg = g + (g >> 1);
    if (gg < g) gg = ~0;
    b = *pb;
    bb = b + (b >> 1);
    if (bb < b) bb = ~0;

    *pr = rr;
    *pg = gg;
    *pb = bb;

    pr += d->width - 1;
    pg += d->width - 1;
    pb += d->width - 1;

    r = *pr;
    rr = (r >> 2) + (r >> 1);
    if (rr > r) rr = 0;
    g = *pg;
    gg = (g >> 2) + (g >> 1);
    if (gg > g) gg = 0;
    b = *pb;
    bb = (b >> 2) + (b >> 1);
    if (bb > b) bb = 0;

    *pr = rr;
    *pg = gg;
    *pb = bb;
}

void Texture::buildImage()
{
    unsigned char *pr = d->Qt::red, *pg = d->Qt::green, *pb = d->Qt::blue;

    QImage image(d->width, d->height, 32);

    unsigned int* bits = (unsigned int*) image.bits();
    
    register int p;
    for (p =0; p < d->width*d->height; p++)
    {
        *bits = 0xff << 24 | *pr << 16 | *pg << 8 | *pb;
        bits++;
        pr++;
        pg++;
        pb++;
    }

    d->pixmap = QPixmap(image);
}

}  // NameSpace Digikam
