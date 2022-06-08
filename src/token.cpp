#include "token.hpp"

#include <unordered_map>

std::unordered_map<TokenCategory, std::string> token_names = {
    {END_OF_FILE, "END_OF_FILE"},
};

void Token::print()
{
    printf("          [%04d, %04d] (%04d, %20s) {%s}",
        (int)m_line, (int)m_col, m_cat, token_names[m_cat].c_str(), m_lex.c_str());
}
