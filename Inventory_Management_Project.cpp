#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

class Product
{
private:
    string id;
    string name;
    string category;
    string brand;
    int quantity;
    float price;

public:
    void input()
    {

        cout << "Enter the ID of the product: ";
        cin.ignore();
        getline(cin, id);

        cout << "Enter the Name of the product: ";
        getline(cin, name);
        cout << "Enter the Category of the product: ";
        getline(cin, category);

        cout << "Enter the Brand of the product: ";
        getline(cin, brand);

        cout << "Enter the Quantity of the product which is to be added: ";
        while (!(cin >> quantity))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong Input, Enter the quantity again!\n";
        }
        cout << "Enter the Price of the product: ";
        while (!(cin >> price))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong Input, Enter the price again!\n";
        }
    }

    void display()
    {
        cout << left
             << setw(10) << id
             << setw(40) << name
             << setw(30) << category
             << setw(20) << brand
             << setw(15) << quantity
             << setw(10) << price
             << endl;
    }

    // Setter Functions
    void set_id(string x)
    {
        id = x;
    }
    void set_name(string x)
    {
        name = x;
    }
    void set_category(string x)
    {
        category = x;
    }
    void set_brand(string x)
    {
        brand = x;
    }
    void set_quantity(int x)
    {
        quantity = x;
    }
    void set_price(float x)
    {
        price = x;
    }

    // Getter Functions
    string get_id()
    {
        return id;
    }
    string get_name()
    {
        return name;
    }
    string get_category()
    {
        return category;
    }
    string get_brand()
    {
        return brand;
    }
    int get_quantity()
    {
        return quantity;
    }
    float get_price()
    {
        return price;
    }
};

class inventory_management
{
    vector<Product> inventory;

public:
    void header()
    {
        cout << endl
             << endl;
        cout << left
             << setw(10) << "ID"
             << setw(40) << "Name"
             << setw(30) << "Category"
             << setw(20) << "Brand"
             << setw(15) << "Quantity"
             << setw(10) << "Price" << endl
             << endl
             << endl;
    }

    void loadfromfile()
{
    ifstream in("Book1.csv");
    if (!in)
    {
        cout << "Error Opening the file!" << endl;
        return;
    }

    string line;
    getline(in, line); 

    while (getline(in, line))
    {
        Product p;
        stringstream ss(line);
        string temp;

        try {
            getline(ss, temp, ',');
            p.set_id(temp);

            getline(ss, temp, ',');
            p.set_name(temp);

            getline(ss, temp, ',');
            p.set_category(temp);

            getline(ss, temp, ',');
            p.set_brand(temp);

           
            getline(ss, temp, ',');
            try {
                size_t pos;
                int quantity = stoi(temp, &pos);
                if (pos != temp.length()) throw invalid_argument("Extra chars");
                p.set_quantity(quantity);
            } catch (invalid_argument) {
                cout << "\n\nInvalid quantity for the Product with item ID: " <<p.get_id()<< "\n\nUse Update Product Quantity to correct the Quantity of the Product" << endl;
                p.set_quantity(-1);
            }

            
            getline(ss, temp, ',');
            try {
                size_t pos;
                float price = stof(temp, &pos);
                if (pos != temp.length()) throw invalid_argument("Extra Chars");
                p.set_price(price);
            } catch (invalid_argument) {
                cout << "\n\nInvalid price for the Product with Item ID: " << p.get_id()<< "\n\nUse Update Product Price to correct the price of the Product" << endl;
                p.set_price(-1);
            }

            inventory.push_back(p);   
        }
        catch (exception &e)
        {
            cout << "Malformed line skipped entirely: " << line << "\nException: " << e.what() << endl;
        }
    }

    in.close();
}



    void savetofile()
    {
        Product p;
        ofstream out("Book1.csv");
        out << "ID,Name,Category,Brand,Quantity,Price\n";
        for (auto &p : inventory)
        {
            out << p.get_id() << "," << p.get_name() << "," << p.get_category() << "," << p.get_brand() << "," << p.get_quantity() << "," << p.get_price() << endl;
        }
        out.close();
        cout << "Data Saved to inventory" << endl;
    }
    
    void add_product()
    {
        Product p;
        p.input();
        inventory.push_back(p);
        cout << "Product Added\n";
    }

    void show_all_products()
    {

        cout << setw(90) << "\nX----------------------X------------------------- INVENTORY ------------------------------X-----------------------X" << endl
             << endl;

        header();
        for (auto &p : inventory)
        {
            p.display();
        }
    }

    void delete_products()
    {
        string product_id;
        cout << "Enter the ID of the product you want to delete\n";
        cin >> product_id;

        transform(product_id.begin(), product_id.end(), product_id.begin(), ::tolower);

        auto it = remove_if(inventory.begin(), inventory.end(), [product_id](Product &p)
                            {
                                string str=p.get_id();
                                transform(str.begin(),str.end(),str.begin(),::tolower);
                                 return str == product_id; });

        if (it != inventory.end())
        {
            inventory.erase(it, inventory.end());
            cout << "Product Deleted\n";
        }
        else
        {
            cout << "Product Not Found\n";
        }
    }

    void delete_product_byname()
    {
        string name;
        cout << "Enter the name of the product you want to delete: ";
        cin.ignore();
        getline(cin, name);
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        int count = 0;

        auto it = remove_if(inventory.begin(), inventory.end(), [name, &count](Product &p) // for remove_if <algorithm> and for tolower <cctype>
                            {
                                string str = p.get_name();
                                transform(str.begin(), str.end(), str.begin(), ::tolower);
                                if (str == name)
                                {
                                    count++;
                                    return true;
                                }
                                return false; });
        if (it != inventory.end())
        {
            inventory.erase(it, inventory.end());
        }

        if (count == 0)
        {
            cout << "No products Found !\n";
        }
        else
        {
            cout << count << " Product(s) Deleted\n";
        }
    }

    void search_products()
    {
        string product_id;
        cout << "Enter the ID of the Product you want to search: ";
        cin >> product_id;
        transform(product_id.begin(), product_id.end(), product_id.begin(), ::tolower);
        for (auto &p : inventory)
        {
            string str = p.get_id();
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            if (str == product_id)
            {
                header();

                p.display();
                return;
            }
        }
        cout << "Product Not Found\n";
    }

    void filter_by_Category()
    {
        string product_category;
        cout << "Enter the category of the product: ";
        cin >> product_category;
        transform(product_category.begin(), product_category.end(), product_category.begin(), ::tolower);
        header();

        bool found = false;
        for (auto &p : inventory)
        {
            string str = p.get_category();
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            if (str == product_category)
            {
                p.display();
                found = true;
            }
        }
        if (!found)
            cout << "Category of the Product Not Found!\n";
    }

    void filter_by_brand()
    {
        string product_brand;
        cout << "Enter the Brand of your Product: ";
        cin >> product_brand;
        transform(product_brand.begin(), product_brand.end(), product_brand.begin(), ::tolower);
        header();

        bool found = false;
        for (auto &p : inventory)
        {
            string str = p.get_brand();
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            if (str == product_brand)
            {
                p.display();
                found = true;
            }
        }
        if (!found)
            cout << "Product Brand Not Found!\n";
    }

    void search_by_name()
    {
        string name;
        cout << "Enter the name of the product you want to search: ";
        cin.ignore();
        getline(cin, name);
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        bool found = false;
        header();
        for (auto &p : inventory)
        {
            string str = p.get_name();
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            if (str == name)
            {

                p.display();
                found = true;
            }
        }
        if (!found)
            cout << "No Product found !\n";
    }

    void update_quantity()
    {
        string item_id;
        cout << "To update the quantity of the product, enter the Item ID of that product: ";
        cin >> item_id;

        transform(item_id.begin(), item_id.end(), item_id.begin(), ::tolower); // Header file: <algorithm> and for tolower <cctype>

        for (auto &p : inventory)
        {
            string str = p.get_id();
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            if (str == item_id)
            {
                int new_quantity;
                cout << "Enter the new quantity of product: ";
                while (!(cin >> new_quantity))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Wrong Input, Enter the quantity again!\n";
                }
                p.set_quantity(new_quantity);
                cout << "Quantity of the Product is Updated\n";
                return;
            }
        }
        cout << "Item ID not found !";
    }

    void update_price()
    {
        string item_id;
        cout << "Enter the ID of the product: ";
        cin >> item_id;

        transform(item_id.begin(), item_id.end(), item_id.begin(), ::tolower); // Header file: <algorithm> and for tolower <cctype>

        for (Product &p : inventory)
        {
            string str = p.get_id();
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            if (str == item_id)
            {
                float new_price;
                cout << "Enter the new price of product: ";
                while (!(cin >> new_price))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Wrong Input, Enter the price again!\n";
                }
                p.set_price(new_price);
                cout << "Price of the Product is Updated\n";
                return;
            }
        }
        cout << "Item ID not found!\n";
    }
    void showMenu()
    {
        cout << "\n------ Inventory Management Menu ------\n\n";
        cout << "1. Add Product\n";
        cout << "2. Show All Products\n";
        cout << "3. Search Product by ID\n";
        cout << "4. Search Product by Name\n";
        cout << "5. Delete Product by ID\n";
        cout << "6. Delete Product by Name\n";
        cout << "7. Filter by Category\n";
        cout << "8. Filter by Brand\n";
        cout << "9. Update Product Quantity\n";
        cout << "10. Update Product Price\n";
        cout << "11. Save and Exit\n\n";
    }
};

int main()
{
    inventory_management shop_inventory;
    int choice;
    shop_inventory.loadfromfile();

    do
    {
        shop_inventory.showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            shop_inventory.add_product();
            break;
        case 2:
            shop_inventory.show_all_products();
            break;
        case 3:
            shop_inventory.search_products();
            break;
        case 4:
            shop_inventory.search_by_name();
            break;
        case 5:
            shop_inventory.delete_products();
            break;
        case 6:
            shop_inventory.delete_product_byname();
            break;
        case 7:
            shop_inventory.filter_by_Category();
            break;
        case 8:
            shop_inventory.filter_by_brand();
            break;
        case 9:
            shop_inventory.update_quantity();
            break;
        case 10:
            shop_inventory.update_price();
            break;
        case 11:
            shop_inventory.savetofile();
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 11);
    return 0;
}