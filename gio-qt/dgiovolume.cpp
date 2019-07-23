#include "dgiomount.h"
#include "dgiovolume.h"

#include <glibmm/refptr.h>
#include <giomm/volume.h>

#include <QDebug>

using namespace Gio;

class DGioVolumePrivate
{
public:
    DGioVolumePrivate(DGioVolume *qq, Volume *gmmVolumePtr);

    Glib::RefPtr<Volume> getGmmVolumeInstance() const;

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

Glib::RefPtr<Volume> DGioVolumePrivate::getGmmVolumeInstance() const
{
    return m_gmmVolumePtr;
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

// Return value can be nullptr
QExplicitlySharedDataPointer<DGioMount> DGioVolume::getMount()
{
    Q_D(DGioVolume);

    Glib::RefPtr<Mount> mnt = d->getGmmVolumeInstance()->get_mount();
    QExplicitlySharedDataPointer<DGioMount> mntPtr(new DGioMount(mnt.release()));

    return mntPtr;
}
