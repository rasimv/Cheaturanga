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

use crate::core1::coords;
use crate::core1::layout;

use std::ops::{Index, IndexMut};

#[derive(Default, Copy, Clone, PartialEq)]
pub struct Position
{
	pub turn: i8,
	pub layout: layout::Layout,
	pub castle: i8,
	pub en_passant: coords::Coords
}

impl Index<coords::Coords> for Position
{
	type Output = i8;

	fn index(&self, coords: coords::Coords) -> &Self::Output
	{
		&self.layout[coords]
	}
}

impl IndexMut<coords::Coords> for Position
{
	fn index_mut(&mut self, coords: coords::Coords) -> &mut Self::Output
	{
		&mut self.layout[coords]
	}
}

impl Position
{
	fn new() -> Self { Position::default() }
}
