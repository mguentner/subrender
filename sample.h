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

#ifndef SAMPLE_H
#define SAMPLE_H

#include <QtGlobal>

class Sample
{
public:

    Sample();
    Sample(quint64 time, double depth, double temperature);

    void setTime(quint64 time);
    void setDepth(double depth);
    void setTemperature(double temperature);


    quint64 getTime();
    quint32 getTimeSeconds();
    bool hasDepth();
    double getDepth();
    bool hasTemperature();
    double getTemperature();

private:

    quint64 m_time;
    bool m_hasDepth;
    double m_depth;
    bool m_hasTemperature;
    double m_temperature;
};

#endif // SAMPLE_H
