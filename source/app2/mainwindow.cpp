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
#include "grid.h"

MainWindow::MainWindow(QWidget *parent):
    QWidget{parent},
    ui{new Ui::MainWindow}
{
    ui->setupUi(this);

    const auto grid = new Grid{this};
    grid->setGeometry(10, 10, 400, 400);
    grid->init(3, 3);
}

MainWindow::~MainWindow()
{
    delete ui;
}
