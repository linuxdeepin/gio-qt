#include "dgiofileiterator.h"
#include "dgiofileinfo.h"

#include <glibmm/refptr.h>

#include <giomm/init.h>
#include <giomm/file.h>

#include <QDebug>

using namespace Gio;

class DGioFileIteratorPrivate
{
public:
    DGioFileIteratorPrivate(DGioFileIterator *qq, FileEnumerator *gmmFileEnumeratorPtr);

    Glib::RefPtr<FileEnumerator> getGmmFileEnumeratorInstance() const;

private:
    Glib::RefPtr<FileEnumerator> m_gmmFileEnumeratorPtr;

    DGioFileIterator *q_ptr;

    Q_DECLARE_PUBLIC(DGioFileIterator)
};

DGioFileIteratorPrivate::DGioFileIteratorPrivate(DGioFileIterator *qq, FileEnumerator *gmmFileEnumeratorPtr)
    : m_gmmFileEnumeratorPtr(gmmFileEnumeratorPtr)
    , q_ptr(qq)
{

}

Glib::RefPtr<FileEnumerator> DGioFileIteratorPrivate::getGmmFileEnumeratorInstance() const
{
    return m_gmmFileEnumeratorPtr;
}


// -------------------------------------------------------------

DGioFileIterator::DGioFileIterator(FileEnumerator* gmmFileEnumeratorPtr, QObject *parent)
    : QObject(parent)
    , d_ptr(new DGioFileIteratorPrivate(this, gmmFileEnumeratorPtr))
{
    // gmmFileEnumeratorPtr must be valid;
    Q_CHECK_PTR(gmmFileEnumeratorPtr);
}

DGioFileIterator::~DGioFileIterator()
{

}

QExplicitlySharedDataPointer<DGioFileInfo> DGioFileIterator::next()
{
    Q_D(DGioFileIterator);

    try {
        // can return nullptr if there is no file left.
        Glib::RefPtr<FileInfo> gmmFileInfoPtr = d->getGmmFileEnumeratorInstance()->next_file();
        if (gmmFileInfoPtr) {
            QExplicitlySharedDataPointer<DGioFileInfo> fileInfo(new DGioFileInfo(gmmFileInfoPtr.release()));
            return fileInfo;
        }
    } catch (const Glib::Error &error) {
        qDebug() << QString::fromStdString(error.what().raw());
    }

    return QExplicitlySharedDataPointer<DGioFileInfo>(nullptr);
}
