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
#include <QMouseEvent>
#include <QPainter>

Square::Square(QWidget *parent):
    QWidget{parent},
    m_content{new QSvgWidget{this}}
{}

Square::~Square() {}

void Square::init(int id)
{
    m_id = id;
}

int Square::id() const { return m_id; }

void Square::setBackground(QColor color, bool repaint)
{
    m_background = std::move(color);
    if (repaint) this->repaint();
}

void Square::setWarrior(char warrior)
{
    Q_ASSERT(m_content != nullptr);

    m_content->load(warriorSVG(warrior));
}

void Square::resizeEvent(QResizeEvent *event)
{
    Q_ASSERT(m_content != nullptr);

    QWidget::resizeEvent(event);
    m_content->setGeometry(0, 0, width(), height());
}

void Square::paintEvent(QPaintEvent *)
{
    QPainter p{this};
    p.setPen(m_background);
    p.setBrush(m_background);
    p.drawRect(0, 0, width(), height());
}

void Square::mousePressEvent(QMouseEvent *event)
{
    Q_ASSERT(event != nullptr);

    emit down(mouseData(DCMousePress, event));

    event->accept();
}

void Square::mouseMoveEvent(QMouseEvent *event)
{
    Q_ASSERT(event != nullptr);

    emit down(mouseData(DCMouseMove, event));

    event->accept();
}

void Square::mouseReleaseEvent(QMouseEvent *event)
{
    Q_ASSERT(event != nullptr);

    emit down(mouseData(DCMouseRelease, event));

    event->accept();
}

QByteArray Square::mouseData(DownCode code, QMouseEvent *event)
{
    Q_ASSERT(event != nullptr);

    QByteArray d;
    QDataStream ds{&d, QIODeviceBase::WriteOnly};
    ds << m_id << code << event->globalPosition();

    return d;
}
