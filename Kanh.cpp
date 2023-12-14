#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

class Student {
private:
    string name;
    double attendance[5];

public:
    void inputDetails() {
        // use of error handling for name of student
        do {
            cout << "Enter student name: ";
            getline(cin, name);
        } while (!isValidName(name));

        // attendance percentage for 5 subjects
        cout << "Enter attendance percentage for subjects:\n";
        for (int i = 0; i < 5; ++i) {
            do {
                cout << "Subject " << getSubjectName(i) << ": ";
                cin >> attendance[i];

                if (cin.fail() || attendance[i] < 0 || attendance[i] > 100) {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Error: Please enter a valid percentage between 0 and 100.\n";
                }
            } while (attendance[i] < 0 || attendance[i] > 100);
        }
        cin.ignore(); // Ignore the newline character left in the buffer
    }

    double calculateMeanPercentage() const {
        double sum = 0;
        for (int i = 0; i < 5; ++i) {
            sum += attendance[i];
        }
        return sum / 5.0;
    }

    string getCategory() const {
        return calculateMeanPercentage() > 90.0 ? "A" : "B";
    }

    string getName() const {
        return name;
    }

private:
    bool isValidName(const string &name) const {
        // Check if the name contains only alphabetic characters
        return all_of(name.begin(), name.end(), [](char c) {
            return isalpha(static_cast<unsigned char>(c)) || isspace(static_cast<unsigned char>(c));
        });
    }

    string getSubjectName(int index) const {
        // Assign subject names based on the index
        switch (index) {
        case 0:
            return "FLAT";
        case 1:
            return "OOPS";
        case 2:
            return "SE";
        case 3:
            return "COA";
        case 4:
            return "CS";
        default:
            return "Unknown Subject";
        }
    }
};

int main() {
    int numStudents;

    // Input number of students with error handling
    do {
        cout << "Enter the number of students (a positive integer): ";
        if (!(cin >> numStudents) || numStudents <= 0) {
            cout << "Error: Please enter a valid positive integer for the number of students.\n";
            cin.clear();                                                    // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    } while (numStudents <= 0);

    cin.ignore(); // Ignore the newline character left in the buffer

    vector<Student> students;

    // Input details for each student
    for (int i = 0; i < numStudents; ++i) {
        Student student;
        student.inputDetails();
        students.push_back(student);
    }

    // Separate students into categories A and B
    vector<Student> categoryA, categoryB;
    for (const auto &student : students) {
        if (student.getCategory() == "A") {
            categoryA.push_back(student);
        } else {
            categoryB.push_back(student);
        }
    }

    // Display details for each student with category
    cout << "\nStudent Details:\n";
    cout << "Category A:\n";
    for (const auto &student : categoryA) {
        cout << student.getName() << " - Mean Percentage: " << student.calculateMeanPercentage() << "%\n";
    }

    cout << "\nCategory B:\n";
    for (const auto &student : categoryB) {
        cout << student.getName() << " - Mean Percentage: " << student.calculateMeanPercentage() << "%\n";
    }

    return 0;
}
