#include <iostream>
#include <fstream>
#include <string>
#include <map>

#define FOREGROUND(color, text) "\x1B[" << static_cast<int>(color) << "m" << text << "\033[0m"
#define BACKGROUND(color, text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"


enum class ForegroundColor : int
{
    Red = 31,
    Green = 32,
    Yellow = 33,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93
};

enum class BackgroundColor : int
{
    Red = 41,
    Green = 42,
    Yellow = 43,
    BrightRed = 101,
    BrightGreen = 102,
    BrightYellow = 103
};

std::string GetRandomWord()
{
    srand(time(0));
    int random = rand() % 8000;
    int lineNumber = 0;

    std::ifstream file ("words.txt");
    std::string line;

    while (getline(file, line))
    {
        lineNumber++;
        if (lineNumber == random)
            return line;
    }
}

void make_uppercase(std::string& string)
{
    int i = 0;

    for (char c : string)
    {
        string[i] = std::toupper(c);
        i++;
    }
}

void print_color(char character, int value)
{
    if(value <= 5)
        std::cout << BACKGROUND(BackgroundColor::Red, character) << " ";

    else if(value > 5 && value < 100)
        std::cout << BACKGROUND(BackgroundColor::Yellow, character) << " ";

    else
        std::cout << BACKGROUND(BackgroundColor::Green, character) << " ";
}

void compare_strings(std::string input_string, std::string random_string)
{
    int value = 0;

    for (size_t i = 0; i < random_string.length(); i++)
    {
        value = 0;

        for (size_t j = 0; j < random_string.length(); j++)
        {
            if (input_string[i] == random_string[j])
            {
                if (i == j)
                {
                    value += 100;
                }
                else
                {
                    value += 10;
                }
            }
            else
            {
                value += 1;
            }
        }
        print_color(input_string[i], value);
    }
}

int main()
{
start_of_main:
    std::string player_input;
    std::string random_string = GetRandomWord();

    int guesses = 0;
    bool running = true;

    std::cout << "Wordle!!\nType your guess:\n";

    while (running)
    {
        if (guesses <= 4) // 5 guesses
        {
            std::cout << "\n";
            std::cin >> player_input;
            guesses++;

            make_uppercase(player_input);
            make_uppercase(random_string);

            compare_strings(player_input, random_string);
        }
        else
        {
            std::cout << "\n";
            std::cout << "The correct word was:\n" << random_string << std::endl;

            std::cout << "Try again?\nY / N" << std::endl;
            std::cin >> player_input;

            if (player_input == "n" || player_input == "N")
                running = false;

            else if (player_input == "y" || player_input == "Y")
                goto start_of_main;

            else
                std::cout << "Y / N";
        }
    }
}