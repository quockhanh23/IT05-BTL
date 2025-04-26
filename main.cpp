#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

int checkInputNumber() {
    int number;
    try {
        cin >> number;
        if (cin.fail()) {
            // Xóa cờ lỗi của cin
            cin.clear();
            // Bỏ qua ký tự thừa trong buffer
            cin.ignore(1000, '\n');
            throw invalid_argument("Must enter a number");
        }
        if (number <= 0) {
            throw invalid_argument("Do not enter negative numbers");
        }
    }
    catch (const invalid_argument &e) {
        throw invalid_argument("Must enter a number");
    }
    return number;
}

class Product {
public:
    long id{};
    string productCode;
    string productName;
    int productQuantity{};
    int productPrice{};

    Product() = default;
};

class Customer {
public:
    long id{};
    string customerCode;
    string customerName;
    string phone;

    Customer() = default;
};

class Bill {
public:
    long id{};
    string billCode;
    string customerCode;
    int totalProduct{};
    int totalPrice{};

    Bill() = default;
};

vector<Product> productList;
vector<Customer> customerList;
vector<Bill> billList;

void writeFile(int type) {
    int productType = 1;
    int customerType = 2;
    int billType = 3;
    if (productType == type) {
        ofstream basicOfStream(R"(E:\CLionProjects\IT05-BTL\product.txt)");
        for (int i = 0; i < productList.size(); i++) {
            basicOfStream << productList[i].productCode << "|" << productList[i].productName << "|"
                          << productList[i].productPrice << endl;
        }
        basicOfStream.close();
    }
    if (customerType == type) {
        ofstream basicOfStream(R"(E:\CLionProjects\IT05-BTL\customer.txt)");
        for (int i = 0; i < customerList.size(); i++) {
            basicOfStream << customerList[i].customerCode << "|" << customerList[i].customerName << "|"
                          << customerList[i].phone << endl;
        }
        basicOfStream.close();
    }
    if (billType == type) {
        ofstream basicOfStream(R"(E:\CLionProjects\IT05-BTL\bill.txt)");
        for (int i = 0; i < productList.size(); i++) {
            basicOfStream << billList[i].billCode << "|" << billList[i].customerCode << "|"
                          << billList[i].totalProduct << "|" << billList[i].totalPrice << endl;
        }
        basicOfStream.close();
    }
}

void readFile(const string &partFile, int type) {
    ifstream fin(partFile);
    int productType = 1;
    int customerType = 2;
    int billType = 3;
    if (productType == type) {
        Product product;
        productList.clear();
        while (getline(fin, product.productCode, '|')) {
            getline(fin, product.productName, '|');
            fin >> product.productPrice;
            fin.ignore();
            productList.push_back(product);
        }
        fin.close();
    }
    if (customerType == type) {
        Customer customer;
        while (getline(fin, customer.customerCode, '|')) {
            getline(fin, customer.customerName, '|');
            fin >> customer.phone;
            fin.ignore();
            customerList.push_back(customer);
        }
        fin.close();
    }
    if (billType == type) {
        Bill bill;
        while (getline(fin, bill.billCode, '|')) {
            getline(fin, bill.customerCode, '|');
            fin >> bill.totalProduct;
            fin >> bill.totalPrice;
            fin.ignore();
            billList.push_back(bill);
        }
        fin.close();
    }
}

void createProduct() {
    string productCode;
    string productName;
    int productQuantity;
    int productPrice;
    cout << "Enter Product Code: ";
    cin >> productCode;
    cout << "Enter Product Name: ";
    cin.ignore();
    getline(cin, productName);
    cout << "Enter Product Quantity: ";
    try {
        productQuantity = checkInputNumber();
    } catch (const invalid_argument &e) {
        cout << "<<-----Invalid Quantity----->>" << endl;
        cout << "<<-----" << e.what() << "----->>" << endl;
        cout << "------------------------------" << endl;
        return;
    }
    cout << "Enter Product Price: ";
    try {
        productPrice = checkInputNumber();
    } catch (const invalid_argument &e) {
        cout << "<<-----Invalid Price----->>" << endl;
        cout << "<<-----" << e.what() << "----->>" << endl;
        cout << "------------------------------" << endl;
        return;
    }
    Product *product = new Product();
    product->id = (long) productList.size() + 1;
    product->productCode = productCode;
    product->productName = productName;
    product->productPrice = productPrice;
    product->productQuantity = productQuantity;
    productList.push_back(*product);
    cout << "<<-----" << "Create successful product" << "----->>" << endl;
}

void createDefaultProduct() {
    auto *product1 = new Product();
    product1->id = (long) productList.size() + 1;
    product1->productCode = "C01";
    product1->productName = "Sam Sung";
    product1->productPrice = 1000;
    product1->productQuantity = 10;
    productList.push_back(*product1);

    auto *product2 = new Product();
    product2->id = (long) productList.size() + 1;
    product2->productCode = "A02";
    product2->productName = "Xiaomi";
    product2->productPrice = 2000;
    product2->productQuantity = 10;
    productList.push_back(*product2);

    auto *product3 = new Product();
    product3->id = (long) productList.size() + 1;
    product3->productCode = "T03";
    product3->productName = "Apple";
    product3->productPrice = 5000;
    product3->productQuantity = 10;
    productList.push_back(*product3);

    auto *product4 = new Product();
    product4->id = (long) productList.size() + 1;
    product4->productCode = "X01";
    product4->productName = "Oppo";
    product4->productPrice = 1500;
    product4->productQuantity = 10;
    productList.push_back(*product4);
}

void updateProduct(Product &product) {
    string productCode;
    string productName;
    int productQuantity;
    int productPrice;
    cout << "Enter Product Code: ";
    cin >> productCode;
    cout << "Enter Product Name: ";
    cin.ignore();
    getline(cin, productName);
    cout << "Enter Product Quantity: ";
    try {
        productQuantity = checkInputNumber();
    } catch (const invalid_argument &e) {
        cout << "<<-----Invalid Quantity----->>" << endl;
        cout << "<<-----" << e.what() << "----->>" << endl;
        cout << "------------------------------" << endl;
        return;
    }
    cout << "Enter Product Price: ";
    try {
        productPrice = checkInputNumber();
    } catch (const invalid_argument &e) {
        cout << "<<-----Invalid Price----->>" << endl;
        cout << "<<-----" << e.what() << "----->>" << endl;
        cout << "------------------------------" << endl;
        return;
    }
    product.productCode = productCode;
    product.productName = productName;
    product.productPrice = productPrice;
    product.productQuantity = productQuantity;
    cout << "<<-----" << "Update successful product" << "----->>" << endl;
}

void printAllProduct(vector<Product> products) {
    cout << "\n--------------------------\n";
    cout << "PRODUCT LIST:" << endl;
    cout << setw(10) << "Product Id" << setw(20) << "Product Code" << setw(20) << "Product Name"
         << setw(20) << "Product Quantity" << setw(20) << "Product Price" << endl;
    for (int i = 0; i < products.size(); i++) {
        cout << setw(10) << products[i].id
             << setw(20) << products[i].productCode
             << setw(20) << products[i].productName
             << setw(20) << products[i].productQuantity
             << setw(20) << products[i].productPrice << endl;
    }
}

void createCustomer() {
    string customerCode;
    string customerName;
    string phone;
    cout << "Enter Customer Code: ";
    cin >> customerCode;
    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, customerName);
    cout << "Enter Customer Phone: ";
    cin >> phone;

    Customer *customer = new Customer();
    customer->id = (long) customerList.size() + 1;
    customer->customerCode = customerCode;
    customer->customerName = customerName;
    customer->phone = phone;
    customerList.push_back(*customer);
    cout << "<<-----" << "Create successful customer" << "----->>" << endl;
}

void updateCustomer(Customer &customer) {
    string customerCode;
    string customerName;
    string phone;
    cout << "Enter Customer Code: ";
    cin >> customerCode;
    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, customerName);
    cout << "Enter Customer Phone: ";
    cin >> phone;
    customer.customerCode = customerCode;
    customer.customerName = customerName;
    customer.phone = phone;
    cout << "<<-----" << "Update successful customer" << "----->>" << endl;
}

void printAllCustomer(vector<Customer> list) {
    cout << "\n--------------------------\n";
    cout << "CUSTOMER LIST:\n";
    cout << setw(10) << "Customer Id" << setw(20) << "Customer Code" << setw(20) << "Customer Name" << setw(20)
         << "Customer Phone\n";
    for (int i = 0; i < list.size(); i++) {
        cout << setw(10) << list[i].id
             << setw(20) << list[i].customerCode
             << setw(20) << list[i].customerName
             << setw(20) << list[i].phone << endl;
    }
}

void createBill() {
    string billCode;
    string customerCode;
    int totalProduct;
    int totalPrice;
    cout << "Enter Bill Code: ";
    cin >> billCode;
    cout << "Enter Customer Code: ";
    cin.ignore();
    getline(cin, customerCode);
    cout << "Enter Total Product: ";
    try {
        totalProduct = checkInputNumber();
    } catch (const invalid_argument &e) {
        cout << "<<-----Invalid Quantity----->>" << endl;
        cout << "<<-----" << e.what() << "----->>" << endl;
        cout << "------------------------------" << endl;
        return;
    }
    cout << "Enter Total Price: ";
    try {
        totalPrice = checkInputNumber();
    } catch (const invalid_argument &e) {
        cout << "<<-----Invalid Quantity----->>" << endl;
        cout << "<<-----" << e.what() << "----->>" << endl;
        cout << "------------------------------" << endl;
        return;
    }
    Bill *bill = new Bill();
    bill->id = (long) billList.size() + 1;
    bill->billCode = billCode;
    bill->customerCode = customerCode;
    bill->totalProduct = totalProduct;
    bill->totalPrice = totalPrice;
    billList.push_back(*bill);
}

void updateBill(Bill &bill) {
    string billCode;
    string customerCode;
    int totalProduct;
    int totalPrice;
    cout << "Enter Bill Code: ";
    cin >> billCode;
    cout << "Enter Customer Code: ";
    cin.ignore();
    getline(cin, customerCode);
    cout << "Enter Total Product: ";
    try {
        totalProduct = checkInputNumber();
    } catch (const invalid_argument &e) {
        cout << "<<-----Invalid Quantity----->>" << endl;
        cout << "<<-----" << e.what() << "----->>" << endl;
        cout << "------------------------------" << endl;
        return;
    }
    cout << "Enter Total Price: ";
    try {
        totalPrice = checkInputNumber();
    } catch (const invalid_argument &e) {
        cout << "<<-----Invalid Quantity----->>" << endl;
        cout << "<<-----" << e.what() << "----->>" << endl;
        cout << "------------------------------" << endl;
        return;
    }
    bill.billCode = billCode;
    bill.customerCode = customerCode;
    bill.totalProduct = totalProduct;
    bill.totalPrice = totalPrice;
    cout << "<<-----" << "Update successful bill" << "----->>" << endl;
}

void printAllBill(vector<Bill> list) {
    cout << "\n--------------------------\n";
    cout << "BILL LIST:\n";
    cout << setw(10) << "Bill Id" << setw(20) << "Bill Code" << setw(20) << "Customer Code"
         << setw(20) << "Total Product" << setw(20) << "Total Price" << endl;
    for (int i = 0; i < list.size(); i++) {
        cout << setw(10) << list[i].id
             << setw(20) << list[i].billCode
             << setw(20) << list[i].customerCode
             << setw(20) << list[i].totalProduct
             << setw(20) << list[i].totalPrice << endl;
    }
}

int checkIdValid(string objectName) {
    cout << "\n--------------------------\n";
    int id;
    cout << "Enter " << objectName << " Id: ";
    try {
        id = checkInputNumber();
    } catch (const invalid_argument &e) {
        cout << "<<-----Invalid Id----->>" << endl;
        cout << "<<-----" << e.what() << "----->>" << endl;
        cout << "------------------------------" << endl;
        return 0;
    }
    return id;
}

void deleteProductById() {
    int id = checkIdValid("Product");
    if (id > 0) {
        for (int i = 0; i < productList.size(); i++) {
            if (productList[i].id == id) {
                productList.erase(productList.begin() + i);
                cout << "<<-----" << "Delete successful" << "----->>" << endl;
                return;
            }
        }
    }
    cout << "Not found product id : " << id << endl;
}

void deleteCustomerById() {
    int id = checkIdValid("Customer");
    if (id > 0) {
        for (int i = 0; i < customerList.size(); i++) {
            if (customerList[i].id == id) {
                customerList.erase(customerList.begin() + i);
                cout << "<<-----" << "Delete successful" << "----->>" << endl;
                return;
            }
        }
    }
    cout << "Not found customer id : " << id << endl;
}

void deleteBillById() {
    int id = checkIdValid("Bill");
    if (id > 0) {
        for (int i = 0; i < billList.size(); i++) {
            if (billList[i].id == id) {
                billList.erase(billList.begin() + i);
                cout << "<<-----" << "Delete successful" << "----->>" << endl;
                return;
            }
        }
    }
    cout << "Not found bill id : " << id << endl;
}

Product &updateProductById() {
    cout << "\n--------------------------\n";
    int id;
    cout << "Enter Product Id: ";
    try {
        id = checkInputNumber();
    } catch (const invalid_argument &e) {
        cout << "<<-----Invalid Id----->>" << endl;
        throw invalid_argument("Invalid Id");
    }
    for (int i = 0; i < productList.size(); i++) {
        if (productList[i].id == id) {
            return productList[i];
        }
    }
    cout << "Not found Product id : " << id << endl;
}

Customer &updateCustomerById() {
    cout << "\n--------------------------\n";
    int id;
    cout << "Enter Customer Id: ";
    try {
        id = checkInputNumber();
    } catch (const invalid_argument &e) {
        cout << "<<-----Invalid Id----->>" << endl;
        throw invalid_argument("Invalid Id");
    }
    for (int i = 0; i < customerList.size(); i++) {
        if (customerList[i].id == id) {
            return customerList[i];
        }
    }
    cout << "Not found Customer id : " << id << endl;
}

Bill &updateBillById() {
    cout << "\n--------------------------\n";
    int id;
    cout << "Enter Bill Id: ";
    try {
        id = checkInputNumber();
    } catch (const invalid_argument &e) {
        cout << "<<-----Invalid Id----->>" << endl;
        throw invalid_argument("Invalid Id");
    }
    for (int i = 0; i < billList.size(); i++) {
        if (billList[i].id == id) {
            return billList[i];
        }
    }
    cout << "Not found Bill id : " << id << endl;
}

void findAllBillByCustomerCode() {
    string customerCode;
    cout << "Enter Customer Code: ";
    cin >> customerCode;
    cout << "All Customer have code like '" << customerCode << endl;
    vector<Bill> list;
    for (auto bill: billList) {
        if (customerCode == bill.customerCode) {
            list.push_back(bill);
        }
    }
    printAllBill(list);
}

void findAllBillByBillCode() {
    string billCode;
    cout << "Enter Customer name: ";
    cin >> billCode;
    cout << "All Bill have code like " << billCode << endl;
    vector<Bill> list;
    for (auto bill: billList) {
        if (billCode == bill.billCode) {
            list.push_back(bill);
        }
    }
    printAllBill(list);
}

void findAllCustomerByCustomerCode() {
    string customerCode;
    cout << "Enter Customer Code: ";
    cin >> customerCode;
    cout << "All Customer have code like '" << customerCode << endl;
    vector<Customer> list;
    for (auto customer: customerList) {
        if (customerCode == customer.customerCode) {
            list.push_back(customer);
        }
    }
    printAllCustomer(list);
}

void findAllCustomerByCustomerName() {
    string customerName;
    cout << "Enter Customer name: ";
    cin >> customerName;
    cout << "All Customer have name like " << customerName << endl;
    vector<Customer> list;
    for (auto customer: customerList) {
        if (customerName == customer.customerName) {
            list.push_back(customer);
        }
    }
    printAllCustomer(list);
}

void findAllProductByProductCode() {
    string productCode;
    cout << "Enter Product Code: ";
    cin >> productCode;
    cout << "All Product have code like '" << productCode << endl;
    vector<Product> list;
    for (auto product: productList) {
        if (productCode == product.productCode) {
            list.push_back(product);
        }
    }
    printAllProduct(list);
}

void findAllProductByProductName() {
    string productName;
    cout << "Enter Product Name: ";
    cin >> productName;
    cout << "All Product have name like " << productName << endl;
    vector<Product> list;
    for (auto product: productList) {
        if (productName == product.productCode) {
            list.push_back(product);
        }
    }
    printAllProduct(list);
}

void sortProductByPriceAsc() {
    sort(productList.begin(), productList.end(), [](Product a, Product b) { return a.productPrice < b.productPrice; });
}

void sortProductByPriceDesc() {
    sort(productList.begin(), productList.end(), [](Product a, Product b) { return a.productPrice > b.productPrice; });
}

void sortProductByNameAsc() {
    sort(productList.begin(), productList.end(), [](Product a, Product b) { return a.productName < b.productName; });
}

void sortProductByCodeAsc() {
    sort(productList.begin(), productList.end(), [](Product a, Product b) { return a.productCode < b.productCode; });
}

void findMaxPriceProduct() {
    cout << "\n--------------------------\n";
    auto maxSP = max_element(productList.begin(), productList.end(),
                             [](Product a, Product b) { return a.productPrice < b.productPrice; });
    cout << "Max Price All Product: " << maxSP->productPrice << endl;
}

void findMinPriceProduct() {
    cout << "\n--------------------------\n";
    auto minSP = min_element(productList.begin(), productList.end(),
                             [](Product a, Product b) { return a.productPrice < b.productPrice; });
    cout << "Min Price All Product: " << minSP->productPrice << endl;

}

void totalPriceAllProduct() {
    int total = 0;
    cout << "\n--------------------------\n";
    for (auto p: productList) total += p.productPrice;
    cout << "Total Price All Product: " << total << endl;
}

void avgPriceAllProduct() {
    int avg = 0;
    cout << "\n--------------------------\n";
    for (auto sp: productList) avg += sp.productPrice;
    cout << "Average Price: " << avg / productList.size() << endl;
}

void objectMenu(string objectName) {
    string name = objectName;
    transform(objectName.begin(), objectName.end(), objectName.begin(), ::toupper);
    cout << "\n--------------------------\n";
    cout << "\n=== " << objectName << " MENU ===\n";
    cout << "1. Create New " << name << endl;
    cout << "2. Print " << name << " List" << endl;
    cout << "3. Write File\n";
    cout << "4. Read File\n";
    cout << "5. Update " << name << " By " << name << " Id\n";
    cout << "6. Delete " << name << " By " << name << " Id\n";
    if (name == "Bill") {
        cout << "7. Find All " << name << " By " << "Customer" << " Code\n";
        cout << "8. Find All " << name << " By " << name << " Code\n";
    } else {
        cout << "7. Find All " << name << " By " << name << " Code\n";
        cout << "8. Find All " << name << " By " << name << " Name\n";
    }
    if (name == "Product") {
        cout << "9. Sort " << name << " By " << name << " Name\n";
        cout << "10. Sort " << name << " By " << name << " Code\n";
        cout << "11. Sort " << name << " By " << name << " Price ASC\n";
        cout << "12. Sort " << name << " By " << name << " Price DESC\n";
        cout << "13. Total Price Of All " << name << endl;
        cout << "14. Average Price Of All " << name << endl;
        cout << "15. Max Price Of All " << name << endl;
        cout << "16. Min Price Of All " << name << endl;
    }
    cout << "0. Exit\n";
    cout << "Choice: ";
}

void customerMenu() {
    int choice;
    do {
        objectMenu("Customer");
        cin >> choice;
        switch (choice) {
            case 1:
                createCustomer();
                break;
            case 2:
                printAllCustomer(customerList);
                break;
            case 3:
                writeFile(2);
                break;
            case 4:
                readFile(R"(E:\CLionProjects\IT05-BTL\customer.txt)", 2);
                break;
            case 5: {
                Customer &customer = updateCustomerById();
                updateCustomer(customer);
                break;
            }
            case 6: {
                deleteCustomerById();
                break;
            }
            case 7: {
                findAllCustomerByCustomerCode();
                break;
            }
            case 8: {
                findAllCustomerByCustomerName();
                break;
            }
            default:
                cout << "No option";
                break;
        }
    } while (choice != 0);
}

void billMenu() {
    int choice;
    do {
        objectMenu("Bill");
        cin >> choice;
        switch (choice) {
            case 1:
                createBill();
                break;
            case 2:
                printAllBill(billList);
                break;
            case 3:
                writeFile(3);
                break;
            case 4:
                readFile(R"(E:\CLionProjects\IT05-BTL\bill.txt)", 2);
                break;
            case 5: {
                Bill &bill = updateBillById();
                updateBill(bill);
                break;
            }
            case 6: {
                deleteBillById();
                break;
            }
            default:
                cout << "No option";
                break;
        }
    } while (choice != 0);
}

void productMenu() {
    int choice;
    do {
        objectMenu("Product");
        cin >> choice;
        switch (choice) {
            case 1:
                createProduct();
                break;
            case 2:
                printAllProduct(productList);
                break;
            case 3:
                writeFile(1);
                break;
            case 4:
                readFile(R"(E:\CLionProjects\IT05-BTL\product.txt)", 1);
                break;
            case 5: {
                Product &product = updateProductById();
                updateProduct(product);
                break;
            }
            case 6: {
                deleteProductById();
                break;
            }
            case 7: {
                findAllProductByProductCode();
                break;
            }
            case 8: {
                findAllProductByProductName();
                break;
            }
            case 9: {
                sortProductByNameAsc();
                break;
            }
            case 10: {
                sortProductByCodeAsc();
                break;
            }
            case 11: {
                sortProductByPriceAsc();
                break;
            }
            case 12: {
                sortProductByPriceDesc();
                break;
            }
            case 13: {
                totalPriceAllProduct();
                break;
            }
            case 14: {
                avgPriceAllProduct();
                break;
            }
            case 15: {
                findMaxPriceProduct();
                break;
            }
            case 16: {
                findMinPriceProduct();
                break;
            }
            default:
                cout << "No option";
                break;
        }
    } while (choice != 0);
}

void mainMenu() {
    createDefaultProduct();
    int choice;
    do {
        cout << "\n--------------------------\n";
        cout << "\n=== MENU ===\n";
        cout << "1. Customer Management\n";
        cout << "2. Product Management\n";
        cout << "3. Bill Management\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        try {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        catch (const invalid_argument &e) {
            choice = 9999;
        }
        switch (choice) {
            case 0:
                cout << "\n--------------------------\n";
                cout << "\nGoodbye and see you again !!!\n";
                cout << "\n--------------------------\n";
                return;
            case 1:
                customerMenu();
                break;
            case 2:
                productMenu();
                break;
            case 3:
                billMenu();
                break;
            default:
                cout << "\n--------------------------\n";
                cout << "No option";
                break;
        }
    } while (choice);
}

int main() {
    mainMenu();
    return 0;
}
