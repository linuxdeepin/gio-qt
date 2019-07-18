#include "dgiomount.h"

#include <glibmm/refptr.h>
#include <giomm/file.h>

#include <QDebug>

using namespace Gio;

class DGioMountPrivate
{
public:
    DGioMountPrivate(DGioMount *qq, Mount *gmountPtr);

    Glib::RefPtr<Mount> getGMountInstance() const;

    QString name() const;
    QString uuid() const;
    bool canUnmount() const;
    bool canEject() const;

private:
    Glib::RefPtr<Mount> m_gmountPtr;

    DGioMount *q_ptr;

    Q_DECLARE_PUBLIC(DGioMount)
};

DGioMountPrivate::DGioMountPrivate(DGioMount *qq, Mount *gmountPtr)
    : m_gmountPtr(gmountPtr)
    , q_ptr(qq)
{

}

Glib::RefPtr<Mount> DGioMountPrivate::getGMountInstance() const
{
    return m_gmountPtr;
}

QString DGioMountPrivate::name() const
{
    return QString::fromStdString(m_gmountPtr->get_name());
}

QString DGioMountPrivate::uuid() const
{
    return QString::fromStdString(m_gmountPtr->get_uuid());
}

// -------------------------------------------------------------

DGioMount::DGioMount(Mount* gmountPtr, QObject *parent)
    : QObject(parent)
    , d_ptr(new DGioMountPrivate(this, gmountPtr))
{
    // gmountPtr must be vaild;
    Q_CHECK_PTR(gmountPtr);
}

DGioMount::~DGioMount()
{

}

DGioMount *DGioMount::createFromPath(QString path, QObject *parent)
{
    Glib::RefPtr<File> gfile = File::create_for_path(path.toStdString());
    try {
        Glib::RefPtr<Mount> gmount = gfile->find_enclosing_mount();
        if (gmount) {
            return new DGioMount(gmount.release(), parent);
        }
    } catch (Glib::Error error) {
        qDebug() << QString::fromStdString(error.what().raw());
    }

    return nullptr;
}

QString DGioMount::name() const
{
    Q_D(const DGioMount);

    return d->name();
}

QString DGioMount::uuid() const
{
    Q_D(const DGioMount);

    return d->uuid();
}

bool DGioMount::canUnmount() const
{
    Q_D(const DGioMount);

    return d->getGMountInstance()->can_unmount();
}

bool DGioMount::canEject() const
{
    Q_D(const DGioMount);

    return d->getGMountInstance()->can_eject();
}

