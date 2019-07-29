#ifndef DGIOUTILS_H
#define DGIOUTILS_H

#include <QObject>

enum DGioUserDirectory
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
Q_ENUMS(DGioUserDirectory);

class DGioUtils
{
public:
    static QString userSpecialDir(DGioUserDirectory userDirectory);
    static QStringList systemDataDirs();
    static QString userDataDir();
    static QString tmpDir();
};

#endif // DGIOUTILS_H
