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

#include "square.h"
#include "warriorSVG.h"

Square::Square(QWidget *parent):
    QWidget{parent},
    m_layout{new QGridLayout{this}},
    m_content{new QSvgWidget{this}}
{
    Q_ASSERT(m_layout != nullptr);
    Q_ASSERT(m_content != nullptr);

    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addWidget(m_content);
    setWarrior('Q');
    init(0, 1);
}

Square::~Square() {}

void Square::init(int id, char type)
{
    m_id = id;

    QPalette pal{palette()};
    pal.setColor(QPalette::Window, type == 0 ? "#efefca" : "#deddfc");
    setPalette(pal);
}

void Square::setWarrior(char warrior)
{
    Q_ASSERT(m_content != nullptr);

    m_content->load(warriorSVG('n'));
}
