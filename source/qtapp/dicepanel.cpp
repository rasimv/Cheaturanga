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

#include "dicepanel.h"

DicePanel::DicePanel(QWidget *parent):
    QWidget{parent},
    m_grid{new Grid{this, Grid::Flags::DiscardWhenDroppedOutside}}
{
    Q_ASSERT(m_grid != nullptr);

    const auto layout = new QGridLayout{this};

    layout->setContentsMargins({});
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);

    m_grid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(m_grid, 0, 0);
}

void DicePanel::init()
{
    setupGrid();
}

void DicePanel::drop(const DropInfo &info)
{
    Q_ASSERT(m_grid != nullptr);

    const auto parentPos{parentWidget()->mapFromGlobal(info.global)};
    if (!geometry().toRectF().contains(parentPos)) return;

    const auto gridPos{m_grid->mapFromGlobal(info.global)};
    const auto s = m_grid->squareByPosition(gridPos);
    if (s != nullptr) s->setWarrior(info.warrior);
}

void DicePanel::set(const QString &dice)
{
    Q_ASSERT(m_grid != nullptr);
    Q_ASSERT(m_grid->columnCount() == Const::NumberOfDice);
    Q_ASSERT(dice.size() == Const::NumberOfDice);

    for (int i = 0; i < m_grid->columnCount(); ++i)
    {
        const auto s = m_grid->square(i, 0);

        Q_ASSERT(s != nullptr);

        s->setWarrior(dice[i].toLatin1());
    }
}

void DicePanel::submit()
{
    Q_ASSERT(m_grid != nullptr);
    Q_ASSERT(m_grid->columnCount() == Const::NumberOfDice);

    QString dice;

    for (int i = 0; i < Const::NumberOfDice; ++i)
    {
        const auto s = m_grid->square(i, 0);

        Q_ASSERT(s != nullptr);

        dice += s->warrior();
    }

    emit submitDice(dice);
}

void DicePanel::setupGrid()
{
    Q_ASSERT(m_grid != nullptr);

    m_grid->init(Const::NumberOfDice, 1);
    m_grid->update();

    for (int j = 0; j < m_grid->columnCount(); ++j)
    {
        const auto s = m_grid->square(j, 0);

        Q_ASSERT(s != nullptr);

        s->setBackground(j == 1 ? 0xd8d8d8 : 0xc8c8c8);
    }
}
