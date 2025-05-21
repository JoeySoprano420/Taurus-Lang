#pragma once
#include <string>
#include <vector>
#include <memory>

enum class ASTNodeType {
    Program, Block, Identifier, Literal,

    // Statements
    Init, Assign, Declaration, Expression,
    If, For, While, Loop, Repeat,
    Break, Continue, Return, Throw, Defer, TryCatch,
    Function, Call, Macro, Await, Async, Mutex,

    // Structures
    StructDecl, ClassDecl, FuncDecl,
    Tuple, List, Array, Matrix, Vector,

    // Operations
    BinaryExpr, UnaryExpr, LogicalExpr, ComparisonExpr,
    CallExpr, IndexExpr, MemberAccess,

    // Pattern Matching
    Match, Case, DefaultCase,

    // I/O & Interop
    IOCommand, FileOp, NetworkOp,

    // Events & Triggers
    EventBlock, Scheduler, TriggerBlock,

    // Meta & Validation
    Assertion, ProofCheck, Reference, StateCheck
};

struct ASTNode {
    ASTNodeType type;
    int line;
    int column;
    virtual ~ASTNode() = default;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;

struct ProgramNode : ASTNode {
    std::vector<ASTNodePtr> body;
    ProgramNode() { type = ASTNodeType::Program; }
};

struct IdentifierNode : ASTNode {
    std::string name;
    IdentifierNode(const std::string& n, int l, int c)
        : name(n) { type = ASTNodeType::Identifier; line = l; column = c; }
};

struct LiteralNode : ASTNode {
    std::string value;
    std::string literalType; // int, float, string, bool, null
    LiteralNode(const std::string& v, const std::string& t, int l, int c)
        : value(v), literalType(t) { type = ASTNodeType::Literal; line = l; column = c; }
};

struct BinaryExprNode : ASTNode {
    ASTNodePtr left;
    std::string op;
    ASTNodePtr right;
    BinaryExprNode(ASTNodePtr l, const std::string& o, ASTNodePtr r, int ln, int col)
        : left(l), op(o), right(r) { type = ASTNodeType::BinaryExpr; line = ln; column = col; }
};

struct IfNode : ASTNode {
    ASTNodePtr condition;
    std::vector<ASTNodePtr> thenBlock;
    std::vector<ASTNodePtr> elseBlock;
    IfNode(int ln, int col) { type = ASTNodeType::If; line = ln; column = col; }
};

struct ForNode : ASTNode {
    ASTNodePtr initializer;
    ASTNodePtr condition;
    ASTNodePtr increment;
    std::vector<ASTNodePtr> body;
    ForNode(int ln, int col) { type = ASTNodeType::For; line = ln; column = col; }
};

struct FuncDeclNode : ASTNode {
    std::string name;
    std::vector<std::string> parameters;
    std::vector<ASTNodePtr> body;
    FuncDeclNode(const std::string& n, int ln, int col)
        : name(n) { type = ASTNodeType::FuncDecl; line = ln; column = col; }
};
