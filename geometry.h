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

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QPointF>
#include <QLineF>

inline QPointF middle(QPointF p1, QPointF p2) {
    return (p1+p2)/2;
}

inline QPointF delta(QPointF p1, QPointF p2) {
    return p2-p1;
}

inline double length(QPointF p1, QPointF p2) {
    return (double) QLineF(p1, p2).length();
}
#endif // GEOMETRY_H
