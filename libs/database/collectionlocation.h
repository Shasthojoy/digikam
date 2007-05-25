/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2007-04-09
 * Description : Collection location abstraction
 *
 * Copyright (C) 2007 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
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

#ifndef COLLECTIONLOCATION_H
#define COLLECTIONLOCATION_H

// Qt includes

#include <qstring.h>

// Local includes

#include "digikam_export.h"

namespace Digikam
{


class DIGIKAM_EXPORT CollectionLocation
{
public:

    enum Status
    {
        LocationAvailable,
        LocationHidden,
        LocationInavailable
    };

    Status status() const;
    QString albumRoot() const;

protected:

    Status m_status;
    QString m_albumRoot;

};

}

#endif
