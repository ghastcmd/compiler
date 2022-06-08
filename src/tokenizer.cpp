#include "tokenizer.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <regex>

const std::vector<std::pair<std::regex, enum TokenCategory>> reg_list {
    {std::regex("^i32[^a-zA-Z0-9]"), INT32 },
    {std::regex("^u32[^a-zA-Z0-9]"), UINT32 },
    {std::regex("^i64[^a-zA-Z0-9]"), INT64 },
    {std::regex("^u64[^a-zA-Z0-9]"), UINT64 },
    {std::regex("^f32[^a-zA-Z0-9]"), FLOAT32 },
    {std::regex("^f64[^a-zA-Z0-9]"), FLOAT64 },
    {std::regex("^char[^a-zA-Z0-9]"), CHAR },
    {std::regex("^str[^a-zA-Z0-9]"), STRING },
    {std::regex("^bool[^a-zA-Z0-9]"), BOOLEAN },
    {std::regex("^(-)?[0-9]+"), INT_LITERAL },
    {std::regex("^(-)?[0-9]+\\.[0-9]+"), FLOAT_LITERAL },
    {std::regex("^\'[^']*\'"), CHAR_LITERAL },
    {std::regex("^\"[^\"]*\""), STRING_LITERAL },
    {std::regex("^true[^a-zA-Z0-9]"), TRUE_CODE },
    {std::regex("^false[^a-zA-Z0-9]"), FALSE_CODE },
    {std::regex("^as "), CAST_OP },
    {std::regex("^="), ASSIGN_OP },
    {std::regex("^\\.\\."), CONCAT_OP },
    {std::regex("^\\^"), LENGTH_OP },
    {std::regex("^\\+"), PLUS_OP },
    {std::regex("^-"), MINUS_OP },
    {std::regex("^\\*"), MULT_OP },
    {std::regex("^/"), DIV_OP },
    {std::regex("^%"), MOD_OP },
    {std::regex("^&&"), AND_OP },
    {std::regex("^\\|\\|"), OR_OP },
    {std::regex("^=="), EQ_OP },
    {std::regex("^!="), NTEQ_OP },
    {std::regex("^!"), NEGATION_OP },
    {std::regex("^>="), GTEQ_OP },
    {std::regex("^<="), LTEQ_OP },
    {std::regex("^>"), GT_OP },
    {std::regex("^<"), LT_OP },
    {std::regex("^main[^a-zA-Z0-9]"), MAIN_CODE },
    {std::regex("^return[^a-zA-Z0-9]"), RETURN_CODE },
    {std::regex("^fn[^a-zA-Z0-9]"), FN_CODE },
    {std::regex("^if[^a-zA-Z0-9]"), IF_CODE },
    {std::regex("^else[^a-zA-Z0-9]"), ELSE_CODE },
    {std::regex("^while[^a-zA-Z0-9]"), WHILE_CODE },
    {std::regex("^for[^a-zA-Z0-9]"), FOR_CODE },
    {std::regex("^\\{"), LEFT_BRACKET },
    {std::regex("^\\["), LEFT_SQRBRACKET },
    {std::regex("^\\("), LEFT_PAREN },
    {std::regex("^\\}"), RIGHT_BRACKET },
    {std::regex("^\\]"), RIGHT_SQRBRACKET },
    {std::regex("^\\)"), RIGHT_PAREN },
    {std::regex("^,"), COMMA },
    {std::regex("^:"), COLON },
    {std::regex("^;"), SEMICOLON },
    {std::regex("^\""), QUOTE },
    {std::regex("^'"), APOSTROPHE },
    {std::regex("^[a-zA-Z][a-zA-Z0-9_]*"), IDENTIFIER},
};

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
            std::cout << " '" << current_char << "' " << col_pos << ' ';

            std::cmatch matches;
            for (const auto &[reg_val, cat] : reg_list)
            {
                std::regex_search(&current_line[col_pos], matches, reg_val);
                if (!matches.empty())
                {
                    std::cout << matches.str(0);
                    size_t match_size = matches.str(0).size();
                    if (matches.str(0)[match_size-1] == ' ')
                    {
                        match_size -= 1;
                    }
                    token_list.push_back({cat, line_pos, col_pos, matches.str(0)});
                    col_pos += match_size;
                    break;
                }
            }
        }
        std::cout << '\n';
    }

    token_list.push_back({END_OF_FILE, line_pos, col_pos, std::string("")});
    return {token_list};
}