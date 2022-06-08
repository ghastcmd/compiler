#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

enum TokenCategory
{
    END_OF_FILE,
};

struct Token
{
public:
    Token(TokenCategory cat, size_t line, size_t col, std::string lex)
        : m_cat(cat), m_line(line), m_col(col), m_lex(lex)
    {
    }

   void print();

private:
    enum TokenCategory m_cat;
    size_t m_line, m_col;
    std::string m_lex;
};