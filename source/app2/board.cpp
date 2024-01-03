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

#include "board.h"

Board::Board(QWidget *parent):
    QWidget{parent},
    m_layout{new QGridLayout{this}},
    m_grid{new Grid{this}},
    m_hor{new Labels{this}}, m_vert{new Labels{this}},
    m_flip{new QCheckBox{this}}
{
    Q_ASSERT(m_layout != nullptr && m_grid != nullptr);
    Q_ASSERT(m_hor != nullptr && m_hor != nullptr);

    m_layout->setContentsMargins({});
    m_layout->setVerticalSpacing(m_layout->verticalSpacing() / 2.2);

    m_grid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_hor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_vert->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    m_flip->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    m_flip->setToolTip("Flip");
    m_flip->setEnabled(false);

    m_layout->addWidget(m_grid, 0, 0);
    m_layout->addWidget(m_vert, 0, 1);
    m_layout->addWidget(m_hor, 1, 0);
    m_layout->addWidget(m_flip, 1, 1);
}

void Board::init()
{
    Q_ASSERT(m_hor != nullptr && m_vert != nullptr);
    Q_ASSERT(m_grid != nullptr);
    Q_ASSERT(m_flip != nullptr);

    m_hor->init(Qt::Horizontal);
    m_vert->init(Qt::Vertical);
    setupGrid();

    m_flip->setEnabled(true);
    QObject::connect(m_flip, &QCheckBox::stateChanged, [&]() { flip(); });
}

void Board::flip()
{
    Q_ASSERT(m_hor != nullptr && m_vert != nullptr);
    Q_ASSERT(m_grid != nullptr);

    m_grid->flip();
    m_hor->flip();
    m_vert->flip();
}

bool Board::hasHeightForWidth() const { return QWidget::hasHeightForWidth(); }

int Board::heightForWidth(int w) const { return QWidget::heightForWidth(w); }

void Board::setupGrid()
{
    Q_ASSERT(m_grid != nullptr);

    m_grid->init(8, 8);
    m_grid->update();

    for (int i = 0; i < m_grid->rowCount(); ++i)
        for (int j = 0; j < m_grid->columnCount(); ++j)
        {
            const auto s = m_grid->square(j, i);

            Q_ASSERT(s != nullptr);

            s->setBackground((j + i) % 2 == 0 ? 0xefefca : 0xfcdddd);
        }

    m_grid->square(3, 5)->setWarrior('Q');
    m_grid->square(6, 2)->setWarrior('k');
}
