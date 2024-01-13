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

#pragma once

#include <deque>
#include <core/mechanics.hpp>
#include <vector>

namespace Cheaturanga::Frontend
{
	class Controller
	{
	public:
		Controller(std::istream &input, std::ostream &output);

		void run();

		static std::vector<std::string> split(const std::string& line);

	private:
		bool processInput();
		void badLine();
		void output(const std::string &line);

		std::istream &m_input;
		std::ostream &m_output;

		std::deque<std::string> m_queue;
	};

	inline Controller::Controller(std::istream &input, std::ostream &output):
		m_input{input}, m_output{output}
	{}

	inline void Controller::run()
	{
		m_output << "ready" << std::endl;

		do
		{
			std::string line;
			std::getline(m_input, line);

			m_queue.emplace_back(std::move(line));
		}
		while (processInput());
	}

	inline bool Controller::processInput()
	{
		assert(std::size(m_queue) > 0);

		std::vector<std::string> tokens{split(m_queue[0])};

		if (std::size(tokens) < 1) { badLine(); return true; }

		if (tokens[0] == "quit") { output("bye"); return false; }

		badLine();

		return true;
	}

	inline std::vector<std::string> Controller::split(const std::string &line)
	{
		std::istringstream iss{line};
		std::string token;
		std::vector<std::string> tokens;

		while (iss >> std::skipws >> token) tokens.emplace_back(std::move(token));

		return tokens;
	}

	inline void Controller::badLine()
	{
		assert(std::size(m_queue) > 0);

		m_queue.pop_front();

		m_output << "error" << std::endl;
	}

	inline void Controller::output(const std::string &line)
	{
		m_output << line << std::endl;
	}
}
