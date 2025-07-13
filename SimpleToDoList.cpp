#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Класс для представления задачи

class Task {
    std::string title;
    enum class Status { Pending, Completed } status = Status::Pending;
// Методы для работы с задачами
public:
    std::string getTitle() const {
        return title;
    }
    void setTitle (const std::string& newTitle) {
        title = newTitle;
    }
    bool isCompleted() const {
        return status == Status::Completed;
    }
    void setStatus(bool completed) {
        status = completed ? Status::Completed : Status::Pending;
    }
    void setDone() {
        status = Status::Completed;
    }
};
class TaskManager {
    std::vector<Task> tasks;
public:
    std::vector<Task> getTasks() const {
        return tasks;
    }
//Методы для управления задачами
    void addTask(const std::string& title) {
    Task newTask;
    newTask.setTitle(title);
    tasks.push_back(newTask);
}
    void removeTask(int index) {
    if (index < 0 || index >= tasks.size()) {
        std::cerr << "Invalid index: " << index << "\n";
        return;
    }
    tasks.erase(tasks.begin() + index);
}
    void markDone(int index) {
    if (index < 0 || index >= tasks.size()) {
        std::cerr << "Invalid index: " << index << "\n";
        return;
    }
    tasks[index].setDone();
}
// Функции для сохранения и загрузки задач из файла
    void saveTasks(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        // Обработка ошибки открытия файла
        std::cerr << "Error opening file for writing: " << filename << "\n";
        return;
    }
    for (const auto& task : tasks) {
        file << task.getTitle() << "\n";
        file << (task.isCompleted() ? "Completed" : "Pending") << "\n";
    }
}

    void loadTasks(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        // Обработка ошибки открытия файла
        std::cout << "Error opening file for reading: " << filename << "\n";
        std::ofstream file(filename);
        std::cerr << "Creating new file: " << filename << "\n";
        return;
    }
    std::string line;
    std::string status;
    while (std::getline(file, line)) {
        Task task;
        task.setTitle(line);
        std::getline(file, status);
        if (status == "Completed") {
            task.setStatus(true);
        } else {
            task.setStatus(false);
        }
        tasks.push_back(task);
    }
}
// Функция для вывода списка задач
    void printTasks() {
    for(int i = 0; i < tasks.size(); i++) {
        std::cout << i + 1 << ')' << (tasks[i].isCompleted() ? "[x] " : "[ ] ") << tasks[i].getTitle() << "\n";
    }
};
};

int main()  {
    std::vector<Task> tasks;
    TaskManager taskManager;
    taskManager.loadTasks("tasks.txt");
    std::string command;
    while (true) {
        std::cout << "Current tasks:\n";
        taskManager.printTasks();
        std::cout << "Enter command (add/remove/markdone/save/exit): ";
        std::cin >> command;

        if (command == "add") {
            std::string title;
            std::cout << "Enter task title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            taskManager.addTask(title);
        }
        else if (command == "remove") {
            int input;
            std::cout << "Enter task index to remove: ";
            std::cin >> input;
            taskManager.removeTask(input - 1);
        }
        else if (command == "markdone") {
            int input;
            std::cout << "Enter task index to mark as done: ";
            std::cin >> input;
            taskManager.markDone(input - 1);
        }
        else if (command == "save") {
            taskManager.saveTasks("tasks.txt");
            std::cout << "Tasks saved to tasks.txt\n";
        }
        else if (command == "exit") {
            taskManager.saveTasks("tasks.txt");
            std::cout << "Exiting and saving tasks to tasks.txt\n";
            break;
        }

    }
}

