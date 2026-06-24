# FruitStore Inventory Sub-System (C++)

A highly optimized console-based Inventory Management System built in modern **C++17**, applying strict **Object-Oriented Design** principles. 

This project was developed as a technical sandbox to implement custom encapsulated data entities and test the computational efficiency of the C++ Standard Template Library (STL).

## ⚡ Technical Architecture & Big O Choices

* **`std::unordered_map<int, Fruit>`**: Used as the primary in-memory database engine. 
  * **Why?** Inventory systems perform heavy *Lookups* and *Updates*. A vector/array would yield `O(n)` lookup speeds. By utilizing a Hash Map keyed by the Product ID, item retrievals, stock validations, and cash-register lookups execute in **`O(1)` constant average time**.
* **Memory Conservatism**: Data transfer across business logic layers uses `const Fruit&` (constant references) to entirely prevent unnecessary object slicing or deep-copy overhead in the stack.
* **Encapsulation**: Raw variables are heavily guarded; stock reductions or price adjustments pass strictly through domain-validated mutator methods.

## 🚀 How to Compile (C++17 Required)

Open your terminal in the root directory and execute:

```bash
g++ -std=c++17 main.cpp -o fruitstore
./fruitstore
