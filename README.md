
# 🚀 42 Cursus - My Programming Journey

<div align="center">

![42 Logo](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Makefile](https://img.shields.io/badge/Makefile-000000?style=for-the-badge&logo=makefile&logoColor=white)

**⭐ Mastering C Programming Through 42's Innovative Curriculum ⭐**

*A comprehensive collection of projects showcasing my progression through 42 School's peer-to-peer learning system*

[![42 School](https://img.shields.io/badge/42-School-000000?style=flat-square)](https://42.fr/)
[![Cursus](https://img.shields.io/badge/Cursus-Complete-4CAF50?style=flat-square)](#)

</div>

---

## 📋 Table of Contents

- [🎯 Overview](#-overview)
- [🔄 Circles Overview](#-circles-overview)
- [📚 Project Structure](#-project-structure)
- [✨ Skills Developed](#-skills-developed)
- [🛠️ Technologies](#️-technologies)
- [📖 About 42](#-about-42)
- [🚀 Usage](#-usage)
- [🤝 Contributing](#-contributing)
- [📧 Contact](#-contact)

---

## 🎯 Overview

<div align="center">

### **The Ultimate Programming Bootcamp**

Welcome to my **42 Cursus** repository! This collection represents my journey through **42 School's** revolutionary peer-to-peer learning curriculum. Each "cercle" (circle) builds upon the previous, challenging me with increasingly complex projects that develop fundamental programming skills.

🧠 **From basic functions to complex systems** - witness the evolution!

</div>

### 🎯 Curriculum Structure

- **Cercle 1**: Foundations - Building core programming skills
- **Cercle 2**: Intermediate - System programming and algorithms
- **Cercle 3**: Advanced - Complex algorithms and graphics
- **Cercle 4**: Expert - Multithreading and shell implementation

---

## 🔄 Circles Overview

<div align="center">

| Circle | Focus | Key Projects | Difficulty |
|--------|-------|--------------|------------|
| **Cercle 1** | C Fundamentals | libft | 🟢 Beginner |
| **Cercle 2** | System Programming | printf, get_next_line, born2beroot | 🟡 Intermediate |
| **Cercle 3** | Algorithms & Graphics | push_swap, pipex, fdf | 🟠 Advanced |
| **Cercle 4** | Concurrency & Systems | minishell, philosophers | 🔴 Expert |

</div>

---

## 📚 Project Structure

### 🎯 Cercle 1 - Foundations

<div align="center">

#### **Building the Foundation**

The first circle focuses on mastering C programming fundamentals through library implementation.

</div>

| Project | Description | Status |
|---------|-------------|--------|
| **[libft](cercle-1/libft/)** | Complete C standard library recreation | ✅ Completed |
| **[libft_clean](cercle-1/libft_clean/)** | Organized, categorized library version | ✅ Completed |

### 🎯 Cercle 2 - System Programming

<div align="center">

#### **Diving into System-Level Programming**

Intermediate projects covering file I/O, formatting, and system administration.

</div>

| Project | Description | Key Features |
|---------|-------------|--------------|
| **[born2beroot](cercle-2/born2beroot/)** | Virtual machine setup & system admin | 🖥️ VM Configuration |
| **[ft_printf](cercle-2/ft_printf/)** | Custom printf implementation | 🖨️ Format parsing, flags |
| **[get_next_line](cercle-2/get_next_line/)** | File descriptor reading utility | 📖 Line-by-line reading |

### 🎯 Cercle 3 - Advanced Algorithms

<div align="center">

#### **Algorithm Optimization & Graphics**

Complex sorting algorithms and 3D rendering challenges.

</div>

| Project | Description | Complexity |
|---------|-------------|------------|
| **[fdf](cercle-3/fdf/)** | 3D wireframe renderer | 🎨 Graphics programming |
| **[pipex](cercle-3/pipex/)** | Shell pipe recreation | 🔧 Process management |
| **[push_swap](cercle-3/push_swap/)** | Optimized sorting algorithm | ⚡ Algorithm efficiency |

### 🎯 Cercle 4 - Expert Systems

<div align="center">

#### **Concurrency & System Design**

Advanced projects involving threading, synchronization, and shell implementation.

</div>

| Project | Description | Technologies |
|---------|-------------|--------------|
| **[minishell](cercle-4/minishell/)** | Custom bash-like shell | 🐚 Command parsing |
| **[philosophers](cercle-4/philosophers/)** | Dining philosophers problem | 🧵 Multithreading |

---

## ✨ Skills Developed

<div align="center">

| 🛠️ Skill Category | Technologies & Concepts |
|-------------------|-------------------------|
| **Core Programming** | C, Memory Management, Pointers |
| **System Programming** | File I/O, Process Management, Signals |
| **Data Structures** | Linked Lists, Stacks, Queues |
| **Algorithms** | Sorting, Searching, Optimization |
| **Graphics** | 3D Rendering, Wireframe Models |
| **Concurrency** | Threads, Mutexes, Synchronization |
| **Shell Programming** | Command Parsing, Environment Variables |

</div>

---

## 🛠️ Technologies

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Bash](https://img.shields.io/badge/Bash-4EAA25?style=for-the-badge&logo=gnu-bash&logoColor=white)
![Makefile](https://img.shields.io/badge/Makefile-000000?style=for-the-badge&logo=makefile&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white)

**Development Environment:**
- **OS**: Linux (Ubuntu/Debian)
- **Compiler**: GCC
- **Build System**: GNU Make
- **Version Control**: Git
- **Code Standards**: 42 Norminette

</div>

---

## 📖 About 42

<div align="center">

### **Revolutionary Peer-to-Peer Learning**

**42** is a tuition-free, project-based programming school founded in France. Unlike traditional education, 42 uses:

- **🎯 Project-Based Learning**: Learn by doing real projects
- **👥 Peer-to-Peer Evaluation**: Code reviewed by fellow students
- **🔄 Circular Curriculum**: Progressive difficulty through "cercles"
- **🌍 Global Network**: 50+ campuses worldwide
- **💻 24/7 Access**: Open lab facilities around the clock

</div>

---

## 🚀 Usage

### Building Projects

Each project includes a `Makefile` for easy compilation:

```bash
# Navigate to any project directory
cd cercle-1/libft

# Build the project
make

# Clean object files
make clean

# Full clean (including executable)
make fclean

# Rebuild from scratch
make re
```

### Project Dependencies

Most projects are self-contained, but some require:

- **fdf**: MiniLibX graphics library
- **born2beroot**: VirtualBox or VMware
- **minishell**: readline library

---

## 🤝 Contributing

<div align="center">

**This repository showcases my personal learning journey. While contributions aren't accepted for graded projects, feel free to:**

- ⭐ Star the repository if you find it helpful
- 🍴 Fork for your own 42 journey
- 💬 Open issues for questions or suggestions
- 📖 Use as reference for similar projects

</div>

---

## 📧 Contact

<div align="center">

**Let's connect and discuss programming!**

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://linkedin.com/in/your-profile)
[![GitHub](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/your-username)
[![42 Profile](https://img.shields.io/badge/42-Profile-000000?style=for-the-badge&logo=42&logoColor=white)](https://profile.intra.42.fr/users/your-username)

**Email:** your.email@example.com

</div>

---

<div align="center">

**🚀 Keep coding, keep learning! 🚀**

*Built with ❤️ during my 42 School journey*

[![42 Cursus](https://img.shields.io/badge/42-Cursus-000000?style=for-the-badge&logo=42&logoColor=white)](#)

</div>
