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

#ifndef WARRIORSVG_H
#define WARRIORSVG_H

#include <QFile>

namespace
{
    inline QByteArray warriorSVG(char warrior)
    {
        static const QString subpath{"D:/development/Cheaturanga/source/qtapp/images/"};

        if (!std::isalnum(warrior)) return {};

        const auto filepath{subpath + QString{warrior}.toLower() +
                            (warrior < 'a' ? '1' : '2') + ".svg"};

        if (!QFile::exists(filepath)) return {};

        QFile file{filepath};

        return file.open(QIODeviceBase::ReadOnly) ? file.readAll() : QByteArray{};
    }
}

#endif // WARRIORSVG_H
