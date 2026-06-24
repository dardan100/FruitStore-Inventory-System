#pragma once
#include "Fruit.hpp"
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdexcept>

class InventoryManager
{
private:
    // Hash Map: Çelësi është ID (int), Vlera është Objekti (Fruit) -> O(1) Lookup
    std::unordered_map<int, Fruit> inventory;

public:
    // Shtimi i një fruti të ri (Kalon me referencë për shpejtësi)
    bool addFruit(const Fruit &fruit)
    {
        if (inventory.find(fruit.getId()) != inventory.end())
        {
            return false; // ID ekziston tashmë
        }
        inventory[fruit.getId()] = fruit;
        return true;
    }

    // Fshirja e një fruti
    bool removeFruit(int id)
    {
        return inventory.erase(id) > 0;
    }

    // Rifurnizim (Restock)
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

    // Kërkim me ID
    Fruit getFruitById(int id) const
    {
        auto it = inventory.find(id);
        if (it != inventory.end())
        {
            return it->second;
        }
        throw std::runtime_error("Error: Fruit ID not found in database.");
    }

    // Raport i produkteve me stok kritik (nën 15 copë)
    std::vector<Fruit> getLowStockAlerts(int threshold = 15) const
    {
        std::vector<Fruit> lowStock;
        // Përdorim C++17 Structured Binding [id, fruit]
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
