#include "InventoryManager.hpp"
#include <iostream>
#include <limits>

void showMenu()
{
    std::cout << "\n>>> FRUIT STORE INVENTORY SUB-SYSTEM <<<\n";
    std::cout << "1. View Entire Stock\n";
    std::cout << "2. Search Item by ID (O(1) Lookup)\n";
    std::cout << "3. Add New Fruit Category\n";
    std::cout << "4. Restock Existing Item\n";
    std::cout << "5. Check Low-Stock Warnings\n";
    std::cout << "6. Exit System\n";
    std::cout << "Select operation (1-6): ";
}

int main()
{
    InventoryManager store;

    store.addFruit(Fruit(101, "Golden Delicious", "Apple", 1.25, 85));
    store.addFruit(Fruit(102, "Cavendish Banana", "Tropical", 0.75, 12)); // Low stock
    store.addFruit(Fruit(103, "Blood Orange", "Citrus", 1.80, 45));
    store.addFruit(Fruit(104, "Hass Avocado", "Tropical", 2.50, 8)); // Low stock
    store.addFruit(Fruit(105, "Wild Blueberry", "Berry", 4.20, 110));

    int choice;
    while (true)
    {
        showMenu();
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 6)
        {
            std::cout << "\nSaving state... System shut down safely.\n";
            break;
        }

        switch (choice)
        {
        case 1:
            store.displayFullInventory();
            break;

        case 2:
        {
            int searchId;
            std::cout << "Enter Product ID: ";
            std::cin >> searchId;
            try
            {
                Fruit found = store.getFruitById(searchId);
                std::cout << "\n[SUCCESS] Item Located Instantly:\n";
                found.display();
            }
            catch (const std::exception &e)
            {
                std::cout << "\n"
                          << e.what() << "\n";
            }
            break;
        }
        case 3:
        {
            int id, qty;
            std::string name, cat;
            double price;

            std::cout << "Enter ID (e.g. 106): ";
            std::cin >> id;
            std::cout << "Enter Name: ";
            std::cin >> name;
            std::cout << "Enter Category: ";
            std::cin >> cat;
            std::cout << "Enter Unit Price ($): ";
            std::cin >> price;
            std::cout << "Enter Starting Qty: ";
            std::cin >> qty;

            if (store.addFruit(Fruit(id, name, cat, price, qty)))
            {
                std::cout << "\n[+] New item registered successfully!\n";
            }
            else
            {
                std::cout << "\n[-] Operation Failed: ID conflict.\n";
            }
            break;
        }
        case 4:
        {
            int id, qty;
            std::cout << "Enter Target ID: ";
            std::cin >> id;
            std::cout << "Enter shipment volume to add: ";
            std::cin >> qty;
            if (store.restockItem(id, qty))
            {
                std::cout << "\n[+] Stock updated!\n";
            }
            else
            {
                std::cout << "\n[-] Target ID does not exist.\n";
            }
            break;
        }
        case 5:
        {
            auto alerts = store.getLowStockAlerts(15);
            std::cout << "\n--- CRITICAL STOCK ALERTS (Qty <= 15) ---\n";
            if (alerts.empty())
                std::cout << "No items are strictly depleted.\n";
            else
            {
                for (const auto &item : alerts)
                    item.display();
            }
            break;
        }
        default:
            std::cout << "Invalid instruction code.\n";
        }
    }
    return 0;
}
