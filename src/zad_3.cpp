#include "../include/zad_3.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <numeric>
#include <optional>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace Day1Year2023
{

constexpr std::pair< std::string_view, int > WORDS[] = {{"one", 1},
                                                        {"two", 2},
                                                        {"three", 3},
                                                        {"four", 4},
                                                        {"five", 5},
                                                        {"six", 6},
                                                        {"seven", 7},
                                                        {"eight", 8},
                                                        {"nine", 9}};

auto load_lines(const std::string& filename) -> std::vector< std::string >
{
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Day1Year2023: Nie mozna otworzyc " + filename);

    std::vector< std::string > lines;
    std::string                line;
    while (std::getline(file, line))
    {
        if (!line.empty())
            lines.push_back(line);
    }
    return lines;
}

std::optional< int > find_digit_at(std::string_view line, size_t i, bool check_words)
{
    if (std::isdigit(line[i]))
    {
        return line[i] - '0';
    }
    if (check_words)
    {
        std::string_view suffix = line.substr(i);
        for (auto [word, val] : WORDS)
        {
            if (suffix.starts_with(word))
            {
                return val;
            }
        }
    }
    return std::nullopt;
}

long long solve_line(const std::string& line, bool part2)
{

    auto digits_view = std::views::iota(0u, line.length()) |
                       std::views::transform([&](size_t i) { return find_digit_at(line, i, part2); }) |
                       std::views::filter([](const auto& opt) { return opt.has_value(); }) |
                       std::views::transform([](const auto& opt) { return *opt; });

    std::vector< int > digits;
    for (int d : digits_view)
    {
        digits.push_back(d);
    }

    if (digits.empty())
        return 0;

    return digits.front() * 10 + digits.back();
}

void run()
{
    try
    {
        std::println("Day 1 Year 2023:");
        auto lines = load_lines("include/zad_3_input.txt");

        long long sum_p1 = 0;
        for (const auto& line : lines)
        {
            sum_p1 += solve_line(line, false);
        }

        long long sum_p2 = 0;
        for (const auto& line : lines)
        {
            sum_p2 += solve_line(line, true);
        }

        std::println("Part 1 (Only digits): {}", sum_p1);
        std::println("Part 2 (Words too): {}", sum_p2);
    }
    catch (const std::exception& e)
    {
        std::cerr << "BLAD (2023 Day 1): " << e.what() << "\n";
    }
}
} // namespace Day1Year2023