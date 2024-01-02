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
#include "board.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent):
    QWidget{parent},
    ui{new Ui::MainWindow},
    board{new Board{this}}
{
    ui->setupUi(this);

    board->setGeometry(10, 10, 500, 500);

    QTimer::singleShot(100, [&](){
        board->init();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    auto geom{board->geometry()};
    geom.setWidth(width() / 1.8);
    geom.setHeight(height() / 1.5);
    board->setGeometry(geom);
}
