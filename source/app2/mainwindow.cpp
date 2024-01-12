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

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent):
    QWidget{parent},
    ui{new Ui::MainWindow},
    m_board{new Board{this}},
    m_warriorPanel{new WarriorPanel{this}},
    m_dicePanel{new DicePanel{this}},
    m_log{new Log{this}},
    m_controller{new Controller{this}}
{
    Q_ASSERT(m_board != nullptr);
    Q_ASSERT(m_warriorPanel != nullptr);
    Q_ASSERT(m_dicePanel != nullptr);
    Q_ASSERT(m_log != nullptr);

    ui->setupUi(this);

    m_board->setGeometry(10, 10, 650, 650);
    m_warriorPanel->setGeometry(680, 250, 3 * 78, 2 * 78);
    m_dicePanel->setGeometry(680, 420, 3 * 78, 78);
    m_log->setGeometry(680, 10, 331, 221);

    init();
    start();
}

void MainWindow::init()
{
    Q_ASSERT(m_board != nullptr);
    Q_ASSERT(m_warriorPanel != nullptr);
    Q_ASSERT(m_dicePanel != nullptr);
    Q_ASSERT(m_log != nullptr);
    Q_ASSERT(m_controller != nullptr);
    Q_ASSERT(ui->pushButton_submitDice != nullptr);

    QTimer::singleShot(0, this, &MainWindow::subInit);
}

void MainWindow::start()
{
    Q_ASSERT(m_controller != nullptr);

    QTimer::singleShot(0, [&]() { m_controller->start(); });
}

void MainWindow::subInit()
{
    Q_ASSERT(m_board != nullptr);
    Q_ASSERT(m_warriorPanel != nullptr);
    Q_ASSERT(m_dicePanel != nullptr);
    Q_ASSERT(m_log != nullptr);
    Q_ASSERT(m_controller != nullptr);

    m_board->init();
    m_warriorPanel->init();
    m_dicePanel->init();
    m_log->init();
    m_controller->init();

    QObject::connect(m_warriorPanel, &WarriorPanel::drop,
                     m_dicePanel, &DicePanel::drop);

    QObject::connect(m_warriorPanel, &WarriorPanel::drop,
                     m_board, &Board::drop);

    QObject::connect(m_controller, &Controller::log,
                     m_log, &Log::append);

    QObject::connect(m_controller, &Controller::toss,
                     m_dicePanel, &DicePanel::set);

    QObject::connect(m_dicePanel, &DicePanel::submitDice,
                     m_controller, &Controller::submitDice);

    QObject::connect(
        ui->pushButton_submitDice, &QPushButton::clicked,
        m_dicePanel, &DicePanel::submit
                    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    /*auto geom{m_board->geometry()};
    geom.setWidth(width() / 1.8);
    geom.setHeight(height() / 1.5);
    m_board->setGeometry(geom);*/
}
