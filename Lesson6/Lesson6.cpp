#include <iostream>
#include <string>
#include <ctime>

std::string current_task_name;  // Имя текущей задачи
std::time_t start_time;         // Время начала задачи
bool task_active = false;       // Флаг активности задачи

void begin_task() {

    if (task_active) {
        std::cout << "Задача \"" << current_task_name << "\" уже выполняется. Завершите её сначала." << std::endl;
        return;
    }
    std::cout << "Введите название задачи: ";
    std::getline(std::cin, current_task_name);
    start_time = std::time(nullptr);  // Время начала задачи
    task_active = true;
    std::cout << "Задача \"" << current_task_name << "\" началась." << std::endl;
}

void end_task() {
    if (!task_active) {
        std::cout << "Нет активной задачи для завершения." << std::endl;
        return;
    }
    std::time_t end_time = std::time(nullptr);  // Время завершения задачи
    double time_spent = std::difftime(end_time, start_time) / 3600.0;  // Время в часах
    std::cout << "Задача \"" << current_task_name << "\" завершена. Время на задачу: " << time_spent << " часов." << std::endl;
    task_active = false;
}

void show_status() {
    if (task_active) {
        std::cout << "Текущая задача: \"" << current_task_name << "\" выполняется." << std::endl;
    }
    else {
        std::cout << "Сейчас нет активной задачи." << std::endl;
    }
}

int main() {
    setlocale(LC_CTYPE, "rus");

    std::string command;

    while (true) {
        std::cout << "Введите команду (begin, end, status, exit): ";
        std::getline(std::cin, command);

        if (command == "begin") {
            begin_task();
        }
        else if (command == "end") {
            end_task();
        }
        else if (command == "status") {
            show_status();
        }
        else if (command == "exit") {
            if (task_active) {
                end_task();
            }
            std::cout << "Выход из программы..." << std::endl;
            break;
        }
        else {
            std::cout << "Неверная команда. Попробуйте снова." << std::endl;
        }
    }

    return 0;
}
