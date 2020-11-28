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
#include <cstddef>

#ifdef __cpp_concepts
#include <concepts>
#endif

#include "../misc/utils.h"
#include "parsing_util_classes.h"

namespace cpparg {

    DLL_PUBLIC class ArgumentParser {

    public:

        ArgumentParser() = default;
        ArgumentParser(const ArgumentParser &) = delete;
        explicit ArgumentParser(std::string name="", std::string description="", std::string version="") :
                                                                                  name(std::move(name)),
                                                                                  description(std::move(description)),
                                                                                  version(std::move(version)) {};

        ArgumentParser& operator=(const ArgumentParser &) = delete;

        void addPositionalArgument(std::string argName, std::string helpName,
                std::optional<long long int> position = std::nullopt, bool required = false,
                std::optional<std::string> defaultValue = std::nullopt, std::vector<ArgumentVariant_t> variants = {},
                std::size_t maxCount = 1) {
            positionalArguments.emplace_back(PositionalArgument(std::move(argName), std::move(helpName),
                    required, std::move(defaultValue),
                    std::move(variants), maxCount, position));
        }

#ifdef __cpp_concepts
        template<std::derived_from<std::string>... Aliases>
#else
        template<typename... Aliases>
#endif
        void addFlag(std::string argName, Aliases... aliases) {
            namedArguments.emplace_back(NamedArgument(std::move(argName),
                    std::vector{(std::move(aliases))...}, false, std::nullopt, 1, true, {}, 1));
        };

        void addNamedArgument(std::string argName, std::vector<std::string> aliases, bool required = false,
                std::optional<std::string> defaultValue = std::nullopt, std::size_t nargs = 1,
                std::vector<ArgumentVariant_t> variants = {}, std::size_t maxCount = 1) {
            namedArguments.emplace_back(NamedArgument(std::move(argName), std::move(aliases), required,
                    std::move(defaultValue), nargs, false, std::move(variants), maxCount));
        };

        void addNamedArgument(std::string argName, std::string alias, bool required = false,
                              std::optional<std::string> defaultValue = std::nullopt, std::size_t nargs = 1,
                              std::vector<ArgumentVariant_t> variants = {}, std::size_t maxCount = 1) {
            namedArguments.emplace_back(NamedArgument(std::move(argName), {std::move(alias)}, required,
                    std::move(defaultValue), nargs, false, std::move(variants), maxCount));
        };

        [[nodiscard]] ParsingResult parse(std::size_t argc, const char **argv) const;
        [[nodiscard]] ParsingResult parse(const std::string &command) const;
        [[nodiscard]] ParsingResult parse(const std::vector<std::string> &args) const;

        std::string name;
        std::string description;
        std::string version;

    protected:

        std::vector<PositionalArgument> positionalArguments;
        std::vector<NamedArgument> namedArguments;

    };

}

#endif //LIBCPPARG_PARSER_H
