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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QFontDialog>

#include <positiondialog.h>
#include <diveselectiondialog.h>
#include <divemanager.h>

#define SUBRENDER_VERSION 0.2

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void updateElements();
    void setupElements();

private slots:
    void on_actionOpen_triggered();


    void on_textColorButton_clicked();

    void textColorChanged(QColor color);

    void on_fontButton_clicked();

    void fontChanged(QFont font);

    void updatePreview();

    void on_graphWidthSpinBox_valueChanged(double arg1);

    void on_graphColorButton_clicked();

    void graphColorChanged(QColor color);

    void on_indicatorStartColorButton_clicked();

    void indicatorStartColorChanged(QColor color);

    void on_indicatorStopColorButton_clicked();

    void indicatorStopColorChanged(QColor color);

    void on_backgroundColorButton_clicked();

    void backgroundColorChanged(QColor color);

    void on_renderButton_clicked();

    void on_timeButton_clicked();

    void timePositionChanged(QPointF position);

    void on_depthButton_clicked();

    void depthPositionChanged(QPointF position);

    void on_radiusSpinBox_valueChanged(double arg1);

    void on_actionQuit_triggered();

    void on_selectDiveButton_clicked();

    void on_actionRender_Settings_triggered();

    void on_actionDefault_Settings_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionAbout_triggered();

    void on_smoothnessSlider_sliderReleased();

    void on_plotStyleComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    /* Dialogs */
    QColorDialog *m_textColorDialog;
    QFontDialog *m_fontDialog;
    QColorDialog *m_graphColorDialog;
    QColorDialog *m_indicatorStartColorDialog;
    QColorDialog *m_indicatorStopColorDialog;
    QColorDialog *m_backgroundColorDialog;
    PositionDialog *m_timePositionDialog;
    PositionDialog *m_depthPositionDialog;
    DiveSelectionDialog *m_diveSelectionDialog;
};

#endif // MAINWINDOW_H
