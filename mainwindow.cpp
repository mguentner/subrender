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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settings.h"
#include "diverenderworker.h"
#include "diverenderer.h"
#include "rendersettingsdialog.h"
#include "renderprogressdialog.h"

#include <QFileDialog>
#include <QTimer>
#include <QMessageBox>
#include <QColorDialog>
#include <QStyle>
#include <QCommonStyle>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Settings::instance()->restore();
    m_textColorDialog = new QColorDialog(this);
    m_textColorDialog->setOption(QColorDialog::ShowAlphaChannel, true);
    m_textColorDialog->setWindowTitle(tr("Select Text Color"));
    m_textColorDialog->hide();
    m_fontDialog = new QFontDialog(this);
    m_fontDialog->hide();
    m_graphColorDialog = new QColorDialog(this);
    m_graphColorDialog->setOption(QColorDialog::ShowAlphaChannel, true);
    m_graphColorDialog->setWindowTitle(tr("Select Graph Color"));
    m_graphColorDialog->hide();
    m_indicatorStartColorDialog = new QColorDialog(this);
    m_indicatorStartColorDialog->setOption(QColorDialog::ShowAlphaChannel, true);
    m_indicatorStartColorDialog->setWindowTitle(tr("Select Start Color"));
    m_indicatorStartColorDialog->hide();
    m_indicatorStopColorDialog = new QColorDialog(this);
    m_indicatorStopColorDialog->setOption(QColorDialog::ShowAlphaChannel, true);
    m_indicatorStopColorDialog->setWindowTitle(tr("Select Stop Color"));
    m_indicatorStopColorDialog->hide();
    m_backgroundColorDialog = new QColorDialog(this);
    m_backgroundColorDialog->setOption(QColorDialog::ShowAlphaChannel, true);
    m_backgroundColorDialog->setWindowTitle(tr("Select Background Color"));
    m_backgroundColorDialog->hide();
    m_timePositionDialog = new PositionDialog(QRectF(0, 0,
                                                     Settings::instance()->getWidth(),
                                                     Settings::instance()->getHeight()), this);
    m_timePositionDialog->hide();
    m_timePositionDialog->setWindowTitle(tr("Select Time Position"));

    m_depthPositionDialog = new PositionDialog(QRectF(0, 0,
                                                     Settings::instance()->getWidth(),
                                                     Settings::instance()->getHeight()), this);
    m_depthPositionDialog->setWindowTitle(tr("Select Depth Position"));
    m_depthPositionDialog->hide();

    m_diveSelectionDialog = new DiveSelectionDialog(this);
    m_diveSelectionDialog->hide();

    connect(m_graphColorDialog, SIGNAL(currentColorChanged(QColor)),
            this, SLOT(graphColorChanged(QColor)));
    connect(m_textColorDialog, SIGNAL(currentColorChanged(QColor)),
            this, SLOT(textColorChanged(QColor)));
    connect(m_indicatorStartColorDialog, SIGNAL(currentColorChanged(QColor)),
            this, SLOT(indicatorStartColorChanged(QColor)));
    connect(m_indicatorStopColorDialog, SIGNAL(currentColorChanged(QColor)),
            this, SLOT(indicatorStopColorChanged(QColor)));
    connect(m_backgroundColorDialog, SIGNAL(currentColorChanged(QColor)),
            this, SLOT(backgroundColorChanged(QColor)));
    connect(m_fontDialog, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(fontChanged(QFont)));
    connect(m_timePositionDialog, SIGNAL(currentCoordiantesChanged(QPointF)),
            this, SLOT(timePositionChanged(QPointF)));
    connect(m_depthPositionDialog, SIGNAL(currentCoordiantesChanged(QPointF)),
            this, SLOT(depthPositionChanged(QPointF)));
    setupElements();
    updateElements();
}

MainWindow::~MainWindow()
{
    Settings::instance()->save();
    delete m_textColorDialog;
    delete m_fontDialog;
    delete m_backgroundColorDialog;
    delete m_indicatorStartColorDialog;
    delete m_indicatorStopColorDialog;
    delete m_depthPositionDialog;
    delete m_timePositionDialog;
    delete m_graphColorDialog;
    delete m_diveSelectionDialog;
    delete ui;
}

void MainWindow::updateElements()
{
    ui->graphColorButton->setStyleSheet("background-color: "
                                        + Settings::instance()->getPathPen().color().name()
                                        + ";");
    ui->backgroundColorButton->setStyleSheet("background-color: "
                                       + Settings::instance()->getBackgroundColor().name()
                                       + ";");
    ui->indicatorStartColorButton->setStyleSheet("background-color: "
                                       + Settings::instance()->getIndicatorStartColor().name()
                                       + ";");
    ui->indicatorStopColorButton->setStyleSheet("background-color: "
                                       + Settings::instance()->getIndicatorStopColor().name()
                                       + ";");
    ui->textColorButton->setStyleSheet("background-color: "
                                       + Settings::instance()->getTextColor().name()
                                       + ";");
    ui->fontLineEdit->setText(Settings::instance()->getTextFont().family()
                              + ", "
                              + QString::number(Settings::instance()->getTextFont().pointSizeF()));
    /* Be safe and block these two spinboxes */
    ui->graphWidthSpinBox->blockSignals(true);
    ui->radiusSpinBox->blockSignals(true);
    ui->graphWidthSpinBox->setValue(Settings::instance()->getPathPen().widthF());
    ui->radiusSpinBox->setValue(Settings::instance()->getIndicatorRadius());
    ui->graphWidthSpinBox->blockSignals(false);
    ui->radiusSpinBox->blockSignals(false);
    if (DiveManager::instance()->empty()) {
        ui->selectDiveButton->setEnabled(false);
    } else {
        ui->selectDiveButton->setEnabled(true);
        ui->diveLCD->display(Settings::instance()->getSelectedDive());
    }
    if (DiveManager::instance()->exists(Settings::instance()->getSelectedDive())) {
        ui->renderButton->setEnabled(true);
    } else {
        ui->renderButton->setEnabled(false);
    }
}

void MainWindow::setupElements()
{
    QCommonStyle style;
    ui->actionOpen->setIcon(style.standardIcon(QStyle::SP_DialogOpenButton));
    ui->actionDefault_Settings->setIcon(style.standardIcon(QStyle::SP_DialogResetButton));
    ui->actionQuit->setIcon(style.standardIcon(QStyle::SP_MessageBoxCritical));
    ui->selectDiveButton->setIcon(style.standardIcon(QStyle::SP_FileDialogListView));
    ui->actionAbout->setIcon(style.standardIcon(QStyle::SP_MessageBoxInformation));
    this->setWindowIcon(QIcon(":/icons/subrender.png"));
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open subsurface log"), QString(), tr("XML Files (*.xmi, *.xml)"));
    if (filename == "")
        return;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Unable to open %1").arg(filename));
        return;
    } else {
        quint16 imported = DiveManager::instance()->importDives(&file);

        if (imported > 0) {
            connect(Settings::instance(), SIGNAL(settingsChanged()),
                    this , SLOT(updatePreview()));
            QMessageBox::information(this, tr("Import successful"),
                                     tr("%n dive(s) have been imported.\nYou can now select a dive.","", imported));
        } else {
            QMessageBox::warning(this, tr("Import failed"),
                                     tr("No dive has been imported.\nPlease check your file and try again."));
        }
        updateElements();
    }
}


void MainWindow::on_textColorButton_clicked()
{
    m_textColorDialog->setCurrentColor(Settings::instance()->getTextColor());
    m_textColorDialog->show();
}

void MainWindow::textColorChanged(QColor color)
{
    Settings::instance()->setTextColor(color);
    updateElements();
}

void MainWindow::on_fontButton_clicked()
{
    m_fontDialog->setCurrentFont(Settings::instance()->getTextFont());
    m_fontDialog->show();
}

void MainWindow::fontChanged(QFont font)
{
    Settings::instance()->setTextFont(font);
    updateElements();
}

void MainWindow::updatePreview()
{
    if (!DiveManager::instance()->exists(Settings::instance()->getSelectedDive())) {
        QMessageBox::warning(this, tr("Warning"), tr("Please select a dive first"));
        return;
    }
    quint16 width = Settings::instance()->getWidth();
    quint16 height = Settings::instance()->getHeight();
    DiveRenderWorker renderer;
    QImage image(width, height, QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    renderer.render(&image, Settings::instance()->getSelectedDive(),
                    (DiveManager::instance()->getDive(Settings::instance()->getSelectedDive()).getDuration())/2.00*1000);
    ui->widget->setPixmap(image);
}

void MainWindow::on_graphWidthSpinBox_valueChanged(double arg1)
{
    QPen tmp = Settings::instance()->getPathPen();
    tmp.setWidth(arg1);
    Settings::instance()->setPathPen(tmp);
}

void MainWindow::on_graphColorButton_clicked()
{
    m_graphColorDialog->setCurrentColor(Settings::instance()->getPathPen().color());
    m_graphColorDialog->show();
}

void MainWindow::graphColorChanged(QColor color)
{
    QPen tmp = Settings::instance()->getPathPen();
    tmp.setColor(color);
    Settings::instance()->setPathPen(tmp);
    updateElements();
}

void MainWindow::on_indicatorStartColorButton_clicked()
{
    m_indicatorStartColorDialog->setCurrentColor(Settings::instance()->getIndicatorStopColor());
    m_indicatorStartColorDialog->show();
}

void MainWindow::indicatorStartColorChanged(QColor color)
{
    Settings::instance()->setIndicatorStartColor(color);
    updateElements();
}

void MainWindow::on_indicatorStopColorButton_clicked()
{
    m_indicatorStopColorDialog->setCurrentColor(Settings::instance()->getIndicatorStopColor());
    m_indicatorStopColorDialog->show();
}

void MainWindow::indicatorStopColorChanged(QColor color)
{
    Settings::instance()->setIndicatorStopColor(color);
    updateElements();
}

void MainWindow::on_backgroundColorButton_clicked()
{
    m_backgroundColorDialog->setCurrentColor(Settings::instance()->getBackgroundColor());
    m_backgroundColorDialog->show();
}

void MainWindow::backgroundColorChanged(QColor color)
{
    Settings::instance()->setBackgroundColor(color);
    updateElements();
}

void MainWindow::on_renderButton_clicked()
{
    RenderProgressDialog dialog;
    dialog.exec();
}

void MainWindow::on_timeButton_clicked()
{
    m_timePositionDialog->setBounds(QRectF(0, 0,
                                            Settings::instance()->getWidth(),
                                            Settings::instance()->getHeight()));
    m_timePositionDialog->setCurrentCoordinates(Settings::instance()->getTimePosition());
    m_timePositionDialog->show();
}

void MainWindow::timePositionChanged(QPointF position)
{
    Settings::instance()->setTimePosition(position);
}

void MainWindow::on_depthButton_clicked()
{
    m_depthPositionDialog->setBounds(QRectF(0, 0,
                                            Settings::instance()->getWidth(),
                                            Settings::instance()->getHeight()));
    m_depthPositionDialog->setCurrentCoordinates(Settings::instance()->getDepthPosition());
    m_depthPositionDialog->show();
}

void MainWindow::depthPositionChanged(QPointF position)
{
    Settings::instance()->setDepthPosition(position);
}

void MainWindow::on_radiusSpinBox_valueChanged(double arg1)
{
    Settings::instance()->setIndicatorRadius(arg1);
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_selectDiveButton_clicked()
{
    m_diveSelectionDialog->updateModel();
    m_diveSelectionDialog->selectDive(Settings::instance()->getSelectedDive());
    if (m_diveSelectionDialog->exec() == QDialog::Accepted) {
        if (m_diveSelectionDialog->hasSelectedDive()) {
            Settings::instance()->setSelectedDive(m_diveSelectionDialog->getSelectedDive());
            updateElements();
            updatePreview();
        }
    }
}

void MainWindow::on_actionRender_Settings_triggered()
{
    RenderSettingsDialog dialog;
    dialog.exec();
}

void MainWindow::on_actionDefault_Settings_triggered()
{
    if(QMessageBox::question(this,
                             tr("Restore default settings"),
                             tr("This will restore the default settings. All current settings will be lost!"),
                             QMessageBox::RestoreDefaults | QMessageBox::No ) == QMessageBox::RestoreDefaults) {
        Settings::instance()->loadDefault();
        updateElements();
    }
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionAbout_triggered()
{
    QString head;
    QString text;
    text = trUtf8("Copyright 2012<br /> Maximilian Güntner &lt;maximilian.guentner@gmail.com&gt;<br />Released under the terms of the GPLv3.");
    head = tr("<h2><b>Subrender %1</b></h2>").arg(QString::number(SUBRENDER_VERSION, 'f', 1));
    QMessageBox::about(this, tr("About subrender"), head + text );
}
