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

#ifndef RENDERSETTINGSDIALOG_H
#define RENDERSETTINGSDIALOG_H

#include "settings.h"

#include <QDialog>

namespace Ui {
class RenderSettingsDialog;
}

class RenderSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit RenderSettingsDialog(QWidget *parent = 0);
    ~RenderSettingsDialog();
    void updateSpinBoxes();

private slots:
    void on_widthSpinBox_valueChanged(int arg1);

    void on_heightSpinBox_valueChanged(int arg1);

    void on_fpsSpinBox_valueChanged(int arg1);

private:
    Ui::RenderSettingsDialog *ui;
};

#endif // RENDERSETTINGSDIALOG_H
