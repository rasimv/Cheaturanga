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

#[derive(Default, Copy, Clone, PartialEq)]
pub struct Fen
{
    pub pos: Position,
    pub halfmove50: i32,
    pub fullmove: i32
}

impl Fen
{
    fn new() -> Self { Fen::default() }
}

fn is_digit(c: char) -> bool { '0' <= c && c <= '9' }

fn parse_int<I>(i: &mut I) -> Result<i32, ()>
where I: Iterator<Item = char>
{
    let mut value: Result<i32, ()> = Err(());

    loop
    {
        match i.next()
        {
            None => return value,

            Some(c) =>
            {
                if c == ' ' { return value }

                if !is_digit(c) { return Err(()) }

                if value.is_err() { value = Ok(0) }

                value = match value
                    {
                        Ok(v) => v.checked_mul(10)
                            .and_then(|v| v.checked_add(c as i32 - '0' as i32))
                            .ok_or(()),

                        Err(_) => Ok(c as i32 - '0' as i32)
                    }
            }
        }
    }
}

pub fn decode(code: &str) -> Result<Fen, ()>
{
    // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

    let mut fen = Fen::new();

    let mut i = code.chars();

    loop
    {
        let mut coords = Coords::new(0, 0);

        match i.next()
        {
            Some(c) if '0' <= c && c <= '9' => coords.h += c as i8 - '0' as i8,

            Some(c) if 'A' <= c && c <= 'Z' || 'a' <= c && c <= 'z' =>
            {
                if !coords.is_valid() { return Err(()) }

                fen.pos[coords] = c as i8; coords.h += 1;
            }

            Some('/') => { coords.h = 0; coords.v += 1; }

            Some(' ') => break,

            _ => return Err(())
        }
    }

    match i.next()
    {
        None => return Err(()),

        Some('b') => fen.pos.turn += 1,
        _ => {}
    }

    if i.next() != Some(' ') { return Err(()) }

    loop
    {
        match i.next()
        {
            None => return Err(()),

            Some('K') => fen.pos.castle |= 1,
            Some('Q') => fen.pos.castle |= 0b10,
            Some('k') => fen.pos.castle |= 0b100,
            Some('q') => fen.pos.castle |= 0b1000,
            Some(' ') => break,
            _ => {}
        }
    }

    match i.clone().next()
    {
        None => return Err(()),

        Some('-') => { i.next(); }
        _ => fen.pos.en_passant = crate::core1::coords::from_string(&mut i)?
    }

    if i.next() != Some(' ') { return Err(()) }

    fen.halfmove50 = parse_int(&mut i)?;

    fen.fullmove = parse_int(&mut i)?;

    Ok(fen)
}
