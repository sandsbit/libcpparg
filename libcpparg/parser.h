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

#include <string>
#include <utility>
#include <vector>
#include <optional>

#include "utils.h"

namespace cpparg {

    /**
     * Processed argument variant.
     */
    typedef std::vector<std::string> ArgumentVariant_t;

    constexpr size_t MAX_ARGS_COUNT_INF = 0;

    DLL_PUBLIC class ArgumentParser;

    DLL_PUBLIC class NamedArgument {

    public:

        friend ArgumentParser;

        NamedArgument() = delete;
        NamedArgument(const NamedArgument &na) = default;

        NamedArgument& operator=(const NamedArgument &na) = default;

    protected:

        NamedArgument(std::string name, std::vector<std::string> aliases, bool required,
                std::optional<std::string> defaultValue, size_t nargs, bool isFlag,
                std::vector<ArgumentVariant_t> variants, size_t maxCount) : name(std::move(name)), aliases(std::move(aliases)),
                                                                            required(required), defaultValue(std::move(defaultValue)),
                                                                            nargs(nargs), isFlag(isFlag),
                                                                            variants(std::move(variants)), maxCount(maxCount),
                                                                            _maxCountLeft(maxCount) {};

        std::string name;
        std::vector<std::string> aliases;

        bool required;  // ignored if is_flag is true
        std::optional<std::string> defaultValue;  // ignored if required is true

        size_t nargs;  // ignored if is_flag is true or if variants is not empty

        bool isFlag;
        std::vector<ArgumentVariant_t> variants;  // ignored if is_flag is true
        size_t maxCount;   // ignored if is_flag is true

        // internal stuff

        size_t _maxCountLeft;

    };

    DLL_PUBLIC class PositionalArgument {

    public:

        friend ArgumentParser;

    };

    DLL_PUBLIC class ArgumentParser {

    };

}

#endif //LIBCPPARG_PARSER_H
