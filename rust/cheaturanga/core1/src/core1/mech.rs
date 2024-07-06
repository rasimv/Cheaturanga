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

use crate::core1::coords::Coords;
use crate::core1::position::Position;

pub fn is_opponent(turn: i8, occ: i8) -> bool
{
	occ != 0 && if turn == 0 { occ >= 'a' as i8 } else { occ < 'a' as i8 }
}

pub fn is_opponent_on_sq(pos: &Position, coords: Coords) -> bool
{
	assert!(coords.is_valid());

	is_opponent(pos[coords], pos.turn)
}

pub fn is_empty_or_opp(pos: &Position, coords: Coords) -> bool
{
	assert!(coords.is_valid());

	let occ = pos[coords];

	occ == 0 || is_opponent(occ, pos.turn)
}

fn test<Shifts>(pos: &Position, coords: Coords, shifts: &Shifts, subplies: &mut Vec<Coords>)
	where Shifts: IntoIterator
{
	assert!(coords.is_valid());
}
