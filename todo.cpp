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

#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

/**
 * @brief Retrieves the directory path of the currently executing executable.
 *
 * This function uses the Windows API to obtain the full path of the executable
 * and extracts the directory portion of the path by finding the last directory separator.
 *
 * @return std::string The directory path where the executable is located.
 */
std::string getExecutableDirectory() {
    char path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH); // Gets the full path to the .exe
    std::string fullPath = path;
    size_t pos = fullPath.find_last_of("\\/");
    return fullPath.substr(0, pos); // Extracts the directory path
}

const std::string FILENAME = getExecutableDirectory() + "\\todo.txt"; /**< File path relative to the .exe location */

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
 * @brief Trims leading and trailing whitespaces from a string.
 *
 * This function removes any leading and trailing whitespace characters, including
 * spaces, tabs, newlines, and carriage returns, from the input string.
 *
 * @param str The input string to be trimmed.
 * @return A new string with leading and trailing whitespaces removed. If the input string
 *         contains only whitespaces, an empty string is returned.
 */
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == string::npos || last == string::npos) {
        return "";
    }
    return str.substr(first, (last - first + 1));
}

/**
 * @brief Loads tasks from a file into the task list.
 *
 * This function reads tasks from a file specified by the `FILENAME` constant.
 * Each task in the file is expected to be stored on a new line in the format:
 *
 *     <completion_status> <task_description>
 *
 * where:
 * - `<completion_status>` is a boolean (0 or 1) indicating whether the task is completed.
 * - `<task_description>` is the string description of the task.
 *
 * Tasks are loaded into the provided vector, clearing any existing tasks before loading.
 * If the file cannot be opened, a message is displayed to the user.
 *
 * @param tasks The vector of tasks to be populated from the file.
 */
void loadTasksFromFile(vector<Task>& tasks) {
    ifstream file(FILENAME);
    if (file.is_open()) {
        string line;
        tasks.clear();
        while (getline(file, line)) {
            stringstream ss(line);
            bool completed;
            string desc;
            ss >> completed;
            getline(ss, desc);
            desc = trim(desc);  // Trim leading/trailing spaces from description
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
    string task;

    for (int i = 2; i < argc; ++i) {
        task += argv[i];
        if (i < argc - 1) task += " "; // Add space between arguments
    }

    if (command == "list") {
        listTasks(tasks);
    } else if (command == "add" && argc > 2) {
        addTask(tasks, task);
        saveTasks(tasks);
        listTasks(tasks);
    } else if (command == "remove" && argc > 2) {
        int index = stoi(task);
        removeTask(tasks, index);
        saveTasks(tasks);
        listTasks(tasks);
    } else if (command == "done" && argc > 2) {
        int index = stoi(task);
        markDone(tasks, index);
        saveTasks(tasks);
        listTasks(tasks);
    } else if (command == "reset") {
        resetTasks(tasks);
        saveTasks(tasks);
        cout << "All tasks reset." << endl;
    } else {
        cout << "Invalid command." << endl;
    }

    return 0;
}
