#include "TokenType.h"
#include "ast.h"
#include <vector>
#include <stdexcept>
#include <memory>

class Parser {
public:
    Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

    std::shared_ptr<ProgramNode> parseProgram() {
        auto program = std::make_shared<ProgramNode>();
        while (!isAtEnd()) {
            auto stmt = parseStatement();
            if (stmt) program->body.push_back(stmt);
        }
        return program;
    }

private:
    const std::vector<Token>& tokens;
    size_t current;

    Token peek() const { return tokens[current]; }
    Token advance() { return tokens[current++]; }
    bool isAtEnd() const { return peek().type == TokenType::END_OF_FILE; }
    bool match(TokenType type) { if (peek().type == type) { advance(); return true; } return false; }

    Token consume(TokenType type, const std::string& errorMessage) {
        if (match(type)) return tokens[current - 1];
        throw std::runtime_error("Parse Error: " + errorMessage);
    }

    ASTNodePtr parseStatement() {
        if (match(TokenType::INIT)) return parseInit();
        if (match(TokenType::IF)) return parseIf();
        if (match(TokenType::FOR)) return parseFor();
        if (match(TokenType::WHILE)) return parseWhile();
        if (match(TokenType::LOOP)) return parseLoop();
        if (match(TokenType::REPEAT)) return parseRepeat();
        if (match(TokenType::TRY)) return parseTryCatch();
        if (match(TokenType::PIPE)) return parseMacro();
        if (match(TokenType::FUNC)) return parseFuncDecl();
        if (match(TokenType::RETURN)) return parseReturn();
        if (match(TokenType::MATCH)) return parseMatch();
        if (match(TokenType::ASYNC)) return parseAsync();
        if (match(TokenType::AWAIT)) return parseAwait();
        if (match(TokenType::MUTEX)) return parseMutex();
        if (match(TokenType::STRUCT)) return parseStruct();
        if (match(TokenType::CLASS)) return parseClass();
        if (match(TokenType::ALOC)) return parseAlloc();
        if (match(TokenType::FREE)) return parseFree();
        return nullptr;
    }

    ASTNodePtr parseMatch() {
        consume(TokenType::LPAREN, "Expected '(' after match");
        auto expr = parseExpression();
        consume(TokenType::RPAREN, "Expected ')'");
        consume(TokenType::LBRACE, "Expected '{'");
        while (!match(TokenType::RBRACE) && !isAtEnd()) {
            if (match(TokenType::CASE)) {
                parseExpression();
                consume(TokenType::COLON, "Expected ':' after case");
                parseBlock();
            } else if (match(TokenType::DEFAULT)) {
                consume(TokenType::COLON, "Expected ':' after default");
                parseBlock();
            }
        }
        return std::make_shared<ASTNode>(ASTNode{ ASTNodeType::Match, expr->line, expr->column });
    }

    ASTNodePtr parseAsync() {
        auto block = parseBlock();
        return std::make_shared<ASTNode>(ASTNode{ ASTNodeType::Async, block.front()->line, block.front()->column });
    }

    ASTNodePtr parseAwait() {
        auto expr = parseExpression();
        return std::make_shared<ASTNode>(ASTNode{ ASTNodeType::Await, expr->line, expr->column });
    }

    ASTNodePtr parseMutex() {
        auto block = parseBlock();
        return std::make_shared<ASTNode>(ASTNode{ ASTNodeType::Mutex, block.front()->line, block.front()->column });
    }

    ASTNodePtr parseStruct() {
        Token name = consume(TokenType::IDENTIFIER, "Expected struct name");
        consume(TokenType::LBRACE, "Expected '{'");
        while (!match(TokenType::RBRACE) && !isAtEnd()) {
            parseStatement();
        }
        return std::make_shared<ASTNode>(ASTNode{ ASTNodeType::StructDecl, name.line, name.column });
    }

    ASTNodePtr parseClass() {
        Token name = consume(TokenType::IDENTIFIER, "Expected class name");
        consume(TokenType::LBRACE, "Expected '{'");
        while (!match(TokenType::RBRACE) && !isAtEnd()) {
            parseStatement();
        }
        return std::make_shared<ASTNode>(ASTNode{ ASTNodeType::ClassDecl, name.line, name.column });
    }

    ASTNodePtr parseAlloc() {
        Token typenameTok = consume(TokenType::IDENTIFIER, "Expected type name for allocation");
        consume(TokenType::SEMICOLON, "Expected ';' after allocation");
        return std::make_shared<ASTNode>(ASTNode{ ASTNodeType::Memory, typenameTok.line, typenameTok.column });
    }

    ASTNodePtr parseFree() {
        Token var = consume(TokenType::IDENTIFIER, "Expected variable name to free");
        consume(TokenType::SEMICOLON, "Expected ';' after free");
        return std::make_shared<ASTNode>(ASTNode{ ASTNodeType::Memory, var.line, var.column });
    }

    // ... (keep existing methods untouched)
};

#include "TokenType.h"
#include "ast.h"
#include <vector>
#include <stdexcept>
#include <memory>

class Parser {
public:
    Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

    std::shared_ptr<ProgramNode> parseProgram() {
        auto program = std::make_shared<ProgramNode>();
        while (!isAtEnd()) {
            auto stmt = parseStatement();
            if (stmt) program->body.push_back(stmt);
        }
        return program;
    }

private:
    const std::vector<Token>& tokens;
    size_t current;

    Token peek() const { return tokens[current]; }
    Token advance() { return tokens[current++]; }
    bool isAtEnd() const { return peek().type == TokenType::END_OF_FILE; }
    bool match(TokenType type) { if (peek().type == type) { advance(); return true; } return false; }

    Token consume(TokenType type, const std::string& errorMessage) {
        if (match(type)) return tokens[current - 1];
        throw std::runtime_error("Parse Error: " + errorMessage);
    }

    ASTNodePtr parseStatement() {
        if (match(TokenType::INIT)) return parseInit();
        if (match(TokenType::IF)) return parseIf();
        if (match(TokenType::FOR)) return parseFor();
        if (match(TokenType::WHILE)) return parseWhile();
        if (match(TokenType::LOOP)) return parseLoop();
        if (match(TokenType::REPEAT)) return parseRepeat();
        if (match(TokenType::TRY)) return parseTryCatch();
        if (match(TokenType::PIPE)) return parseMacro();
        if (match(TokenType::FUNC)) return parseFuncDecl();
        if (match(TokenType::RETURN)) return parseReturn();
        return nullptr;
    }

    ASTNodePtr parseInit() {
        Token name = consume(TokenType::IDENTIFIER, "Expected variable name after Init");
        consume(TokenType::ASSIGN, "Expected '=' after variable name");
        auto value = parseExpression();
        consume(TokenType::SEMICOLON, "Expected ';'");
        return std::make_shared<InitStmt>("InitStmt", name.line, name.column, name.lexeme, std::dynamic_pointer_cast<LiteralNode>(value));
    }

    ASTNodePtr parseReturn() {
        int line = peek().line;
        int col = peek().column;
        consume(TokenType::SEMICOLON, "Expected ';' after Return");
        return std::make_shared<ASTNode>(ASTNode{ ASTNodeType::Return, line, col });
    }

    ASTNodePtr parseIf() {
        consume(TokenType::LPAREN, "Expected '('");
        auto condition = parseExpression();
        consume(TokenType::RPAREN, "Expected ')'");

        auto ifNode = std::make_shared<IfNode>(peek().line, peek().column);
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
            auto stmt = parseStatement();
            if (stmt) block.push_back(stmt);
        }
        return block;
    }

    ASTNodePtr parseFor() {
        consume(TokenType::LPAREN, "Expected '('");
        auto init = parseInit();
        auto cond = parseExpression();
        consume(TokenType::SEMICOLON, "Expected ';' in for");
        auto incr = parseExpression();
        consume(TokenType::RPAREN, "Expected ')'");

        auto node = std::make_shared<ForNode>(peek().line, peek().column);
        node->initializer = init;
        node->condition = cond;
        node->increment = incr;
        node->body = parseBlock();
        return node;
    }

    ASTNodePtr parseWhile() {
        consume(TokenType::LPAREN, "Expected '(' after while");
        auto condition = parseExpression();
        consume(TokenType::RPAREN, "Expected ')'");
        auto node = std::make_shared<ForNode>(peek().line, peek().column); // Reusing ForNode as a base loop node
        node->condition = condition;
        node->body = parseBlock();
        return node;
    }

    ASTNodePtr parseLoop() {
        auto node = std::make_shared<ForNode>(peek().line, peek().column);
        node->body = parseBlock();
        return node;
    }

    ASTNodePtr parseRepeat() {
        auto node = std::make_shared<ForNode>(peek().line, peek().column);
        node->body = parseBlock();
        return node;
    }

    ASTNodePtr parseTryCatch() {
        auto node = std::make_shared<ASTNode>(ASTNode{ ASTNodeType::TryCatch, peek().line, peek().column });
        parseBlock();
        consume(TokenType::CATCH, "Expected 'catch' after try block");
        parseBlock();
        return node;
    }

    ASTNodePtr parseMacro() {
        Token name = consume(TokenType::IDENTIFIER, "Expected macro name");
        consume(TokenType::COLON, "Expected ':' after macro name");
        while (!match(TokenType::PIPE) && !isAtEnd()) advance();
        return std::make_shared<ASTNode>(ASTNode{ ASTNodeType::Macro, name.line, name.column });
    }

    ASTNodePtr parseFuncDecl() {
        Token name = consume(TokenType::IDENTIFIER, "Expected function name");
        consume(TokenType::LPAREN, "Expected '('");

        std::vector<std::string> params;
        if (peek().type != TokenType::RPAREN) {
            do {
                Token param = consume(TokenType::IDENTIFIER, "Expected parameter name");
                params.push_back(param.lexeme);
            } while (match(TokenType::COMMA));
        }
        consume(TokenType::RPAREN, "Expected ')'");

        auto func = std::make_shared<FuncDeclNode>(name.lexeme, name.line, name.column);
        func->parameters = params;
        func->body = parseBlock();
        return func;
    }

    ASTNodePtr parseExpression() {
        return parseEquality();
    }

    ASTNodePtr parseEquality() {
        auto expr = parseComparison();
        while (match(TokenType::EQ) || match(TokenType::NEQ)) {
            std::string op = tokens[current - 1].lexeme;
            auto right = parseComparison();
            expr = std::make_shared<BinaryExprNode>(expr, op, right, peek().line, peek().column);
        }
        return expr;
    }

    ASTNodePtr parseComparison() {
        auto expr = parseTerm();
        while (match(TokenType::LT) || match(TokenType::GT) || match(TokenType::LE) || match(TokenType::GE)) {
            std::string op = tokens[current - 1].lexeme;
            auto right = parseTerm();
            expr = std::make_shared<BinaryExprNode>(expr, op, right, peek().line, peek().column);
        }
        return expr;
    }

    ASTNodePtr parseTerm() {
        auto expr = parseFactor();
        while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
            std::string op = tokens[current - 1].lexeme;
            auto right = parseFactor();
            expr = std::make_shared<BinaryExprNode>(expr, op, right, peek().line, peek().column);
        }
        return expr;
    }

    ASTNodePtr parseFactor() {
        auto expr = parseUnary();
        while (match(TokenType::MUL) || match(TokenType::DIV) || match(TokenType::MOD)) {
            std::string op = tokens[current - 1].lexeme;
            auto right = parseUnary();
            expr = std::make_shared<BinaryExprNode>(expr, op, right, peek().line, peek().column);
        }
        return expr;
    }

    ASTNodePtr parseUnary() {
        if (match(TokenType::NOT) || match(TokenType::MINUS)) {
            std::string op = tokens[current - 1].lexeme;
            auto right = parseUnary();
            return std::make_shared<BinaryExprNode>(nullptr, op, right, peek().line, peek().column);
        }
        return parsePrimary();
    }

    ASTNodePtr parsePrimary() {
        Token token = advance();
        switch (token.type) {
            case TokenType::NUMBER:
                return std::make_shared<LiteralNode>(token.lexeme, "int", token.line, token.column);
            case TokenType::STRING_LITERAL:
                return std::make_shared<LiteralNode>(token.lexeme, "string", token.line, token.column);
            case TokenType::IDENTIFIER:
                return std::make_shared<IdentifierNode>(token.lexeme, token.line, token.column);
            case TokenType::LPAREN: {
                auto expr = parseExpression();
                consume(TokenType::RPAREN, "Expected ')'");
                return expr;
            }
            default:
                throw std::runtime_error("Unexpected token in expression");
        }
    }
};
