#include "dgiomount.h"
#include "dgiovolumemanager.h"

#include <glibmm.h>
#include <giomm.h>

#include <glibmm/refptr.h>
#include <giomm/volumemonitor.h>

using namespace Gio;

class DGioVolumeManagerPrivate
{
    DGioVolumeManagerPrivate(DGioVolumeManager *qq);

private:
    DGioVolumeManager *q_ptr;

    Q_DECLARE_PUBLIC(DGioVolumeManager)
};

DGioVolumeManagerPrivate::DGioVolumeManagerPrivate(DGioVolumeManager *qq)
    : q_ptr(qq)
{

}


DGioVolumeManager::DGioVolumeManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DGioVolumeManagerPrivate(this))
{
    // Do Gio's init or things like Gio::VolumeMonitor::get() won't working
    // can we init it multiple times?
    Glib::init();
    Gio::init();
}

DGioVolumeManager::~DGioVolumeManager()
{
    //
}

const QList<QExplicitlySharedDataPointer<DGioMount> > DGioVolumeManager::getMounts()
{
    QList<QExplicitlySharedDataPointer<DGioMount> > mounts;

    Glib::RefPtr<VolumeMonitor> vm = Gio::VolumeMonitor::get();

    Glib::ListHandle<Glib::RefPtr<Mount>> mnt = vm->get_mounts();
    for (Glib::RefPtr<Mount> oneMnt : mnt) {

        QExplicitlySharedDataPointer<DGioMount> mntPtr(new DGioMount(oneMnt.release()));
        mounts.append(mntPtr);
    }

    return mounts;
}
