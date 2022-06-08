#pragma once

#include "token.hpp"

#include <fstream>

struct Token
{
    int line, col;
    enum TokenCategory cat;
    std::string lex;
};

struct TokenList
{
    Token nextToken();
};

TokenList tokenizer(std::fstream &file);