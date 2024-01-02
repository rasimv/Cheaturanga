// Cheaturanga. A simple dice-chess program
// Copyright (C) 2024  Rasim Valiullin

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

#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QGridLayout>
#include "grid.h"
#include "labels.h"

class Board: public QWidget
{
    Q_OBJECT

public:
    Board(QWidget *parent = nullptr);

    void init();

private:
    void setupGrid();

    QGridLayout *m_layout = nullptr;
    Grid *m_grid = nullptr;
    Labels *m_hor = nullptr, *m_vert = nullptr;
};

#endif // BOARD_H
