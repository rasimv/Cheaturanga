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

use std::ops::{Add, Sub, Neg, AddAssign, SubAssign};

#[derive(Copy, Clone, PartialEq)]
pub struct Coords
{
	h: i8,
	v: i8
}

impl Default for Coords
{
	fn default() -> Self { Coords{h: -1, v: -1} }
}

impl Add for Coords
{
	type Output = Self;

	fn add(self, other: Self) -> Self
	{
		Coords{h: self.h + other.h, v: self.v + other.v}
	}
}

impl Sub for Coords
{
	type Output = Self;

	fn sub(self, other: Self) -> Self
	{
		Coords{h: self.h - other.h, v: self.v - other.v}
	}
}

impl AddAssign for Coords
{
	fn add_assign(&mut self, other: Self)
	{
		self.h += other.h;
		self.v += other.v;
	}
}

impl SubAssign for Coords
{
	fn sub_assign(&mut self, other: Self)
	{
		self.h -= other.h;
		self.v -= other.v;
	}
}

impl Neg for Coords
{
	type Output = Self;

	fn neg(self) -> Self::Output
	{
		Coords{h: -self.h, v: -self.v}
	}
}

impl Coords
{
	pub fn new(h: i8, v: i8) -> Self { Coords{h, v} }

	pub fn valid(&self) -> bool { valid(self) }
}

pub fn valid(c: &Coords) -> bool
{
	c.h >= 0 && c.h < dim::WIDTH && c.v >= 0 && c.v < dim::HEIGHT
}
