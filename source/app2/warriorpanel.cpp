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

#include "warriorpanel.h"

WarriorPanel::WarriorPanel(QWidget *parent):
    QWidget{parent},
    m_grid{new Grid{this, Grid::Flags::DoNotHideSourceAndDisableInternalMove}}
{
    Q_ASSERT(m_grid != nullptr);

    const auto layout = new QGridLayout{this};

    layout->setContentsMargins({});
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);

    m_grid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(m_grid, 0, 0);
}

void WarriorPanel::init()
{
    Q_ASSERT(m_grid != nullptr);

    setupGrid();

    connect(m_grid, &Grid::drop, [&](const DropInfo &info)
            { emit drop(info); });
}

void WarriorPanel::setSide(char warrior)
{
    Q_ASSERT(m_grid != nullptr);
    Q_ASSERT(m_grid->columnCount() == 3 && m_grid->rowCount() == 2);

    for (int i = 0; i < m_grid->rowCount() * m_grid->columnCount(); ++i)
        m_grid->square(i % m_grid->columnCount(), i / m_grid->columnCount())->
            setWarrior((warrior < 'a' ? "PNBRQK" : "pnbrqk")[i]);
}

void WarriorPanel::setupGrid()
{
    Q_ASSERT(m_grid != nullptr);

    m_grid->init(3, 2);
    m_grid->update();

    for (int i = 0; i < m_grid->rowCount(); ++i)
        for (int j = 0; j < m_grid->columnCount(); ++j)
        {
            const auto s = m_grid->square(j, i);

            Q_ASSERT(s != nullptr);

            s->setBackground(0xd8d8d8);
        }

    setSide('K');
}
