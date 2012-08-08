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
    double pixelPerSecond = target->width()*0.9 / tmpDive.getSample(tmpDive.size()-1).getTimeSeconds();
    double pixelPerMeter = target->height()*0.9 / tmpDive.getMaxDepth();
    /* Begin dive path */
    QVector<QLineF> divePath;
    QPointF lastPoint(target->width()*0.05, target->height()*0.05);
    for (quint16 i = 0; i < tmpDive.getDuration(); i++) {
        Sample tmpSample = tmpDive.getSampleByTime(i*1000);
        QPointF newPoint(target->width()*0.05+i*pixelPerSecond, target->height()*0.05+tmpSample.getDepth()*pixelPerMeter);
        divePath.append(QLineF(lastPoint,newPoint));
        lastPoint = newPoint;
    }
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Settings::instance()->getPathPen());
    painter.drawLines(divePath);
    /* End dive path */
    /* Begin position marker */
    Sample tmpSample = tmpDive.getSampleByTime(time);
    double radius = Settings::instance()->getIndicatorRadius();
    QPointF center = QPointF(target->width()*0.05+time/1000.00*pixelPerSecond,
                             target->height()*0.05+tmpSample.getDepth()*pixelPerMeter);
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
