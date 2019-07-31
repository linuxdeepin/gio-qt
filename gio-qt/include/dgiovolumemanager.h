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

private:
    QScopedPointer<DGioVolumeManagerPrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioVolumeManager)
};

#endif // DGIOVOLUMEMANAGER_H
