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

class DGioMountOperationPrivate;
class DGioMountOperation : public QObject
{
    Q_OBJECT
public:
    explicit DGioMountOperation(QObject *parent);
    ~DGioMountOperation();

    QString username() const;

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
