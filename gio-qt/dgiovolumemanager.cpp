#include "dgiomount.h"
#include "dgiovolume.h"
#include "dgiovolumemanager.h"

#include <glibmm/refptr.h>

#include <giomm/init.h>
#include <giomm/volumemonitor.h>

using namespace Gio;

class DGioVolumeManagerPrivate
{
    DGioVolumeManagerPrivate(DGioVolumeManager *qq);

private:
    Glib::RefPtr<VolumeMonitor> m_gmmVolumeMonitorPtr;

    DGioVolumeManager *q_ptr;

    void slot_mountAdded(const Glib::RefPtr< Mount >& gmmMount);
    void slot_mountRemoved(const Glib::RefPtr< Mount >& gmmMount);
    void slot_mountPreRemoved(const Glib::RefPtr< Mount >& gmmMount);
    void slot_mountChanged(const Glib::RefPtr< Mount >& gmmMount);

    Q_DECLARE_PUBLIC(DGioVolumeManager)
};

DGioVolumeManagerPrivate::DGioVolumeManagerPrivate(DGioVolumeManager *qq)
    : q_ptr(qq)
{
    // Do Gio's init or things like Gio::VolumeMonitor::get() won't working
    // Gio::init() will also call Glib::init() so we don't need to call it again.
    Gio::init();

    m_gmmVolumeMonitorPtr = VolumeMonitor::get();

    m_gmmVolumeMonitorPtr->signal_mount_added().connect(sigc::mem_fun(*this, &DGioVolumeManagerPrivate::slot_mountAdded));
    m_gmmVolumeMonitorPtr->signal_mount_removed().connect(sigc::mem_fun(*this, &DGioVolumeManagerPrivate::slot_mountRemoved));
    m_gmmVolumeMonitorPtr->signal_mount_pre_unmount().connect(sigc::mem_fun(*this, &DGioVolumeManagerPrivate::slot_mountPreRemoved));
    m_gmmVolumeMonitorPtr->signal_mount_changed().connect(sigc::mem_fun(*this, &DGioVolumeManagerPrivate::slot_mountChanged));
}

void DGioVolumeManagerPrivate::slot_mountAdded(const Glib::RefPtr<Mount> &gmmMount)
{
    Q_Q(DGioVolumeManager);

    Glib::RefPtr<Mount> copy(gmmMount);

    QExplicitlySharedDataPointer<DGioMount> mount(new DGioMount(copy.release()));

    Q_EMIT q->mountAdded(mount);
}

void DGioVolumeManagerPrivate::slot_mountRemoved(const Glib::RefPtr<Mount> &gmmMount)
{
    Q_Q(DGioVolumeManager);

    Glib::RefPtr<Mount> copy(gmmMount);

    QExplicitlySharedDataPointer<DGioMount> mount(new DGioMount(copy.release()));

    Q_EMIT q->mountRemoved(mount);
}

void DGioVolumeManagerPrivate::slot_mountPreRemoved(const Glib::RefPtr<Mount> &gmmMount)
{
    Q_Q(DGioVolumeManager);

    Glib::RefPtr<Mount> copy(gmmMount);

    QExplicitlySharedDataPointer<DGioMount> mount(new DGioMount(copy.release()));

    Q_EMIT q->mountPreRemoved(mount);
}

void DGioVolumeManagerPrivate::slot_mountChanged(const Glib::RefPtr<Mount> &gmmMount)
{
    Q_Q(DGioVolumeManager);

    Glib::RefPtr<Mount> copy(gmmMount);

    QExplicitlySharedDataPointer<DGioMount> mount(new DGioMount(copy.release()));

    Q_EMIT q->mountChanged(mount);
}


DGioVolumeManager::DGioVolumeManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new DGioVolumeManagerPrivate(this))
{

}

DGioVolumeManager::~DGioVolumeManager()
{

}

const QList<QExplicitlySharedDataPointer<DGioMount> > DGioVolumeManager::getMounts()
{
    // ensure GIO got initialized
    Gio::init();

    QList<QExplicitlySharedDataPointer<DGioMount> > mounts;

    Glib::RefPtr<VolumeMonitor> vm = Gio::VolumeMonitor::get();

    Glib::ListHandle<Glib::RefPtr<Mount> > mnt = vm->get_mounts();
    for (Glib::RefPtr<Mount> oneMnt : mnt) {

        QExplicitlySharedDataPointer<DGioMount> mntPtr(new DGioMount(oneMnt.release()));
        mounts.append(mntPtr);
    }

    return mounts;
}

const QList<QExplicitlySharedDataPointer<DGioVolume> > DGioVolumeManager::getVolumes()
{
    // ensure GIO got initialized
    Gio::init();

    QList<QExplicitlySharedDataPointer<DGioVolume> > volumes;

    Glib::RefPtr<VolumeMonitor> vm = Gio::VolumeMonitor::get();

    Glib::ListHandle<Glib::RefPtr<Volume> > vol = vm->get_volumes();
    for (Glib::RefPtr<Volume> oneVol : vol) {

        QExplicitlySharedDataPointer<DGioVolume> volPtr(new DGioVolume(oneVol.release()));
        volumes.append(volPtr);
    }

    return volumes;
}
