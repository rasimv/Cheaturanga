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

pub struct Controller<'a>
{
	input: &'a mut dyn std::io::Read,
	output: &'a mut dyn std::io::Write,

	queue: std::collections::LinkedList<String>
}

type IoResultBool = Result<bool, std::io::Error>;

impl<'a> Controller<'a>
{
	pub fn new(input: &'a mut dyn std::io::Read, output: &'a mut dyn std::io::Write) -> Self
	{
		Controller
			{
				input: input,
				output: output,
				queue: std::collections::LinkedList::new()
			}
	}

	pub fn run(&mut self) -> IoResultBool
	{
		self.output_line("ready")?;

		loop
		{
			use std::io::{BufRead, BufReader};
			let mut reader = BufReader::new(&mut self.input);

			let mut line = String::new();
			reader.read_line(&mut line)?;

			self.queue.push_back(line);

			if !self.process_input()? { break }
		}

		Ok(true)
	}

	fn output_line(&mut self, string: &str) -> IoResultBool
	{
		self.output.write_all(string.as_bytes())?;
		self.output.write_all("\n".as_bytes())?;
		self.output.flush()?;

		Ok(true)
	}

	fn process_input(&mut self) -> IoResultBool
	{
		assert!(self.queue.len() > 0);

		if let Some(line) = self.queue.front()
			{ if line == "quit\r\n" { return Ok(false); } }

		self.queue.pop_front();

		Ok(true)
	}
}
