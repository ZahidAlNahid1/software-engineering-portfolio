#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace {

constexpr const char* kDataFile = "items.txt";

struct Item {
    int id{};
    std::string name;
    std::string company;
    int quantity{};
};

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::vector<Item> loadItems() {
    std::vector<Item> items;
    std::ifstream file(kDataFile);
    Item item;
    while (file >> item.id >> item.name >> item.company >> item.quantity) {
        items.push_back(item);
    }
    return items;
}

bool saveItems(const std::vector<Item>& items) {
    std::ofstream file(kDataFile, std::ios::trunc);
    if (!file) return false;
    for (const auto& item : items) {
        file << item.id << ' ' << item.name << ' ' << item.company << ' ' << item.quantity << '\n';
    }
    return static_cast<bool>(file);
}

void printItem(const Item& item) {
    std::cout << "ID: " << item.id
              << " | Name: " << item.name
              << " | Company: " << item.company
              << " | Quantity: " << item.quantity << '\n';
}

void addItem() {
    auto items = loadItems();
    Item item;
    std::cout << "Item ID: ";
    if (!(std::cin >> item.id)) { clearInput(); std::cout << "Invalid ID.\n"; return; }

    if (std::any_of(items.begin(), items.end(), [&](const Item& current) { return current.id == item.id; })) {
        std::cout << "An item with that ID already exists.\n";
        return;
    }

    std::cout << "Item name (single word): ";
    std::cin >> item.name;
    std::cout << "Company (single word): ";
    std::cin >> item.company;
    std::cout << "Quantity: ";
    if (!(std::cin >> item.quantity) || item.quantity < 0) {
        clearInput();
        std::cout << "Invalid quantity.\n";
        return;
    }

    items.push_back(item);
    std::cout << (saveItems(items) ? "Item added.\n" : "Unable to save data.\n");
}

void displayItems() {
    const auto items = loadItems();
    if (items.empty()) {
        std::cout << "No items found.\n";
        return;
    }
    for (const auto& item : items) printItem(item);
}

void checkItem() {
    const auto items = loadItems();
    int id{};
    std::cout << "Item ID: ";
    if (!(std::cin >> id)) { clearInput(); std::cout << "Invalid ID.\n"; return; }
    const auto found = std::find_if(items.begin(), items.end(), [&](const Item& item) { return item.id == id; });
    if (found == items.end()) std::cout << "Item not found.\n";
    else printItem(*found);
}

void updateItem() {
    auto items = loadItems();
    int id{};
    std::cout << "Item ID to update: ";
    if (!(std::cin >> id)) { clearInput(); std::cout << "Invalid ID.\n"; return; }

    const auto found = std::find_if(items.begin(), items.end(), [&](const Item& item) { return item.id == id; });
    if (found == items.end()) { std::cout << "Item not found.\n"; return; }

    std::cout << "New item name (single word): ";
    std::cin >> found->name;
    std::cout << "New company (single word): ";
    std::cin >> found->company;
    std::cout << "New quantity: ";
    if (!(std::cin >> found->quantity) || found->quantity < 0) {
        clearInput();
        std::cout << "Invalid quantity.\n";
        return;
    }
    std::cout << (saveItems(items) ? "Item updated.\n" : "Unable to save data.\n");
}

void deleteItem() {
    auto items = loadItems();
    int id{};
    std::cout << "Item ID to delete: ";
    if (!(std::cin >> id)) { clearInput(); std::cout << "Invalid ID.\n"; return; }

    const auto oldSize = items.size();
    items.erase(std::remove_if(items.begin(), items.end(), [&](const Item& item) { return item.id == id; }), items.end());
    if (items.size() == oldSize) { std::cout << "Item not found.\n"; return; }
    std::cout << (saveItems(items) ? "Item deleted.\n" : "Unable to save data.\n");
}

} // namespace

int main() {
    while (true) {
        std::cout << "\n=== Department Store Management System ===\n"
                  << "1. Add item\n"
                  << "2. Display items\n"
                  << "3. Check item\n"
                  << "4. Update item\n"
                  << "5. Delete item\n"
                  << "6. Exit\n"
                  << "Choice: ";

        int choice{};
        if (!(std::cin >> choice)) {
            clearInput();
            std::cout << "Invalid choice.\n";
            continue;
        }

        switch (choice) {
            case 1: addItem(); break;
            case 2: displayItems(); break;
            case 3: checkItem(); break;
            case 4: updateItem(); break;
            case 5: deleteItem(); break;
            case 6: return 0;
            default: std::cout << "Please choose 1-6.\n"; break;
        }
    }
}
