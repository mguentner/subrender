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

#include "sample.h"

Sample::Sample()
{
    m_hasDepth = false;
    m_hasTemperature = false;
    m_temperature = 0;
    m_depth = 0;
}

Sample::Sample(quint64 time, double depth, double temperature)
{
    m_time = time;
    m_depth = depth;
    m_temperature = temperature;
    m_hasDepth = true;
    m_hasTemperature = true;
}

void Sample::setTime(quint64 time)
{
    m_time = time;
}

void Sample::setDepth(double depth)
{
    m_hasDepth = true;
    m_depth = depth;
}

void Sample::setTemperature(double temperature)
{
    m_hasTemperature = true;
    m_temperature = temperature;
}

quint64 Sample::getTime()
{
    return m_time;
}

quint32 Sample::getTimeSeconds()
{
    return m_time/1000;
}

bool Sample::hasDepth()
{
    return m_hasDepth;
}

double Sample::getDepth()
{
    return m_depth;
}

bool Sample::hasTemperature()
{
    return m_hasTemperature;
}

double Sample::getTemperature()
{
    return m_temperature;
}
