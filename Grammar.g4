grammar Taurus;

program     : statement* EOF ;
statement   : initStmt | assignStmt | controlStmt | returnStmt | macroStmt | funcStmt ;

initStmt    : 'Init' ID assignOp expr ';' ;
assignStmt  : ID assignOp expr ';' ;

controlStmt : ifStmt | forStmt | whileStmt | tryCatchStmt ;

ifStmt      : 'if' '(' expr ')' block ('else' block)? ;
forStmt     : 'for' '(' assignStmt expr ';' expr ')' block ;
whileStmt   : 'while' '(' expr ')' block ;
tryCatchStmt: 'try' block 'catch' block ;

returnStmt  : 'Return' ';' ;

macroStmt   : '|' ID ':' macroBody '|' ;
macroBody   : .*? ; // flexible macro script

funcStmt    : 'Start' block 'Return' ';' ;

block       : '{' statement* '}' ;

expr        : expr op=('*'|'/') expr
            | expr op=('+'|'-') expr
            | expr op=('=='|'!='|'<'|'>'|'&&'|'||') expr
            | '(' expr ')'
            | ID
            | NUMBER
            | STRING ;

assignOp    : '=' | '==' ;

ID          : [a-zA-Z][a-zA-Z0-9]* ;
NUMBER      : [0-9]+ ;
STRING      : '"' .*? '"' ;

WS          : [ \t\r\n]+ -> skip ;
COMMENT     : '#' ~[\r\n]* -> skip ;
MULTILINE   : '**' .*? '**' -> skip ;
