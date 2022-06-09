#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

enum TokenCategory
{
    END_OF_FILE,
    WHITE_SPACE,
    IDENTIFIER,
    INT32,
    UINT32,
    INT64,
    UINT64,
    FLOAT32,
    FLOAT64,
    CHAR,
    STRING,
    BOOLEAN,
    INT_LITERAL,
    FLOAT_LITERAL,
    CHAR_LITERAL,
    STRING_LITERAL,
    TRUE_CODE,
    FALSE_CODE,
    NEGATION_OP,
    CAST_OP,
    ASSIGN_OP,
    CONCAT_OP,
    LENGTH_OP,
    PLUS_OP,
    MINUS_OP,
    MULT_OP,
    DIV_OP,
    MOD_OP,
    AND_OP,
    OR_OP,
    EQ_OP,
    NTEQ_OP,
    GT_OP,
    LT_OP,
    GTEQ_OP,
    LTEQ_OP,
    MAIN_CODE,
    RETURN_CODE,
    FN_CODE,
    IF_CODE,
    ELSE_CODE,
    WHILE_CODE,
    FOR_CODE,
    LEFT_BRACKET,
    LEFT_SQRBRACKET,
    LEFT_PAREN,
    RIGHT_BRACKET,
    RIGHT_SQRBRACKET,
    RIGHT_PAREN,
    COMMA,
    COLON,
    SEMICOLON,
    QUOTE,
    APOSTROPHE,
};

struct Token
{
public:
    Token(TokenCategory cat, size_t line, size_t col, std::string lex)
        : m_cat(cat), m_line(line), m_col(col), m_lex(lex)
    {
    }

   void print() const;

private:
    enum TokenCategory m_cat;
    size_t m_line, m_col;
    std::string m_lex;
};