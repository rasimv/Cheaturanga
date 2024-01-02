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

#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <QGridLayout>
#include "square.h"

class Grid: public QWidget
{
    Q_OBJECT

public:
    Grid(QWidget *parent = nullptr);

    void init(int columns, int rows);

    int columnCount() const;
    int rowCount() const;

    Square *square(int col, int row);

public slots:
    void flip();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Square *squareByPosition(const QPointF &global, int *column = nullptr, int *row = nullptr);

    QGridLayout *m_layout = nullptr;
    Square *m_dragged = nullptr;

    Square *m_source = nullptr;
};

#endif // GRID_H
