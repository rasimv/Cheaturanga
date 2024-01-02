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

#include "labels.h"
#include <QLabel>

Labels::Labels(QWidget *parent):
    QWidget{parent},
    m_layout{new QGridLayout{this}}
{
    m_layout->setContentsMargins({});
    m_layout->setHorizontalSpacing(0);
    m_layout->setVerticalSpacing(0);
}

void Labels::init(Qt::Orientation ori)
{
    Q_ASSERT(m_layout != nullptr);
    Q_ASSERT(m_layout->count() == 0);

    for (int i = 0; i < 8; ++i)
    {
        const auto label = new QLabel{this};
        label->setAlignment(Qt::AlignCenter);

        if (ori == Qt::Horizontal)
        {
            label->setText(QString{char('a' + i)});
            m_layout->addWidget(label, 0, i);
        }
        else
        {
            label->setText(QString{"%1"}.arg(8 - i));
            m_layout->addWidget(label, i, 0);
        }
    }
}

void Labels::flip()
{
    Q_ASSERT(m_layout != nullptr);
    Q_ASSERT(m_layout->columnCount() == 1 && m_layout->rowCount() == 8 ||
             m_layout->rowCount() == 1 && m_layout->columnCount() == 8);

    const auto max = std::max(m_layout->rowCount(), m_layout->columnCount());
    for (int i = 0; i < max / 2; ++i)
    {
        if (m_layout->rowCount() == 1)
        {
            const auto item1 = m_layout->itemAtPosition(0, i),
                        item2 = m_layout->itemAtPosition(0, max - i - 1);
            Q_ASSERT(item1 != nullptr && item2 != nullptr);

            m_layout->removeItem(item1);
            m_layout->removeItem(item2);

            m_layout->addItem(item2, 0, i);
            m_layout->addItem(item1, 0, max - i - 1);
        }
        else
        {
            const auto item1 = m_layout->itemAtPosition(i, 0),
                        item2 = m_layout->itemAtPosition(7 - i, 0);
            Q_ASSERT(item1 != nullptr && item2 != nullptr);

            m_layout->removeItem(item1);
            m_layout->removeItem(item2);

            m_layout->addItem(item2, i, 0);
            m_layout->addItem(item1, 7 - i, 0);
        }
    }
}
