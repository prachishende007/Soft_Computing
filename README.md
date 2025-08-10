# 🧠 Soft Computing 

Welcome to the **Soft Computing** repository!  
This project contains **C++ implementations** of intelligent computing techniques inspired by the human brain’s ability to deal with uncertainty, approximation, and learning.

---

## 📚 Overview

**Soft Computing** is a branch of computational intelligence focusing on:
- **Fuzzy Logic** 🤖 – managing uncertainty & partial truths
- **Artificial Neural Networks** 🧬 – learning patterns from data
- **Genetic Algorithms** 🧪 – optimization inspired by evolution
- **Hybrid Systems** 🔗 – combining multiple AI techniques

This repository is designed for:
- Students 📖 learning soft computing concepts
- Developers 💻 implementing algorithms in **C++**
- Researchers 🔬 experimenting with intelligent models

---

## 🚀 Features

- C++ implementations of:
  - **Fuzzy Inference Systems**
  - **Basic Neural Networks**
  - **Genetic Algorithms**
- Modular code for **easy extension**
- Commented source files for **better understanding**
- Example input/output for each algorithm

---

 📁 Repository Structure

---

## 🛠️ Technologies Used

- **Language:** C++  
- **Compiler:** g++ 
- **Tools:** GitHub, VS Code 

---

## ⚡ Example: Fuzzy Logic in C++

```cpp
#include <iostream>
#include "fuzzy.h"
using namespace std;

int main() {
    FuzzyController controller;
    controller.setTemperature(28.5);
    controller.compute();
    return 0;
}


