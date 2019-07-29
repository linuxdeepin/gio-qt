#ifndef DGIOHELPER_H
#define DGIOHELPER_H

#include <giomm/icon.h>

#include <QStringList>

namespace DGioPrivate {
    QStringList getThemedIconNames(Glib::RefPtr<const Gio::Icon> icon);
}

#endif // DGIOHELPER_H
