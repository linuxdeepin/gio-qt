#include <QDebug>
#include <QExplicitlySharedDataPointer>

#include <dgiomount.h>
#include <dgiovolumemanager.h>

int main()
{
    DGioMount * m = DGioMount::createFromPath("/media/wzc/aaaaaaaaaaaaaaaa");
    if (m) {
        qDebug() << m->name();
    }

    DGioVolumeManager mgr;
    const QList<QExplicitlySharedDataPointer<DGioMount> > lst = mgr.getMounts();

    for (const QExplicitlySharedDataPointer<DGioMount> &p : lst) {
        qDebug() << p->name() << m->uuid() << m->canUnmount();
    }

    return 0;
}
