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

#include <cassert>

namespace Cheaturanga
{
	constexpr auto Width = 8;
	constexpr auto Height = 8;

	struct Coords { char h = -1, v = -1; };

	struct Step { Coords from, to; };

	struct Layout { char d[Height][Width]{ 0 }; };

	struct Position
	{
		char side = 0;
		Layout layout;
		char castling = 0;
		Coords enPassant;

		auto &operator[](const Coords &coords);
		const auto &operator[](const Coords &coords) const;
	};

	inline bool operator==(const Coords &o, const Coords &a)
	{
		return o.h == a.h && o.v == a.v;
	}

	inline Coords operator+(const Coords &o, const Coords &a)
	{
		return {char(o.h + a.h), char(o.v + a.v)};
	}

	inline Coords operator-(const Coords &o, const Coords &a)
	{
		return {char(o.h - a.h), char(o.v - a.v)};
	}

	inline Coords operator-(const Coords &o)
	{
		return {char(-o.h), char(-o.v)};
	}

	inline Coords &operator+=(Coords &o, const Coords &a)
	{
		o.h += a.h; o.v += a.v;
		return o;
	}

	inline Coords &operator-=(Coords &o, const Coords &a)
	{
		o.h -= a.h; o.v -= a.v;
		return o;
	}

	inline bool valid(const Coords &coords)
	{
		return coords.h >= 0 && coords.h < Width && coords.v >= 0 && coords.v < Height;
	}

	inline auto &Position::operator[](const Coords &coords)
	{
		assert(valid(coords));

		return layout.d[coords.v][coords.h];
	}

	const auto &Position::operator[](const Coords &coords) const
	{
		assert(valid(coords));

		return layout.d[coords.v][coords.h];
	}

	inline bool opponent(char occ, char side)
	{
		return occ != 0 && (side == 0 ? occ >= 'a' : occ < 'a');
	}

	inline bool opponent(const Position &pos, const Coords &coords)
	{
		assert(valid(coords));

		return opponent(pos[coords], pos.side);
	}

	inline bool emptyOrOpponent(const Position &pos, const Coords &coords)
	{
		assert(valid(coords));

		const auto occ = pos[coords];
		return occ == 0 || opponent(occ, pos.side);
	}

	template<typename Shifts, typename StepCallback>
	inline void test(const Position &pos, const Coords &start,
										const Shifts &shifts, StepCallback stepCallback)
	{
		assert(valid(start));

		for (const auto &i : shifts)
		{
			const Coords target{start + i};
			if (valid(target) && emptyOrOpponent(pos, target))
				stepCallback(Step{start, target});
		}
	}

	template<typename StepCallback>
	inline void king(const Position &pos, const Coords &start, StepCallback stepCallback)
	{
		assert(valid(start));

		constexpr Coords shifts[]
				{ {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1} };

		test(pos, start, shifts, stepCallback);
	}

	template<typename StepCallback>
	inline void pawn(const Position &pos, const Coords &start, StepCallback stepCallback)
	{
		assert(valid(start));

		const auto side = pos.side;
		const Coords r{1, 0}, rf{1, side == 0 ? -1 : 1},
						f{0, side == 0 ? -1 : 1}, lf{-1, side == 0 ? -1 : 1}, l{-1, 0};

		Coords target{start + f};
		if (pos[target] == 0)
		{
			stepCallback(Step{start, target});
			if (start.v == (side == 0 ? Width - 2 : 1) && pos[target += f] == 0)
				stepCallback(Step{start, target});
		}

		target = start + rf;
		if (valid(target) && (opponent(pos, target) || target == pos.enPassant))
			stepCallback(Step{start, target});
		target = start + lf;
		if (valid(target) && (opponent(pos, target) || target == pos.enPassant))
			stepCallback(Step{start, target});
	}

	template<typename StepCallback>
	inline void knight(const Position &pos, const Coords &start, StepCallback stepCallback)
	{
		assert(valid(start));

		constexpr Coords shifts[]
				{ {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1} };

		test(pos, start, shifts, stepCallback);
	}

	template<typename StepCallback>
	inline void test(const Position &pos, const Coords &start,
											const Coords &step, StepCallback stepCallback)
	{
		assert(valid(start));

		for (auto target{start}; valid(target += step); )
		{
			if (emptyOrOpponent(pos, target)) stepCallback(Step{start, target});
			if (pos[target] != 0) break;
		}
	}

	template<typename StepCallback>
	inline void bishop(const Position &pos, const Coords &start, StepCallback stepCallback)
	{
		assert(valid(start));

		test(pos, start, {1, -1}, stepCallback);
		test(pos, start, {-1, -1}, stepCallback);
		test(pos, start, {-1, 1}, stepCallback);
		test(pos, start, {1, 1}, stepCallback);
	}

	template<typename StepCallback>
	inline void rook(const Position &pos, const Coords &start, StepCallback stepCallback)
	{
		assert(valid(start));

		test(pos, start, {1, 0}, stepCallback);
		test(pos, start, {0, -1}, stepCallback);
		test(pos, start, {-1, 0}, stepCallback);
		test(pos, start, {0, 1}, stepCallback);
	}

	template<typename StepCallback>
	inline void queen(const Position &pos, const Coords &start, StepCallback stepCallback)
	{
		assert(valid(start));

		bishop(pos, start, stepCallback);
		rook(pos, start, stepCallback);
	}

	template<typename StepCallback>
	inline void castling(const Position &pos, StepCallback stepCallback)
	{
		const auto b = pos.side == 0 ? pos.castling : pos.castling >> 2;
		if ((b & 1) != 0)
		{
			const Coords k{Width / 2, pos.side == 0 ? Height - 1 : 0}, r{Width - 1, k.v};
			for (Coords w{k}; w += Coords{1, 0}, true; )
			{
				if (w == r) { stepCallback(Step{k, k + Coords{2, 0}}); break; }
				if (pos[w] != 0) break;
			}
		}
		if ((b & 0b10) != 0)
		{
			const Coords k{Width / 2, pos.side == 0 ? Height - 1 : 0}, r{0, k.v};
			for (Coords w{k}; w -= Coords{1, 0}, true; )
			{
				if (w == r) { stepCallback(Step{k, k - Coords{2, 0}}); break; }
				if (pos[w] != 0) break;
			}
		}
	}

	template<typename StepCallback>
	inline void test(const Position &pos, const Coords &coords, StepCallback stepCallback)
	{
		assert(valid(coords));

		const auto occ = pos[coords];
		if (occ == 0 || opponent(occ, pos.side))
			return;

		switch (occ)
		{
		case 'K': case 'k': king(pos, coords, stepCallback); break;
		case 'P': case 'p': pawn(pos, coords, stepCallback); break;
		case 'N': case 'n': knight(pos, coords, stepCallback); break;
		case 'B': case 'b': bishop(pos, coords, stepCallback); break;
		case 'R': case 'r': rook(pos, coords, stepCallback); break;
		case 'Q': case 'q': queen(pos, coords, stepCallback); break;
		}
	}

	template<typename StepCallback>
	inline void step(const Position &pos, StepCallback stepCallback)
	{
		for (Coords start{0, 0}; start.v < Height; ++start.v)
			for (start.h = 0; start.h < Width; ++start.h)
				test(pos, start, stepCallback);
		castling(pos, stepCallback);
	}

	Position fromFEN(const std::string &fen)
	{
		// rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

		Position pos;

		Coords coords{0, 0};
		size_t i = 0;
		for (; ; ++i)
		{
			assert(i < std::size(fen));

			const auto c = fen[i];
			if ('0' <= c && c <= '9') coords.h += c - '0';
			else if ('A' <= c && c <= 'Z' || 'a' <= c && c <= 'z')
			{	valid(coords); pos[coords] = c; ++coords.h;	}
			else if (c == '/') { coords.h = 0; ++coords.v; }
			else break;
		}

		if (fen[++i] != 'w') ++pos.side;

		for (++i; ++i; )
		{
			assert(i < std::size(fen));

			const auto c = fen[i];
			if (c == 'K') pos.castling |= 1;
			else if (c == 'Q') pos.castling |= 0b10;
			else if (c == 'k') pos.castling |= 0b100;
			else if (c == 'q') pos.castling |= 0b1000;
			else break;
		}

		assert(i < std::size(fen));

		if (fen[++i] != '-')
		{
			assert(i + 1 < std::size(fen));

			pos.enPassant = {fen[i] - 'a', '8' - fen[++i]};
		}

		return pos;
	}
}
