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
    m_dicePanel{new DicePanel{this}}
{
    Q_ASSERT(m_board != nullptr);
    Q_ASSERT(m_warriorPanel != nullptr && m_dicePanel != nullptr);

    ui->setupUi(this);

    m_board->setGeometry(10, 10, 650, 650);
    m_warriorPanel->setGeometry(680, 250, 3 * 78, 2 * 78);
    m_dicePanel->setGeometry(680, 420, 3 * 78, 78);

    QTimer::singleShot(100, [&](){
        m_board->init();
        m_warriorPanel->init();
        m_dicePanel->init();

        QObject::connect(m_warriorPanel, &WarriorPanel::dropped,
                         m_dicePanel, &DicePanel::onDropped);

        QObject::connect(m_warriorPanel, &WarriorPanel::dropped,
                         m_board, &Board::onDropped);
    });
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
