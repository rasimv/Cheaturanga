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

#include <iostream>
#include <cheaturanga/mechanics.hpp>

int main()
{
	Cheaturanga::Position pos{ Cheaturanga::
		//fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1")};
		fromFEN("3rkb1r/1bppqp1p/ppn2n2/4p1pP/4P3/P4N2/1PPPBPP1/RNBQ1RK1 w k g6 0 10") };

	Cheaturanga::step(pos, [](const auto& q)
		{
			std::cout << "<" << int(q.from.h) << " | " << int(q.from.v) << ">" << "\t" <<
				"<" << int(q.to.h) << " | " << int(q.to.v) << ">" << std::endl;
		});

	return 0;
}
