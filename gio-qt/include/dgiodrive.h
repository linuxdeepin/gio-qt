#ifndef DGIODRIVE_H
#define DGIODRIVE_H

#include <QObject>
#include <QSharedData>

namespace Gio {
class Drive;
}

class DGioMount;
class DGioDrivePrivate;
class DGioDrive : public QObject, public QSharedData{
    Q_OBJECT
public:
    explicit DGioDrive(Gio::Drive *gmmDrivePtr, QObject *parent = nullptr);
    ~DGioDrive();

    QString name() const;

private:
    QScopedPointer<DGioDrivePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DGioDrive)
};


#endif // DGIODRIVE_H
