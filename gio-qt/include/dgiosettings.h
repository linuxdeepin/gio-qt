/*
 * Copyright (C) 2011 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     justforlxz <justforlxz@outlook.com>
 *
 * Maintainer: justforlxz <justforlxz@outlook.com>
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

#ifndef DGIOSETTINGS_H
#define DGIOSETTINGS_H

#include <QObject>
#include <QScopedPointer>

class DGioSettingsPrivate;
class DGioSettings : public QObject
{
    Q_OBJECT
public:
    explicit DGioSettings(const QString& schemaId, QObject* parent = nullptr);
    DGioSettings(const QString& schemaId, const QString& path, QObject* parent = nullptr);

    ~DGioSettings();

    void sync();

    bool setValue(const QString& key, const QVariant& value, bool sync = false);
    QVariant value(const QString& key) const;

    Q_DECL_DEPRECATED QStringList keys() const;

    void reset(const QString& key);

    static bool isSchemaInstalled(const QString& schemaId);

Q_SIGNALS:
    void valueChanged(const QString& key, const QVariant& value);

private:
    QScopedPointer<DGioSettingsPrivate> d_private;

    Q_DECLARE_PRIVATE_D(d_private, DGioSettings)
};

#endif // DGIOSETTINGS_H
