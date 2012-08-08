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

#include "divemanager.h"

#include <QDebug>

DiveManager* DiveManager::m_instance = NULL;

DiveManager::DiveManager() : m_iterator(m_dives)
{
}

DiveManager* DiveManager::instance()
{
    if(m_instance == NULL)
        m_instance = new DiveManager();
    return m_instance;
}

Dive DiveManager::getDive(quint16 diveNumber)
{
    return m_dives.value(diveNumber);
}

quint16 DiveManager::importDives(QIODevice *device)
{

    QXmlStreamReader reader(device);
    Dive *dive;
    QDate date;
    QTime time;
    quint16 number = 0;
    quint16 success = 0;

    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType token = reader.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement) {
            if (reader.name() == "dive" ) {
                QXmlStreamAttributes attributes = reader.attributes();
                date = QDate::currentDate();
                time = QTime::currentTime();
                number = 0;
                if (attributes.hasAttribute("date"))
                    date = QDate::fromString(attributes.value("date").toString(),"yyyy-MM-dd");
                if (attributes.hasAttribute("time"))
                    time = QTime::fromString(attributes.value("time").toString(),"HH:mm:ss");
                if (attributes.hasAttribute("number"))
                    number = attributes.value("number").toString().toInt();
                dive = new Dive(number, QDateTime(date,time));
                token = reader.readNext();
            } else {
                continue;
            }
            /*
             * We fake the first sample since most dive computers
             * do not log above 1m.
             */
            Sample fakeSample;
            fakeSample.setTime(0);
            fakeSample.setDepth(0);
            dive->insertSample(fakeSample);

            while(!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "dive")) {
                if (reader.name() == "depth" && reader.tokenType() == QXmlStreamReader::StartElement) {
                    double average = 0;
                    double max = 0;
                    QXmlStreamAttributes attributes = reader.attributes();
                    if (attributes.hasAttribute("max")) {
                        QStringList list = attributes.value("max").toString().split(" ");
                        max = list.at(0).toDouble();
                    }
                    if (attributes.hasAttribute("mean")) {
                        QStringList list = attributes.value("mean").toString().split(" ");
                        average = list.at(0).toDouble();
                    }
                    dive->setAverageDepth(average);
                    dive->setMaxDepth(max);
                }
                if (reader.name() == "sample" && reader.tokenType() == QXmlStreamReader::StartElement) {
                    Sample sample;
                    quint64 divetime;
                    double depth;
                    double temp;
                    QXmlStreamAttributes attributes = reader.attributes();
                    /* We should assert that we only submit samples with a time */
                    if (attributes.hasAttribute("time")) {
                        QRegExp rx("(\\d+):(\\d+)\\s.");
                        int pos = rx.indexIn(attributes.value("time").toString());
                        if (pos > -1) {
                            divetime = (rx.cap(1).toInt()*60+rx.cap(2).toInt())*1000;
                            /*
                             * We create an offset of 1 second for all real samples
                             */
                            sample.setTime(divetime+1000);
                        }
                        else
                            qDebug() << "Unable to parse time!";
                    }
                    if (attributes.hasAttribute("depth")) {
                        QStringList list = attributes.value("depth").toString().split(" ");
                        depth = list.at(0).toDouble();
                        sample.setDepth(depth);
                    }
                    if (attributes.hasAttribute("temp")) {
                        QStringList list = attributes.value("temp").toString().split(" ");
                        temp = list.at(0).toDouble();
                        sample.setTemperature(temp);
                    }
                    dive->insertSample(sample);
                }
                token = reader.readNext();
            }
            /*
             * We fake the last sample since most dive computers
             * do not log above 1m.
             */
            Sample fakeSample2;
            fakeSample2.setTime(dive->getSample(dive->size()-1).getTime()+1000);
            fakeSample2.setDepth(0);
            dive->insertSample(fakeSample2);

            m_dives.insert(number, *dive);
            success++;
            delete dive;
        }
    }
    if (reader.hasError()) {
    }
    return success;
}


quint16 DiveManager::size()
{
    return m_dives.size();
}

bool DiveManager::empty()
{
    return m_dives.empty();
}

bool DiveManager::exists(quint16 diveNumber)
{
    return m_dives.contains(diveNumber);
}

void DiveManager::toBack()
{
    m_iterator.toBack();
}

void DiveManager::toFront()
{
    m_iterator.toFront();
}

bool DiveManager::hasNext()
{
    return m_iterator.hasNext();
}

bool DiveManager::hasPrevious()
{
    return m_iterator.hasPrevious();
}

Dive DiveManager::next()
{
    m_iterator.next();
    return m_iterator.value();
}

Dive DiveManager::peekNext()
{
    m_iterator.peekNext();
    return m_iterator.value();
}
