#pragma once
#include <string>
#include <memory>
#include <vector>

enum class ASTNodeType {
    Program, Init, Assign, If, For, While, Return, Expression, Block,
    Function, Macro, Literal, Identifier, BinaryExpr, UnaryExpr
};

struct ASTNode {
    ASTNodeType type;
    int line;
    int column;
    virtual ~ASTNode() = default;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;

struct Identifier : ASTNode {
    std::string name;
    Identifier(const std::string& n, int l, int c)
        : name(n) { type = ASTNodeType::Identifier; line = l; column = c; }
};

struct Literal : ASTNode {
    std::string value;
    Literal(const std::string& v, int l, int c)
        : value(v) { type = ASTNodeType::Literal; line = l; column = c; }
};

struct Expression : ASTNode {
    ASTNodePtr left;
    std::string op;
    ASTNodePtr right;
    Expression(ASTNodePtr l, const std::string& o, ASTNodePtr r, int ln, int col)
        : left(l), op(o), right(r) { type = ASTNodeType::BinaryExpr; line = ln; column = col; }
};

struct InitStmt : ASTNode {
    std::string varName;
    ASTNodePtr value;
    InitStmt(const std::string& v, ASTNodePtr val, int ln, int col)
        : varName(v), value(val) { type = ASTNodeType::Init; line = ln; column = col; }
};

struct AssignStmt : ASTNode {
    std::string varName;
    ASTNodePtr value;
    AssignStmt(const std::string& v, ASTNodePtr val, int ln, int col)
        : varName(v), value(val) { type = ASTNodeType::Assign; line = ln; column = col; }
};

struct ReturnStmt : ASTNode {
    ReturnStmt(int ln, int col) { type = ASTNodeType::Return; line = ln; column = col; }
};

struct IfStmt : ASTNode {
    ASTNodePtr condition;
    std::vector<ASTNodePtr> thenBlock;
    std::vector<ASTNodePtr> elseBlock;
    IfStmt(ASTNodePtr cond, int ln, int col)
        : condition(cond) { type = ASTNodeType::If; line = ln; column = col; }
};

struct BlockStmt : ASTNode {
    std::vector<ASTNodePtr> statements;
    BlockStmt() { type = ASTNodeType::Block; }
};

struct Program : ASTNode {
    std::vector<ASTNodePtr> statements;
    Program() { type = ASTNodeType::Program; }
};
