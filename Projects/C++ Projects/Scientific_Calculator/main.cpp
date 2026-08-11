#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

namespace {

bool readNumber(const char* prompt, double& value) {
    std::cout << prompt;
    if (std::cin >> value) {
        return true;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid number.\n";
    return false;
}

} // namespace

int main() {
    std::cout << std::setprecision(12);

    while (true) {
        std::cout << "\n=== Scientific Calculator ===\n"
                  << "1. Power\n"
                  << "2. Sine (radians)\n"
                  << "3. Square root\n"
                  << "4. Cosine (radians)\n"
                  << "5. Tangent (radians)\n"
                  << "6. Natural logarithm\n"
                  << "7. Base-10 logarithm\n"
                  << "0. Exit\n"
                  << "Choice: ";

        int choice{};
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice.\n";
            continue;
        }
        if (choice == 0) return 0;

        double x{}, y{};
        switch (choice) {
            case 1:
                if (readNumber("Base: ", x) && readNumber("Exponent: ", y))
                    std::cout << "Result: " << std::pow(x, y) << '\n';
                break;
            case 2:
                if (readNumber("Angle in radians: ", x))
                    std::cout << "Result: " << std::sin(x) << '\n';
                break;
            case 3:
                if (readNumber("Value: ", x)) {
                    if (x < 0) std::cout << "Square root requires a non-negative value.\n";
                    else std::cout << "Result: " << std::sqrt(x) << '\n';
                }
                break;
            case 4:
                if (readNumber("Angle in radians: ", x))
                    std::cout << "Result: " << std::cos(x) << '\n';
                break;
            case 5:
                if (readNumber("Angle in radians: ", x))
                    std::cout << "Result: " << std::tan(x) << '\n';
                break;
            case 6:
                if (readNumber("Value: ", x)) {
                    if (x <= 0) std::cout << "Logarithm requires a positive value.\n";
                    else std::cout << "Result: " << std::log(x) << '\n';
                }
                break;
            case 7:
                if (readNumber("Value: ", x)) {
                    if (x <= 0) std::cout << "Logarithm requires a positive value.\n";
                    else std::cout << "Result: " << std::log10(x) << '\n';
                }
                break;
            default:
                std::cout << "Please choose an option from 0-7.\n";
        }
    }
}
