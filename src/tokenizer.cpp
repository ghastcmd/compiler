#include "tokenizer.hpp"

#include <iostream>

Token TokenList::nextToken()
{
    return {};
}

TokenList tokenizer(std::fstream &file)
{
    std::cout << file.rdbuf() << '\n';
    return {};
}