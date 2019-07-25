#ifndef DGIOFILE_H
#define DGIOFILE_H

#include <QObject>
#include <QSharedData>

namespace Gio {
class File;
}

class DGioFileInfo;
class DGioFilePrivate;
class DGioFile : public QObject, public QSharedData
{
    Q_OBJECT
public:
    explicit DGioFile(Gio::File *gmmFilePtr, QObject *parent = nullptr);
    ~DGioFile();

    static DGioFile * createFromPath(QString path, QObject *parent = nullptr);
    static DGioFile * createFromUri(QString uri, QObject *parent = nullptr);

    QString basename() const;
    QString path() const;
    QString uri() const;
    QExplicitlySharedDataPointer<DGioFileInfo> createFileSystemInfo();

private:
    QScopedPointer<DGioFilePrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioFile)
};

#endif // DGIOFILE_H
