#ifndef DGIOMOUNT_H
#define DGIOMOUNT_H

#include <QObject>
#include <QSharedData>

namespace Gio {
class Mount;
}

class DGioMountPrivate;
class DGioMount : public QObject, public QSharedData
{
    Q_OBJECT
public:
    explicit DGioMount(Gio::Mount *gmountPtr, QObject *parent = nullptr);
    ~DGioMount();

    static DGioMount * createFromPath(QString path, QObject *parent = nullptr);

    QString name() const;
    QString uuid() const;
    bool canUnmount() const;
    bool canEject() const;

private:
    QScopedPointer<DGioMountPrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioMount)
};

#endif // DGIOMOUNT_H
