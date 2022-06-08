#include "tokenizer.hpp"

#include <iostream>
#include <string>
#include <vector>

TokenList tokenizer(std::fstream &file)
{
    std::deque<Token> token_list;

    std::string current_line;
    size_t line_pos, col_pos;
    for (line_pos = 0; std::getline(file, current_line); line_pos++)
    {
        char current_char = current_line[0];

        printf("%4d  %s\n", (int)line_pos, current_line.c_str());

        std::cout << line_pos << "-- \n\t";
        size_t max_lenght;
        for (col_pos = 0, max_lenght = current_line.length(); col_pos <= max_lenght; col_pos++)
        {
            current_char = current_line[col_pos];
            // std::cout << (int)current_char << '\n';
            std::cout << " '" << current_char << "' " << (int)current_char << ' ';
        }
        std::cout << '\n';
    }

    token_list.push_back({END_OF_FILE, line_pos, col_pos, std::string("")});
    return {token_list};
}