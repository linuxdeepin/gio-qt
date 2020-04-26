/*
 * Copyright (C) 2019 Deepin Technology Co., Ltd.
 *
 * Author:     Gary Wang <wzc782970009@gmail.com>
 *
 * Maintainer: Gary Wang <wangzichong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DGIOFILE_H
#define DGIOFILE_H

#include <QObject>
#include <QSharedData>

namespace Gio {
class File;
}

enum DGioFileQueryInfoFlag
{
    FILE_QUERY_INFO_NONE = 0x0,
    FILE_QUERY_INFO_NOFOLLOW_SYMLINKS = (1 << 0)
};

Q_DECLARE_FLAGS(DGioFileQueryInfoFlags, DGioFileQueryInfoFlag)

class DGioFileInfo;
class DGioMount;
class DGioFileIterator;
class DGioMountOperation;
class DGioFilePrivate;
class DGioFile : public QObject, public QSharedData
{
    Q_OBJECT
public:
    explicit DGioFile(Gio::File *gmmFilePtr, QObject *parent = nullptr);
    ~DGioFile();

    static DGioFile * createFromPath(QString path, QObject *parent = nullptr);
    static DGioFile * createFromUri(QString uri, QObject *parent = nullptr);
    static DGioFile * createFromCmdArg(QString uri, QObject *parent = nullptr);

    QString basename() const;
    QString path() const;
    QString uri() const;

    QExplicitlySharedDataPointer<DGioFileInfo> createFileInfo(QString attr = "*", DGioFileQueryInfoFlags queryInfoFlags = FILE_QUERY_INFO_NONE, unsigned long timeout_msec = ULONG_MAX);
    QExplicitlySharedDataPointer<DGioFileInfo> createFileSystemInfo(QString attr = "*");
    QExplicitlySharedDataPointer<DGioFileIterator> createFileIterator(QString attr = "*", DGioFileQueryInfoFlags queryInfoFlags = FILE_QUERY_INFO_NONE);
    void createFileIteratorAsync(QString attr = "*", DGioFileQueryInfoFlags queryInfoFlags = FILE_QUERY_INFO_NONE);

    void mountEnclosingVolume(DGioMountOperation *dgioMountOperation);

    QExplicitlySharedDataPointer<DGioMount> findEnclosingMount();

Q_SIGNALS:
    void createFileIteratorReady(QExplicitlySharedDataPointer<DGioFileIterator> iter);
    void mountEnclosingVolumeReady(bool result, QString msg);

private:
    QScopedPointer<DGioFilePrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioFile)
};

#endif // DGIOFILE_H
