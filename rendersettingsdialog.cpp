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

#include "rendersettingsdialog.h"
#include "ui_rendersettingsdialog.h"

RenderSettingsDialog::RenderSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenderSettingsDialog)
{
    ui->setupUi(this);
    updateSpinBoxes();
}

RenderSettingsDialog::~RenderSettingsDialog()
{
    delete ui;
}

void RenderSettingsDialog::updateSpinBoxes()
{
    ui->widthSpinBox->blockSignals(true);
    ui->heightSpinBox->blockSignals(true);
    ui->widthSpinBox->blockSignals(true);
    ui->widthSpinBox->setValue(Settings::instance()->getWidth());
    ui->heightSpinBox->setValue(Settings::instance()->getHeight());
    ui->fpsSpinBox->setValue(Settings::instance()->getFps());
    ui->widthSpinBox->blockSignals(false);
    ui->heightSpinBox->blockSignals(false);
    ui->widthSpinBox->blockSignals(false);
}

void RenderSettingsDialog::on_widthSpinBox_valueChanged(int arg1)
{
    Settings::instance()->setWidth(arg1);
}

void RenderSettingsDialog::on_heightSpinBox_valueChanged(int arg1)
{
    Settings::instance()->setHeight(arg1);
}

void RenderSettingsDialog::on_fpsSpinBox_valueChanged(int arg1)
{
    Settings::instance()->setFps(arg1);
}
