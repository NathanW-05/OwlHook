#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

namespace string_util
{
    inline bool equals_ignore_case(const std::string& a, const std::string& b)
    {
        return std::equal(a.begin(), a.end(),
            b.begin(), b.end(),
            [](char a, char b) {
                return tolower(a) == tolower(b);
            });
    }

    inline std::vector<std::string> groups_by_token(std::string string, char token)
    {
        std::vector<std::string> words;

        std::stringstream check1(string);

        std::string intermediate;

        // Tokenizing w.r.t. space ' '
        while (getline(check1, intermediate, token))
        {
            words.push_back(intermediate);
        }

        return words;
    }
}