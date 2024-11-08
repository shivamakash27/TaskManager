#include <iostream>
#include <string>

using namespace std;


struct Task {
    string description;
    int priority;
    Task* next;
};


class TaskManager {
private:
    Task* head;

public:
    TaskManager() : head(nullptr) {}

 
    void addTask(const string& description, int priority) {
        Task* newTask = new Task{description, priority, nullptr};
        if (!head || head->priority > priority) {
            newTask->next = head;
            head = newTask;
        } else {
            Task* current = head;
            while (current->next && current->next->priority <= priority) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }
        cout << "Task added: " << description << " with priority " << priority << endl;
    }

    void removeTask(const string& description) {
        if (!head) {
            cout << "No tasks to remove." << endl;
            return;
        }

        if (head->description == description) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Task removed: " << description << endl;
            return;
        }

        Task* current = head;
        while (current->next && current->next->description != description) {
            current = current->next;
        }

        if (current->next) {
            Task* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Task removed: " << description << endl;
        } else {
            cout << "Task not found: " << description << endl;
        }
    }

   
    void displayTasks() {
        if (!head) {
            cout << "No tasks available." << endl;
            return;
        }

        cout << "Tasks:" << endl;
        Task* current = head;
        while (current) {
            cout << "Description: " << current->description << ", Priority: " << current->priority << endl;
            current = current->next;
        }
    }

    ~TaskManager() {
        while (head) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }
};


int main() {
    TaskManager taskManager;
    int choice;
    string description;
    int priority;

    do {
        cout << "\nTask Management System" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Remove Task" << endl;
        cout << "3. Display Tasks" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter task description: ";
                cin.ignore(); 
                getline(cin, description);
                cout << "Enter task priority (lower number means higher priority): ";
                cin >> priority;
                taskManager.addTask(description, priority);
                break;
            case 2:
                cout << "Enter task description to remove: ";
                cin.ignore();
                getline(cin, description);
                taskManager.removeTask(description);
                break;
            case 3:
                taskManager.displayTasks();
                break;
            case 4:
                cout << "Exiting the Task Management System." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}