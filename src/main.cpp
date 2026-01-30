#include "../include/zad_1.hpp"
#include "../include/zad_2.hpp"
#include "../include/zad_3.hpp"
#include "../include/zad_4.hpp"
#include <print>
#include <iostream>

int main()
{
    std::println("Projekt 2, autor: Hubert Piwowarski");
    std::println("Zadania z Advent of Code:");
    std::println("Wybierz zadanie:");
    std::println("1. 2024 Day 1 (Locations)");
    std::println("2. 2024 Day 2 (Reports)");
    std::println("3. 2023 Day 1 (Trebuchet)");
    std::println("4. 2022 Day 1 (Calories)");
    std::println("0. Wyjscie");
    std::print("> ");

    int choice;
    if (!(std::cin >> choice))
        return 0;

    switch (choice)
    {
    case 1:
        Day1Year2024::run();
        break;
    case 2:
        Day2Year2024::run();
        break;
    case 3:
        Day1Year2023::run();
        break;
    case 4:
        Day1Year2022::run();
        break;
    default:
        std::cout << "Koniec programu.\n";
    }

    return 0;
}