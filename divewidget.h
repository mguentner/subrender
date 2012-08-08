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

#ifndef DIVEWIDGET_H
#define DIVEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QImage>

class DiveWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DiveWidget(QWidget *parent = 0);
    void setPixmap(const QImage &image);
signals:
    
public slots:
    void paintEvent(QPaintEvent *);
private:
    QImage m_image;
    bool m_imageSet;
};

#endif // DIVEWIDGET_H
