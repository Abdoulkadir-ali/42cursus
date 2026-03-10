# 🚀 Push Swap

<div align="center">

![42 Logo](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Makefile](https://img.shields.io/badge/Build-Makefile-1f6feb?style=for-the-badge)

**A 42 sorting project built around two stacks, a restricted instruction set,
and a cost-based insertion strategy.**

</div>

---

## Overview

`push_swap` sorts a list of unique integers using only the operations allowed by
the 42 subject. The project contains two executables:

- `push_swap`, which outputs the instruction sequence needed to sort the input
- `checker`, which reads an instruction sequence from standard input and
	verifies whether it sorts the stack correctly

The project is organized around a few clear layers:

- parsing builds and validates the initial stacks
- primitive moves implement the legal instruction set
- the algorithm layer computes targets, costs, and move order
- helper modules support the circular stack structure and shared output logic

---

## Allowed Operations

| Operation | Description |
| :--- | :--- |
| `sa` | Swap the first two elements of stack `a` |
| `sb` | Swap the first two elements of stack `b` |
| `ss` | Perform `sa` and `sb` at the same time |
| `pa` | Push the top of stack `b` onto stack `a` |
| `pb` | Push the top of stack `a` onto stack `b` |
| `ra` | Rotate stack `a` upward |
| `rb` | Rotate stack `b` upward |
| `rr` | Perform `ra` and `rb` at the same time |
| `rra` | Reverse rotate stack `a` |
| `rrb` | Reverse rotate stack `b` |
| `rrr` | Perform `rra` and `rrb` at the same time |

---

## Build

### Requirements

- `cc`
- `make`
- a Unix-like environment

### Targets

```bash
# build push_swap
make

# build checker
make bonus

# remove objects
make clean

# remove objects and binaries
make fclean

# full rebuild
make re
```

The project builds against the bundled libft in `packages/libft`.

---

## Usage

### push_swap

```bash
./push_swap 4 2 8 1 3
./push_swap "4 2 8 1 3"
./push_swap 3 2 1 | wc -l
```

### checker

```bash
./push_swap 3 2 1 | ./checker 3 2 1
echo -e "sa\npb\npa" | ./checker 2 1
./push_swap 3 2 1 | ./checker_linux 3 2 1
```

### quick random test

```bash
ARG=$(seq 1 100 | sort -R)
./push_swap $ARG | wc -l
./push_swap $ARG | ./checker_linux $ARG
```

---

## Algorithm Summary

This implementation is built around a target-and-cost strategy rather than a
fixed chunk table.

At a high level, the flow is:

1. Parse the input and build stack `a` as a circular linked list.
2. Reduce stack `a` by pushing values into stack `b`.
3. For each candidate move, compute:
	 - the target node in the opposite stack
	 - the cost of reaching that target
4. Move the cheapest candidate first.
5. Reinsert nodes from `b` into `a` with combined rotations when possible.
6. Rotate the final stack so the extreme value is at the head.

The algorithm code is split into:

- `target/` for insertion targets
- `cost/` for push-cost computation
- `sort/` for the forward reduction phase and small-stack handling
- `moves.c` and `push_swap.c` for top-level orchestration

---

## Project Layout

```text
.
├── includes/
│   ├── push_swap.h
│   ├── README.md
│   └── Example.md
├── packages/
│   └── libft/
├── srcs/
│   ├── algo/
│   │   ├── cost/
│   │   ├── sort/
│   │   ├── target/
│   │   ├── moves.c
│   │   ├── push_swap.c
│   │   └── README.md
│   ├── checker/
│   │   ├── checker.c
│   │   └── README.md
│   ├── helper/
│   │   ├── display/
│   │   ├── lst/
│   │   └── README.md
│   ├── main/
│   │   ├── main.c
│   │   └── README.md
│   ├── moves/
│   │   ├── push.c
│   │   ├── reverse_rotate.c
│   │   ├── rotate.c
│   │   ├── swap.c
│   │   └── README.md
│   └── parsing/
│       ├── moves/
│       ├── stacks/
│       └── README.md
├── checker_linux
├── Makefile
├── tester.sh
└── README.md
```

---

## Documentation Map

The repository now includes folder-level documentation for most runtime areas:

- `includes/README.md`
- `srcs/algo/README.md`
- `srcs/checker/README.md`
- `srcs/helper/README.md`
- `srcs/main/README.md`
- `srcs/moves/README.md`
- `srcs/parsing/README.md`

Each subpackage also has its own README where needed.

---

## Configuration Notes

The main compile-time switches live in `includes/push_swap.h`.

Important ones include:

- `DEBUG`
- `ASCENDING`
- `MULTIPLE_SIGN_INVALID`

These affect debug output, ordering behavior, and numeric parsing rules.

---

## Notes

The stack implementation is based on circular linked lists. That choice affects
parsing, primitive operations, and the algorithm itself, especially for rotate
and reverse-rotate behavior.

The checker and main program share most of the same runtime layers. The main
difference is that `push_swap` generates operations, while `checker` consumes
them and validates the result.

<div align="center">

### **🌟 Welcome Contributors!**

We love contributions! Here's how you can help:

</div>

### 🛠️ Development Setup

```bash
# 📥 Clone the repository
git clone https://github.com/Abdoulkadir-ali/42cursus
cd cercle-3/push_swap

# 🏗️ Build and test
make && make test

# 🧪 Run comprehensive tests
./tester.sh
```

### 📝 Adding Features

1. **🔍 Check Issues**: Look for open issues or feature requests
2. **🍴 Fork**: Create your feature branch
3. **💻 Code**: Implement your changes
4. **✅ Test**: Ensure all tests pass
5. **📤 PR**: Submit a pull request

### 🐛 Bug Reports

Found a bug? Please report it with:

- **🐛 Clear description** of the issue
- **📝 Steps to reproduce**
- **💻 Expected vs actual behavior**
- **🖥️ System information**

---

## 📈 Performance

<div align="center">

### **⚡ Operation Counts (Approximate)**

| Input Size | Max Operations | Target Score |
|------------|----------------|--------------|
| **5** | 12 | ✅ |
| **100** | 700 | ✅ 5 points |
| **500** | 5500 | ✅ 5 points |

</div>

### 📊 Complexity Analysis

- **Time**: O(n²) worst case, O(n log n) optimized
- **Space**: O(n) for stack storage
- **Operations**: Minimized through cost calculation

---

## 🙏 Acknowledgments

<div align="center">

### **🎓 42 School Project**

**Special thanks to:**

- **42 School** for the challenging curriculum
- **Peer reviewers** for valuable feedback
- **Open source community** for inspiration

---

### **📞 Contact**

<div align="center">

**Questions? Suggestions?** Feel free to reach out!

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://linkedin.com/in/yourprofile)
[![GitHub](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/Adoulkadir-ali)

---

**⭐ If you found this project helpful, please give it a star! ⭐**

</div>

---

<div align="center">

**Made with ❤️ at 42 School**

*Last updated: December 2025*

</div></content>
<parameter name="filePath">/home/abdoali/Documents/42cursus/cercle-3/push_swap/README.md