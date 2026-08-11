#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace {

struct Subject {
    std::string name;
    double credits{};
    double gradePoint{};
};

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readPositiveInt(const std::string& prompt) {
    int value{};
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value > 0) {
            return value;
        }
        std::cout << "Please enter a positive whole number.\n";
        clearInput();
    }
}

double readNonNegativeDouble(const std::string& prompt) {
    double value{};
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= 0.0) {
            return value;
        }
        std::cout << "Please enter a non-negative number.\n";
        clearInput();
    }
}

void calculateGpa() {
    const int count = readPositiveInt("Number of subjects: ");
    std::vector<Subject> subjects;
    subjects.reserve(static_cast<std::size_t>(count));

    for (int i = 0; i < count; ++i) {
        Subject subject;
        std::cout << "\nSubject " << (i + 1) << " name: ";
        std::cin >> std::ws;
        std::getline(std::cin, subject.name);
        subject.credits = readNonNegativeDouble("Credits: ");
        subject.gradePoint = readNonNegativeDouble("Grade point: ");
        subjects.push_back(subject);
    }

    double totalCredits = 0.0;
    double weightedPoints = 0.0;
    for (const auto& subject : subjects) {
        totalCredits += subject.credits;
        weightedPoints += subject.credits * subject.gradePoint;
    }

    if (totalCredits == 0.0) {
        std::cout << "GPA cannot be calculated because total credits are zero.\n";
        return;
    }

    std::cout << std::fixed << std::setprecision(2)
              << "\nTotal credits: " << totalCredits
              << "\nWeighted GPA: " << (weightedPoints / totalCredits) << "\n";
}

void calculateCgpa() {
    const int count = readPositiveInt("Number of semesters: ");
    std::vector<double> semesterGpas;
    semesterGpas.reserve(static_cast<std::size_t>(count));

    for (int i = 0; i < count; ++i) {
        semesterGpas.push_back(
            readNonNegativeDouble("Semester " + std::to_string(i + 1) + " GPA: "));
    }

    double total = 0.0;
    for (double gpa : semesterGpas) {
        total += gpa;
    }

    std::cout << std::fixed << std::setprecision(2)
              << "\nCGPA: " << (total / static_cast<double>(semesterGpas.size())) << "\n";
}

void showMethod() {
    std::cout << "\nGPA = sum(credit hours x grade points) / total credit hours\n"
              << "CGPA = average of semester GPAs in this calculator.\n"
              << "Note: institutions may calculate CGPA differently when semester credit loads differ.\n";
}

} // namespace

int main() {
    while (true) {
        std::cout << "\n=== GPA / CGPA Calculator ===\n"
                  << "1. Calculate GPA\n"
                  << "2. Calculate CGPA\n"
                  << "3. Show calculation method\n"
                  << "4. Exit\n"
                  << "Choice: ";

        int choice{};
        if (!(std::cin >> choice)) {
            clearInput();
            std::cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1: calculateGpa(); break;
            case 2: calculateCgpa(); break;
            case 3: showMethod(); break;
            case 4: return 0;
            default: std::cout << "Please choose 1-4.\n"; break;
        }
    }
}
