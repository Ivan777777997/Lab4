#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

// Функция для удаления лишних пробелов
std::string removeExtraSpaces(const std::string& str) {
        std::string result = str;
        bool prevSpace = false;
        int index = 0;
        
        while (index < result.length()) {
            if (result[index] == ' ') {
                if (prevSpace) {
                    result.erase(index, 1);
                    continue;
                }
                prevSpace = true;
            } else {
                prevSpace = false;
            }
            index++;
        }
        
        return result;
    }

// Функция для удаления лишних знаков препинания
std::string removeExtraPunctuation(const std::string& str) {
    std::string result = str;
    int pos = 0;

    while (pos < result.length()) {
        if (ispunct(result[pos])) {
            int start = pos;
            while (pos < result.length() && ispunct(result[pos]))
                ++pos;
            result.erase(start, pos - start);
        } else {
            ++pos;
        }
    }

    return result;
}

// Функция для исправления регистра букв
std::string fixLetterCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    result[0] = std::toupper(result[0]);
    return result;
}

// Функция для разделения слов по типам (буквы, цифры, буквы и цифры)
void separateWordsByType(const std::vector<std::string>& words) {
    std::vector<std::string> onlyLetters;
    std::vector<std::string> onlyDigits;
    std::vector<std::string> lettersAndDigits;

    for (const auto& word : words) {
        bool isLetter = true;
        bool isDigit = true;

        for (const auto& ch : word) {
            if (!isalpha(ch))
                isLetter = false;
            if (!isdigit(ch))
                isDigit = false;
        }

        if (isLetter)
            onlyLetters.push_back(word);
        else if (isDigit)
            onlyDigits.push_back(word);
        else
            lettersAndDigits.push_back(word);
    }

    std::cout << "Слова, содержащие только буквы:\n";
    for (const auto& word : onlyLetters)
        std::cout << word << "\n";

    std::cout << "\nСлова, содержащие только цифры:\n";
    for (const auto& word : onlyDigits)
        std::cout << word << "\n";

    std::cout << "\nСлова, содержащие и буквы, и цифры:\n";
    for (const auto& word : lettersAndDigits)
        std::cout << word << "\n";
}

// Функция для вывода слов вертикально
void printWordsVertically(const std::vector<std::string>& words) {
    std::cout << "Слова вертикально:\n";
    for (const auto& word : words)
        std::cout << word << "\n";
}

// Функция для поиска подстроки в строке
void findSubstring(const std::string& str, const std::string& substring) {
    std::size_t found = str.find(substring);
    if (found != std::string::npos)
        std::cout << "Подстрока найдена в позиции " << found << "\n";
    else
        std::cout << "Подстрока не найдена\n";
}

int main() {
    setlocale(LC_ALL, "russian");
    std::cout << "Выберите способ ввода текста:\n";
    std::cout << "1. С клавиатуры\n";
    std::cout << "2. Из файла (*)\n";

    int choice;
    std::cin >> choice;

    std::string input;
    if (choice == 1) {
        std::cout << "Введите текст:\n";
        std::cin.ignore();
        std::getline(std::cin, input);
    } else if (choice == 2) {
        std::cout << "Файла нет:\n";
    }

    // Удаление лишних пробелов
    std::string noExtraSpaces = removeExtraSpaces(input);

    // Удаление лишних знаков препинания
    std::string noExtraPunctuation = removeExtraPunctuation(noExtraSpaces);

    // Исправление регистра букв
    std::string fixedCase = fixLetterCase(noExtraPunctuation);

    // Разделение слов по типам
    std::vector<std::string> words;
    std::istringstream iss(fixedCase);
    std::string word;
    while (iss >> word)
        words.push_back(word);

    separateWordsByType(words);

    // Вывод слов вертикально
    printWordsVertically(words);

    // Поиск подстроки
    std::cout << "\nВведите подстроку для поиска:\n";
    std::string substring;
    std::cin.ignore();
    std::getline(std::cin, substring);

    findSubstring(input, substring);

    return 0;
}