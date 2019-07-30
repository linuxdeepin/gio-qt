#ifndef DGIOFILEITERATOR_H
#define DGIOFILEITERATOR_H

#include <QObject>
#include <QSharedData>

namespace Gio {
class FileEnumerator;
}

class DGioFileInfo;
class DGioFileIteratorPrivate;
class DGioFileIterator : public QObject, public QSharedData
{
    Q_OBJECT
public:
    explicit DGioFileIterator(Gio::FileEnumerator *gmmFileEnumeratorPtr, QObject *parent = nullptr);
    ~DGioFileIterator();

    QExplicitlySharedDataPointer<DGioFileInfo> nextFile();

private:
    QScopedPointer<DGioFileIteratorPrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioFileIterator)
};

#endif // DGIOFILEITERATOR_H
