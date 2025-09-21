# CSpine Lang 🦴

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

Make sure you have `g++` installed:

```bash
g++ main.cpp Lexer/tokenizer.cpp AST/builder.cpp VM/vm.cpp -o cspine
```

Run the binary:

```bash
./cspine
```

Alternatively, you can use the `run` script if set up.

---

## 📖 Example Usage

```bash
./cspine
```

Example (to be expanded):

```
Toy language running...
```

Later this will support `.cspine` files with actual syntax.

---

## 🧠 Learning Goals

- Understand how **lexers** and **parsers** work.
- Build a **bytecode interpreter** from scratch.
- Explore how VMs execute instructions.
- Experiment with toy-language design (syntax, features).

---

## 🔮 Roadmap

- [ ] Add `.cspine` file input
- [ ] Expand tokenizer with operators & keywords
- [ ] Support expressions in AST
- [ ] Define custom bytecode instructions
- [ ] Implement full VM loop
- [ ] Add simple standard library (print, math)

---

## 🤝 Contributing

This is a personal learning project, but feel free to fork, play around, and suggest improvements.

---

## 📜 License

MIT License. Yoo cna do whatever you want with it.
