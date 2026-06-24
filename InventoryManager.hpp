#pragma once
#include "Fruit.hpp"
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdexcept>

class InventoryManager
{
private:
    std::unordered_map<int, Fruit> inventory;

public:
    bool addFruit(const Fruit &fruit)
    {
        if (inventory.find(fruit.getId()) != inventory.end())
        {
            return false;
        }
        inventory[fruit.getId()] = fruit;
        return true;
    }

    bool removeFruit(int id)
    {
        return inventory.erase(id) > 0;
    }

    bool restockItem(int id, int addedQuantity)
    {
        auto it = inventory.find(id);
        if (it != inventory.end())
        {
            it->second.addQuantity(addedQuantity);
            return true;
        }
        return false;
    }

    Fruit getFruitById(int id) const
    {
        auto it = inventory.find(id);
        if (it != inventory.end())
        {
            return it->second;
        }
        throw std::runtime_error("Error: Fruit ID not found in database.");
    }

    std::vector<Fruit> getLowStockAlerts(int threshold = 15) const
    {
        std::vector<Fruit> lowStock;

        for (const auto &[id, fruit] : inventory)
        {
            if (fruit.getQuantity() <= threshold)
            {
                lowStock.push_back(fruit);
            }
        }
        return lowStock;
    }

    void displayFullInventory() const
    {
        std::cout << "\n=================================================================\n";
        std::cout << std::left << std::setw(6) << "ID"
                  << std::setw(16) << "Fruit Name"
                  << std::setw(14) << "Category"
                  << std::setw(10) << "Price"
                  << std::setw(10) << "Stock Qty" << "\n";
        std::cout << "=================================================================\n";

        for (const auto &[id, fruit] : inventory)
        {
            fruit.display();
        }
        std::cout << "=================================================================\n";
    }
};
