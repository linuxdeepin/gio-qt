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
#ifndef DGIOMOUNTOPERATION_H
#define DGIOMOUNTOPERATION_H

#include <QObject>

enum DGioAskPasswordFlag
{
    ASK_PASSWORD_NEED_PASSWORD = (1 << 0),
    ASK_PASSWORD_NEED_USERNAME = (1 << 1),
    ASK_PASSWORD_NEED_DOMAIN = (1 << 2),
    ASK_PASSWORD_SAVING_SUPPORTED = (1 << 3),
    ASK_PASSWORD_ANONYMOUS_SUPPORTED = (1 << 4)
};
Q_DECLARE_FLAGS(DGioAskPasswordFlags, DGioAskPasswordFlag)

//! Indicated the mount operation result
/*!
 *  Wrapper of GMountOperationResult.
 */
enum DGioMountOperationResult
{
    MOUNT_OPERATION_HANDLED, /*!< The request was fulfilled and the user specified data is now available */
    MOUNT_OPERATION_ABORTED, /*!< The user requested the mount operation to be aborted */
    MOUNT_OPERATION_UNHANDLED /*!< The request was unhandled (i.e. not implemented) */
};
Q_ENUMS(DGioMountOperationResult);

enum DGioPasswordSave
{
  PASSWORD_SAVE_NEVER,
  PASSWORD_SAVE_FOR_SESSION,
  PASSWORD_SAVE_PERMANENTLY
};
Q_ENUMS(DGioPasswordSave);

class DGioMountOperationPrivate;
class DGioMountOperation : public QObject
{
    Q_OBJECT
public:
    explicit DGioMountOperation(QObject *parent);
    ~DGioMountOperation();

    QString username() const;
    void setUsername(QString name);
    QString password() const;
    void setPassword(QString password);
    DGioPasswordSave passwordSave();
    void setPasswordSave(DGioPasswordSave save);
    QString domain() const;
    void setDomain(QString domain);

    bool anonymous()const;
    void setAnonymous(bool anonymous =  true);
    int choice()const;
    void setChoice(int choice);

    void reply(DGioMountOperationResult result);

Q_SIGNALS:
    void askPassword(QString message, QString defaultUser, QString defaultDomain, DGioAskPasswordFlags flags);
    void askQuestion(QString message, QStringList choices);
    void showUnmountProgress(QString message, qint64 timeLeftMs, qint64 bytesLeft);

private:
    QScopedPointer<DGioMountOperationPrivate> d_ptr;

    Q_DECLARE_PRIVATE(DGioMountOperation)
};

#endif // DGIOMOUNTOPERATION_H
