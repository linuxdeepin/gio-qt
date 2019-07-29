#ifndef DGIOMOUNT_H
#define DGIOMOUNT_H

#include <QObject>
#include <QSharedData>

namespace Gio {
class Mount;
}

class DGioFile;
class DGioVolume;
class DGioMountPrivate;
class DGioMount : public QObject, public QSharedData
{
    Q_OBJECT
public:
    explicit DGioMount(Gio::Mount *gmmMountPtr, QObject *parent = nullptr);
    ~DGioMount();

    static DGioMount * createFromPath(QString path, QObject *parent = nullptr);

    QString name() const;
    QString uuid() const;
    bool isShadowed() const;
    bool canUnmount() const;
    bool canEject() const;
    QStringList themedIconNames() const;
    QStringList themedSymbolicIconNames() const;

    void unmount(bool forceUnmount = false);

    QExplicitlySharedDataPointer<DGioFile> getRootFile();
    QExplicitlySharedDataPointer<DGioFile> getDefaultLocationFile();
    QExplicitlySharedDataPointer<DGioVolume> getVolume();

private:
    QScopedPointer<DGioMountPrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioMount)
};

#endif // DGIOMOUNT_H
