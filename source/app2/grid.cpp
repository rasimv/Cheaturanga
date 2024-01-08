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
#include <QMouseEvent>

Grid::Grid(QWidget *parent, Flags flags):
    QWidget{parent},
    m_layout{new QGridLayout{this}},
    m_dragged{new Square{this, Qt::Window | Qt::FramelessWindowHint | Qt::Tool}},
    m_flags{flags}
{
    Q_ASSERT(m_layout != nullptr);

    m_layout->setContentsMargins({});
    m_layout->setHorizontalSpacing(0);
    m_layout->setVerticalSpacing(0);
}

void Grid::init(int columns, int rows)
{
    Q_ASSERT(m_layout != nullptr);
    Q_ASSERT(columns > 0 && rows > 0);
    Q_ASSERT(m_layout->count() == 0);
    Q_ASSERT(!m_flipView);

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
        {
            const auto square = new Square{this};
            square->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            m_layout->addWidget(square, i, j);

            square->init(j + i * columns);
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

Square *Grid::square(int col, int row, bool actual)
{
    Q_ASSERT(m_layout != nullptr);
    Q_ASSERT(col < m_layout->columnCount() && row < m_layout->rowCount());

    const auto actualColumn = !actual && m_flipView ?
                                  m_layout->columnCount() - col - 1 : col;
    const auto actualRow = !actual && m_flipView ?
                               m_layout->rowCount() - row - 1 : row;

    const auto w = m_layout->
                   itemAtPosition(actualRow, actualColumn)->widget();
    return dynamic_cast<Square *>(w);
}

Square *Grid::squareByPosition(const QPointF &pos,
                               int *actualColumn, int *actualRow)
{
    for (int i = 0; i < rowCount(); ++i)
        for (int j = 0; j < columnCount(); ++j)
        {
            const auto s = square(j, i);

            Q_ASSERT(s != nullptr);

            if (s->geometry().contains(pos.toPoint()))
            {
                if (actualColumn != nullptr) *actualColumn = j;
                if (actualRow != nullptr) *actualRow = i;
                return s;
            }
        }

    return nullptr;
}

QPoint Grid::coordsFromId(int id) const
{
    return {id % columnCount(), id / columnCount()};
}

void Grid::flipView()
{
    Q_ASSERT(m_layout != nullptr);

    m_flipView = !m_flipView;

    const int outer = (m_layout->rowCount() + 1) / 2;
    for (int i = 0; i < outer; ++i)
    {
        const int inner = i + 1 < outer || m_layout->rowCount() % 2 == 0 ?
                              m_layout->columnCount() :
                              m_layout->columnCount() / 2;

        for (int j = 0; j < inner; ++j)
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
}

void Grid::mousePressEvent(QMouseEvent *event)
{
    Q_ASSERT(event != nullptr);
    Q_ASSERT(m_dragged != nullptr);

    if (m_source != nullptr || event->buttons() != Qt::LeftButton)
    {
        QWidget::mousePressEvent(event);
        return;
    }

    const auto source = squareByPosition(event->pos());
    if (source != nullptr && source->warrior() != 0)
    {
        m_source = source;

        const QPointF squareSize(m_source->width(), m_source->height());
        const QRectF g{event->globalPosition() - squareSize / 1.8,
                       event->globalPosition() + squareSize / 1.8};

        m_dragged->setGeometry(g.toRect());
        m_dragged->setWarrior(m_source->warrior());
        m_dragged->setVisible(true);

        if (!QFlags{m_flags}.testFlag(Flags::DoNotHideSource))
            m_source->setWarriorVisible(false);

        event->accept();
        return;
    }

    QWidget::mousePressEvent(event);
}

void Grid::mouseMoveEvent(QMouseEvent *event)
{
    Q_ASSERT(event != nullptr);
    Q_ASSERT(m_dragged != nullptr);

    if (m_source != nullptr)
    {
        const QPointF squareSize(m_dragged->width(), m_dragged->height());
        const QRectF g{event->globalPosition() - squareSize / 2,
                       event->globalPosition() + squareSize / 2};

        m_dragged->setGeometry(g.toRect());

        event->accept();
        return;
    }

    QWidget::mouseMoveEvent(event);
}

void Grid::mouseReleaseEvent(QMouseEvent *event)
{
    Q_ASSERT(event != nullptr);
    Q_ASSERT(m_dragged != nullptr);

    if (m_source != nullptr && !QFlags{event->buttons()}.testFlag(Qt::LeftButton))
    {
        m_dragged->setVisible(false);

        const auto target = squareByPosition(event->pos());

        const DropInfo info{coordsFromId(m_source->id()),
            target == nullptr ? QPoint{-1, -1} : coordsFromId(target->id()),
                            event->globalPosition(), m_source->warrior()};

        emit dropped(info);

        if (QFlags{m_flags}.testFlag(Flags::DiscardWhenDroppedOutside) &&
            target == nullptr)
            m_source->setWarrior(0, false);

        if (!QFlags{m_flags}.testFlag(Flags::DisableInternalMove) &&
            target != nullptr && m_source != target)
        {
            target->setWarrior(m_source->warrior());
            m_source->setWarrior(0, false);
        }

        m_source->setWarriorVisible(true);
        m_source = nullptr;

        event->accept();
        return;
    }

    QWidget::mouseReleaseEvent(event);
}
