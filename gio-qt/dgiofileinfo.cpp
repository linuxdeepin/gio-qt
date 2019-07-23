#include "dgiofileinfo.h"

#include <giomm/fileinfo.h>

using namespace Gio;

class DGioFileInfoPrivate
{
public:
    DGioFileInfoPrivate(DGioFileInfo *qq, FileInfo *gmmFileInfoPtr);

    Glib::RefPtr<FileInfo> getGmmFileInfoInstance() const;

    bool getAttributeBoolean(const std::string &attribute) const;
    quint64 getAttributeUint64(const std::string &attribute) const;

private:
    Glib::RefPtr<FileInfo> m_gmmFileInfoPtr;

    QString uri() const;

    DGioFileInfo *q_ptr;

    Q_DECLARE_PUBLIC(DGioFileInfo)
};

DGioFileInfoPrivate::DGioFileInfoPrivate(DGioFileInfo *qq, FileInfo *gmmFileInfoPtr)
    : m_gmmFileInfoPtr(gmmFileInfoPtr)
    , q_ptr(qq)
{

}

Glib::RefPtr<FileInfo> DGioFileInfoPrivate::getGmmFileInfoInstance() const
{
    return m_gmmFileInfoPtr;
}

bool DGioFileInfoPrivate::getAttributeBoolean(const std::string &attribute) const
{
    return m_gmmFileInfoPtr->get_attribute_boolean(attribute);
}

quint64 DGioFileInfoPrivate::getAttributeUint64(const std::string &attribute) const
{
    return m_gmmFileInfoPtr->get_attribute_uint64(attribute);
}

// -------------------------------------------------------------

DGioFileInfo::DGioFileInfo(FileInfo *gmmFileInfoInfoPtr, QObject *parent)
    : QObject(parent)
    , d_ptr(new DGioFileInfoPrivate(this, gmmFileInfoInfoPtr))
{

}

DGioFileInfo::~DGioFileInfo()
{

}

bool DGioFileInfo::isReadOnly() const
{
    Q_D(const DGioFileInfo);

    return d->getAttributeBoolean(G_FILE_ATTRIBUTE_FILESYSTEM_READONLY);
}

quint64 DGioFileInfo::fsTotalBytes() const
{
    Q_D(const DGioFileInfo);

    return d->getAttributeUint64(G_FILE_ATTRIBUTE_FILESYSTEM_SIZE);
}

quint64 DGioFileInfo::fsUsedBytes() const
{
    Q_D(const DGioFileInfo);

    return d->getAttributeUint64(G_FILE_ATTRIBUTE_FILESYSTEM_USED);
}

quint64 DGioFileInfo::fsFreeBytes() const
{
    Q_D(const DGioFileInfo);

    return d->getAttributeUint64(G_FILE_ATTRIBUTE_FILESYSTEM_FREE);
}
