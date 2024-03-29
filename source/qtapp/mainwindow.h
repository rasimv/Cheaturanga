// Cheaturanga. A simple dice-chess program
// Copyright (C) 2023  Rasim Valiullin

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// rasimvaliullin@hotmail.com

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "board.h"
#include "warriorpanel.h"
#include "dicepanel.h"
#include "log.h"
#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow: public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init();
    void start();
    void subInit();

    void resizeEvent(QResizeEvent *event);

    Ui::MainWindow *ui = nullptr;

    Board *m_board = nullptr;
    WarriorPanel *m_warriorPanel = nullptr;
    DicePanel *m_dicePanel = nullptr;
    Log *m_log = nullptr;

    Controller *m_controller = nullptr;
};

#endif // MAINWINDOW_H
