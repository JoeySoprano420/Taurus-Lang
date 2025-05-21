#pragma once
#include <string>

enum class TokenType {
    // Keywords
    START, RETURN, INIT, IF, ELSE, FOR, WHILE, TRY, CATCH, THROW,

    // Operators
    ASSIGN, IMMUTABLE_ASSIGN, PLUS, MINUS, MUL, DIV, MOD,
    EQ, NEQ, LT, GT, LE, GE, AND, OR, NOT,
    EXPONENT, RAISE, TRANSITION, ROLLBACK, RUN,
    ADD_ASSIGN, SUB_ASSIGN, MUL_ASSIGN, DIV_ASSIGN,

    // Symbols
    LPAREN, RPAREN, LBRACE, RBRACE, LBRACKET, RBRACKET,
    SEMICOLON, COLON, DOT, COMMA, PIPE, HASH, BACKSLASH,

    // Literals and Identifiers
    IDENTIFIER, NUMBER, STRING,

    // Macro and Control
    MACRO_OPEN, MACRO_CLOSE, TEXTURIZER, CONFIG, SPECIFIER, MODIFIER,

    // Comments
    COMMENT, MULTILINE_COMMENT,

    // Special
    END_OF_FILE, UNKNOWN
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;

    Token(TokenType t, const std::string& l, int ln, int col)
        : type(t), lexeme(l), line(ln), column(col) {}
};
