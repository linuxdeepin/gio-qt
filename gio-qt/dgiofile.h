#ifndef DGIOFILE_H
#define DGIOFILE_H

#include <QObject>
#include <QSharedData>

namespace Gio {
class File;
}

enum DGioFileQueryInfoFlag
{
    FILE_QUERY_INFO_NONE = 0x0,
    FILE_QUERY_INFO_NOFOLLOW_SYMLINKS = (1 << 0)
};

Q_DECLARE_FLAGS(DGioFileQueryInfoFlags, DGioFileQueryInfoFlag)

class DGioFileInfo;
class DGioFileIterator;
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
    QExplicitlySharedDataPointer<DGioFileIterator> createFileIterator(QString attr, DGioFileQueryInfoFlags queryInfoFlags = FILE_QUERY_INFO_NONE);

private:
    QScopedPointer<DGioFilePrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioFile)
};

#endif // DGIOFILE_H
