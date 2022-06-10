#pragma once

#include "token.hpp"

#include <fstream>
#include <deque>

struct TokenList
{
    TokenList(std::deque<Token> vec)
        : m_deque(vec)
    {
    }

    auto begin()
    {
        return m_deque.begin();
    }

    auto end()
    {
        return m_deque.end();
    }

    Token nextToken()
    {
        const auto token = m_deque.front();
        if (token.cat() != END_OF_FILE)
        {
            m_deque.erase(m_deque.begin());
        }
        return token;
    }

private:
    std::deque<Token> m_deque;
};

struct Tokenizer
{
    Tokenizer(const char *path);

    bool is_open() const;

    auto get_line();

    Token nextToken();

    void analyse_line();

private:
    std::fstream m_file;
    size_t m_line_pos, m_col_pos;
    
    std::string m_current_line;
    std::deque<Token> m_token_list;
};

TokenList tokenizer(std::fstream &file);