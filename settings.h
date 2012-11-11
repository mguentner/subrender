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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QPen>
#include <QColor>
#include <QFont>

class Settings : public QObject
{
    Q_OBJECT
public:
    enum PlotStyle {HorizontalVertical = 0, Vertical = 1};

    static Settings* instance();
    /* Path settings */
    QPen getPathPen();
    void setPathPen(const QPen &pathPen);
    quint16 getSmoothness();
    void setSmoothness(quint16 smoothness);
    PlotStyle getPlotStyle();
    void setPlotStyle(PlotStyle plotStyle);
    /* Text settings */
    QColor getTextColor();
    void setTextColor(const QColor &textColor);
    QFont getTextFont();
    void setTextFont(const QFont &textFont);
    /* Text position settings */
    QPointF getTimePosition();
    void setTimePosition(const QPointF &position);
    QPointF getDepthPosition();
    void setDepthPosition(const QPointF &position);
    /* Image settings */
    quint16 getWidth();
    void setWidth(quint16 width);
    quint16 getHeight();
    void setHeight(quint16 height);
    quint16 getFps();
    void setFps(quint16 fps);
    /* Background settings */
    QColor getBackgroundColor();
    void setBackgroundColor(const QColor &color);
    /* Indicator settings */
    QColor getIndicatorStartColor();
    void setIndicatorStartColor(const QColor &color);
    QColor getIndicatorStopColor();
    void setIndicatorStopColor(const QColor &color);
    double getIndicatorRadius();
    void setIndicatorRadius(double radius);
    /* Misc settings */
    quint16 getSelectedDive();
    void setSelectedDive(quint16 diveNumber);
    /* Save / restore from disk */
    void save();
    void restore();
    void loadDefault();

private:
    Settings();

private:
    static Settings* m_instance;
    /* Path settings */
    QPen m_pathPen;
    quint16 m_smoothness;
    PlotStyle m_plotStyle;
    /* Text settings */
    QColor m_textColor;
    QFont  m_textFont;
    /* Text position settings */
    QPointF m_timePosition;
    QPointF m_depthPosition;
    /* Background settings */
    QColor m_backgroundColor;
    /* Indicator settings */
    QColor m_indicatorStartColor;
    QColor m_indicatorStopColor;
    double m_indicatorRadius;
    /* Image settings */
    quint16 m_width;
    quint16 m_height;
    quint16 m_fps;
    /* Misc */
    quint16 m_selectedDive;

signals:
    void settingsChanged();

};

#endif // SETTINGS_H
