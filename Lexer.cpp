#include "TokenType.h"
#include <cctype>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <iostream>

class Lexer {
public:
    Lexer(const std::string& src) : source(src), start(0), current(0), line(1), column(1) {}

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        while (!isAtEnd()) {
            start = current;
            Token token = scanToken();
            if (token.type != TokenType::COMMENT && token.type != TokenType::MULTILINE_COMMENT)
                tokens.push_back(token);
        }
        tokens.emplace_back(TokenType::END_OF_FILE, "", line, column);
        return tokens;
    }

private:
    std::string source;
    size_t start;
    size_t current;
    int line;
    int column;

    std::unordered_map<std::string, TokenType> keywords = {
        {"Start", TokenType::START}, {"Return", TokenType::RETURN}, {"Init", TokenType::INIT},
        {"if", TokenType::IF}, {"else", TokenType::ELSE}, {"for", TokenType::FOR},
        {"while", TokenType::WHILE}, {"try", TokenType::TRY}, {"catch", TokenType::CATCH},
        {"throw", TokenType::THROW}
    };

    Token scanToken() {
        char c = advance();

        switch (c) {
            case '(': return makeToken(TokenType::LPAREN);
            case ')': return makeToken(TokenType::RPAREN);
            case '{': return makeToken(TokenType::LBRACE);
            case '}': return makeToken(TokenType::RBRACE);
            case '[': return makeToken(TokenType::LBRACKET);
            case ']': return makeToken(TokenType::RBRACKET);
            case ';': return makeToken(TokenType::SEMICOLON);
            case ':': return makeToken(TokenType::COLON);
            case '.': return makeToken(TokenType::DOT);
            case ',': return makeToken(TokenType::COMMA);
            case '|': return makeToken(TokenType::PIPE);
            case '@': return makeToken(TokenType::SPECIFIER);
            case '$': return makeToken(TokenType::MODIFIER);
            case '!': return makeToken(TokenType::CONFIG);
            case '^': return makeToken(TokenType::EXPONENT);
            case '~':
                if (match('>')) return makeToken(TokenType::RAISE);
                break;
            case '-':
                if (match('>')) return makeToken(TokenType::TRANSITION);
                return makeToken(TokenType::MINUS);
            case '<':
                if (match('~')) return makeToken(TokenType::CONFIG);
                if (match('-')) return makeToken(TokenType::THROW);
                if (match('<')) return makeToken(TokenType::ROLLBACK);
                return makeToken(TokenType::LT);
            case '>':
                if (match('>')) return makeToken(TokenType::RUN);
                return makeToken(TokenType::GT);
            case '+': return makeToken(TokenType::PLUS);
            case '*': return makeToken(TokenType::MUL);
            case '/': return makeToken(TokenType::DIV);
            case '%': return makeToken(TokenType::MOD);
            case '=':
                if (match('=')) return makeToken(TokenType::IMMUTABLE_ASSIGN);
                return makeToken(TokenType::ASSIGN);
            case '#':
                while (peek() != '\n' && !isAtEnd()) advance();
                return makeToken(TokenType::COMMENT);
            case '*':
                if (peek() == '*') {
                    advance(); // consume second '*'
                    while (!isAtEnd() && !(peek() == '*' && peekNext() == '*')) advance();
                    if (!isAtEnd()) { advance(); advance(); }
                    return makeToken(TokenType::MULTILINE_COMMENT);
                }
                break;
            case '"': return string();
            default:
                if (std::isdigit(c)) return number();
                if (std::isalpha(c)) return identifier();
                break;
        }

        return makeToken(TokenType::UNKNOWN);
    }

    Token makeToken(TokenType type) {
        std::string lexeme = source.substr(start, current - start);
        return Token(type, lexeme, line, column);
    }

    char advance() {
        if (!isAtEnd()) {
            current++;
            column++;
            return source[current - 1];
        }
        return '\0';
    }

    bool match(char expected) {
        if (isAtEnd() || source[current] != expected) return false;
        current++;
        column++;
        return true;
    }

    char peek() const {
        return isAtEnd() ? '\0' : source[current];
    }

    char peekNext() const {
        return (current + 1 >= source.size()) ? '\0' : source[current + 1];
    }

    bool isAtEnd() const {
        return current >= source.size();
    }

    Token string() {
        while (!isAtEnd() && peek() != '"') {
            if (peek() == '\n') line++;
            advance();
        }
        if (isAtEnd()) return makeToken(TokenType::UNKNOWN);
        advance(); // closing "
        return makeToken(TokenType::STRING);
    }

    Token number() {
        while (std::isdigit(peek())) advance();
        return makeToken(TokenType::NUMBER);
    }

    Token identifier() {
        while (std::isalnum(peek())) advance();
        std::string text = source.substr(start, current - start);
        TokenType type = keywords.count(text) ? keywords[text] : TokenType::IDENTIFIER;
        return Token(type, text, line, column);
    }
};
