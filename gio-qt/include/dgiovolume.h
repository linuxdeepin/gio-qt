/*
 * Copyright (C) 2019 Deepin Technology Co., Ltd.
 *
 * Author:     Gary Wang <wzc782970009@gmail.com>
 *
 * Maintainer: Gary Wang <wangzichong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DGIOVOLUME_H
#define DGIOVOLUME_H

#include <QObject>
#include <QSharedData>

namespace Gio {
class Volume;
}

class DGioMount;
class DGioVolumePrivate;
class DGioVolume : public QObject, public QSharedData
{
    Q_OBJECT
public:
    explicit DGioVolume(Gio::Volume *gmmVolumePtr, QObject *parent = nullptr);
    ~DGioVolume();

    QString name() const;

    QExplicitlySharedDataPointer<DGioMount> getMount();

private:
    QScopedPointer<DGioVolumePrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioVolume)
};

#endif // DGIOVOLUME_H
