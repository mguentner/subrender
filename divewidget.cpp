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

#include "divewidget.h"

DiveWidget::DiveWidget(QWidget *parent) :
    QWidget(parent)
{
    m_imageSet = false;
}

void DiveWidget::setPixmap(const QImage &image)
{
    m_image = image;
    m_imageSet = true;
    update();
}

void DiveWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QImage scaled;
    QBrush grayEven(QColor("#4B4B4B"));
    QBrush grayOdd(QColor("#ECECEC"));
    painter.setPen(Qt::NoPen);
    for (quint16 coloum = 0; coloum <= width()/20; coloum++) {
        for(quint16 row = 0; row <= height()/20; row++) {
            if (row%2 == coloum%2)
                painter.setBrush(grayEven);
            else
                painter.setBrush(grayOdd);
            painter.drawRect(QRect(QPoint(coloum*20, row*20), QPoint((coloum+1)*20,(row+1)*20)));
        }
    }
    if (m_imageSet == false)
        return;
    if (m_image.height() > m_image.width()) {
        scaled = m_image.scaledToHeight(this->height(), Qt::SmoothTransformation);
        painter.drawImage(width()/2 - scaled.width()/2, 0,scaled);
    } else {
       scaled = m_image.scaledToWidth(this->width(), Qt::SmoothTransformation);
       painter.drawImage(0, height()/2 -scaled.height()/2 ,scaled);
    }
}
