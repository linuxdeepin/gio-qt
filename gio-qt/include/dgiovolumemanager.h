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
#ifndef DGIOVOLUMEMANAGER_H
#define DGIOVOLUMEMANAGER_H

#include <QExplicitlySharedDataPointer>
#include <QObject>

class DGioMount;
class DGioVolume;
class DGioDrive;
class DGioVolumeManagerPrivate;
class DGioVolumeManager : public QObject
{
    Q_OBJECT
public:
    explicit DGioVolumeManager(QObject *parent = nullptr);
    ~DGioVolumeManager();

    static const QList<QExplicitlySharedDataPointer<DGioMount> > getMounts();
    static const QList<QExplicitlySharedDataPointer<DGioVolume> > getVolumes();
    static const QList<QExplicitlySharedDataPointer<DGioDrive> > getDrives();

Q_SIGNALS:
    void mountAdded(QExplicitlySharedDataPointer<DGioMount> mount);
    void mountRemoved(QExplicitlySharedDataPointer<DGioMount> mount);
    void mountPreRemoved(QExplicitlySharedDataPointer<DGioMount> mount);
    void mountChanged(QExplicitlySharedDataPointer<DGioMount> mount);
    void volumeAdded(QExplicitlySharedDataPointer<DGioVolume> volume);
    void volumeRemoved(QExplicitlySharedDataPointer<DGioVolume> volume);
    void volumeChanged(QExplicitlySharedDataPointer<DGioVolume> volume);
    void driveConnected(QExplicitlySharedDataPointer<DGioDrive> drive);
    void driveDisconnected(QExplicitlySharedDataPointer<DGioDrive> drive);
    void driveChanged(QExplicitlySharedDataPointer<DGioDrive> drive);

private:
    QScopedPointer<DGioVolumeManagerPrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioVolumeManager)
};

#endif // DGIOVOLUMEMANAGER_H
