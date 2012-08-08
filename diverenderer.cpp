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

#include "diverenderer.h"
#include "diverenderworker.h"
#include "settings.h"

#include <QImage>

DiveRenderer::DiveRenderer(QObject *parent) : QObject(parent)
{
}

void DiveRenderer::setData(const QString &path, const quint16 &dive)
{
    m_path = path;
    m_dive = dive;
}

void DiveRenderer::render()
{
    m_abort = false;
    quint16 fps = Settings::instance()->getFps();
    quint16 width = Settings::instance()->getWidth();
    quint16 height = Settings::instance()->getHeight();
    quint32 frame = 0;
    quint32 totalFrames = DiveManager::instance()->getDive(m_dive).getDuration()*fps;
    DiveRenderWorker worker;
    for (quint32 i = 0; i < DiveManager::instance()->getDive(m_dive).getDuration()*1000; i = i+1000/fps) {
        if (m_abort == true) {
            emit finished(true);
            return;
        }
        QImage image(width, height, QImage::Format_ARGB32);
        image.fill(Qt::transparent);
        worker.render(&image, m_dive, i);
        image.save(m_path + "/subrender-dive" + QString::number(m_dive) + "-frame-" + QString::number(frame) + ".png", "PNG");
        emit renderProgress(frame, totalFrames);
        frame++;
    }
    emit finished(false);
}

void DiveRenderer::abort()
{
    m_abort = true;
}



