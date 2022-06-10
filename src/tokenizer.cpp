#include "tokenizer.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <regex>

const std::vector<std::pair<std::regex, enum TokenCategory>> reg_list_words
{
    {std::regex("^[0-9]+\\.[0-9]+[^a-zA-Z0-9\\._]"), FLOAT_LITERAL },
    {std::regex("^[0-9]+[^a-zA-Z0-9\\._]"), INT_LITERAL },
    {std::regex("^i32[^a-zA-Z0-9_]"), INT32 },
    {std::regex("^u32[^a-zA-Z0-9_]"), UINT32 },
    {std::regex("^i64[^a-zA-Z0-9_]"), INT64 },
    {std::regex("^u64[^a-zA-Z0-9_]"), UINT64 },
    {std::regex("^f32[^a-zA-Z0-9_]"), FLOAT32 },
    {std::regex("^f64[^a-zA-Z0-9_]"), FLOAT64 },
    {std::regex("^char[^a-zA-Z0-9_]"), CHAR },
    {std::regex("^str[^a-zA-Z0-9_]"), STRING },
    {std::regex("^bool[^a-zA-Z0-9_]"), BOOLEAN },
    {std::regex("^true[^a-zA-Z0-9_]"), TRUE_CODE },
    {std::regex("^false[^a-zA-Z0-9_]"), FALSE_CODE },
    {std::regex("^as[ ]"), CAST_OP },
    {std::regex("^main[^a-zA-Z0-9_]"), MAIN_CODE },
    {std::regex("^printf[^a-zA-Z0-9_]"), PRINTF_CODE },
    {std::regex("^read[^a-zA-Z0-9_]"), READ_CODE },
    {std::regex("^return[^a-zA-Z0-9_]"), RETURN_CODE },
    {std::regex("^fn[^a-zA-Z0-9_]"), FN_CODE },
    {std::regex("^if[^a-zA-Z0-9_]"), IF_CODE },
    {std::regex("^else[^a-zA-Z0-9_]"), ELSE_CODE },
    {std::regex("^while[^a-zA-Z0-9_]"), WHILE_CODE },
    {std::regex("^for[^a-zA-Z0-9_]"), FOR_CODE },
};

const std::vector<std::pair<std::regex, enum TokenCategory>> reg_list_complement
{
    {std::regex("^\'[^']\'"), CHAR_LITERAL },
    {std::regex("^\"[^\"]*\""), STRING_LITERAL },
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
    {std::regex("^="), ASSIGN_OP },
    {std::regex("^!="), NTEQ_OP },
    {std::regex("^!"), NEGATION_OP },
    {std::regex("^>="), GTEQ_OP },
    {std::regex("^<="), LTEQ_OP },
    {std::regex("^>"), GT_OP },
    {std::regex("^<"), LT_OP },
    {std::regex("^\\{"), LEFT_BRACKET },
    {std::regex("^\\["), LEFT_SQRBRACKET },
    {std::regex("^\\("), LEFT_PAREN },
    {std::regex("^\\}"), RIGHT_BRACKET },
    {std::regex("^\\]"), RIGHT_SQRBRACKET },
    {std::regex("^\\)"), RIGHT_PAREN },
    {std::regex("^,"), COMMA },
    {std::regex("^:"), COLON },
    {std::regex("^;"), SEMICOLON },
    {std::regex("^[a-zA-Z][a-zA-Z0-9_]*"), IDENTIFIER },

    // The following are only for erros
    {std::regex("^[0-9.][0-9\\.a-zA-Z]*"), ERR_NUMBER_LITERAL},
    {std::regex("^\'[^']*\'"), ERR_CHAR},
};

std::regex reg_comment("^//");
std::regex reg_white_space("^ ");

TokenList tokenizer(std::fstream &file)
{
    std::deque<Token> token_list;

    std::string current_line;
    size_t line_pos, col_pos;
    for (line_pos = 0; std::getline(file, current_line); line_pos++)
    {
        printf("%4d  %s", (int)line_pos, current_line.c_str());

        size_t max_lenght;
        for (col_pos = 0, max_lenght = current_line.length(); col_pos < max_lenght; col_pos++)
        {
            std::cmatch matches;

            std::regex_search(&current_line[col_pos], matches, reg_comment);
            if (!matches.empty())
            {
                break;
            }

            std::regex_search(&current_line[col_pos], matches, reg_white_space);
            if (!matches.empty())
            {
                continue;
            }

            bool found = false;

            for (const auto &[reg_val, cat] : reg_list_words)
            {
                std::regex_search(&current_line[col_pos], matches, reg_val);
                if (!matches.empty())
                {
                    size_t match_size = matches.str(0).size() - 2;
                    token_list.push_back({cat, line_pos, col_pos, matches.str(0).substr(0, match_size+1)});
                    col_pos += match_size;

                    found = true;
                    break;
                }
            }

            if (found) continue;

            for (const auto &[reg_val, cat] : reg_list_complement)
            {
                std::regex_search(&current_line[col_pos], matches, reg_val);
                if (!matches.empty())
                {
                    size_t match_size = matches.str(0).size() - 1;
                    token_list.push_back({cat, line_pos, col_pos, matches.str(0)});
                    col_pos += match_size;

                    found = true;
                    break;
                }
            }

            if (!found)
            {
                std::string to_insert (1, current_line[col_pos]);
                token_list.push_back({ERR_SYMBOL, line_pos, col_pos, to_insert});
                col_pos += 1;
            }
        }
        std::cout << '\n';
    }

    token_list.push_back({END_OF_FILE, line_pos-1, col_pos, std::string("")});
    return {token_list};
}

Tokenizer::Tokenizer(const char *path)
    : m_file(path), m_line_pos(0), m_col_pos(0)
{
}

bool Tokenizer::is_open() const
{
    if (!m_file.is_open())
    {
        std::cerr << "File does not exits.\n Exiting...\n";
        return false;
    }
    return true;
}

auto Tokenizer::get_line()
{
    std::getline(m_file, m_current_line);
    if (m_file.eof())
    {
        return false;
    }
    return true;
}

Token Tokenizer::nextToken()
{
    if (m_token_list.size() == 0)
    {
        analyse_line();
    }
    const auto token = m_token_list.front();
    if (token.cat() != END_OF_FILE)
    {
        m_token_list.erase(m_token_list.begin());
    }
    return token;
}

void Tokenizer::analyse_line()
{
    if (!get_line())
    {
        m_token_list.push_back({END_OF_FILE, m_line_pos - 1, m_col_pos, std::string("")});
    }

    printf("%4d  %s\n", (int)m_line_pos, m_current_line.c_str());

    size_t max_lenght;
    for (m_col_pos = 0, max_lenght = m_current_line.length(); m_col_pos < max_lenght; m_col_pos++)
    {
        std::cmatch matches;

        std::regex_search(&m_current_line[m_col_pos], matches, reg_comment);
        if (!matches.empty())
        {
            break;
        }

        std::regex_search(&m_current_line[m_col_pos], matches, reg_white_space);
        if (!matches.empty())
        {
            continue;
        }
        
        bool found = false;

        for (const auto &[reg_val, cat] : reg_list_words)
        {
            std::regex_search(&m_current_line[m_col_pos], matches, reg_val);
            if (!matches.empty())
            {
                size_t match_size = matches.str(0).size() - 2;
                m_token_list.push_back({cat, m_line_pos, m_col_pos, matches.str(0).substr(0, match_size+1)});
                m_col_pos += match_size;

                found = true;
                break;
            }
        }

        if (found) continue;

        for (const auto &[reg_val, cat] : reg_list_complement)
        {
            std::regex_search(&m_current_line[m_col_pos], matches, reg_val);
            if (!matches.empty())
            {
                size_t match_size = matches.str(0).size() - 1;
                m_token_list.push_back({cat, m_line_pos, m_col_pos, matches.str(0)});
                m_col_pos += match_size;

                found = true;
                break;
            }
        }

        if (found) continue;

        { // if no strings matches
            std::string to_insert (1, m_current_line[m_col_pos]);
            m_token_list.push_back({ERR_SYMBOL, m_line_pos, m_col_pos, to_insert});
            m_col_pos += 1;
        }
    }

    m_line_pos += 1;
}