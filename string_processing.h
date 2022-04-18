#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <set>
#include <map>

template <typename StringContainer>
std::set<std::string, std::less<>> MakeUniqueNonEmptyStrings(const StringContainer& strings) {
    std::set<std::string, std::less<>> non_empty_strings;
    for (std::string_view str : strings) {
        if (!str.empty()) {
            non_empty_strings.insert(static_cast<std::string>(str));
        }
    }
    return non_empty_strings;
}

std::vector<std::string_view> SplitIntoWords(std::string_view text);
std::vector<std::string> SplitIntoWords(const std::string& text);