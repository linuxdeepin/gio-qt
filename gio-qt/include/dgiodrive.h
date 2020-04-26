/*
 * Copyright (C) 2019 Deepin Technology Co., Ltd.
 *
 * Author:     Mike Chen <kegechen@gmail.com>
 *
 * Maintainer: Mike Chen <chenke_cm@deepin.com>
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
#ifndef DGIODRIVE_H
#define DGIODRIVE_H

#include <QObject>
#include <QSharedData>

#define DGIODRIVE_IDENTIFIER_KIND_UNIX_DEVICE "unix-device"

namespace Gio {
class Drive;
}

class DGioDrivePrivate;
class DGioDrive : public QObject, public QSharedData {
    Q_OBJECT
public:
    explicit DGioDrive(Gio::Drive *gmmDrivePtr, QObject *parent = nullptr);
    ~DGioDrive();

    QString name() const;
    QString identifier(const QString & kind = DGIODRIVE_IDENTIFIER_KIND_UNIX_DEVICE) const;
    bool hasVolumes() const;
    bool canStart() const;
    bool canStop() const;
    bool canEject() const;
    bool isMediaRemovable() const;
    bool isRemovable() const;

private:
    QScopedPointer<DGioDrivePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DGioDrive)
};


#endif // DGIODRIVE_H
