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

#ifndef DIVEMANAGER_H
#define DIVEMANAGER_H
#include <QMap>
#include <QIODevice>
#include <sample.h>
#include <dive.h>
#include <QtXml/QXmlStreamReader>
#include <QStringList>

class DiveManager
{
public:
    quint16 importDives(QIODevice *device);
    static DiveManager* instance();
    Dive getDive(quint16 diveNumber);
    quint16 size();
    bool empty();
    bool exists(quint16 diveNumber);
    /* Iterator Operations */
    void toBack();
    void toFront();
    bool hasNext();
    bool hasPrevious();
    Dive next();
    Dive peekNext();

private:
    DiveManager();

private:
    static DiveManager* m_instance;
    QMap<quint16, Dive> m_dives;
    QMutableMapIterator<quint16, Dive> m_iterator;

};

#endif // DIVEMANAGER_H
