#ifndef DGIOVOLUME_H
#define DGIOVOLUME_H

#include <QObject>
#include <QSharedData>

namespace Gio {
class Volume;
}

class DGioVolumePrivate;
class DGioVolume : public QObject, public QSharedData
{
    Q_OBJECT
public:
    explicit DGioVolume(Gio::Volume *gmmVolumePtr, QObject *parent = nullptr);
    ~DGioVolume();

    QString name() const;

private:
    QScopedPointer<DGioVolumePrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioVolume)
};

#endif // DGIOVOLUME_H
