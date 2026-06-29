#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Course {
    string courseNumber;
    string courseTitle;
    string prerequisites;
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) {
        course = c;
        left = nullptr;
        right = nullptr;
    }
};
class BinarySearchTree {
private:
    Node* root;

    // Helper function to add node recursively
    void addNode(Node* node, Course course) {

        if (course.courseNumber < node->course.courseNumber) {

            if (node->left == nullptr) {
                node->left = new Node(course);
            }
            else {
                addNode(node->left, course);
            }
        }
        else {

            if (node->right == nullptr) {
                node->right = new Node(course);
            }
            else {
                addNode(node->right, course);
            }
        }
    }

    // In-order traversal for sorted output
    void inOrder(Node* node) {

        if (node == nullptr) {
            return;
        }

        inOrder(node->left);

        cout << node->course.courseNumber
            << ", "
            << node->course.courseTitle
            << endl;

        inOrder(node->right);
    }

public:

    // Constructor
    BinarySearchTree() {
        root = nullptr;
    }

    // Insert course into BST
    void Insert(Course course) {

        if (root == nullptr) {
            root = new Node(course);
        }
        else {
            addNode(root, course);
        }
    }

    // Print all courses in sorted order
    void PrintAll() {
        inOrder(root);
    }

    // Search for a course
    Course Search(string courseNumber) {

        Node* current = root;

        while (current != nullptr) {

            if (current->course.courseNumber == courseNumber) {
                return current->course;
            }

            if (courseNumber < current->course.courseNumber) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        return Course{ "", "", "" };
    }
};
BinarySearchTree courseTree;

void loadFile(string filename) {

    ifstream file(filename);

    // Error handling if file cannot open
    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;

    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        Course course;

        // Read course number
        getline(ss, course.courseNumber, ',');

        // Read course title
        getline(ss, course.courseTitle, ',');

        // Read prerequisites
        string prereq;

        while (getline(ss, prereq, ',')) {

            if (!course.prerequisites.empty()) {
                course.prerequisites += ", ";
            }

            course.prerequisites += prereq;
        }

        // Insert into BST
        courseTree.Insert(course);
    }

    file.close();

    cout << "Courses loaded successfully." << endl;
}
void printCourse(string courseNumber) {

    Course course = courseTree.Search(courseNumber);

    if (course.courseNumber == "") {
        cout << "Course not found." << endl;
        return;
    }

    cout << course.courseNumber
        << ", "
        << course.courseTitle
        << endl;

    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: "
            << course.prerequisites
            << endl;
    }
}
void displayMenu() {

    cout << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
}
int main() {

    string choice;
    string filename;

    cout << "Welcome to the course planner." << endl;

    while (choice != "9") {

        displayMenu();

        cout << "What would you like to do? ";
        cin >> choice;

        // Load data
        if (choice == "1") {

            cout << "Enter file name: ";
            cin >> filename;

            loadFile(filename);
        }

        // Print sorted course list
        else if (choice == "2") {

            cout << endl;
            cout << "Here is a sample schedule:" << endl;

            courseTree.PrintAll();
        }

        // Search for course
        else if (choice == "3") {

            string courseNumber;

            cout << "What course do you want to know about? ";
            cin >> courseNumber;

            // Convert input to uppercase
            for (char& c : courseNumber) {
                c = toupper(c);
            }

            printCourse(courseNumber);
        }

        // Exit
        else if (choice == "9") {

            cout << "Thank you for using the course planner!" << endl;
        }

        // Invalid input
        else {

            cout << choice
                << " is not a valid option."
                << endl;
        }
    }

    return 0;
}