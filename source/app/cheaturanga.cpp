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
#include <deque>

void intro();

int main()
{
	intro();

	std::cout << std::endl << "ready" << std::endl;

	std::deque<std::string> queue;

	while (true)
	{
		std::string line;
		std::getline(std::cin, line);

		if (line == "quit") break;

		queue.emplace_back(std::move(line));
	}

	Cheaturanga::FEN fen1{Cheaturanga::
		decode("rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR w KQkq - 0 3")};

	Cheaturanga::step(fen1.pos, [](const auto &q)
		{
			std::cout << q.from << '\t' << q.to << std::endl;
		});

	const auto fenS{Cheaturanga::encode(fen1)};

	return 0;
}

void intro()
{
	std::cout << "Cheaturanga  Copyright (C) 2024  Rasim Valiullin" << std::endl <<
		std::endl <<
		"This program is free software: you can redistribute it and/or modify" << std::endl <<
		"it under the terms of the GNU General Public License as published by" << std::endl <<
		"the Free Software Foundation, either version 3 of the License, or" << std::endl <<
		"(at your option) any later version." << std::endl <<
		std::endl <<
		"This program is distributed in the hope that it will be useful," << std::endl <<
		"but WITHOUT ANY WARRANTY; without even the implied warranty of" << std::endl <<
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << std::endl <<
		"GNU General Public License for more details." << std::endl <<
		std::endl <<
		"You should have received a copy of the GNU General Public License" << std::endl <<
		"along with this program.  If not, see <https://www.gnu.org/licenses/>." << std::endl;
}
