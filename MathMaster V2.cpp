#include <iostream>     // ввод и вывод
#include <cstdlib>      // rand(), srand()
#include <ctime>        // time()
#include <string>       // string
#include <chrono>       // таймер

using namespace std;
using namespace std::chrono;

int main() {
    setlocale(LC_ALL, "Russian");   // корректный вывод русского текста
    srand(time(0));                 // инициализация генератора случайных чисел

    int record = 0;                 // рекорд за текущий запуск программы

    while (true) {
        // ===== Правила игры =====
        cout << "=== МАТЕМАТИЧЕСКАЯ ИГРА ===\n";
        cout << "Правила:\n";
        cout << "1. Решайте примеры\n";
        cout << "2. На каждый пример даётся 10 секунд\n";
        cout << "3. За каждый правильный ответ +1 очко\n";
        cout << "Введите START для начала игры\n\n";

        string command;
        cin >> command;

        if (command != "START") {
            cout << "Игра не запущена.\n\n";
            continue;
        }

        int score = 0;   // очки за текущую игру
        bool gameOver = false;

        // ===== Основной игровой цикл =====
        while (!gameOver) {
            int a = rand() % 10 + 1;
            int b = rand() % 10 + 1;
            int correctAnswer;
            char operation;

            int type = rand() % 3; // 0 +, 1 *, 2 /

            if (type == 0) {
                operation = '+';
                correctAnswer = a + b;
            }
            else if (type == 1) {
                operation = '*';
                correctAnswer = a * b;
            }
            else {
                correctAnswer = a;
                b = rand() % 9 + 1;
                a = correctAnswer * b;
                operation = '/';
            }

            cout << "\nПример: " << a << " " << operation << " " << b << " = ";

            // ===== Таймер =====
            steady_clock::time_point start = steady_clock::now();

            int userAnswer;
            cin >> userAnswer;

            steady_clock::time_point end = steady_clock::now();
            int secondsPassed = duration_cast<seconds>(end - start).count();

            if (secondsPassed > 10) {
                cout << "Время вышло!\n";
                gameOver = true;
            }
            else if (userAnswer == correctAnswer) {
                score++;
                cout << "Верно! Очки: " << score << endl;
            }
            else {
                cout << "Неверно! Правильный ответ: " << correctAnswer << endl;
                gameOver = true;
            }
        }

        // ===== Конец игры =====
        cout << "\nИгра окончена.\n";
        cout << "Ваш результат: " << score << endl;

        if (score > record) {
            record = score;
            cout << "Новый рекорд!\n";
        }
        else {
            cout << "Рекорд: " << record << endl;
        }

        cout << "\nВведите Заново для новой игры или EXIT для выхода: ";
        string choice;
        cin >> choice;

        if (choice != "Заново") {
            break;
        }

        cout << "\n";
    }

    cout << "Спасибо за игру!\n";
    return 0;
}