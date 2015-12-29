/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2009-28-04
 * Description : first run assistant dialog
 *
 * Copyright (C) 2009-2016 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#include "assistantdlg.h"

// Qt includes

#include <QPushButton>

// KDE includes

#include <klocalizedstring.h>

// Local incudes

#include "dxmlguiwindow.h"
#include "welcomepage.h"
#include "collectionpage.h"
#include "databasepage.h"
#include "rawpage.h"
#include "metadatapage.h"
#include "previewpage.h"
#include "openfilepage.h"
#include "tooltipspage.h"
#include "startscanpage.h"

namespace Digikam
{

class AssistantDlg::Private
{
public:

    Private() :
        welcomePage(0),
        collectionPage(0),
        databasePage(0),
        rawPage(0),
        metadataPage(0),
        previewPage(0),
        openFilePage(0),
        tooltipsPage(0),
        startScanPage(0)
    {
    }

    WelcomePage*    welcomePage;
    CollectionPage* collectionPage;
    DatabasePage*   databasePage;
    RawPage*        rawPage;
    MetadataPage*   metadataPage;
    PreviewPage*    previewPage;
    OpenFilePage*   openFilePage;
    TooltipsPage*   tooltipsPage;
    StartScanPage*  startScanPage;
};

AssistantDlg::AssistantDlg(QWidget* const parent)
    : QWizard(parent),
      d(new Private)
{
    setWizardStyle(QWizard::ClassicStyle);
    setButtonLayout(QList<QWizard::WizardButton>() << QWizard::HelpButton << QWizard::BackButton << QWizard::CancelButton
                                                   << QWizard::NextButton << QWizard::FinishButton);

    d->welcomePage    = new WelcomePage(this);    // First assistant page
    d->collectionPage = new CollectionPage(this);
    d->databasePage   = new DatabasePage(this);
    d->rawPage        = new RawPage(this);
    d->metadataPage   = new MetadataPage(this);
    d->previewPage    = new PreviewPage(this);
    d->openFilePage   = new OpenFilePage(this);
    d->tooltipsPage   = new TooltipsPage(this);

    // NOTE: Added here new assistant pages...

    d->startScanPage  = new StartScanPage(this);  // Last assistant page

    resize(600, 600);
    
    connect(button(QWizard::FinishButton), SIGNAL(clicked()),
            this, SLOT(slotFinishPressed()));

    connect(this, SIGNAL(helpRequested()),
            this, SLOT(slotHelp()));
}

AssistantDlg::~AssistantDlg()
{
    delete d;
}

void AssistantDlg::slotHelp()
{
    DXmlGuiWindow::openHandbook(QLatin1String("firstrundialog.anchor"), QLatin1String("digikam"));
}

QString AssistantDlg::firstAlbumPath() const
{
    return d->collectionPage->firstAlbumPath();
}

DbEngineParameters AssistantDlg::getDbEngineParameters() const
{
    return d->databasePage->getDbEngineParameters();
}

bool AssistantDlg::validateCurrentPage()
{
    if (currentPage() == d->collectionPage)
    {
        if (!d->collectionPage->checkSettings())
        {
            return false;
        }
        else
        {
            d->databasePage->setDatabasePath(firstAlbumPath());
        }
    }

    
    if (currentPage() == d->databasePage)
    {
        if (!d->databasePage->checkSettings())
        {
            return false;
        }
    }

    return true;
}

void AssistantDlg::slotFinishPressed()
{
    // Save settings to rc files.
    d->collectionPage->saveSettings();
    d->databasePage->saveSettings();
    d->rawPage->saveSettings();
    d->metadataPage->saveSettings();
    d->previewPage->saveSettings();
    d->openFilePage->saveSettings();
    d->tooltipsPage->saveSettings();
}

}   // namespace Digikam
