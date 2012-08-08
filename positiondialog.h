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

#ifndef POSITIONDIALOG_H
#define POSITIONDIALOG_H

#include <QDialog>
#include <QPointF>

namespace Ui {
class PositionDialog;
}

class PositionDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PositionDialog(const QRectF &bounds, QWidget *parent = 0);
    ~PositionDialog();

    void setCurrentCoordinates(const QPointF &coordinates);
    void setBounds(const QRectF &bounds);
    QPointF getCurrentCoordinates();

signals:
    void currentCoordiantesChanged(QPointF);

private slots:
    void updateElements();

    void on_upButton_clicked();

    void on_leftButton_clicked();

    void on_rightButton_clicked();

    void on_downButton_clicked();

    void on_centerButton_clicked();

    void on_xSpinBox_valueChanged(double arg1);

    void on_ySpinBox_valueChanged(double arg1);

private:
    Ui::PositionDialog *ui;
    QPointF m_coordinates;
    QRectF m_bounds;
};

#endif // POSITIONDIALOG_H
