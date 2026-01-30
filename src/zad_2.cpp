#include "../include/zad_2.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

namespace Day2Year2024
{

using Report = std::vector< int >;

auto load_reports(const std::string& filename) -> std::vector< Report >
{
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Day2Year2024: Nie mozna otworzyc " + filename);

    std::vector< Report > reports;
    std::string           line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        std::stringstream ss(line);
        Report            r;
        int               level;
        while (ss >> level)
            r.push_back(level);
        reports.push_back(r);
    }
    return reports;
}

bool is_safe_report(const Report& r)
{
    if (r.size() < 2)
        return true;

    auto pairs = r | std::views::adjacent< 2 >;

    bool inc = std::ranges::all_of(pairs, [](const auto& p) {
        auto [a, b] = p;
        return (b - a) >= 1 && (b - a) <= 3;
    });
    bool dec = std::ranges::all_of(pairs, [](const auto& p) {
        auto [a, b] = p;
        return (b - a) <= -1 && (b - a) >= -3;
    });
    return inc || dec;
}

bool is_safe_with_dampener(const Report& r)
{
    if (is_safe_report(r))
        return true;
    for (size_t i = 0; i < r.size(); ++i)
    {
        Report temp = r;
        temp.erase(temp.begin() + i);
        if (is_safe_report(temp))
            return true;
    }
    return false;
}

void run()
{
    try
    {
        std::println("Day 2 Year 2024:");
        auto reports = load_reports("include/zad_2_input.txt");

        auto p1 = std::ranges::distance(reports | std::views::filter(is_safe_report));
        auto p2 = std::ranges::distance(reports | std::views::filter(is_safe_with_dampener));

        std::println("Part 1: {}", p1);
        std::println("Part 2: {}", p2);
    }
    catch (const std::exception& e)
    {
        std::cerr << "BLAD (2024 Day 2): " << e.what() << "\n";
    }
}
} // namespace Day2Year2024