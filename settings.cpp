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

#include "settings.h"

Settings* Settings::m_instance = NULL;


Settings::Settings()
{
    loadDefault();
}

Settings* Settings::instance()
{
    if (m_instance == NULL)
        m_instance = new Settings();
    return m_instance;
}

QPen Settings::getPathPen()
{
    return m_pathPen;
}

void Settings::setPathPen(const QPen &pathPen)
{
    if (m_pathPen != pathPen) {
        m_pathPen = pathPen;
        emit settingsChanged();
    }
}

QColor Settings::getTextColor()
{
    return m_textColor;
}

void Settings::setTextColor(const QColor &textColor)
{
    if (m_textColor != textColor) {
        m_textColor = textColor;
        emit settingsChanged();
    }
}

QFont Settings::getTextFont()
{
    return m_textFont;
}

void Settings::setTextFont(const QFont &textFont)
{
    if (m_textFont != textFont) {
        m_textFont = textFont;
        emit settingsChanged();
    }
}

QPointF Settings::getTimePosition()
{
    return m_timePosition;
}

void Settings::setTimePosition(const QPointF &position)
{
    if (m_timePosition != position) {
        m_timePosition = position;
        emit settingsChanged();
    }
}

QPointF Settings::getDepthPosition()
{
    return m_depthPosition;
}

void Settings::setDepthPosition(const QPointF &position)
{
    if (m_depthPosition != position) {
        m_depthPosition = position;
        emit settingsChanged();
    }
}

quint16 Settings::getWidth()
{
    return m_width;
}

void Settings::setWidth(quint16 width)
{
    if (m_width != width) {
        m_width = width;
        emit settingsChanged();
    }
}

quint16 Settings::getHeight()
{
    return m_height;
}

void Settings::setHeight(quint16 height)
{
    if (m_height != height) {
        m_height = height;
        emit settingsChanged();
    }
}

quint16 Settings::getFps()
{
    return m_fps;
}

void Settings::setFps(quint16 fps)
{
    if (m_fps != fps) {
       m_fps = fps;
       emit settingsChanged();
    }
}
QColor Settings::getBackgroundColor()
{
    return m_backgroundColor;
}

void Settings::setBackgroundColor(const QColor &color)
{
    if (m_backgroundColor != color ) {
        m_backgroundColor = color;
        emit settingsChanged();
    }
}

QColor Settings::getIndicatorStartColor()
{
    return m_indicatorStartColor;
}

void Settings::setIndicatorStartColor(const QColor &color)
{
    if (m_indicatorStartColor != color) {
        m_indicatorStartColor = color;
        emit settingsChanged();
    }
}

QColor Settings::getIndicatorStopColor()
{
    return m_indicatorStopColor;
}

void Settings::setIndicatorStopColor(const QColor &color)
{
    if (m_indicatorStopColor != color) {
        m_indicatorStopColor = color;
        emit settingsChanged();
    }
}

double Settings::getIndicatorRadius()
{
    return m_indicatorRadius;
}

void Settings::setIndicatorRadius(double radius)
{
    if (m_indicatorRadius != radius) {
        m_indicatorRadius = radius;
        emit settingsChanged();
    }
}

quint16 Settings::getSelectedDive()
{
    return m_selectedDive;
}

void Settings::setSelectedDive(quint16 diveNumber)
{
    if (m_selectedDive != diveNumber) {
        m_selectedDive = diveNumber;
        emit settingsChanged();
    }
}

void Settings::save()
{
    QSettings settings("subrender", "subrender");

    settings.beginGroup("path");
    settings.setValue("pen", m_pathPen);
    settings.endGroup();

    settings.beginGroup("text");
    settings.setValue("color", m_textColor);
    settings.setValue("font", m_textFont);
    settings.endGroup();

    settings.beginGroup("position");
    settings.setValue("time", m_timePosition);
    settings.setValue("depth", m_depthPosition);
    settings.endGroup();

    settings.beginGroup("background");
    settings.setValue("color", m_backgroundColor);
    settings.endGroup();

    settings.beginGroup("indicator");
    settings.setValue("startColor", m_indicatorStartColor);
    settings.setValue("stopColor", m_indicatorStopColor);
    settings.setValue("radius", m_indicatorRadius);
    settings.endGroup();

    settings.beginGroup("image");
    settings.setValue("width", m_width);
    settings.setValue("height", m_height);
    settings.setValue("fps", m_fps);
    settings.endGroup();

}

void Settings::restore()
{
    QSettings settings("subrender", "subrender");
    if (settings.isWritable() == false) {
        loadDefault();
        return;
    }
    settings.beginGroup("path");
    m_pathPen = settings.value("pen").value<QPen>();
    settings.endGroup();

    settings.beginGroup("text");
    m_textColor = settings.value("color").value<QColor>();
    m_textFont = settings.value("font").value<QFont>();
    settings.endGroup();

    settings.beginGroup("position");
    m_timePosition = settings.value("time").toPointF();
    m_depthPosition = settings.value("depth").toPointF();
    settings.endGroup();

    settings.beginGroup("background");
    m_backgroundColor = settings.value("color").value<QColor>();
    settings.endGroup();

    settings.beginGroup("indicator");
    m_indicatorStartColor = settings.value("startColor").value<QColor>();
    m_indicatorStopColor = settings.value("stopColor").value<QColor>();
    m_indicatorRadius = settings.value("radius").toDouble();
    settings.endGroup();

    settings.beginGroup("image");
    m_width = settings.value("width").toUInt();
    m_height = settings.value("height").toUInt();
    m_fps = settings.value("fps").toUInt();
    settings.endGroup();
}

void Settings::loadDefault()
{
    m_pathPen = QPen(Qt::gray, 4.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    m_textColor = Qt::white;
    m_textFont  = QFont("Arial", 20, QFont::Bold);
    m_backgroundColor = QColor("#0b0b0b");
    m_indicatorStartColor = QColor("#FF0000");
    m_indicatorStopColor = QColor("#520000");
    m_indicatorRadius = 12;
    m_fps = 15;
    m_width = 400;
    m_height = 720;
    m_depthPosition = QPointF(m_width*0.70, m_height*0.90);
    m_timePosition = QPointF(m_width*0.20, m_height*0.90);
    m_selectedDive = 1;
}
