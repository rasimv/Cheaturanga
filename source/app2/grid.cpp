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

#include "grid.h"
#include "square.h"

Grid::Grid(QWidget *parent):
    QWidget{parent},
    m_layout{new QGridLayout{this}}
{
    m_layout->setContentsMargins({});
    m_layout->setHorizontalSpacing(0);
    m_layout->setVerticalSpacing(0);
}

void Grid::init(int columns, int rows)
{
    Q_ASSERT(m_layout != nullptr);
    Q_ASSERT(columns > 0 && rows > 0);
    Q_ASSERT(m_layout->count() == 0);

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
        {
            const auto square = new Square{this};
            square->init(j + i * columns);

            connect(square, &Square::down, this, &Grid::onDown);

            m_layout->addWidget(square, i, j);
        }
}

void Grid::onDown(const QByteArray &d)
{
    QByteArray l{d};
    QDataStream ds{&l, QIODeviceBase::ReadOnly};
    int id = -1;
    Square::DownCode code;
    QPointF p;
    ds >> id >> code >> p;

    qDebug() << p.x() << " | " << p.y();
}
