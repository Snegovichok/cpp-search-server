#pragma once

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

template <typename Key, typename Value>
auto& Print(std::ostream& out, const std::map<Key, Value>& map) {
    bool first_elem = true;
    for (const auto& [k, v] : map) {
        if (first_elem) {
            out << k << ": " << v;
            first_elem = false;
            continue;
        }
        out << ", " << k << ": " << v;
    }

    return out;
}

template <typename Element>
auto& Print(std::ostream& out, const Element& elem) {
    bool first_elem = true;
    for (const auto& el : elem) {
        if (first_elem) {
            out << el;
            first_elem = false;
            continue;
        }
        out << ", " << el;
    }

    return out;
}

template <typename Vector>
std::ostream& operator<<(std::ostream& out, const std::vector<Vector>& vec) {
    out << "[";
    return Print(out, vec) << "]";
}

template <typename Set>
std::ostream& operator<<(std::ostream& out, const std::set<Set>& set) {
    out << "{";
    return Print(out, set) << "}";
}

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& out, const std::map<Key, Value>& map) {
    out << "{";
    return Print(out, map) << "}";
}

template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const std::string& t_str, const std::string& u_str, const std::string& file,
    const std::string& func, unsigned line, const std::string& hint) {
    if (t != u) {
        std::cerr << std::boolalpha;
        std::cerr << file << "(" << line << "): " << func << ": ";
        std::cerr << "ASSERT_EQUAL(" << t_str << ", " << u_str << ") failed: ";
        std::cerr << t << " != " << u << ".";
        if (!hint.empty()) {
            std::cerr << " Hint: " << hint;
        }
        std::cerr << std::endl;
        abort();
    }
}

void AssertImpl(bool value, const std::string& expr_str, const std::string& file, const std::string& func, unsigned line,
    const std::string& hint);

template <typename Func, typename Str>
void RunTestImpl(const Func& func, const Str& func_str) {
    func();
    std::cerr << func_str << " OK" << std::endl;
}