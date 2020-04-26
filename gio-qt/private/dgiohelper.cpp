/*
 * Copyright (C) 2019 Deepin Technology Co., Ltd.
 *
 * Author:     Gary Wang <wzc782970009@gmail.com>
 *
 * Maintainer: Gary Wang <wangzichong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "dgiohelper.h"

#include <glibmm/refptr.h>

#include <giomm/themedicon.h>

using namespace Gio;

namespace DGioPrivate {

QStringList getThemedIconNames(Glib::RefPtr<const Gio::Icon> icon)
{
    QStringList iconNames;

    Glib::RefPtr<const ThemedIcon> themedIcon = Glib::RefPtr<const ThemedIcon>::cast_dynamic(icon);

    // due to https://gitlab.gnome.org/GNOME/glibmm/issues/50 we cannot use the glibmm way to get icon name.
    // upstream already fixed the issue but we still need debian backport the patch so we can use it.
    // see: https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=932950

    //    if (G_IS_THEMED_ICON(themedIcon->gobj()) ) {
    //        qDebug() << "Yes and";
    //    }

    //    if (themedIcon) {
    //        qDebug() << "Yes";
    //    }

    if (themedIcon) {
        char **names;
        char **iter;
        names = NULL;
        g_object_get(G_THEMED_ICON(themedIcon->gobj()), "names", &names, NULL);
        for (iter = names; *iter; iter++) {
            iconNames.append(QString(*iter));
        }
        g_strfreev(names);
        return iconNames;
    }

    //    return {QStringList::fromStdList(themedIcon->get_names())};

    //    char* name = 0;
    //    g_object_get(G_OBJECT(themedIcon->gobj()), "name", &name, NULL);
    //    return {QString(name)};

    //    if (themedIcon) {
    //        auto ustring_names = themedIcon->get_names();
    ////        for (const Glib::ustring &str : ustring_names) {
    ////            iconNames.append(QString::fromStdString(str.raw()));
    ////        }
    //    }
    return iconNames;
}

gchar *converToGChar(const QByteArray &array) {
    GString *str = g_string_new(nullptr);

    for (const QChar c : array) {
        g_string_append_c(str, c.toLower().toLatin1());
    }

    return g_string_free(str, FALSE);
}

}

