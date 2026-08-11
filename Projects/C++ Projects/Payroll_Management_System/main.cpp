#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace {
constexpr const char* kDataFile = "employees.csv";

struct Employee {
    int id{};
    std::string name;
    std::string title;
    double monthlySalary{};
    double allowance{};
    double deduction{};
};

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::vector<Employee> loadEmployees() {
    std::vector<Employee> employees;
    std::ifstream in(kDataFile);
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        Employee employee;
        std::string id, salary, allowance, deduction;
        if (std::getline(ss, id, ',') && std::getline(ss, employee.name, ',') &&
            std::getline(ss, employee.title, ',') && std::getline(ss, salary, ',') &&
            std::getline(ss, allowance, ',') && std::getline(ss, deduction, ',')) {
            try {
                employee.id = std::stoi(id);
                employee.monthlySalary = std::stod(salary);
                employee.allowance = std::stod(allowance);
                employee.deduction = std::stod(deduction);
                employees.push_back(employee);
            } catch (const std::exception&) {
                // Skip malformed legacy rows instead of terminating the application.
            }
        }
    }
    return employees;
}

bool saveEmployees(const std::vector<Employee>& employees) {
    std::ofstream out(kDataFile, std::ios::trunc);
    if (!out) return false;
    out << std::setprecision(12);
    for (const auto& e : employees) {
        out << e.id << ',' << e.name << ',' << e.title << ','
            << e.monthlySalary << ',' << e.allowance << ',' << e.deduction << '\n';
    }
    return static_cast<bool>(out);
}

std::optional<std::size_t> findEmployee(const std::vector<Employee>& employees, int id) {
    for (std::size_t i = 0; i < employees.size(); ++i) {
        if (employees[i].id == id) return i;
    }
    return std::nullopt;
}

bool readMoney(const std::string& prompt, double& value) {
    std::cout << prompt;
    if (std::cin >> value && value >= 0.0) return true;
    clearInput();
    std::cout << "Please enter a non-negative number.\n";
    return false;
}

void printEmployee(const Employee& e) {
    const double net = e.monthlySalary + e.allowance - e.deduction;
    std::cout << "ID: " << e.id << "\nName: " << e.name << "\nTitle: " << e.title
              << std::fixed << std::setprecision(2)
              << "\nBase salary: $" << e.monthlySalary
              << "\nAllowance: $" << e.allowance
              << "\nDeduction: $" << e.deduction
              << "\nNet monthly pay: $" << net << "\n";
}

void addEmployee(std::vector<Employee>& employees) {
    Employee e;
    std::cout << "Employee ID: ";
    if (!(std::cin >> e.id)) { clearInput(); std::cout << "Invalid ID.\n"; return; }
    if (findEmployee(employees, e.id)) { std::cout << "That employee ID already exists.\n"; return; }

    std::cout << "Name: ";
    std::cin >> std::ws;
    std::getline(std::cin, e.name);
    std::cout << "Job title: ";
    std::getline(std::cin, e.title);
    if (!readMoney("Monthly salary: $", e.monthlySalary) ||
        !readMoney("Monthly allowance: $", e.allowance) ||
        !readMoney("Monthly deduction: $", e.deduction)) return;

    employees.push_back(e);
    std::cout << (saveEmployees(employees) ? "Employee saved.\n" : "Unable to save employees.\n");
}

void editEmployee(std::vector<Employee>& employees) {
    int id{};
    std::cout << "Employee ID: ";
    if (!(std::cin >> id)) { clearInput(); return; }
    const auto index = findEmployee(employees, id);
    if (!index) { std::cout << "Employee not found.\n"; return; }

    Employee& e = employees[*index];
    std::cout << "New name: ";
    std::cin >> std::ws;
    std::getline(std::cin, e.name);
    std::cout << "New job title: ";
    std::getline(std::cin, e.title);
    if (!readMoney("Monthly salary: $", e.monthlySalary) ||
        !readMoney("Monthly allowance: $", e.allowance) ||
        !readMoney("Monthly deduction: $", e.deduction)) return;
    std::cout << (saveEmployees(employees) ? "Employee updated.\n" : "Unable to save employees.\n");
}

void deleteEmployee(std::vector<Employee>& employees) {
    int id{};
    std::cout << "Employee ID: ";
    if (!(std::cin >> id)) { clearInput(); return; }
    const auto oldSize = employees.size();
    employees.erase(std::remove_if(employees.begin(), employees.end(),
                                   [&](const Employee& e) { return e.id == id; }), employees.end());
    if (employees.size() == oldSize) { std::cout << "Employee not found.\n"; return; }
    std::cout << (saveEmployees(employees) ? "Employee deleted.\n" : "Unable to save employees.\n");
}

void listEmployees(const std::vector<Employee>& employees) {
    if (employees.empty()) { std::cout << "No employees stored.\n"; return; }
    for (const auto& e : employees) {
        std::cout << e.id << " | " << e.name << " | " << e.title << '\n';
    }
}

void salarySlip(const std::vector<Employee>& employees) {
    int id{};
    std::cout << "Employee ID: ";
    if (!(std::cin >> id)) { clearInput(); return; }
    const auto index = findEmployee(employees, id);
    if (!index) { std::cout << "Employee not found.\n"; return; }
    std::cout << "\n=== Salary Slip ===\n";
    printEmployee(employees[*index]);
}
} // namespace

int main() {
    auto employees = loadEmployees();
    while (true) {
        std::cout << "\n=== Payroll Management System ===\n"
                  << "1. Add employee\n2. Edit employee\n3. Delete employee\n"
                  << "4. List employees\n5. Salary slip\n0. Exit\nChoice: ";
        int choice{};
        if (!(std::cin >> choice)) { clearInput(); continue; }
        switch (choice) {
            case 1: addEmployee(employees); break;
            case 2: editEmployee(employees); break;
            case 3: deleteEmployee(employees); break;
            case 4: listEmployees(employees); break;
            case 5: salarySlip(employees); break;
            case 0: return 0;
            default: std::cout << "Please choose 0-5.\n";
        }
    }
}
