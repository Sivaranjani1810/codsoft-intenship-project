#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Task {
    string description;
    bool completed;

    Task(string desc) : description(desc), completed(false) {}
};

class TodoList {
private:
    vector<Task> tasks;

public:
    void addTask() {
        string taskDesc;
        cout << "Enter task description: ";
        getline(cin, taskDesc);

        if (taskDesc.empty()) {
            cout << "Task can't be empty! Try again.\n";
            return;
        }

        tasks.push_back(Task(taskDesc));
        cout << "Task added successfully!\n";
    }

    void viewTasks() {
        if (tasks.empty()) {
            cout << "No tasks yet. Add some tasks first!\n";
            return;
        }

        cout << "\n=== YOUR TODO LIST ===\n";
        for (int i = 0; i < tasks.size(); i++) {
            string status = tasks[i].completed ? "[X] COMPLETED" : "[ ] PENDING";
            cout << (i+1) << ". " << status << " - " << tasks[i].description << endl;
        }
        cout << "======================\n\n";
    }

    void markCompleted() {
        viewTasks();
        if (tasks.empty()) return;

        int taskNum;
        cout << "Enter task number to mark as completed: ";
        cin >> taskNum;
        cin.ignore(); // clear newline

        if (taskNum < 1 || taskNum > tasks.size()) {
            cout << "Invalid task number!\n";
            return;
        }

        tasks[taskNum-1].completed = true;
        cout << "Task marked as completed!\n";
    }

    void deleteTask() {
        viewTasks();
        if (tasks.empty()) return;

        int taskNum;
        cout << "Enter task number to delete: ";
        cin >> taskNum;
        cin.ignore();

        if (taskNum < 1 || taskNum > tasks.size()) {
            cout << "Invalid task number!\n";
            return;
        }

        tasks.erase(tasks.begin() + taskNum - 1);
        cout << "Task deleted successfully!\n";
    }
};

int main() {
    TodoList todo;
    int choice;

    cout << "=== SIMPLE TODO LIST MANAGER ===\n";

    while (true) {
        cout << "\n1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task Complete\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "Choose option (1-5): ";

        cin >> choice;
        cin.ignore(); // handle newline after number input

        switch (choice) {
            case 1:
                todo.addTask();
                break;
            case 2:
                todo.viewTasks();
                break;
            case 3:
                todo.markCompleted();
                break;
            case 4:
                todo.deleteTask();
                break;
            case 5:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice! Pick 1-5.\n";
        }
    }

    return 0;
}
