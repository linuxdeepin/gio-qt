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
#ifndef DGLIBUTILS_H
#define DGLIBUTILS_H

#include <QObject>

enum DGlibUserDirectory
{
    USER_DIRECTORY_DESKTOP,
    USER_DIRECTORY_DOCUMENTS,
    USER_DIRECTORY_DOWNLOAD,
    USER_DIRECTORY_MUSIC,
    USER_DIRECTORY_PICTURES,
    USER_DIRECTORY_PUBLIC_SHARE,
    USER_DIRECTORY_TEMPLATES,
    USER_DIRECTORY_VIDEOS,
    USER_N_DIRECTORIES
};
Q_ENUMS(DGlibUserDirectory);

class DGlibUtils
{
public:
    static QString userSpecialDir(DGlibUserDirectory userDirectory);
    static QStringList systemDataDirs();
    static QString userDataDir();
    static QString tmpDir();
};

#endif // DGLIBUTILS_H
