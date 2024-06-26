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

mod frontend;

fn main()
{
	notice();

	println!("----------------------------------------------------------------");

	println!("{}", core1::magic(123));

	let mut input = std::io::stdin();
	let mut output = std::io::stdout();

	let mut controller = frontend::Controller::new(&mut input, &mut output);

	controller.run();
}

fn notice()
{
	println!(
		"Copyright (C) 2024  Rasim Valiullin\n\
		\n\
		This program is free software: you can redistribute it and/or modify\n\
		it under the terms of the GNU General Public License as published by\n\
		the Free Software Foundation, either version 3 of the License, or\n\
		(at your option) any later version.\n\
		\n\
		This program is distributed in the hope that it will be useful,\n\
		but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
		GNU General Public License for more details.\n\
		\n\
		You should have received a copy of the GNU General Public License\n\
		along with this program.  If not, see <https://www.gnu.org/licenses/>.\n"
			);
}
