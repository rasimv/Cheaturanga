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

            square->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            square->init(j + i * columns);

            connect(square, &Square::down, this, &Grid::onDown);

            m_layout->addWidget(square, i, j);
        }
}

int Grid::columnCount() const
{
    Q_ASSERT(m_layout != nullptr);

    return m_layout->columnCount();
}

int Grid::rowCount() const
{
    Q_ASSERT(m_layout != nullptr);

    return m_layout->rowCount();
}

Square *Grid::square(int col, int row)
{
    Q_ASSERT(m_layout != nullptr);
    Q_ASSERT(col < m_layout->columnCount() && row < m_layout->rowCount());

    const auto w = m_layout->itemAtPosition(row, col)->widget();
    return dynamic_cast<Square *>(w);
}

void Grid::flip()
{
    Q_ASSERT(m_layout != nullptr);

    for (int i = 0; i < m_layout->rowCount() / 2; ++i)
        for (int j = 0; j < m_layout->columnCount(); ++j)
        {
            const auto item1 = m_layout->itemAtPosition(i, j),
                        item2 = m_layout->itemAtPosition(
                           m_layout->rowCount() - i - 1,
                           m_layout->columnCount() - j - 1);

            Q_ASSERT(item1 != nullptr && item2 != nullptr);

            m_layout->removeItem(item1);
            m_layout->removeItem(item2);

            m_layout->addItem(item2, i, j);
            m_layout->addItem(item1, m_layout->rowCount() - i - 1,
                                        m_layout->columnCount() - j - 1);
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
