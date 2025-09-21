# CSpine Lang

_A toy programming language built in C++ for fun and learning._

## 🚀 Overview

CSpine is a **mini programming language** experiment inspired by interpreters and compilers.  
It follows a classic flow:

1. **Lexing** → source code is tokenized (`Lexer/`).
2. **Parsing** → tokens are converted into an AST (`AST/`).
3. **Bytecode Generation** → AST is translated into bytecode (`Bytecode/`).
4. **Execution** → a custom virtual machine executes the bytecode (`VM/`).

This project is mostly for **systems-level learning** (compilers, interpreters, VMs).

---

## 🛠️ Building

Make sure you have `g++` installed. Run this to compile the code:

```bash
./c
```

Run the binary:

```bash
./run
```

Make changes to the test.cspine file to test any features of the language

---

## 🧠 Learning Goals

- Understand how **lexers** and **parsers** work.
- Build a **bytecode interpreter** from scratch.
- Explore how VMs execute instructions.
- Experiment with toy-language design (syntax, features).

---

More info is available in the docs folder.

## 🤝 Contributing

This is a personal learning project, but feel free to fork, play around, and suggest improvements.

---

## 📜 License

MIT License. Yoo cna do whatever you want with it.
