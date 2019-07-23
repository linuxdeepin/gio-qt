#ifndef DGIOFILEINFO_H
#define DGIOFILEINFO_H

#include <QObject>
#include <QSharedData>

namespace Gio {
class FileInfo;
}

class DGioFileInfoPrivate;
class DGioFileInfo : public QObject, public QSharedData
{
    Q_OBJECT
public:
    explicit DGioFileInfo(Gio::FileInfo *gmmFileInfoInfoPtr, QObject *parent = nullptr);
    ~DGioFileInfo();

    bool isReadOnly() const;

    quint64 fsTotalBytes() const;
    quint64 fsUsedBytes() const;
    quint64 fsFreeBytes() const;

private:
    QScopedPointer<DGioFileInfoPrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioFileInfo)
};

#endif // DGIOFILEINFO_H
