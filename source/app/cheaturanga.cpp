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
	Cheaturanga::FEN fen1{Cheaturanga::
		decode("rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR w KQkq - 0 3")};

	Cheaturanga::step(fen1.pos, [](const auto &q)
		{
			std::cout << q.from << '\t' << q.to << std::endl;
		});

	const auto fenS{Cheaturanga::encode(fen1)};

	return 0;
}
