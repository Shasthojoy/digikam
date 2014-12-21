/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2009-28-04
 * Description : first run assistant dialog
 *
 * Copyright (C) 2009-2014 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#include "startscanpage.h"

// Qt includes

#include <QLabel>

// KDE includes

#include <kvbox.h>
#include <klocalizedstring.h>
#include <kstandarddirs.h>
#include <kiconloader.h>

namespace Digikam
{

StartScanPage::StartScanPage(KAssistantDialog* const dlg)
    : AssistantDlgPage(dlg, i18n("Scan Your Collection"))
{
    RVBox* const vbox  = new RVBox(this);
    QLabel* const text = new QLabel(vbox);
    text->setWordWrap(true);
    text->setOpenExternalLinks(true);
    text->setText(i18n("<qt>"
                       "<p>Congratulations. Your minimal setup is done.</p>"
                       "<p>Remember, you can customize more settings using the digiKam configuration panel. "
                       "To learn more about the digiKam world, we recommend reading the <b>digiKam handbook</b> "
                       "using the <b>Help/Handbook</b> menu entry (you need to install the separate digiKam documentation package.) "
                       "You can also read the manual online from the "
                       "<a href='http://www.digikam.org/docs'>digikam.org website</a>.</p>"
                       "<p>Press <b>Finish</b> to close this assistant. digiKam will scan your "
                       "collection to register all albums in the database. Items including in "
                       "albums are collected after startup stage in background.</p>"
                       "<p><i>Note:</i> depending of your collection size, this operation can take a while. "
                       "If you cancel the scanning operation, it will start again at next digiKam session.</p>"
                       "<p>When scanning has completed, at next start-up, digiKam will only check your collection "
                       "to identify new albums - which is much faster. You can force digiKam to scan for new items "
                       "manually using the <b>Tools->Maintenance->Scan for new items</b> menu entry.</p>"
                       "</qt>"));

    setPageWidget(vbox);
    setLeftBottomPix(KIconLoader::global()->loadIcon("system-search", KIconLoader::NoGroup, KIconLoader::SizeEnormous));
}

StartScanPage::~StartScanPage()
{
}

}   // namespace Digikam
