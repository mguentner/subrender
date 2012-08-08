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

#ifndef DIVESELECTIONDIALOG_H
#define DIVESELECTIONDIALOG_H

#include <QDialog>
#include <QtGui>

#include <divemanager.h>

namespace Ui {
class DiveSelectionDialog;
}

class DiveSelectionDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DiveSelectionDialog(QWidget *parent = 0);
    void updateModel();
    void selectDive(quint16 dive);
    bool hasSelectedDive();
    quint16 getSelectedDive();
    ~DiveSelectionDialog();
    
private:
    Ui::DiveSelectionDialog *ui;
    QStandardItemModel *m_diveModel;
};

#endif // DIVESELECTIONDIALOG_H
