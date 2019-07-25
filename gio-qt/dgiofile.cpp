#include "dgiofile.h"
#include "dgiofileinfo.h"

#include <glibmm/refptr.h>

#include <giomm/init.h>
#include <giomm/file.h>

#include <QDebug>

using namespace Gio;

class DGioFilePrivate
{
public:
    DGioFilePrivate(DGioFile *qq, File *gmmFilePtr);

    Glib::RefPtr<File> getGmmFileInstance() const;

private:
    Glib::RefPtr<File> m_gmmFilePtr;

    QString uri() const;

    DGioFile *q_ptr;

    Q_DECLARE_PUBLIC(DGioFile)
};

DGioFilePrivate::DGioFilePrivate(DGioFile *qq, File *gmmFilePtr)
    : m_gmmFilePtr(gmmFilePtr)
    , q_ptr(qq)
{

}

Glib::RefPtr<File> DGioFilePrivate::getGmmFileInstance() const
{
    return m_gmmFilePtr;
}

QString DGioFilePrivate::uri() const
{
    return QString::fromStdString(m_gmmFilePtr->get_uri());
}

// -------------------------------------------------------------

DGioFile::DGioFile(File* gmmFilePtr, QObject *parent)
    : QObject(parent)
    , d_ptr(new DGioFilePrivate(this, gmmFilePtr))
{
    // gmountPtr must be vaild;
    Q_CHECK_PTR(gmmFilePtr);
}

DGioFile::~DGioFile()
{

}

/*!
 * \brief Create a DGioFile instance by given \a path
 *
 * This operation never fails since Gio::File::create_for_path never fails, but the returned
 * object might not support any I/O operation if path is malformed.
 *
 * Caller take the ownership of the created object, you can also provide a \a parent object.
 *
 * \return the created DGioFile instance
 */
DGioFile *DGioFile::createFromPath(QString path, QObject *parent)
{
    // ensure GIO got initialized
    Gio::init();

    // File::create_for_path never falls.
    Glib::RefPtr<File> gmmFile = File::create_for_path(path.toStdString());

    return new DGioFile(gmmFile.release(), parent);
}

/*!
 * \brief Create a DGioFile instance by given \a uri
 *
 * This operation never fails since Gio::File::create_for_uri never fails, but the returned
 * object might not support any I/O operation if uri is malformed.
 *
 * Caller take the ownership of the created object, you can also provide a \a parent object.
 *
 * \return the created DGioFile instance
 */
DGioFile *DGioFile::createFromUri(QString uri, QObject *parent)
{
    // ensure GIO got initialized
    Gio::init();

    // File::create_for_path never falls.
    Glib::RefPtr<File> gmmFile = File::create_for_uri(uri.toStdString());

    return new DGioFile(gmmFile.release(), parent);
}

QString DGioFile::basename() const
{
    Q_D(const DGioFile);

    return QString::fromStdString(d->getGmmFileInstance()->get_basename());
}

QString DGioFile::path() const
{
    Q_D(const DGioFile);

    return QString::fromStdString(d->getGmmFileInstance()->get_path());
}

QString DGioFile::uri() const
{
    Q_D(const DGioFile);

    return d->uri();
}

QExplicitlySharedDataPointer<DGioFileInfo> DGioFile::createFileSystemInfo()
{
    Q_D(DGioFile);

    try {
        Glib::RefPtr<FileInfo> gmmFileInfo = d->getGmmFileInstance()->query_filesystem_info("filesystem::*");
        if (gmmFileInfo) {
            QExplicitlySharedDataPointer<DGioFileInfo> fileInfoPtr(new DGioFileInfo(gmmFileInfo.release()));
            return fileInfoPtr;
        }
    } catch (Glib::Error error) {
        qDebug() << QString::fromStdString(error.what().raw());
    }

    return QExplicitlySharedDataPointer<DGioFileInfo>(nullptr);
}
