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

#include "log.h"
#include <QScrollBar>
#include <QTimer>

Log::Log(QWidget *parent):
    QWidget{parent},
    m_textEdit{new QPlainTextEdit{this}}
{
    Q_ASSERT(m_textEdit != nullptr);

    m_textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);

    const auto layout = new QGridLayout{this};

    layout->setContentsMargins({});
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);

    layout->addWidget(m_textEdit, 0, 0);
}

void Log::init() {}

void Log::append(const QStringList &piece)
{
    Q_ASSERT(m_textEdit != nullptr);

    for (const auto &p: piece)
        m_textEdit->appendPlainText(p);

    QTimer::singleShot(0, [&]()
        {
            m_textEdit->verticalScrollBar()->
                setValue(m_textEdit->verticalScrollBar()->maximum());
            m_textEdit->horizontalScrollBar()->
                setValue(m_textEdit->horizontalScrollBar()->minimum());
        });
}
