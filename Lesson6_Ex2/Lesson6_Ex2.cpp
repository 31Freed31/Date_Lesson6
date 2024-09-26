#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

struct Friend {
    std::string name;
    int year, month, day;
};

int days_until_birthday(int current_year, int current_month, int current_day, int birth_month, int birth_day) {
    if (birth_month > current_month || (birth_month == current_month && birth_day >= current_day)) {
        std::tm this_year_birthday = {};
        this_year_birthday.tm_year = current_year - 1900;
        this_year_birthday.tm_mon = birth_month - 1;
        this_year_birthday.tm_mday = birth_day;

        std::tm today = {};
        today.tm_year = current_year - 1900;
        today.tm_mon = current_month - 1;
        today.tm_mday = current_day;

        std::time_t today_time = std::mktime(&today);
        std::time_t birthday_time = std::mktime(&this_year_birthday);

        return (birthday_time - today_time) / (60 * 60 * 24);
    }
    std::tm next_year_birthday = {};
    next_year_birthday.tm_year = current_year + 1 - 1900;
    next_year_birthday.tm_mon = birth_month - 1;
    next_year_birthday.tm_mday = birth_day;

    std::tm today = {};
    today.tm_year = current_year - 1900;
    today.tm_mon = current_month - 1;
    today.tm_mday = current_day;

    std::time_t today_time = std::mktime(&today);
    std::time_t birthday_time = std::mktime(&next_year_birthday);

    return (birthday_time - today_time) / (60 * 60 * 24);
}

int main() {
    setlocale(LC_CTYPE, "rus");
    std::vector<Friend> friends;
    std::string name;

    while (true) {
        std::cout << "Введите имя друга (или 'end' для завершения ввода): ";
        std::getline(std::cin, name);

        if (name == "end") break;

        Friend new_friend;
        new_friend.name = name;

        std::cout << "Введите дату рождения (год месяц день): ";
        std::cin >> new_friend.year >> new_friend.month >> new_friend.day;
        std::cin.ignore();

        friends.push_back(new_friend);
    }

    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);

    int current_year = local_time->tm_year + 1900;
    int current_month = local_time->tm_mon + 1;
    int current_day = local_time->tm_mday;

    std::string closest_friend_name;
    int min_days = 366;

    bool birthday_today = false;

    for (const auto& f : friends) {
        int days_to_birthday = days_until_birthday(current_year, current_month, current_day, f.month, f.day);

        if (days_to_birthday == 0) {
            std::cout << "Сегодня день рождения у " << f.name << "!" << std::endl;
            birthday_today = true;
        }
        else if (days_to_birthday < min_days) {
            min_days = days_to_birthday;
            closest_friend_name = f.name;
        }
    }

    if (!birthday_today && !closest_friend_name.empty()) {
        std::cout << "Ближайший день рождения у " << closest_friend_name << " через " << min_days << " дней." << std::endl;
    }

    return 0;
}
