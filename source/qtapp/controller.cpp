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

#include "controller.h"
#include <QFileInfo>
#include <QCoreApplication>
#include <QTextStream>

Controller::Controller(QObject *parent):
    QObject{parent},
    m_engine{new QProcess{this}}
{}

void Controller::init()
{
    Q_ASSERT(m_engine != nullptr);

    QObject::connect(m_engine, &QProcess::readyReadStandardOutput,
                                    this, &Controller::outputReady);
}

void Controller::start()
{
    Q_ASSERT(m_engine != nullptr);

    const QFileInfo fi{QCoreApplication::applicationDirPath() + "/../../rust/cheaturanga/target/debug/cheaturanga.exe"};

    qDebug() << fi.canonicalFilePath();

    m_engine->setProgram(fi.canonicalFilePath());
    m_engine->start();

    /*while (true)
    {
        QCoreApplication::processEvents();
         const auto s{m_engine->readAllStandardOutput()};
        if (s.size() > 0) qDebug() << s;
    }*/

    connect(&m_timer, &QTimer::timeout, [&]()
        {
            // emit log(QStringList{"123"});
        });

    m_timer.start(1000);
}

void Controller::submitDice(const QString &dice)
{
    emit log(QStringList{dice});
}

void Controller::outputReady()
{
    Q_ASSERT(m_engine != nullptr);

    m_rawQueue += m_engine->readAllStandardOutput();

    while (true)
    {
        auto newline{std::find(std::begin(m_rawQueue),
                                std::end(m_rawQueue), '\n')};
        if (newline == std::end(m_rawQueue)) break;

        auto lengh = std::distance(std::begin(m_rawQueue), newline);
        if (lengh > 0 && *(newline - 1) == '\r') --lengh;
        m_queue += QByteArray{std::begin(m_rawQueue), lengh};

        m_rawQueue.erase(std::begin(m_rawQueue), ++newline);

        emit log(QStringList{m_queue.last()});
    }
}
