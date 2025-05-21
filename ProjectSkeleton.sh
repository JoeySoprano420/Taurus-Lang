TaurusCompiler/
├── include/
│   ├── lexer.h
│   ├── parser.h
│   ├── ast.h
│   ├── macro_expander.h
│   ├── semantic_analyzer.h
│   ├── symbol_table.h
│   ├── error_reporter.h
│   └── codegen.h
├── src/
│   ├── main.cpp
│   ├── lexer.cpp
│   ├── parser.cpp
│   ├── ast.cpp
│   ├── macro_expander.cpp
│   ├── semantic_analyzer.cpp
│   ├── codegen.cpp
│   └── nasm_emitter.cpp
├── runtime/
│   └── runtime_stubs.asm
├── samples/
│   └── hello_world.taurus
├── output/
│   ├── hello_world.asm
│   ├── hello_world.exe
│   ├── hello_world.fir
│   ├── hello_world.ast
│   └── compile.log
├── tools/
│   ├── install.bat
│   └── install.sh
├── syntax/
│   └── Taurus.tmLanguage.json
├── Makefile
└── README.md
