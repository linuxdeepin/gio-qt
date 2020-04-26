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
#ifndef DGIOFILEINFO_H
#define DGIOFILEINFO_H

#include <QObject>
#include <QSharedData>

enum DGioFileType {
    FILE_TYPE_NOT_KNOWN,
    FILE_TYPE_REGULAR,
    FILE_TYPE_DIRECTORY,
    FILE_TYPE_SYMBOLIC_LINK,
    FILE_TYPE_SPECIAL,
    FILE_TYPE_SHORTCUT,
    FILE_TYPE_MOUNTABLE
};
Q_ENUMS(DGioFileType);

namespace Gio {
class FileInfo;
}

class DGioFileInfoPrivate;
class DGioFileInfo : public QObject, public QSharedData
{
    Q_OBJECT
public:
    explicit DGioFileInfo(Gio::FileInfo *gmmFileInfoInfoPtr, QObject *parent = nullptr);
    ~DGioFileInfo();

    // file info
    QString displayName() const;
    DGioFileType fileType() const;
    quint64 fileSize() const;
    QString contentType() const;
    QString iconString() const;
    QStringList themedIconNames() const;

    // filesystem info.
    bool fsReadOnly() const;
    quint64 fsTotalBytes() const;
    quint64 fsUsedBytes() const;
    quint64 fsFreeBytes() const;
    QString fsType() const;

private:
    QScopedPointer<DGioFileInfoPrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioFileInfo)
};

#endif // DGIOFILEINFO_H
