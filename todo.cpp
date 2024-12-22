/**
* @file todo.cpp
 * @brief A simple ToDo command-line program to manage tasks.
 *
 * This program allows the user to:
 * - Add, remove, and list tasks.
 * - Mark tasks as completed.
 * - Reset all tasks.
 *
 * The tasks are saved in the "todo.txt" file.
 *
 * @see todo class
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

const string FILENAME = "todo.txt"; /**< The filename where tasks are stored. */

/**
 * @struct Task
 * @brief Represents a task in the ToDo list.
 *
 * Each task has a description and a completion status.
 */
struct Task {
    string description; /**< The description of the task. */
    bool completed;     /**< The completion status of the task. */

    /**
     * @brief Constructs a Task.
     * @param desc The task description.
     * @param comp The completion status, default is false.
     */
    Task(const string& desc, bool comp = false) : description(desc), completed(comp) {}
};

/**
 * @brief Lists all tasks.
 *
 * Iterates through the tasks vector and displays each task's description
 * and its completion status.
 * @param tasks The vector of tasks to be listed.
 */
void listTasks(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available." << endl;
        return;
    }

    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". [" << (tasks[i].completed ? "X" : " ") << "] " << tasks[i].description << endl;
    }
}

/**
 * @brief Adds a new task.
 *
 * Creates a new task with the given description and adds it to the tasks list.
 * @param tasks The vector of tasks.
 * @param task The description of the task to be added.
 */
void addTask(vector<Task>& tasks, const string& task) {
    tasks.push_back(Task(task));
}

/**
 * @brief Removes a task by index.
 *
 * Removes the task at the specified index in the tasks list.
 * @param tasks The vector of tasks.
 * @param index The index of the task to be removed.
 */
void removeTask(vector<Task>& tasks, int index) {
    if (index >= 1 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1);
    } else {
        cout << "Invalid task index." << endl;
    }
}

/**
 * @brief Marks a task as completed.
 *
 * Sets the completion status of the task at the specified index to true.
 * @param tasks The vector of tasks.
 * @param index The index of the task to be marked as done.
 */
void markDone(vector<Task>& tasks, int index) {
    if (index >= 1 && index <= tasks.size()) {
        tasks[index - 1].completed = true;
    } else {
        cout << "Invalid task index." << endl;
    }
}

/**
 * @brief Clears all tasks.
 *
 * Removes all tasks from the tasks list.
 * @param tasks The vector of tasks.
 */
void resetTasks(vector<Task>& tasks) {
    tasks.clear();
}

/**
 * @brief Loads tasks from the file.
 *
 * Reads tasks from the "todo.txt" file and populates the tasks list.
 * @param tasks The vector of tasks to be populated.
 */
void loadTasksFromFile(vector<Task>& tasks) {
    ifstream file(FILENAME);
    if (file.is_open()) {
        string line;
        tasks.clear();
        while (getline(file, line)) {
            stringstream ss(line);
            string desc;
            bool completed;
            ss >> completed;
            getline(ss, desc);
            tasks.push_back(Task(desc, completed));
        }
        file.close();
    } else {
        cout << "No saved tasks found." << endl;
    }
}

/**
 * @brief Saves tasks to the file.
 *
 * Writes the current tasks to the "todo.txt" file, saving the description and completion status.
 * @param tasks The vector of tasks to be saved.
 */
void saveTasks(const vector<Task>& tasks) {
    ofstream file(FILENAME);
    if (file.is_open()) {
        for (const auto& task : tasks) {
            file << task.completed << " " << task.description << endl;
        }
        file.close();
    }
}

/**
 * @brief Main entry point of the ToDo application.
 *
 * Handles command-line arguments to execute the appropriate task-related functions.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return An integer status code (1 for invalid input, 0 for success).
 */
int main(int argc, char* argv[]) {
    vector<Task> tasks;

    // Load tasks from the file at the beginning
    loadTasksFromFile(tasks);

    if (argc < 2) {
        cout << "Usage: todo [COMMAND] [ARGUMENTS]" << endl;
        return 1;
    }

    string command = argv[1];

    if (command == "list") {
        listTasks(tasks);
    } else if (command == "add" && argc > 2) {
        string task(argv[2]);
        addTask(tasks, task);
        saveTasks(tasks);
    } else if (command == "remove" && argc > 2) {
        int index = stoi(argv[2]);
        removeTask(tasks, index);
        saveTasks(tasks);
    } else if (command == "done" && argc > 2) {
        int index = stoi(argv[2]);
        markDone(tasks, index);
        saveTasks(tasks);
    } else if (command == "reset") {
        resetTasks(tasks);
        saveTasks(tasks);
    } else {
        cout << "Invalid command." << endl;
    }

    return 0;
}
