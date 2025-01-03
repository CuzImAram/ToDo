---

# ToDo Command Line Program

A simple command-line ToDo application that allows you to manage your tasks. Tasks are stored in a file (`todo.txt`), and the program provides commands for adding, removing, marking tasks as done, listing tasks, resetting tasks, and saving them to a file on Windows.

---

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
    - [Commands](#available-commands)
- [File Format](#file-format)
- [Make the `todo` Command Globally Executable on Windows](#make-the-todo-command-globally-executable-on-windows)
- [Doxygen Documentation](#doxygen-documentation)

---

## Features

- **Add Tasks**: Add a new task to the list.
- **Remove Tasks**: Remove a task by its index.
- **Mark Tasks as Done**: Mark a task as completed.
- **List Tasks**: Display all tasks with their completion status.
- **Reset Tasks**: Clear all tasks from the list.
- **Persistent Storage**: Tasks are saved to and loaded from `todo.txt`.

---

## Installation

### Requirements:
- A C++ compiler (e.g., `g++`, `clang++`) to compile the program.
- A terminal/command prompt.

### Steps to Install:

1. **Clone the repository** or download the source code.
2. Open your terminal and navigate to the project folder.
3. Compile the code using `g++` (or another C++ compiler):

   ```bash
   g++ -o todo todo.cpp
   ```

4. After compilation, the `todo` executable will be created in the same directory.

---

## Usage

Once the program is compiled, you can use the `todo` command from your terminal.

### Running the Program:

```bash
./todo [COMMAND] [ARGUMENTS]
```

### Available Commands:

1. **`list`**: Lists all tasks.
    - Displays the tasks saved in the `todo.txt` file along with their completion status.
    - Example usage:
      ```bash
      ./todo list
      ```
    - **Example output**:
      ```
      1. [ ] Buy groceries
      2. [ ] Clean the house
      ```

2. **`add [TASK]`**: Adds a new task to the list.
    - Adds the task specified in the argument to the list.
    - Example usage:
      ```bash
      ./todo add "Buy groceries"
      ./todo add "Clean the house"
      ```

3. **`remove [INDEX]`**: Removes a task by its index.
    - Removes the task at the specified index (1-based indexing).
    - Example usage:
      ```bash
      ./todo remove 1
      ```

4. **`done [INDEX]`**: Marks a task as completed.
    - Marks the task at the specified index as done.
    - Example usage:
      ```bash
      ./todo done 2
      ```

5. **`reset`**: Clears all tasks.
    - Deletes all tasks from the task list.
    - Example usage:
      ```bash
      ./todo reset
      ```

---

## File Format

The tasks are stored in a file named `todo.txt` in the following format:

```
[COMPLETION_STATUS] [TASK_DESCRIPTION]
```

- **[COMPLETION_STATUS]**: A boolean value (`0` for incomplete, `1` for completed).
- **[TASK_DESCRIPTION]**: A string that describes the task.

### Example of `todo.txt`:

```
0 Buy groceries
0 Clean the house
1 Finish project
```

---

## Notes:

- The **completion status** (`[X]` for done, `[ ]` for incomplete) is displayed when you list the tasks using the `list` command.
- Tasks are saved automatically to `todo.txt` when any modification is made (adding, removing, or marking tasks as done).
- When you run the program, it loads tasks from `todo.txt` into memory to perform operations.

---

## Make the `todo` Command Globally Executable on Windows

To execute the `todo` program from anywhere in your terminal without needing to specify its full path:

### Move the Executable to a Folder in the PATH

You need to place `todo.exe` in a directory that is included in your system's `PATH` environment variable. Alternatively, you can use the directory where your project is located, as long as the `todo.exe` file is in it.

**Steps**:

1. **Use Your Project Directory**:  
   Ensure `todo.exe` is in the same folder as your project. For example, if your project is in `C:\MyProjects\TodoApp`, `todo.exe` should also be in `C:\MyProjects\TodoApp`.

2. **Add Your Project Folder to the PATH**:
   - Open **Environment Variables** (Search for "Environment Variables" in the Start Menu).
   - Under **User Variables** or **System Variables**, locate and select `Path`.
   - Click **Edit** and add the directory of your project (e.g., `C:\MyProjects\TodoApp`).
   - Save and close.

3. **Verify the Change**:
   - Open a **new** Command Prompt.
   - Run:
     ```cmd
     where todo
     ```
   - If the path to `todo.exe` appears, it’s now accessible globally.

4. **Test the `todo` Command**:  
   Run any command to ensure the program works:
   ```cmd
   todo list
   ```

## Doxygen Documentation

If you want to view the generated Doxygen documentation for this project:

1. Navigate to the `docs/html` folder in the project directory.
2. Open the `index.html` file in your web browser.

This will show you the detailed documentation for the code, including classes, functions, and descriptions.

---


