/*
 * Copyright (C) 2019 Deepin Technology Co., Ltd.
 *
 * Author:     Gary Wang <wzc782970009@gmail.com>
 *
 * Maintainer: Gary Wang <wangzichong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "dgioutils.h"

#include <QStringList>

#include <glibmm/miscutils.h>

/*!
 * \brief Get the full path by directory type.
 *
 * Wrapper of Glib::get_user_data_dir(), behavior similar to QStandardPaths::writableLocation(),
 * but at least it has USER_DIRECTORY_TEMPLATES .
 *
 * On UNIX platforms this is determined using the mechanisms described in the
 * [XDG Base Directory Specification](http://www.freedesktop.org/Standards/basedir-spec).
 */
QString DGioUtils::userSpecialDir(DGioUserDirectory userDirectory)
{
    return QString::fromStdString(Glib::get_user_special_dir(static_cast<Glib::UserDirectory>(userDirectory)));
}

/*!
 * \brief Get an ordered list of base directories in which to access system-wide application data.
 *
 * Wrapper of Glib::get_system_data_dirs(), behavior similar (should be the same under UNIX) to
 * QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).
 *
 * On UNIX platforms this is determined using the mechanisms described in the
 * [XDG Base Directory Specification](http://www.freedesktop.org/Standards/basedir-spec)
 * In this case the list of directories retrieved will be XDG_DATA_DIRS.
 */
QStringList DGioUtils::systemDataDirs()
{
    std::vector<std::string> dirs = Glib::get_system_data_dirs();
    QStringList lst;

    for (auto dir : dirs) {
        lst.append(QString::fromStdString(dir));
    }

    return lst;
}

/*!
 * \brief Get a base directory in which to access application data such as icons that is customized for a particular user.
 *
 * Wrapper of Glib::get_user_data_dir(), behavior similar (should be the same under UNIX) to
 * QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation).
 *
 * On UNIX platforms this is determined using the mechanisms described in the
 * [XDG Base Directory Specification](http://www.freedesktop.org/Standards/basedir-spec).
 * In this case the directory retrieved will be `XDG_DATA_HOME`.
 */
QString DGioUtils::userDataDir()
{
    return QString::fromStdString(Glib::get_user_data_dir());
}

/*!
 * \brief Gets the directory to use for temporary files.
 *
 * Wrapper of Glib::get_user_data_dir(), behavior similar (but not the same) to QDir::temp() or
 * QStandardPaths::writableLocation(QStandardPaths::TempLocation).
 *
 * This is found from inspecting the environment variables TMPDIR, TMP, and TEMP in that order. If none of those are defined
 * "/tmp" is returned on UNIX and "C:\\" on Windows.
 *
 * \return The directory to use for temporary files.
 */
QString DGioUtils::tmpDir()
{
    return QString::fromStdString(Glib::get_tmp_dir());
}
