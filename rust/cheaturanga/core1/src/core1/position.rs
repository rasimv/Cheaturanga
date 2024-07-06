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
use crate::core1::layout::Layout;

#[derive(Default, Copy, Clone, PartialEq)]
pub struct Position
{
	pub turn: i8,
	pub layout: Layout,
	pub castle: i8,
	pub en_passant: Coords
}

impl std::ops::Index<Coords> for Position
{
	type Output = i8;

	fn index(&self, coords: Coords) -> &Self::Output
	{
		&self.layout[coords]
	}
}

impl std::ops::IndexMut<Coords> for Position
{
	fn index_mut(&mut self, coords: Coords) -> &mut Self::Output
	{
		&mut self.layout[coords]
	}
}

impl Position
{
	fn new() -> Self { Position::default() }
}
