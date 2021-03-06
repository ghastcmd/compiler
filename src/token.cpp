#include "token.hpp"

#include <unordered_map>
#include <stdio.h>

std::unordered_map<TokenCategory, std::string> token_names = {
    { END_OF_FILE,"END_OF_FILE" },
    { IDENTIFIER,"IDENTIFIER" },
    { INT32,"INT32" },
    { UINT32,"UINT32" },
    { INT64,"INT64" },
    { UINT64,"UINT64" },
    { FLOAT32,"FLOAT32" },
    { FLOAT64,"FLOAT64" },
    { CHAR,"CHAR" },
    { STRING,"STRING" },
    { BOOLEAN,"BOOLEAN" },
    { INT_LITERAL,"INT_LITERAL" },
    { FLOAT_LITERAL,"FLOAT_LITERAL" },
    { CHAR_LITERAL,"CHAR_LITERAL" },
    { STRING_LITERAL,"STRING_LITERAL" },
    { TRUE_CODE,"TRUE_CODE" },
    { FALSE_CODE,"FALSE_CODE" },
    { NEGATION_OP,"NEGATION_OP" },
    { CAST_OP,"CAST_OP" },
    { ASSIGN_OP,"ASSIGN_OP" },
    { CONCAT_OP,"CONCAT_OP" },
    { LENGTH_OP,"LENGTH_OP" },
    { PLUS_OP,"PLUS_OP" },
    { MINUS_OP,"MINUS_OP" },
    { MULT_OP,"MULT_OP" },
    { DIV_OP,"DIV_OP" },
    { MOD_OP,"MOD_OP" },
    { AND_OP,"AND_OP" },
    { OR_OP,"OR_OP" },
    { EQ_OP,"EQ_OP" },
    { NTEQ_OP,"NTEQ_OP" },
    { GT_OP,"GT_OP" },
    { LT_OP,"LT_OP" },
    { GTEQ_OP,"GTEQ_OP" },
    { LTEQ_OP,"LTEQ_OP" },
    { MAIN_CODE,"MAIN_CODE" },
    { PRINTF_CODE, "PRINTF_CODE" },
    { READ_CODE, "READ_CODE" },
    { RETURN_CODE,"RETURN_CODE" },
    { FN_CODE,"FN_CODE" },
    { IF_CODE,"IF_CODE" },
    { ELSE_CODE,"ELSE_CODE" },
    { WHILE_CODE,"WHILE_CODE" },
    { FOR_CODE,"FOR_CODE" },
    { LEFT_BRACKET,"LEFT_BRACKET" },
    { LEFT_SQRBRACKET,"LEFT_SQRBRACKET" },
    { LEFT_PAREN,"LEFT_PAREN" },
    { RIGHT_BRACKET,"RIGHT_BRACKET" },
    { RIGHT_SQRBRACKET,"RIGHT_SQRBRACKET" },
    { RIGHT_PAREN,"RIGHT_PAREN" },
    { COMMA,"COMMA" },
    { COLON,"COLON" },
    { SEMICOLON,"SEMICOLON" },

    {ERR_NUMBER_LITERAL, "ERR_NUMBER_LITERAL"},
    {ERR_SYMBOL, "ERR_SYMBOL"},
    {ERR_CHAR, "ERR_CHAR"},
};

void Token::print() const
{
    printf("          [%04d, %04d] (%04d, %20s) {%s}\n",
        (int)m_line, (int)m_col, m_cat, token_names[m_cat].c_str(), m_lex.c_str());
}

TokenCategory Token::cat() const
{
    return m_cat;
}