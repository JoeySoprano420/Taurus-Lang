#include "TokenType.h"
#include "ast.h"
#include <vector>
#include <stdexcept>

class Parser {
public:
    Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

    std::shared_ptr<Program> parseProgram() {
        auto program = std::make_shared<Program>();
        while (!isAtEnd()) {
            program->statements.push_back(parseStatement());
        }
        return program;
    }

private:
    const std::vector<Token>& tokens;
    size_t current;

    Token peek() const { return tokens[current]; }
    Token advance() { return tokens[current++]; }
    bool match(TokenType type) {
        if (peek().type == type) { advance(); return true; }
        return false;
    }

    bool isAtEnd() const { return peek().type == TokenType::END_OF_FILE; }

    Token consume(TokenType type, const std::string& errMsg) {
        if (match(type)) return tokens[current - 1];
        throw std::runtime_error("Parse error at line " + std::to_string(peek().line) + ": " + errMsg);
    }

    ASTNodePtr parseStatement() {
        if (match(TokenType::INIT)) return parseInit();
        if (match(TokenType::IDENTIFIER)) return parseAssignment();
        if (match(TokenType::IF)) return parseIf();
        if (match(TokenType::RETURN)) return std::make_shared<ReturnStmt>(peek().line, peek().column);
        if (match(TokenType::START)) return parseFunction();
        return nullptr;
    }

    ASTNodePtr parseInit() {
        Token var = consume(TokenType::IDENTIFIER, "Expected variable name after Init");
        consume(TokenType::ASSIGN, "Expected '=' after variable name");
        auto value = parseExpression();
        consume(TokenType::SEMICOLON, "Expected ';' after Init");
        return std::make_shared<InitStmt>(var.lexeme, value, var.line, var.column);
    }

    ASTNodePtr parseAssignment() {
        Token var = tokens[current - 1];
        consume(TokenType::ASSIGN, "Expected '=' in assignment");
        auto value = parseExpression();
        consume(TokenType::SEMICOLON, "Expected ';' after assignment");
        return std::make_shared<AssignStmt>(var.lexeme, value, var.line, var.column);
    }

    ASTNodePtr parseExpression() {
        return parseBinary();
    }

    ASTNodePtr parseBinary(int precedence = 0) {
        auto left = parsePrimary();
        while (isBinaryOperator(peek().type)) {
            std::string op = advance().lexeme;
            auto right = parsePrimary();
            left = std::make_shared<Expression>(left, op, right, peek().line, peek().column);
        }
        return left;
    }

    bool isBinaryOperator(TokenType type) {
        return type == TokenType::PLUS || type == TokenType::MINUS ||
               type == TokenType::MUL  || type == TokenType::DIV  ||
               type == TokenType::MOD  || type == TokenType::EQ   ||
               type == TokenType::LT   || type == TokenType::GT;
    }

    ASTNodePtr parsePrimary() {
        Token token = advance();
        switch (token.type) {
            case TokenType::NUMBER:
            case TokenType::STRING:
                return std::make_shared<Literal>(token.lexeme, token.line, token.column);
            case TokenType::IDENTIFIER:
                return std::make_shared<Identifier>(token.lexeme, token.line, token.column);
            case TokenType::LPAREN: {
                auto expr = parseExpression();
                consume(TokenType::RPAREN, "Expected ')'");
                return expr;
            }
            default:
                throw std::runtime_error("Unexpected token: " + token.lexeme);
        }
    }

    ASTNodePtr parseIf() {
        consume(TokenType::LPAREN, "Expected '(' after if");
        auto condition = parseExpression();
        consume(TokenType::RPAREN, "Expected ')' after condition");

        auto ifNode = std::make_shared<IfStmt>(condition, peek().line, peek().column);
        ifNode->thenBlock = parseBlock();

        if (match(TokenType::ELSE)) {
            ifNode->elseBlock = parseBlock();
        }

        return ifNode;
    }

    std::vector<ASTNodePtr> parseBlock() {
        consume(TokenType::LBRACE, "Expected '{'");
        std::vector<ASTNodePtr> block;
        while (!match(TokenType::RBRACE) && !isAtEnd()) {
            block.push_back(parseStatement());
        }
        return block;
    }

    ASTNodePtr parseFunction() {
        auto func = std::make_shared<BlockStmt>();
        func->statements = parseBlock();
        consume(TokenType::RETURN, "Expected 'Return;' after block");
        consume(TokenType::SEMICOLON, "Expected ';' after Return");
        return func;
    }
};
