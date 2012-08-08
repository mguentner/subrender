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

#include "renderprogressdialog.h"
#include "ui_renderprogressdialog.h"

#include "settings.h"
#include "rendersettingsdialog.h"
#include "diverenderer.h"

#include <QTimer>
#include <QFileDialog>
#include <QThread>
#include <QMessageBox>
#include <QStyle>
#include <QCommonStyle>

RenderProgressDialog::RenderProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenderProgressDialog)
{
    ui->setupUi(this);
    connect(Settings::instance(), SIGNAL(settingsChanged()), this, SLOT(updateSettings()));
    connect(this, SIGNAL(pathChanged(QString)), this, SLOT(processPathChange(QString)));
    connect(ui->pathLine, SIGNAL(textEdited(QString)), this, SLOT(processPathChange(QString)));
    ui->renderProcessButton->setEnabled(false);
    ui->abortRenderButton->setEnabled(false);
    ui->notificationLabel->setVisible(true);
    QTimer::singleShot(0, this, SLOT(updateSettings()));
    QCommonStyle style;
    ui->selectPathButton->setIcon(style.standardIcon(QStyle::SP_DirOpenIcon));
}

RenderProgressDialog::~RenderProgressDialog()
{
    delete ui;
}


void RenderProgressDialog::on_changeSettingsButton_clicked()
{
    RenderSettingsDialog dialog;
    dialog.exec();

}

void RenderProgressDialog::updateRenderProgress(quint32 frame, quint32 totalFrames)
{
    ui->progressBar->setMaximum(totalFrames);
    ui->progressBar->setValue(frame);
}


void RenderProgressDialog::updateSettings()
{
    QString settingsString;
    settingsString = tr("Width: %1 px, Height: %2 px\n FPS: %3")
            .arg(QString::number(Settings::instance()->getWidth()))
            .arg(QString::number(Settings::instance()->getHeight()))
            .arg(QString::number(Settings::instance()->getFps()));
    ui->currentSettingsValues->setText(settingsString);
}

void RenderProgressDialog::on_renderProcessButton_clicked()
{
    QThread *thread = new QThread;
    DiveRenderer *renderer = new DiveRenderer;
    renderer->setData(m_path, Settings::instance()->getSelectedDive());
    renderer->moveToThread(thread);
    connect(thread, SIGNAL(started()), renderer, SLOT(render()));
    connect(renderer, SIGNAL(finished(bool)), thread, SLOT(quit()));
    connect(renderer, SIGNAL(finished(bool)), renderer, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(renderer, SIGNAL(renderProgress(quint32,quint32)),
            this, SLOT(updateRenderProgress(quint32,quint32)));
    connect(renderer, SIGNAL(finished(bool)), this, SLOT(renderingDone(bool)));
    connect(ui->abortRenderButton, SIGNAL(clicked()), renderer, SLOT(abort()), Qt::DirectConnection);
    /* Disable all buttons */
    ui->pathLine->setEnabled(false);
    ui->changeSettingsButton->setEnabled(false);
    ui->selectPathButton->setEnabled(false);
    ui->renderProcessButton->setEnabled(false);
    ui->buttonBox->setEnabled(false);
    ui->renderProcessButton->setText(tr("Rendering..."));
    ui->abortRenderButton->setEnabled(true);
    thread->start();
}

void RenderProgressDialog::on_selectPathButton_clicked()
{
    emit pathChanged(QFileDialog::getExistingDirectory(this, tr("Choose the target directory")));
}

void RenderProgressDialog::processPathChange(QString path)
{
    QPalette imageLinePalette = QApplication::palette();
    QFileInfo imageFileInfo(path);
    if (!imageFileInfo.exists() || !imageFileInfo.isDir() || !imageFileInfo.isReadable()) {
        imageLinePalette.setColor(QPalette::WindowText,Qt::red);
        imageLinePalette.setColor(QPalette::Text,Qt::red);
        ui->renderProcessButton->setEnabled(false);
        ui->notificationLabel->setVisible(true);
    } else {
        ui->renderProcessButton->setEnabled(true);
        ui->notificationLabel->setVisible(false);
    }
    ui->pathLine->setText(path);
    ui->pathLine->setPalette(imageLinePalette);
    m_path = path;
}

void RenderProgressDialog::renderingDone(bool error)
{
    disconnect(ui->abortRenderButton, SIGNAL(clicked()), 0 ,0);
    ui->pathLine->setEnabled(true);
    ui->changeSettingsButton->setEnabled(true);
    ui->selectPathButton->setEnabled(true);
    ui->renderProcessButton->setEnabled(true);
    ui->buttonBox->setEnabled(true);
    ui->abortRenderButton->setEnabled(false);
    ui->renderProcessButton->setText(tr("Start Render Process"));
    updateRenderProgress(0,100);
    if (error)
        QMessageBox::warning(this, tr("Rendering done"), tr("An error occured during the process\nor the process has been aborted."));
    else
        QMessageBox::information(this, tr("Rendering done"), tr("The render process has been completed."));
}
