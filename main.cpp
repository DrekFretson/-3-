#include "StackTests.hpp"
#include <iostream>
#include <cstdlib>

int main() {
    FILE* inFile = nullptr;
    errno_t err = fopen_s(&inFile, "input.txt", "r");
    if (err != 0 || inFile == nullptr) {
        std::cerr << "Ошибка: Не удалось открыть файл input.txt для чтения. Код ошибки: " << err << std::endl;
        return EXIT_FAILURE;
    }


    FILE* outFile = nullptr;
    err = fopen_s(&outFile, "output.txt", "w");
    if (err != 0 || outFile == nullptr) {
        std::cerr << "Ошибка: Не удалось открыть файл output.txt для записи. Код ошибки: " << err << std::endl;
        fclose(inFile);
        return EXIT_FAILURE;
    }

    try {
        RunTestsFromFile(inFile, outFile);

        std::cout << "Тесты успешно выполнены. Результаты записаны в output.txt" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Исключение при выполнении тестов: " << ex.what() << std::endl;
        fclose(inFile);
        fclose(outFile);
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Неизвестное исключение при выполнении тестов" << std::endl;
        fclose(inFile);
        fclose(outFile);
        return EXIT_FAILURE;
    }


    fclose(inFile);
    fclose(outFile);

    return EXIT_SUCCESS;
}
