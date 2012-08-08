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

#ifndef RENDERPROGRESSDIALOG_H
#define RENDERPROGRESSDIALOG_H

#include <QDialog>

namespace Ui {
class RenderProgressDialog;
}

class RenderProgressDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit RenderProgressDialog(QWidget *parent = 0);
    ~RenderProgressDialog(); 

private slots:
    void on_changeSettingsButton_clicked();

    void updateSettings();

    void updateRenderProgress(quint32 frame, quint32 totalFrames);

    void on_renderProcessButton_clicked();

    void on_selectPathButton_clicked();

    void processPathChange(QString path);

    void renderingDone(bool error);

signals:
    void pathChanged(QString path);

private:
    Ui::RenderProgressDialog *ui;
    QString m_path;
};

#endif // RENDERPROGRESSDIALOG_H
