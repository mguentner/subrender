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

#include "positiondialog.h"
#include "ui_positiondialog.h"

#include <QStyle>
#include <QCommonStyle>

PositionDialog::PositionDialog(const QRectF &bounds, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PositionDialog),
    m_bounds(bounds)
{
    ui->setupUi(this);
    connect(this, SIGNAL(currentCoordiantesChanged(QPointF)), this, SLOT(updateElements()));
    QCommonStyle style;
    ui->upButton->setIcon(style.standardIcon(QStyle::SP_ArrowUp));
    ui->downButton->setIcon(style.standardIcon(QStyle::SP_ArrowDown));
    ui->leftButton->setIcon(style.standardIcon(QStyle::SP_ArrowLeft));
    ui->rightButton->setIcon(style.standardIcon(QStyle::SP_ArrowRight));

}

PositionDialog::~PositionDialog()
{
    delete ui;
}

void PositionDialog::setCurrentCoordinates(const QPointF &coordinates)
{
    m_coordinates = coordinates;
    emit currentCoordiantesChanged(m_coordinates);
}

void PositionDialog::setBounds(const QRectF &bounds)
{
    m_bounds = bounds;
    ui->ySpinBox->setRange(m_bounds.top(), m_bounds.bottom());
    ui->xSpinBox->setRange(m_bounds.left(), m_bounds.right());
}

QPointF PositionDialog::getCurrentCoordinates()
{
    return m_coordinates;
}

void PositionDialog::on_upButton_clicked()
{
    if (m_bounds.contains(m_coordinates.x(), m_coordinates.y()-1)) {
        m_coordinates.setY(m_coordinates.y()-1);
        emit currentCoordiantesChanged(m_coordinates);
    }
}

void PositionDialog::on_leftButton_clicked()
{
    if (m_bounds.contains(m_coordinates.x()-1, m_coordinates.y())) {
        m_coordinates.setX(m_coordinates.x()-1);
        emit currentCoordiantesChanged(m_coordinates);
    }
}

void PositionDialog::on_rightButton_clicked()
{
    if (m_bounds.contains(m_coordinates.x()+1, m_coordinates.y())) {
        m_coordinates.setX(m_coordinates.x()+1);
        emit currentCoordiantesChanged(m_coordinates);
    }
}

void PositionDialog::on_downButton_clicked()
{
    if (m_bounds.contains(m_coordinates.x(), m_coordinates.y()+1)) {
        m_coordinates.setY(m_coordinates.y()+1);
        emit currentCoordiantesChanged(m_coordinates);
    }
}

void PositionDialog::on_centerButton_clicked()
{
    m_coordinates.setX(m_bounds.left()+(m_bounds.right()-m_bounds.left())/2);
    m_coordinates.setY(m_bounds.top()+(m_bounds.bottom()-m_bounds.top())/2);
    emit currentCoordiantesChanged(m_coordinates);
}

void PositionDialog::on_xSpinBox_valueChanged(double arg1)
{
    if (m_bounds.contains(arg1, m_coordinates.y())) {
        m_coordinates.setX(arg1);
        emit currentCoordiantesChanged(m_coordinates);
    }
}

void PositionDialog::on_ySpinBox_valueChanged(double arg1)
{
    if (m_bounds.contains(m_coordinates.x(), arg1)) {
        m_coordinates.setY(arg1);
        emit currentCoordiantesChanged(m_coordinates);
    }
}

void PositionDialog::updateElements()
{
    ui->xSpinBox->blockSignals(true);
    ui->ySpinBox->blockSignals(true);
    ui->xSpinBox->setValue(m_coordinates.x());
    ui->ySpinBox->setValue(m_coordinates.y());
    ui->xSpinBox->blockSignals(false);
    ui->ySpinBox->blockSignals(false);
}
