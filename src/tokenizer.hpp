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

    Token nextToken()
    {
        const auto token = m_deque.front();
        m_deque.erase(m_deque.begin());
        return token;
    }

private:
    std::deque<Token> m_deque;
};

TokenList tokenizer(std::fstream &file);