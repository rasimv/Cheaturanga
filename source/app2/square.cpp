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
#include "warriorsvg.h"
#include <QPainter>

Square::Square(QWidget *parent, Qt::WindowFlags f):
    QWidget{parent, f},
    m_svgRenderer{new QSvgRenderer{this}}
{
    setAttribute(Qt::WA_TranslucentBackground);
}

Square::~Square() {}

void Square::init(int id)
{
    m_id = id;
}

int Square::id() const { return m_id; }

char Square::warrior() const { return m_warrior; }

void Square::setBackground(QColor color, bool repaint)
{
    m_background = std::move(color);
    if (repaint) this->repaint();
}

void Square::setWarrior(char warrior, bool repaint)
{
    Q_ASSERT(m_svgRenderer != nullptr);

    m_svgRenderer->load(warriorSVG(m_warrior = warrior));
    if (repaint) this->repaint();
}

void Square::setWarriorVisible(bool visible, bool repaint)
{
    m_warriorVisible = visible;
    if (repaint) this->repaint();
}

void Square::paintEvent(QPaintEvent *)
{
    Q_ASSERT(m_svgRenderer != nullptr);

    QPainter p{this};
    p.setPen(m_background);
    p.setBrush(m_background);
    p.drawRect(0, 0, width(), height());

    if (m_warriorVisible) m_svgRenderer->render(&p);
}
