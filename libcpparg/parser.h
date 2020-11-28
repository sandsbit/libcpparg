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

#include "utils.h"

namespace cpparg {

    /**
     * Processed argument variant.
     */
    typedef std::vector<std::string> ArgumentVariant_t;

    constexpr std::size_t MAX_ARGS_COUNT_INF = 0;

    DLL_PUBLIC class ArgumentParser;

    DLL_PUBLIC class NamedArgument {

    public:

        friend ArgumentParser;

        NamedArgument() = delete;
        NamedArgument(const NamedArgument &na) = default;

        NamedArgument& operator=(const NamedArgument &na) = default;

    protected:

        NamedArgument(std::string name, std::vector<std::string> aliases, bool required,
                std::optional<std::string> defaultValue, std::size_t nargs, bool isFlag,
                std::vector<ArgumentVariant_t> variants, std::size_t maxCount) :
                                                                             name(std::move(name)),
                                                                             aliases(std::move(aliases)),
                                                                             required(required),
                                                                             defaultValue(std::move(defaultValue)),
                                                                             nargs(nargs), isFlag(isFlag),
                                                                             variants(std::move(variants)),
                                                                             maxCount(maxCount),
                                                                             _maxCountLeft(maxCount) {};

        std::string name;
        std::vector<std::string> aliases;

        bool required;  // ignored if is_flag is true
        std::optional<std::string> defaultValue;  // ignored if required is true

        std::size_t nargs;  // ignored if is_flag is true or if variants is not empty

        bool isFlag;
        std::vector<ArgumentVariant_t> variants;  // ignored if is_flag is true
        std::size_t maxCount;   // ignored if is_flag is true

        // internal stuff
        std::size_t _maxCountLeft;

    };

    DLL_PUBLIC class PositionalArgument {

    public:

        friend ArgumentParser;

        PositionalArgument() = delete;
        PositionalArgument(const PositionalArgument &pa) = default;

        PositionalArgument& operator=(const PositionalArgument &pa) = default;

        // for std::sort
        bool operator<(const PositionalArgument &pa) const {
            return position < pa.position;
        }

    protected:

        PositionalArgument(std::string name, std::string helpName, bool required,
                std::optional<std::string> defaultValue, std::vector<ArgumentVariant_t> variants,
                std::size_t maxCount, std::optional<long long int> position = std::nullopt) :
                                                                                  name(std::move(name)),
                                                                                  helpName(std::move(helpName)),
                                                                                  required(required),
                                                                                  defaultValue(std::move(defaultValue)),
                                                                                  variants(std::move(variants)),
                                                                                  maxCount(maxCount),
                                                                                  _maxCountLeft(maxCount) {
            this->position = position ? position.value() : ++positionCount;
        };

        std::string name;
        std::string helpName;

        bool required;
        std::optional<std::string> defaultValue;  // ignored if required is true

        std::vector<ArgumentVariant_t> variants;
        std::size_t maxCount;

        long long int position; // parsing several positional arguments with same position is UB

        // internal stuff
        std::size_t _maxCountLeft;
        static long long int positionCount;

    };

    DLL_PUBLIC class ParsedArgument {

    public:

        ParsedArgument(const ParsedArgument &pa) = default;
        ParsedArgument& operator=(const ParsedArgument &pa) = default;

        [[nodiscard]] std::string getString() const;
        [[nodiscard]] char getChar() const;
        [[nodiscard]] int getInt() const;
        [[nodiscard]] unsigned int getUInt() const;
        [[nodiscard]] long long int getLong() const;
        [[nodiscard]] unsigned long long int getULong() const;
        [[nodiscard]] float getFloat() const;
        [[nodiscard]] double getDouble() const;
        [[nodiscard]] long double getLongDouble() const;
        [[nodiscard]] bool getBool() const;

        inline operator std::string() const {
            return getString();
        }

        inline operator char() const {
            return getChar();
        }

        inline operator int() const {
            return getInt();
        }

        inline operator unsigned int() const {
            return getUInt();
        }

        inline operator long long int() const {
            return getLong();
        }

        inline operator unsigned long long int() const {
            return getULong();
        }

        inline operator float() const {
            return getFloat();
        }

        inline operator double () const {
            return getDouble();
        }

        inline operator long double() const {
            return getLongDouble();
        }

        inline operator bool() const {
            return getBool();
        }

    protected:

        ParsedArgument() = default;
        explicit ParsedArgument(std::string v) : value(std::move(v)) {};

        std::string value;

    };

    DLL_PUBLIC class ParsingResult {
        // TODO
    };

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
