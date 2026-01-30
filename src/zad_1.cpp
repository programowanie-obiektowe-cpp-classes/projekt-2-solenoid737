#include "../include/zad_1.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <print>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

namespace Day1Year2024
{

auto load_data(const std::string& filename) -> std::pair< std::vector< int >, std::vector< int > >
{
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Day1Year2024: Nie mozna otworzyc " + filename);

    std::vector< int > left, right;
    int                l, r;
    while (file >> l >> r)
    {
        left.push_back(l);
        right.push_back(r);
    }
    if (left.empty())
        throw std::runtime_error("Day1Year2024: Pusty plik");
    return {left, right};
}

long long solve_part_1(std::vector< int > left, std::vector< int > right)
{
    std::ranges::sort(left);
    std::ranges::sort(right);

    auto distances = std::views::zip(left, right) | std::views::transform([](const auto& pair) {
                         auto [l, r] = pair;
                         return std::abs(l - r);
                     });
    return std::ranges::fold_left(distances, 0LL, std::plus<>{});
}

long long solve_part_2(const std::vector< int >& left, const std::vector< int >& right)
{
    std::unordered_map< int, int > counts;
    for (int num : right)
        counts[num]++;

    auto scores = left | std::views::filter([&](int num) { return counts.contains(num); }) |
                  std::views::transform([&](int num) { return static_cast< long long >(num) * counts[num]; });
    return std::ranges::fold_left(scores, 0LL, std::plus<>{});
}

void run()
{
    try
    {
        std::println("Day 1 Year 2024:");
        auto [l, r] = load_data("include/zad_1_input.txt");

        std::println("Part 1: {}", solve_part_1(l, r));
        std::println("Part 2: {}", solve_part_2(l, r));
    }
    catch (const std::exception& e)
    {
        std::cerr << "BLAD (Day 1 Year 2024): " << e.what() << "\n";
    }
}
} // namespace Day1Year2024