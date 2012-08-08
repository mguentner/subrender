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

#include "diveselectiondialog.h"
#include "ui_diveselectiondialog.h"

DiveSelectionDialog::DiveSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiveSelectionDialog)
{
    ui->setupUi(this);
    m_diveModel = NULL;
}

DiveSelectionDialog::~DiveSelectionDialog()
{
    delete ui;
}

void DiveSelectionDialog::updateModel()
{
    if (m_diveModel != NULL)
        delete m_diveModel;
    QStringList header;
    quint16 row = 0;
    m_diveModel = new QStandardItemModel(DiveManager::instance()->size(), 5, this);
    header << tr("Dive Number") << tr("Date") << tr("Time") << tr("Duration") << tr("Max Depth");
    m_diveModel->setHorizontalHeaderLabels(header);
    DiveManager::instance()->toFront();
    while(DiveManager::instance()->hasNext()) {
        Dive tmp = DiveManager::instance()->next();
        QModelIndex index = m_diveModel->index(row, 0);
        m_diveModel->setData(index, tmp.getDiveNumber());
        index = m_diveModel->index(row, 1);
        m_diveModel->setData(index, tmp.getDateTime().date());
        index = m_diveModel->index(row, 2);
        m_diveModel->setData(index, tmp.getDateTime().time());
        index = m_diveModel->index(row, 3);
        QString timeSeconds = QString::number(tmp.getDuration()%60);
        QString timeMinutes = QString::number(tmp.getDuration()/60);
        if (tmp.getDuration()/60 < 10)
            timeMinutes = "0" + timeMinutes;
        if (tmp.getDuration()%60 < 10)
            timeSeconds = "0" + timeSeconds;
        m_diveModel->setData(index, timeMinutes + ":" + timeSeconds);
        index = m_diveModel->index(row, 4);
        m_diveModel->setData(index, QString::number(tmp.getMaxDepth(), 'f', 2) + " m");
        row++;
    }
    ui->tableView->setModel(m_diveModel);
}

void DiveSelectionDialog::selectDive(quint16 dive)
{
    quint16 row;
    QModelIndex index;
    for(row = 0; row < m_diveModel->rowCount(); row++) {
        index = m_diveModel->index(row, 0);
        if (m_diveModel->data(index).toUInt() == dive) {
            ui->tableView->selectionModel()->select(index, QItemSelectionModel::Select);
            ui->tableView->setCurrentIndex(index);
            ui->tableView->setFocus();
            return;
        }
    }
}

bool DiveSelectionDialog::hasSelectedDive()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    if (indexes.count() > 0)
        return true;
    else
        return false;
}

quint16 DiveSelectionDialog::getSelectedDive()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    if (indexes.count() > 0) {
        QModelIndex index = m_diveModel->index(indexes.at(0).row(), 0);
        return m_diveModel->data(index).toInt();
    } else {
        qDebug() << tr("Nothing has been selected");
        return 0;
    }
}

