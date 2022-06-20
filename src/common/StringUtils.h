//
// Created by xiaozhuai on 2020/11/26.
//

#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

inline char toLowerChar(char c) {
    return static_cast<char>(::tolower(c));
}

inline char toUpperChar(char c) {
    return static_cast<char>(::toupper(c));
}

class StringUtils {
public:
    StringUtils() = delete;

    static inline std::string trimCopy(std::string str, const char *characters = " \t\r\n") {
        return str.erase(0, str.find_first_not_of(characters))
                .erase(str.find_last_not_of(characters) + 1);
    }

    static inline std::string ltrimCopy(std::string str, const char *characters = " \t\r\n") {
        return str.erase(0, str.find_first_not_of(characters));
    }

    static inline std::string rtrimCopy(std::string str, const char *characters = " \t\r\n") {
        return str.erase(str.find_last_not_of(characters) + 1);
    }

    static inline std::string &trim(std::string &str, const char *characters = " \t\r\n") {
        return str.erase(0, str.find_first_not_of(characters))
                .erase(str.find_last_not_of(characters) + 1);
    }

    static inline std::string &ltrim(std::string &str, const char *characters = " \t\r\n") {
        return str.erase(0, str.find_first_not_of(characters));
    }

    static inline std::string &rtrim(std::string &str, const char *characters = " \t\r\n") {
        return str.erase(str.find_last_not_of(characters) + 1);
    }

    static inline std::string toLowerCopy(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), toLowerChar);
        return str;
    }

    static inline std::string toUpperCopy(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), toUpperChar);
        return str;
    }

    static inline std::string &toLower(std::string &str) {
        std::transform(str.begin(), str.end(), str.begin(), toLowerChar);
        return str;
    }

    static inline std::string &toUpper(std::string &str) {
        std::transform(str.begin(), str.end(), str.begin(), toUpperChar);
        return str;
    }

    static std::string replaceCopy(std::string text, const std::string &search, const std::string &replace) {
        if (search == replace) {
            return text;
        }
        size_t index = text.find(search, 0);
        size_t searchLength = search.length();
        size_t replaceLength = replace.length();

        while (std::string::npos != index) {
            text.replace(index, searchLength, replace);
            index = text.find(search, index - searchLength + replaceLength + 1);
        }
        return text;
    }

    static std::string &replace(std::string &text, const std::string &search, const std::string &replace) {
        if (search == replace) {
            return text;
        }
        size_t index = text.find(search, 0);
        size_t searchLength = search.length();
        size_t replaceLength = replace.length();

        while (std::string::npos != index) {
            text.replace(index, searchLength, replace);
            index = text.find(search, index - searchLength + replaceLength + 1);
        }
        return text;
    }

    static std::vector<std::string> explode(const std::string &text, const std::string &separator, size_t limit = -1) {
        std::vector<std::string> result;
        size_t pos = 0;
        size_t separatorPos = text.find(separator, pos);
        while (separatorPos != std::string::npos) {
            std::string token = text.substr(pos, separatorPos - pos);
            result.push_back(token);
            pos = separatorPos + separator.length();
            if (result.size() + 1 == limit) {
                break;
            }
            separatorPos = text.find(separator, pos);
        }
        result.push_back(text.substr(pos));
        return result;
    }

    static bool startsWith(const std::string &str, const std::string &prefix, bool ignoreCase = false) {
        size_t s = str.size();
        size_t ps = prefix.size();
        if (ignoreCase) {
            return s >= ps && StringUtils::toLowerCopy(str.substr(0, ps)) == StringUtils::toLowerCopy(prefix);
        } else {
            return s >= ps && str.substr(0, ps) == prefix;
        }
    }

    static bool endsWith(const std::string &str, const std::string &suffix, bool ignoreCase = false) {
        size_t s = str.size();
        size_t ss = suffix.size();
        if (ignoreCase) {
            return s >= ss && StringUtils::toLowerCopy(str.substr(s - ss, s)) == StringUtils::toLowerCopy(suffix);
        } else {
            return s >= ss && str.substr(s - ss, s) == suffix;
        }
    }

    static std::string padLeft(const std::string &str, char c, int size) {
        return str.size() < size ? (std::string(size - str.size(), c) + str) : str;
    }

    static std::string padRight(const std::string &str, char c, int size) {
        return str.size() < size ? (str + std::string(size - str.size(), c)) : str;
    }
};
