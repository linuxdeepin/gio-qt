#include "dgiovolume.h"

#include <glibmm/refptr.h>
#include <giomm/volume.h>

#include <QDebug>

using namespace Gio;

class DGioVolumePrivate
{
public:
    DGioVolumePrivate(DGioVolume *qq, Volume *gmmVolumePtr);

    Glib::RefPtr<Mount> getGmmVolumeInstance() const;

    QString name() const;

private:
    Glib::RefPtr<Volume> m_gmmVolumePtr;

    DGioVolume *q_ptr;

    Q_DECLARE_PUBLIC(DGioVolume)
};

DGioVolumePrivate::DGioVolumePrivate(DGioVolume *qq, Volume *gmmVolumePtr)
    : m_gmmVolumePtr(gmmVolumePtr)
    , q_ptr(qq)
{
//    m_gvolumePtr = Glib::wrap(gvolumePtr);
}

QString DGioVolumePrivate::name() const
{
    return QString::fromStdString(m_gmmVolumePtr->get_name());
}

// -------------------------------------------------------------

DGioVolume::DGioVolume(Volume* gmmVolumePtr, QObject *parent)
    : QObject(parent)
    , d_ptr(new DGioVolumePrivate(this, gmmVolumePtr))
{
    // gvolumePtr must be vaild;
    Q_CHECK_PTR(gmmVolumePtr);
}

DGioVolume::~DGioVolume()
{

}

QString DGioVolume::name() const
{
    Q_D(const DGioVolume);

    return d->name();
}
