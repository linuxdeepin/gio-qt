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
#include "dgiomountoperation.h"

#include <giomm/mountoperation.h>

using namespace Gio;

class DGioMountOperationPrivate
{
    DGioMountOperationPrivate(DGioMountOperation *qq);

    Glib::RefPtr<MountOperation> getGmmMountOperationInstance() const;

    QString username() const;

    void slot_askPassword(const Glib::ustring& message, const Glib::ustring& default_user, const Glib::ustring& default_domain, AskPasswordFlags flags);
    void slot_askQuestion(const Glib::ustring& message, const Glib::StringArrayHandle& choices);
    void slot_showUnmountProgress(const Glib::ustring &message, gint64 time_left, gint64 bytes_left);

private:
    Glib::RefPtr<MountOperation> m_gmmMountOperationPtr;

    DGioMountOperation *q_ptr;

    Q_DECLARE_PUBLIC(DGioMountOperation)
};

DGioMountOperationPrivate::DGioMountOperationPrivate(DGioMountOperation *qq)
    : q_ptr(qq)
{
    m_gmmMountOperationPtr = Gio::MountOperation::create();

    m_gmmMountOperationPtr->signal_ask_password().connect(sigc::mem_fun(*this, &DGioMountOperationPrivate::slot_askPassword));
    m_gmmMountOperationPtr->signal_ask_question().connect(sigc::mem_fun(*this, &DGioMountOperationPrivate::slot_askQuestion));
    m_gmmMountOperationPtr->signal_show_unmount_progress().connect(sigc::mem_fun(*this, &DGioMountOperationPrivate::slot_showUnmountProgress));
}

Glib::RefPtr<MountOperation> DGioMountOperationPrivate::getGmmMountOperationInstance() const
{
    return m_gmmMountOperationPtr;
}

QString DGioMountOperationPrivate::username() const
{
    return QString::fromStdString(m_gmmMountOperationPtr->get_username().raw());
}

void DGioMountOperationPrivate::slot_askPassword(const Glib::ustring &message, const Glib::ustring &default_user, const Glib::ustring &default_domain, AskPasswordFlags flags)
{
    Q_Q(DGioMountOperation);

    QString msg = QString::fromStdString(message.raw());
    QString defaultUser = QString::fromStdString(default_user.raw());
    QString defaultDomain = QString::fromStdString(default_domain.raw());
    DGioAskPasswordFlags askPasswordFlags(static_cast<DGioAskPasswordFlag>(flags));

    Q_EMIT q->askPassword(msg, defaultUser, defaultDomain, askPasswordFlags);
}

void DGioMountOperationPrivate::slot_askQuestion(const Glib::ustring &message, const Glib::StringArrayHandle &choices)
{
    Q_Q(DGioMountOperation);

    QString msg = QString::fromStdString(message.raw());
    QStringList choiceList;
    for (auto oneChoice : choices) {
        choiceList.append(QString::fromStdString(oneChoice.raw()));
    }

    Q_EMIT q->askQuestion(msg, choiceList);
}

void DGioMountOperationPrivate::slot_showUnmountProgress(const Glib::ustring& message, gint64 time_left, gint64 bytes_left)
{
    Q_Q(DGioMountOperation);

    Q_EMIT q->showUnmountProgress(QString::fromStdString(message.raw()), time_left, bytes_left);
}

// -------------------------------------------------------------

DGioMountOperation::DGioMountOperation(QObject *parent)
    : QObject(parent)
    , d_ptr(new DGioMountOperationPrivate(this))
{

}

DGioMountOperation::~DGioMountOperation()
{

}

QString DGioMountOperation::username() const
{
    Q_D(const DGioMountOperation);

    return d->username();
}

void DGioMountOperation::reply(DGioMountOperationResult result)
{
    Q_D(DGioMountOperation);

    d->getGmmMountOperationInstance()->reply(static_cast<MountOperationResult>(result));
}
