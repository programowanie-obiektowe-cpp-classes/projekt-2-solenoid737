#include "../include/zad_4.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <print>
#include <ranges>
#include <string>
#include <vector>

namespace Day1Year2022
{

auto load_elves_data(const std::string& filename) -> std::vector< long long >
{
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Day1Year2022: Nie mozna otworzyc " + filename);

    std::vector< long long > elves_sums;
    std::string              line;
    long long                current_elf_sum = 0;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            elves_sums.push_back(current_elf_sum);
            current_elf_sum = 0;
        }
        else
        {
            current_elf_sum += std::stoll(line);
        }
    }

    if (current_elf_sum > 0)
    {
        elves_sums.push_back(current_elf_sum);
    }

    return elves_sums;
}

void run()
{
    try
    {
        std::println("Day 1 Year 2022: ");
        auto elves = load_elves_data("include/zad_4_input.txt");

        if (elves.empty())
        {
            std::println("Brak danych.");
            return;
        }

        long long max_calories = std::ranges::max(elves);
        std::println("Part 1 (Max calories): {}", max_calories);

        std::ranges::sort(elves, std::greater<>{});

        auto top3_view = elves | std::views::take(3);

        long long top3_sum = std::ranges::fold_left(top3_view, 0LL, std::plus<>{});

        std::println("Part 2 (Top 3 sum):    {}", top3_sum);
    }
    catch (const std::exception& e)
    {
        std::cerr << "BLAD (2022 Day 1): " << e.what() << "\n";
    }
}
} // namespace Day1Year2022