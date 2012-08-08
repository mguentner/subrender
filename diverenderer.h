/*
 * This file is part of subrender
 *
 * Copyright (C) 2012 Maximilian Güntner <maximilian.guentner@gmail.com>
 *
 * Subrender is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Subrender is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Subrender. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef DIVERENDERER_H
#define DIVERENDERER_H
#include <QObject>

#include <dive.h>
#include <divemanager.h>

class DiveRenderer : public QObject
{
    Q_OBJECT
public:
    DiveRenderer(QObject *parent = 0);
    void setData(const QString &path, const quint16 &dive);
public slots:
    void render();
    void abort();
signals:
    void renderProgress(quint32 done, quint32 total);
    void finished(bool error);
private:
    QString m_path;
    quint16 m_dive;
    bool m_abort;
};

#endif // DIVERENDERER_H
