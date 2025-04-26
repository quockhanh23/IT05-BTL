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
    int productQuantity = 0;
    int productPrice = 0;
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

void printAllProduct() {
    cout << "\n---------------------------------------------\n";
    cout << "PRODUCT LIST:" << endl;
    cout << setw(10) << "Product Id" << setw(20) << "Product Code" << setw(20) << "Product Name"
         << setw(20) << "Product Quantity" << setw(20) << "Product Price" << endl;
    for (int i = 0; i < productList.size(); i++) {
        cout << setw(10) << productList[i].id
             << setw(20) << productList[i].productCode
             << setw(20) << productList[i].productName
             << setw(20) << productList[i].productQuantity
             << setw(20) << productList[i].productPrice << endl;
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
    customer->id = (long) productList.size() + 1;
    customer->customerCode = customerCode;
    customer->customerName = customerName;
    customer->phone = phone;
    customerList.push_back(*customer);
}

void printAllCustomer() {
    cout << "\n---------------------------------------------\n";
    cout << "CUSTOMER LIST:\n";
    cout << setw(10) << "Customer Id" << setw(20) << "Customer Code" << setw(20) << "Customer Name" << setw(20)
         << "Customer Phone\n";
    for (int i = 0; i < customerList.size(); i++) {
        cout << setw(10) << customerList[i].id
             << setw(20) << customerList[i].customerCode
             << setw(20) << customerList[i].customerName
             << setw(20) << customerList[i].phone << endl;
    }
}

void createBill() {
    string billCode;
    string customerCode;
    int totalProduct = 0;
    int totalPrice = 0;
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
    bill->id = (long) productList.size() + 1;
    bill->billCode = billCode;
    bill->customerCode = customerCode;
    bill->totalProduct = totalProduct;
    bill->totalPrice = totalPrice;
    billList.push_back(*bill);
}

void printAllBill() {
    cout << "\n---------------------------------------------\n";
    cout << "BILL LIST:\n";
    cout << setw(10) << "Bill Id" << setw(20) << "Bill Code" << setw(20) << "Customer Code"
         << setw(20) << "Total Product" << setw(20) << "Total Price" << endl;
    for (int i = 0; i < billList.size(); i++) {
        cout << setw(10) << billList[i].id
             << setw(20) << billList[i].billCode
             << setw(20) << billList[i].customerCode
             << setw(20) << billList[i].totalProduct
             << setw(20) << billList[i].totalPrice << endl;
    }
}

void xoaSanPhamTheoMaSP(vector<Product> &dsSP) {
    string ma;
    cout << "Nhap ma san pham can xoa: ";
    cin.ignore();
    getline(cin, ma);
    for (auto it = dsSP.begin(); it != dsSP.end(); ++it) {
        if (it->productCode == ma) {
            dsSP.erase(it);
            cout << "Da xoa san pham co ma: " << ma << endl;
            return;
        }
    }
    cout << "Khong tim thay san pham co ma: " << ma << endl;
}

void timSanPhamTheoGia(double g) {
    cout << "San pham co gia >= " << g << ":\n";
    for (auto sp: productList)
        if (sp.productPrice >= g) {

        }
}

void timSanPhamTheoMaSP(string maSP) {
    cout << "San pham co ten chua '" << maSP << "':\n";
    for (auto sp: productList) {

    }
}

void timSanPhamTheoTen(string ten) {
    cout << "San pham co ten chua '" << ten << "':\n";
    for (auto sp: productList) {

    }
}

// ==== Sắp xếp ====
void sapXepSP_TangTheoGia() {
    sort(productList.begin(), productList.end(), [](Product a, Product b) { return a.productPrice < b.productPrice; });
}

void sapXepSP_GiamTheoGia() {
    sort(productList.begin(), productList.end(), [](Product a, Product b) { return a.productPrice > b.productPrice; });
}

void sapXepSP_TheoTen() {
    sort(productList.begin(), productList.end(), [](Product a, Product b) { return a.productName < b.productName; });
}

// ==== Tìm lớn nhất / nhỏ nhất ====
void sanPhamGiaMax() {
    auto maxSP = max_element(productList.begin(), productList.end(),
                             [](Product a, Product b) { return a.productPrice < b.productPrice; });
    cout << "San pham co gia cao nhat:\n";

}

void sanPhamGiaMin() {
    auto minSP = min_element(productList.begin(), productList.end(),
                             [](Product a, Product b) { return a.productPrice < b.productPrice; });
    cout << "San pham co gia thap nhat:\n";
}

// ==== Tổng / trung bình / đếm ====
void tongGiaSP() {
    double tong = 0;
    for (auto sp: productList) tong += sp.productPrice;
    cout << "Tong gia tat ca san pham: " << tong << endl;
}

void trungBinhGiaSP() {
    double tong = 0;
    for (auto sp: productList) tong += sp.productPrice;
    cout << "Gia trung binh: " << tong / productList.size() << endl;
}

void demSPGiaCaoHon(double g) {
    int dem = count_if(productList.begin(), productList.end(), [&](Product sp) { return sp.productPrice > g; });
    cout << "So san pham co gia > " << g << " la: " << dem << endl;
}

// ==== Thống kê theo điều kiện ====
void thongKeSPGiaTren(double g) {
    cout << "San pham co gia tren " << g << ":\n";
    for (auto sp: productList) {

    }

}

void thongKeSPGiaTuDen(double minG, double maxG) {
    cout << "San pham co gia tu " << minG << " den " << maxG << ":\n";
    for (auto sp: productList) {

    }
}

void customerMenu() {
    int choice;
    do {
        cout << "\n--------------------------\n";
        cout << "\n=== CUSTOMER MENU ===\n";
        cout << "1. Create New Customer\n";
        cout << "2. Print Customer list\n";
        cout << "3. Print File\n";
        cout << "4. Read File\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                createCustomer();
                break;
            case 2:
                printAllCustomer();
                break;
            case 3:
                writeFile(2);
                break;
            case 4:
                readFile(R"(E:\CLionProjects\IT05-BTL\customer.txt)", 2);
                break;
            default:
                cout << "No option\n";
                break;
        }
    } while (choice != 0);
}

void billMenu() {
    int choice;
    do {
        cout << "\n--------------------------\n";
        cout << "\n=== BILL MENU ===\n";
        cout << "1. Create New Bill\n";
        cout << "2. Print Bill List\n";
        cout << "3. Print File\n";
        cout << "4. Read File\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                createBill();
                break;
            case 2:
                printAllBill();
                break;
            case 3:
                writeFile(3);
                break;
            case 4:
                readFile(R"(E:\CLionProjects\IT05-BTL\bill.txt)", 2);
                break;
            default:
                cout << "No option\n";
                break;
        }
    } while (choice != 0);
}

void productMenu() {
    int choice;
    do {
        cout << "\n--------------------------\n";
        cout << "\n=== PRODUCT MENU ===\n";
        cout << "1. Create New Product\n";
        cout << "2. Print Product List\n";
        cout << "3. Print File\n";
        cout << "4. Read File\n";
        cout << "5. Update Product By Product Code\n";
        cout << "6. Delete Product By Product Code\n";
        cout << "7. Find Product By Product Code\n";
        cout << "7. Find Product By Product Name\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                createProduct();
                break;
            case 2:
                printAllProduct();
                break;
            case 3:
                writeFile(1);
                break;
            case 4:
                readFile(R"(E:\CLionProjects\IT05-BTL\product.txt)", 1);
                break;
            case 5: {

                break;
            }
            case 6: {

                break;
            }
            case 7:

                break;
            default:
                cout << "No option\n";
                break;
        }
    } while (choice != 0);
}

void mainMenu() {
    int choice;
    do {
        cout << "\n--------------------------\n";
        cout << "\n=== MENU ===\n";
        cout << "1. Customer Management\n";
        cout << "2. Product Management\n";
        cout << "3. Bill Management\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice) {
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
                cout << "No option\n";
                break;
        }
    } while (choice);
}

int main() {
    mainMenu();
    return 0;
}
