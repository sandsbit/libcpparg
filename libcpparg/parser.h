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

#ifndef LIBCPPARG_PARSER_H
#define LIBCPPARG_PARSER_H

#include "utils.h"

namespace cpparg {

    DLL_PUBLIC class ArgumentParser;

    DLL_PUBLIC class NamedArgument {

    public:

        friend ArgumentParser;

    };

    DLL_PUBLIC class PositionalArgument {

    public:

        friend ArgumentParser;

    };

    DLL_PUBLIC class ArgumentParser {

    };

}

#endif //LIBCPPARG_PARSER_H
