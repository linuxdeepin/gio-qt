#include "dgiodrive.h"

#include <glibmm/refptr.h>
#include <giomm/drive.h>

#include <QDebug>

using namespace Gio;

class DGioDrivePrivate{
public:
    DGioDrivePrivate(DGioDrive *qq, Drive *gmmDrivePtr);

    Glib::RefPtr<Drive> getGmmDriveInstence();

    QString name() const;

private:
    Glib::RefPtr<Drive> m_gmmDrivePtr;

    DGioDrive *q_ptr;
    Q_DECLARE_PUBLIC(DGioDrive)
};

DGioDrivePrivate::DGioDrivePrivate(DGioDrive *qq, Drive *gmmDrivePtr)
    : m_gmmDrivePtr(gmmDrivePtr)
    , q_ptr(qq)
{

}

Glib::RefPtr<Drive> DGioDrivePrivate::getGmmDriveInstence()
{
    return  m_gmmDrivePtr;
}

QString DGioDrivePrivate::name() const
{
    return QString::fromStdString(m_gmmDrivePtr->get_name());
}

///////////////////////////////////////////////////////////////
//// class DGioDrive
/// ///////////////////////////////////////////////////////////
DGioDrive::DGioDrive(Gio::Drive *gmmDrivePtr, QObject *parent)
    : QObject(parent)
    , d_ptr(new DGioDrivePrivate(this, gmmDrivePtr))
{
    Q_CHECK_PTR(gmmDrivePtr);
}

DGioDrive::~DGioDrive()
{

}

QString DGioDrive::name() const
{
    Q_D(const DGioDrive);
    return d->name();
}
