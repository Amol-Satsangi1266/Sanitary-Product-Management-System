/******************************************************
Railway Sanitary Product Management System (C++)
Clean Structured Implementation
Author: (Put your name)
******************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;

// ======================================================
// Utility
// ======================================================

string currentTime()
{
time_t now = time(0);
return string(ctime(&now));
}

// ======================================================
// Supplier Class
// ======================================================

class Supplier
{
public:
int id;
string name;
string contact;

```
Supplier() {}
Supplier(int i, string n, string c)
    : id(i), name(n), contact(c) {}
```

};

// ======================================================
// Product Class
// ======================================================

class Product
{
public:
int id;
string name;
string category;
int quantity;
string unit;
int supplierId;

```
Product() {}

Product(int i, string n, string c, int q, string u, int s)
    : id(i), name(n), category(c),
      quantity(q), unit(u), supplierId(s) {}
```

};

// ======================================================
// Transaction Log
// ======================================================

class Transaction
{
public:
int productId;
int change;
string type;
string time;

```
Transaction(int p, int ch, string t)
{
    productId = p;
    change = ch;
    type = t;
    time = currentTime();
}
```

};

// ======================================================
// Inventory System
// ======================================================

class InventorySystem
{
private:
vector<Product> products;
vector<Supplier> suppliers;
vector<Transaction> logs;

public:

```
// ---------------- Add Supplier ----------------
void addSupplier()
{
    int id;
    string name, contact;

    cout << "\nSupplier ID: ";
    cin >> id;
    cin.ignore();

    cout << "Name: ";
    getline(cin, name);

    cout << "Contact: ";
    getline(cin, contact);

    suppliers.emplace_back(id, name, contact);
    cout << "Supplier Added!\n";
}

// ---------------- Add Product ----------------
void addProduct()
{
    int id, qty, sid;
    string name, cat, unit;

    cout << "\nProduct ID: ";
    cin >> id;
    cin.ignore();

    cout << "Name: ";
    getline(cin, name);

    cout << "Category (Cleaner/Toilet/Paper/etc): ";
    getline(cin, cat);

    cout << "Initial Quantity: ";
    cin >> qty;

    cout << "Unit (Ltrs/Pcs/Kg): ";
    cin >> unit;

    cout << "Supplier ID: ";
    cin >> sid;

    products.emplace_back(id, name, cat, qty, unit, sid);
    logs.emplace_back(id, qty, "INITIAL");

    cout << "Product Added!\n";
}

// ---------------- Display Products ----------------
void displayProducts()
{
    cout << "\n====== PRODUCT LIST ======\n";

    for (auto &p : products)
    {
        cout << "\nID: " << p.id
             << "\nName: " << p.name
             << "\nCategory: " << p.category
             << "\nQuantity: " << p.quantity << " " << p.unit
             << "\nSupplier ID: " << p.supplierId
             << "\n----------------------\n";
    }
}

// ---------------- Stock Update ----------------
void updateStock(bool add)
{
    int id, qty;
    cout << "\nProduct ID: ";
    cin >> id;

    for (auto &p : products)
    {
        if (p.id == id)
        {
            cout << "Quantity: ";
            cin >> qty;

            if (add)
            {
                p.quantity += qty;
                logs.emplace_back(id, qty, "IN");
            }
            else
            {
                if (qty > p.quantity)
                {
                    cout << "Not enough stock!\n";
                    return;
                }
                p.quantity -= qty;
                logs.emplace_back(id, qty, "OUT");
            }

            cout << "Stock Updated!\n";
            return;
        }
    }
    cout << "Product not found!\n";
}

// ---------------- Show Logs ----------------
void showLogs()
{
    cout << "\n===== TRANSACTION LOG =====\n";

    for (auto &l : logs)
    {
        cout << "Product: " << l.productId
             << " | Change: " << l.change
             << " | Type: " << l.type
             << " | Time: " << l.time;
    }
}

// ---------------- Save to File ----------------
void save()
{
    ofstream f("products.dat");

    for (auto &p : products)
    {
        f << p.id << " "
          << p.name << " "
          << p.category << " "
          << p.quantity << " "
          << p.unit << " "
          << p.supplierId << "\n";
    }

    f.close();
    cout << "Data Saved!\n";
}

// ---------------- Menu ----------------
void menu()
{
    int choice;

    while (true)
    {
        cout << "\n====== RAILWAY SANITARY MANAGEMENT ======\n";
        cout << "1. Add Supplier\n";
        cout << "2. Add Product\n";
        cout << "3. Show Products\n";
        cout << "4. Stock IN\n";
        cout << "5. Stock OUT\n";
        cout << "6. Transaction Logs\n";
        cout << "7. Save\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1: addSupplier(); break;
        case 2: addProduct(); break;
        case 3: displayProducts(); break;
        case 4: updateStock(true); break;
        case 5: updateStock(false); break;
        case 6: showLogs(); break;
        case 7: save(); break;
        case 0: return;
        default: cout << "Invalid!\n";
        }
    }
}
```

};

// ======================================================
// Main
// ======================================================

int main()
{
InventorySystem system;
system.menu();
return 0;
}
