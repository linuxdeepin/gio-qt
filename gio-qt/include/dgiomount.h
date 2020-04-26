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
#ifndef DGIOMOUNT_H
#define DGIOMOUNT_H

#include <QObject>
#include <QSharedData>

namespace Gio {
class Mount;
}

class DGioFile;
class DGioVolume;
class DGioMountPrivate;
class DGioMount : public QObject, public QSharedData
{
    Q_OBJECT
public:
    explicit DGioMount(Gio::Mount *gmmMountPtr, QObject *parent = nullptr);
    ~DGioMount();

    static DGioMount * createFromPath(QString path, QObject *parent = nullptr);

    QString name() const;
    QString uuid() const;
    QString mountClass() const;
    bool isShadowed() const;
    bool canUnmount() const;
    bool canEject() const;
    QString sortKey() const;
    QStringList themedIconNames() const;
    QStringList themedSymbolicIconNames() const;

    void unmount(bool forceUnmount = false);
    void eject(bool forceEject = false);

    QExplicitlySharedDataPointer<DGioFile> getRootFile();
    QExplicitlySharedDataPointer<DGioFile> getDefaultLocationFile();
    QExplicitlySharedDataPointer<DGioVolume> getVolume();

private:
    QScopedPointer<DGioMountPrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioMount)
};

#endif // DGIOMOUNT_H
