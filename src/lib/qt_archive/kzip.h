/* This file is part of the KDE libraries
   Copyright (C) 2002 Holger Schroeder <holger-kde@holgis.net>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#ifndef KZIP_H
#define KZIP_H

#include <karchive.h>

#include "kzipfileentry.h" // for source compat

class KZipFileEntry;
/**
 *   A class for reading / writing zip archives.
 *
 *   You can use it in QIODevice::ReadOnly or in QIODevice::WriteOnly mode, and it
 *   behaves just as expected.
 *   It can also be used in QIODevice::ReadWrite mode, in this case one can
 *   append files to an existing zip archive. When you append new files, which
 *   are not yet in the zip, it works as expected, i.e. the files are appended at the end.
 *   When you append a file, which is already in the file, the reference to the
 *   old file is dropped and the new one is added to the zip - but the
 *   old data from the file itself is not deleted, it is still in the
 *   zipfile. So when you want to have a small and garbage-free zipfile,
 *   just read the contents of the appended zip file and write it to a new one
 *   in QIODevice::WriteOnly mode. This is especially important when you don't want
 *   to leak information of how intermediate versions of files in the zip
 *   were looking.
 *
 *   For more information on the zip fileformat go to
 *   http://www.pkware.com/products/enterprise/white_papers/appnote.html
 * @author Holger Schroeder <holger-kde@holgis.net>
 */
class KARCHIVE_EXPORT KZip : public KArchive
{
public:
    /**
     * Creates an instance that operates on the given filename.
     * using the compression filter associated to given mimetype.
     *
     * @param filename is a local path (e.g. "/home/holger/myfile.zip")
     */
    KZip(const QString &filename);

    /**
     * Creates an instance that operates on the given device.
     * The device can be compressed (KFilterDev) or not (QFile, etc.).
     * @warning Do not assume that giving a QFile here will decompress the file,
     * in case it's compressed!
     * @param dev the device to access
     */
    KZip(QIODevice *dev);

    /**
     * If the zip file is still opened, then it will be
     * closed automatically by the destructor.
     */
    virtual ~KZip();

    /**
     * Describes the contents of the "extra field" for a given file in the Zip archive.
     */
    enum ExtraField { NoExtraField = 0,      ///< No extra field
                      ModificationTime = 1,  ///< Modification time ("extended timestamp" header)
                      DefaultExtraField = 1
                    };

    /**
     * Call this before writeFile or prepareWriting, to define what the next
     * file to be written should have in its extra field.
     * @param ef the type of "extra field"
     * @see extraField()
     */
    void setExtraField(ExtraField ef);

    /**
     * The current type of "extra field" that will be used for new files.
     * @return the current type of "extra field"
     * @see setExtraField()
     */
    ExtraField extraField() const;

    /**
     * Describes the compression type for a given file in the Zip archive.
     */
    enum Compression { NoCompression = 0,     ///< Uncompressed.
                       DeflateCompression = 1 ///< Deflate compression method.
                     };

    /**
     * Call this before writeFile or prepareWriting, to define whether the next
     * files to be written should be compressed or not.
     * @param c the new compression mode
     * @see compression()
     */
    void setCompression(Compression c);

    /**
     * The current compression mode that will be used for new files.
     * @return the current compression mode
     * @see setCompression()
     */
    Compression compression() const;

    /**
     * Write data to a file that has been created using prepareWriting().
     * @param data a pointer to the data
     * @param size the size of the chunk
     * @return true if successful, false otherwise
     */
    bool writeData(const char *data, qint64 size) ;;

protected:
    /// Reimplemented from KArchive
    bool doWriteSymLink(const QString &name, const QString &target,
                        const QString &user, const QString &group,
                        mode_t perm, const QDateTime &atime, const QDateTime &mtime, const QDateTime &ctime) ;;
    /// Reimplemented from KArchive
    bool doPrepareWriting(const QString &name, const QString &user,
                          const QString &group, qint64 size, mode_t perm,
                          const QDateTime &atime, const QDateTime &mtime, const QDateTime &creationTime) ;;

    /**
     * Write data to a file that has been created using prepareWriting().
     * @param size the size of the file
     * @return true if successful, false otherwise
     */
    bool doFinishWriting(qint64 size) ;;

    /**
     * Opens the archive for reading.
     * Parses the directory listing of the archive
     * and creates the KArchiveDirectory/KArchiveFile entries.
     * @param mode the mode of the file
     */
    bool openArchive(QIODevice::OpenMode mode) ;;

    /// Closes the archive
    bool closeArchive() ;;

    /// Reimplemented from KArchive
    bool doWriteDir(const QString &name, const QString &user, const QString &group, mode_t perm,
                    const QDateTime &atime, const QDateTime &mtime, const QDateTime &ctime) ;;

protected:
    void virtual_hook(int id, void *data) ;;

private:
    class KZipPrivate;
    KZipPrivate *const d;
};

#endif