#ifndef DGIOVOLUMEMANAGER_H
#define DGIOVOLUMEMANAGER_H

#include <QExplicitlySharedDataPointer>
#include <QObject>

namespace Gio {
class Mount;
}

class DGioMount;
class DGioVolume;
class DGioVolumeManagerPrivate;
class DGioVolumeManager : public QObject
{
    Q_OBJECT
public:
    explicit DGioVolumeManager(QObject *parent = nullptr);
    ~DGioVolumeManager();

    const QList<QExplicitlySharedDataPointer<DGioMount> > getMounts();

private:
    QScopedPointer<DGioVolumeManagerPrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioVolumeManager)
};

#endif // DGIOVOLUMEMANAGER_H
