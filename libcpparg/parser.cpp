/**
 *  _     _ _
 * | |   (_) |__   ___ _ __  _ __   __ _ _ __ __ _
 * | |   | | '_ \ / __| '_ \| '_ \ / _` | '__/ _` |
 * | |___| | |_) | (__| |_) | |_) | (_| | | | (_| |
 * |_____|_|_.__/ \___| .__/| .__/ \__,_|_|  \__, |
                    |_|   |_|              |___/
 *
 * Yet another C++ powerful command line argument parsing library.
 * Copyright (C) 2020 Nikita Serba. All rights reserved
 * https://github.com/sandsbit/libcpparg/
 *
 *  This file is part of libcpparg.
 *
 *  libcpparg is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of
 *  the License, or (at your option) any later version.
 *
 *  libcpparg is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  and GNU Lesser General Public License along with libcpparg.  If not,
 *  see <https://www.gnu.org/licenses/>.
 */

#include "parser.h"

#include <string>
#include <vector>
#include <cstddef>
#include <sstream>
#include <iterator>

namespace cpparg {

long long int PositionalArgument::positionCount = 0;

cpparg::ParsingResult ArgumentParser::parse(std::size_t argc, char **argv) const {
    return parse(std::vector<std::string>(argv, argv + argc));
}

cpparg::ParsingResult ArgumentParser::parse(const std::string &command) const {
    std::stringstream ss(command);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    return parse(std::vector<std::string>(begin, end));
}

cpparg::ParsingResult ArgumentParser::parse(const std::vector<std::string> &args) const {
    // TODO
    return cpparg::ParsingResult();
}

}