#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class Fruit
{
private:
    int id;
    std::string name;
    std::string category;
    double price;
    int quantity;

public:
    // Constructor me Default values (i domosdoshëm për std::unordered_map)
    Fruit(int id = 0, std::string name = "", std::string category = "", double price = 0.0, int quantity = 0)
        : id(id), name(name), category(category), price(price), quantity(quantity) {}

    // Getters (të shënuara 'const' për siguri të memories)
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getCategory() const { return category; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    // Setters & Modifiers
    void setPrice(double newPrice) { price = newPrice; }
    void addQuantity(int amount) { quantity += amount; }
    void reduceQuantity(int amount)
    {
        if (quantity >= amount)
            quantity -= amount;
    }

    // Funksion ndihmës për printim të bukur në konsolë
    void display() const
    {
        std::cout << std::left << std::setw(6) << id
                  << std::setw(16) << name
                  << std::setw(14) << category
                  << "$" << std::setw(9) << std::fixed << std::setprecision(2) << price
                  << std::setw(10) << quantity << "\n";
    }
};
