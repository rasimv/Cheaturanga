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

use crate::core1::dim;

#[derive(Default, Copy, Clone, PartialEq)]
struct Layout
{
	d: [[i8; dim::WIDTH_US]; dim::HEIGHT_US]
}

impl Layout
{
	fn new() -> Self
	{
		Layout{d: [[0; dim::WIDTH_US]; dim::HEIGHT_US]}
	}
}
