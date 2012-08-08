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

#ifndef DIVE_H
#define DIVE_H

#include <sample.h>

#include <QDateTime>
#include <QVector>


class Dive
{
public:
    Dive();
    Dive(quint16 diveNumber, const QDateTime &datetime);

    quint16 getDiveNumber();
    void setDiveNumber(quint16 diveNumber);

    QDateTime getDateTime();

    Sample getSample(int i);
    Sample getSampleByTime(quint64 time);

    void setDuration(quint64 duration);
    quint32 getDuration();

    void setMaxDepth(double maxDepth);
    double getMaxDepth();

    void setAverageDepth(double averageDepth);
    double getAverageDepth();

    double getMaxTemperature();
    double getAverageTemperature();
    double getMinTemperature();

    void insertSample(Sample sample);
    quint16 size();

private:
    void calculateValues();
    double calculateFactor(quint64 first, quint64 second, quint64 third);

private:
    quint16 m_diveNumber;
    QVector<Sample> m_samples;
    QDateTime m_datetime;
    /* Always set this to true when */
    bool m_dirty;
    /* These values will be calculated once a get function is being called
     * with bool m_dirty being true.
     */
    quint32 m_duration;
    double m_maxDepth;
    double m_averageDepth;
    double m_maxTemperature;
    double m_averageTemperature;
    double m_minTemperature;

};

#endif // DIVE_H
