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

#include "dive.h"

Dive::Dive()
{
}

Dive::Dive(quint16 diveNumber, const QDateTime &datetime)
{
    m_diveNumber = diveNumber;
    m_datetime = datetime;
}

quint16 Dive::getDiveNumber()
{
    return m_diveNumber;
}

void Dive::setDiveNumber(quint16 diveNumber)
{
    m_diveNumber = diveNumber;
}

QDateTime Dive::getDateTime()
{
    return m_datetime;
}

Sample Dive::getSample(int i)
{
    return m_samples[i];
}

Sample Dive::getSampleByTime(quint64 time)
{
    Sample first;
    Sample second;
    Sample newSample;
    double depth = 0;
    double temperature = 0;
    double factor;
    quint16 i = 0;
    quint16 lastKnown = 0;
    /* Interpolation of Depth */

    while (i < m_samples.size() && m_samples[i].getTime() <= time) {
        if (m_samples[i].hasDepth())
            lastKnown = i;
        i++;
    }
    first = m_samples[lastKnown];
    while (i < m_samples.size()) {
        if (m_samples[i].hasDepth()) {
            lastKnown = i;
            break;
        }
        i++;
    }
    second = m_samples[lastKnown];
    factor = calculateFactor(first.getTime(),second.getTime(),time);
    depth = (1-factor)*first.getDepth()+factor*second.getDepth();

    /* Interpolation of Temperature */
    i=0;
    while (i < m_samples.size() && m_samples[i].getTime() <= time) {
        if (m_samples[i].hasTemperature())
            lastKnown = i;
        i++;
    }
    first = m_samples[lastKnown];
    while (i < m_samples.size()) {
        if(m_samples[i].hasTemperature()) {
            lastKnown = i;
            break;
        }
        i++;
    }
    second = m_samples[lastKnown];
    factor = calculateFactor(first.getTime(),second.getTime(),time);

    temperature = (1-factor)*first.getTemperature()+factor*second.getTemperature();

    newSample.setTime(time);
    newSample.setTemperature(temperature);
    newSample.setDepth(depth);

    return newSample;
}

void Dive::setDuration(quint64 duration)
{
    m_duration = duration;
}

void Dive::calculateValues()
{
    /* No need to update */
    if (m_dirty == false || m_samples.empty())
        return;
    double m_temperatureCount = 0;
    m_maxTemperature = 1000;
    m_averageTemperature = 0;
    m_minTemperature = 0;
    for (qint16 i=0; i < m_samples.size(); i++) {
        if (m_samples[i].hasTemperature() == false)
            continue;
        m_averageTemperature +=  m_samples[i].getTemperature();
        if (i == 0) {
            m_maxTemperature = m_samples[i].getTemperature();
            m_minTemperature = m_samples[i].getTemperature();
        } else {
            if (m_samples[i].getTemperature() > m_maxTemperature)
                m_maxTemperature = m_samples[i].getTemperature();
            if (m_samples[i].getTemperature() < m_minTemperature)
                m_minTemperature = m_samples[i].getTemperature();
        }
        m_temperatureCount++;
    }
    if (m_temperatureCount > 0)
        m_averageTemperature /= m_temperatureCount;
    m_dirty = false;
}

double Dive::calculateFactor(quint64 first, quint64 second, quint64 third)
{
    double factor = 0;
    if (second-first == 0)
        factor = 0;
    else
        factor = (double)(third-first)/(double)(second-first);
    return factor;
}

quint32 Dive::getDuration()
{
    return m_samples.last().getTimeSeconds();
}

void Dive::setMaxDepth(double maxDepth)
{
    m_maxDepth = maxDepth;
}

double Dive::getMaxDepth()
{
    calculateValues();
    return m_maxDepth;
}

void Dive::setAverageDepth(double averageDepth)
{
    m_averageDepth = averageDepth;
}

double Dive::getAverageDepth()
{
    return m_averageDepth;
}

double Dive::getMaxTemperature()
{
    calculateValues();
    return m_maxTemperature;
}

double Dive::getAverageTemperature()
{
    calculateValues();
    return m_averageTemperature;
}

double Dive::getMinTemperature()
{
    calculateValues();
    return m_minTemperature;
}

void Dive::insertSample(Sample sample)
{
    quint64 sampleTime = sample.getTime();
    quint16 i = 0;
    if (m_samples.isEmpty()) {
        m_samples.append(sample);
        return;
    }
    for (i = 0; i < m_samples.size(); i++ )
        if (m_samples[i].getTime() > sampleTime)
            break;
    m_samples.insert(i, sample);
    /* We need to update some values */
    m_dirty = true;
}

quint16 Dive::size()
{
    return m_samples.size();
}


