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

#include "diverenderworker.h"
#include "settings.h"
#include "geometry.h"

DiveRenderWorker::DiveRenderWorker()
{
}

void DiveRenderWorker::render(QImage *target, quint16 dive, quint64 time)
{
    QPainter painter(target);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(QRectF(0,0,target->width(),target->height()), Settings::instance()->getBackgroundColor());
    if (DiveManager::instance()->exists(dive) == false)
        return;
    Dive tmpDive = DiveManager::instance()->getDive(dive);
    QPointF topLeftBorder;
    if (Settings::instance()->getPlotStyle() == Settings::Vertical)
        topLeftBorder = QPointF(target->width()/2, target->height()*0.05);
    else if(Settings::instance()->getPlotStyle() == Settings::HorizontalVertical)
        topLeftBorder = QPointF(target->width()*0.05, target->height()*0.05);
    QPointF bottomRightBorder = QPointF(target->width()*0.9, target->height()*0.9);
    double pixelPerSecond = 0;
    if (Settings::instance()->getPlotStyle() == Settings::Vertical)
        pixelPerSecond = 0;
    else if(Settings::instance()->getPlotStyle() == Settings::HorizontalVertical)
        pixelPerSecond = bottomRightBorder.x() / tmpDive.getSample(tmpDive.size()-1).getTimeSeconds();
    double pixelPerMeter = target->height()*0.9 / tmpDive.getMaxDepth();
    /* Begin dive path */
    QVector<QPointF> divePoints;
    divePoints.append(topLeftBorder);
    for (quint16 i = 0; i <= tmpDive.getDuration(); i++) {
        Sample tmpSample = tmpDive.getSampleByTime(i*1000);
        divePoints.append(QPoint(topLeftBorder.x()+i*pixelPerSecond, topLeftBorder.y()+tmpSample.getDepth()*pixelPerMeter));
    }
    double smoothness = Settings::instance()->getSmoothness() / 100.00;
    QPainterPath divePath;
    divePath.moveTo(divePoints.at(0));
    if (Settings::instance()->getPlotStyle() == Settings::Vertical)
        divePath.lineTo(QPointF(topLeftBorder.x(),topLeftBorder.y()+bottomRightBorder.y()));
    else if(Settings::instance()->getPlotStyle() == Settings::HorizontalVertical) {
        for (quint16 i = 2; i < divePoints.size(); i++) {
            QPointF mid1 = middle(divePoints.at(i-2), divePoints.at(i-1));
            QPointF mid2 = middle(divePoints.at(i-1), divePoints.at(i));
            QPointF mid3;
            if (i == divePoints.size()-1)
                mid3 = middle(divePoints.at(i), QPointF(1.25*divePoints.at(i).x(), divePoints.at(i).y()));
            else
                mid3 = middle(divePoints.at(i), divePoints.at(i+1));

            double len1 = length(divePoints.at(i-2), divePoints.at(i-1));
            double len2 = length(divePoints.at(i-1), divePoints.at(i));
            double len3;
            if (i == divePoints.size()-1)
                len3 = length(divePoints.at(i), QPointF(1.25*divePoints.at(i).x(), divePoints.at(i).y()));
            else
                len3 = length(divePoints.at(i), divePoints.at(i+1));

            double k1 = len1 / (len1 + len2);
            double k2 = len2 / (len2 + len3);

            QPointF controlMid1 = mid1 + (mid2 - mid1) * k1;
            QPointF controlMid2 = mid2 + (mid3 - mid2) * k2;

            QPointF controlPoint1 = controlMid1 + (mid2 - controlMid1) * smoothness + divePoints.at(i-1) - controlMid1;
            QPointF controlPoint2 = controlMid2 + (mid2 - controlMid2) * smoothness + divePoints.at(i) - controlMid2;
            divePath.cubicTo(controlPoint1, controlPoint2, divePoints.at(i));
        }
    }
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Settings::instance()->getPathPen());
    painter.drawPath(divePath);
    /* End dive path */
    /* Begin position marker */
    Sample tmpSample = tmpDive.getSampleByTime(time);
    double radius = Settings::instance()->getIndicatorRadius();
    QPointF center = QPointF(topLeftBorder.x()+time/1000.00*pixelPerSecond,
                             topLeftBorder.y()+tmpSample.getDepth()*pixelPerMeter);
    QRadialGradient radialGradient(center, radius);
    radialGradient.setColorAt(0, Settings::instance()->getIndicatorStartColor());
    radialGradient.setColorAt(1, Settings::instance()->getIndicatorStopColor());
    painter.setPen(Qt::NoPen);
    painter.setBrush(radialGradient);
    painter.drawEllipse(center, radius, radius);
    /* End position marker */
    /* Begin text */
    painter.setFont(Settings::instance()->getTextFont());
    painter.setPen(Settings::instance()->getTextColor());
    painter.drawText(Settings::instance()->getDepthPosition(), QString::number(tmpSample.getDepth(), 'f', 2));

    QFontMetrics fm = painter.fontMetrics();
    double offset = fm.width("00,00 ");
    painter.drawText(Settings::instance()->getDepthPosition() + QPointF(offset, 0), "m");
    QString timeSeconds = QString::number((time%60000)/1000);
    QString timeMinutes = QString::number(time/60000);
    if (time/60000 < 10)
        timeMinutes = "0" + timeMinutes;
    if ((time%60000)/1000 < 10)
        timeSeconds = "0" + timeSeconds;
    painter.drawText(Settings::instance()->getTimePosition(), timeMinutes + ":" + timeSeconds);
    /* End text */

}
