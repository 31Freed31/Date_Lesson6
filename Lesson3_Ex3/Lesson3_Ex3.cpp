#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <ctime>
#include <sstream>

int main() {
    setlocale(LC_CTYPE, "rus");
    int minutes, seconds;

    std::cout << "Введите время для таймера в формате MM:SS: ";
    std::string input;
    std::getline(std::cin, input);

    std::stringstream ss(input);
    char colon;
    ss >> minutes >> colon >> seconds;

    if (colon != ':' || minutes < 0 || seconds < 0 || seconds >= 60) {
        std::cerr << "Неверный формат времени." << std::endl;
        return 1;
    }

    int total_seconds = minutes * 60 + seconds;

    while (total_seconds > 0) {
        int display_minutes = total_seconds / 60;
        int display_seconds = total_seconds % 60;

        std::cout << std::setw(2) << std::setfill('0') << display_minutes << ":"
            << std::setw(2) << std::setfill('0') << display_seconds << "\r" << std::flush;

        std::this_thread::sleep_for(std::chrono::seconds(1));

        --total_seconds;
    }

    std::cout << "\nDING! DING! DING!" << std::endl;

    return 0;
}
