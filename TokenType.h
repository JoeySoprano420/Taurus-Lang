#pragma once
#include <string>

enum class TokenType {
    // --- Core Control Flow ---
    START, RETURN, IF, ELSE, FOR, WHILE, LOOP, REPEAT,
    TRY, CATCH, THROW, DEFER, BREAK, CONTINUE, HALT, PAUSE,

    // --- Concurrency / Sync ---
    ASYNC, AWAIT, MUTEX, COROUTINE, SCHEDULE, EVENT, TRIGGER, WATCH, LISTEN,

    // --- Variables and Declarations ---
    INIT, LET, VAL, VAR, CONST, STATIC, DYNAMIC,
    INT, FLOAT, BOOL, STRING, CHAR, NULLVAL, TRUEVAL, FALSEVAL,

    // --- Memory & Scope ---
    ALOC, FREE, POINTER, MEMORY, REFERENCE, SCOPE, BOUNDARY, SWEEP, GARBAGE,

    // --- Logic & Conditionals ---
    EQ, NEQ, LT, GT, LE, GE, AND, OR, NOT,
    XOR, NAND, NOR, IMPLIES, CONDITIONAL,

    // --- Operators ---
    ASSIGN, ADD, SUB, MUL, DIV, MOD, EXPONENT,
    INCREMENT, DECREMENT, ADD_EQ, SUB_EQ, MUL_EQ, DIV_EQ, MOD_EQ,
    RAISE, TRANSITION, ROLLBACK, RUN, PERCENT,

    // --- Comments & Whitespace ---
    COMMENT, MULTILINE_COMMENT, WHITESPACE,

    // --- Macro Scripts & C.I.A.M.S. ---
    MACRO_BEGIN, MACRO_END, PIPE, TEXTURIZER,
    CONFIG, MODIFIER, SPECIFIER, INLINE_MACRO,

    // --- Structures / Data Constructs ---
    STRUCT, CLASS, ENUM, FUNC, CALL,
    TUPLE, ARRAY, LIST, MATRIX, VECTOR, NODE, CHILD, BRANCH, NEST,

    // --- Categories, Labels, Descriptors ---
    CATEGORY, LABEL, DESCRIPTOR, TYPEDEF, IDENTIFIER,

    // --- Files, I/O, Runtime ---
    FILE, FOLDER, SOCKET, API, LINK, BIND, WRAP, INTEROP,
    INPUT, OUTPUT, IO, OPEN, CLOSE, READ, WRITE, COMPILE, RENDER, REPLACE, ACCEPT,

    // --- Security ---
    ENCRYPT, DECRYPT, OBFUSCATE, CIPHER, PROXY, FIREWALL,
    SECURE, UNSECURE, PRIVATE, PUBLIC, DENY, ALLOW, BYPASS, VALIDATE, CONFIGURE,

    // --- Event & Task Scheduling ---
    TASK, ROUTINE, SUBROUTINE, FUNC_CALL,
    SCHEDULER, TIMER, COUNTER, CHECKPOINT, EVENT_BLOCK, TRIGGER_BLOCK,

    // --- Diagnostics ---
    DEBUG, INSPECT, LOG, TRACE, ERROR, WARNING, ASSERT, RAISE_FLAG, WATCHDOG,

    // --- Pattern Matching / AI ---
    MATCH, CASE, DEFAULT, QUERY, LOOKUP, STATE, TRUTH, PROOF, CONTEXT,

    // --- Collections ---
    APPEND, INSERT, REMOVE, REPLACE_ITEM, COLLECT, FILTER, FOLD, REDUCE, MAP,

    // --- Networking / Comms ---
    PING, SEND, RECEIVE, CONNECT, DISCONNECT, LISTEN_SOCKET,

    // --- Symbolic, Meta, Validation ---
    REFER, CROSSREF, RESOLVE, RESULT, CHECKSUM, KEY, SCALE, WEIGHT,

    // --- Flow Modifiers ---
    ALT, TRICKLE, SUBVERT, EXCEPT, INSTEAD_OF, SIMULATE, ROTATE, DELETE,

    // --- Misc Delimiters ---
    SEMICOLON, COLON, COMMA, DOT,
    LPAREN, RPAREN, LBRACE, RBRACE, LBRACKET, RBRACKET,

    // --- Literals & Base Types ---
    NUMBER, STRING_LITERAL, CHAR_LITERAL, BOOL_LITERAL,

    // --- End ---
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
