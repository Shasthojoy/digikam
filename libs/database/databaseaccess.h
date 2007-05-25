/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2007-03-18
 * Description : Database access wrapper.
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

#ifndef DATABASEACCESS_H
#define DATABASEACCESS_H

#include "digikam_export.h"
#include "databaseparameters.h"

namespace Digikam
{

class DatabaseBackend;
class AlbumDB;
class ImageInfoCache;
class DatabaseAttributesWatch;
class DatabaseAccessStaticPriv;

class DIGIKAM_EXPORT DatabaseAccess
{
public:

    /** The DatabaseAccess provides access to the database:
      * Create an instance of this class on the stack to retrieve a pointer to the database.
      * While you hold an instance of DatabaseAccess, the database access is locked for other threads,
      * but _not_ for other processes. This is due to the fact that while databases allow
      * concurrent access (of course), their client libs may not be thread-safe.
      *
      * When initializing your application, you need to call two methods:
      * - in a not-yet-multithreaded context, you need to call setParameters
      * - to make sure that the database is available and the schema
      *   is properly initialized, call checkReadyForUse()
      */

    /**
      * Create a DatabaseAccess object for the default database.
      * Note that when initializing your app, setParameters need to be called
      * (in a not-yet-multithreaded context) for this to work.
      */
    DatabaseAccess();
    ~DatabaseAccess();

    /**
      * Retrieve a pointer to the album database
      */
    AlbumDB *db() const;

    /**
      * Retrieve a pointer to the database backend
      */
    DatabaseBackend *backend() const;

    /**
      * Return the default parameters
      */
    static DatabaseParameters parameters();

    /**
      * Set the default parameters.
      * Call this function at least once in the starting phase of your application,
      * when no other threads will yet access the database, to initialize DatabaseAcccess.
      * After this initial call, it is thread-safe to call this function again.
      * In a subsequent call, if the parameters are identical, nothing is done.
      * If the parameters change, the current database will be closed.
      * When parameters have been set or changed, the new one will be opened on-demand,
      * i.e. when the first DatabaseAccess object is constructed.
      */
    static void setParameters(const DatabaseParameters &parameters);

    /**
      * Convenience method to initialize a database when new parameters have been set:
      * Make sure that the database is open, that the schema has properly been initialized,
      * and returns true on success.
      * If the parameters were not changed, this method has no effect.
      * @returns if the database is ready for use
      */
    static bool checkReadyForUse();

    /**
      * Clean up the database access.
      * When this function has been called, the access can be restored by calling setParameters.
      * Construction a database access object otherwise after calling this method will crash.
      */
    static void cleanUpDatabase();

    /**
      * This method is a temporary workaround until the album root is contained in the db.
      * Returns the global album root, including the trailing slash.
      */
    static QString albumRoot();

    /**
      * Return the ImageInfoCache. This object is not for public use outside libs/database/
      */
    ImageInfoCache *imageInfoCache() const;

    /**
      * Return the DatabaseAttributesWatch. This object is not for public use outside libs/database/
      */
    static DatabaseAttributesWatch *attributesWatch();

private:

    static DatabaseAccessStaticPriv *d;
};

}

#endif

