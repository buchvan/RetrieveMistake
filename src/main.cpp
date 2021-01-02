#include <memory>
#include <iostream>
#include "../headers/polynomials/Polynomial.h"
#include "../headers/mistakes/Mistake.h"
#include "../headers/mistakes/IncorrectSquareOfSumBinomialMistake.h"

/**
 * Возвращает указатель на IncorrectSquareOfSumBinomialMistake если распозналась соответствующая ошибка.
 */
std::shared_ptr<Mistake>
retrieveIncorrectSquareOfSumBinomialMistake(const Polynomial &lhs_p, const int lhs_n, const Polynomial &rhs) {
    if (lhs_n != 2) {
        return nullptr;
    }
    if (!lhs_p.isBinomial()) {
        return nullptr;
    }
    if (!lhs_p.isClearSum()) {
        return nullptr;
    }
    if (lhs_p.pow(lhs_n)->operator!=(rhs)) {
        return std::make_shared<IncorrectSquareOfSumBinomialMistake>("Incorrect square of sum binomial mistake");
    }
    return nullptr;
}

/**
 * Возвращает указатель на IncorrectSquareOfDifMistake если распозналась соответствующая ошибка.
 */
std::shared_ptr<Mistake>
retrieveIncorrectSquareOfDifBinomialMistake(const Polynomial &lhs_p, const int lhs_n, const Polynomial &rhs) {
    if (lhs_n != 2) {
        return nullptr;
    }
    if (!lhs_p.isBinomial()) {
        return nullptr;
    }
    if (lhs_p.isClearSum()) {
        return nullptr;
    }
    if (lhs_p.pow(lhs_n)->operator!=(rhs)) {
        return std::make_shared<IncorrectSquareOfSumBinomialMistake>("Incorrect square of dif binomial mistake");
    }
    return nullptr;
}

/**
 * Возвращает указатель на IncorrectCubeOfSumBinomialMistake если распозналась соответствующая ошибка.
 */
std::shared_ptr<Mistake>
retrieveIncorrectCubeOfSumBinomialMistake(const Polynomial &lhs_p, const int lhs_n, const Polynomial &rhs) {
    if (lhs_n != 3) {
        return nullptr;
    }
    if (!lhs_p.isBinomial()) {
        return nullptr;
    }
    if (!lhs_p.isClearSum()) {
        return nullptr;
    }
    if (lhs_p.pow(lhs_n)->operator!=(rhs)) {
        return std::make_shared<IncorrectSquareOfSumBinomialMistake>("Incorrect cube of sum binomial mistake");
    }
    return nullptr;
}

/**
 * Возвращает указатель на IncorrectCubeOfDifMistake если распозналась соответствующая ошибка.
 */
std::shared_ptr<Mistake>
retrieveIncorrectCubeOfDifBinomialMistake(const Polynomial &lhs_p, const int lhs_n, const Polynomial &rhs) {
    if (lhs_n != 3) {
        return nullptr;
    }
    if (!lhs_p.isBinomial()) {
        return nullptr;
    }
    if (lhs_p.isClearSum()) {
        return nullptr;
    }
    if (lhs_p.pow(lhs_n)->operator!=(rhs)) {
        return std::make_shared<IncorrectSquareOfSumBinomialMistake>("Incorrect cube of dif binomial mistake");
    }
    return nullptr;
}

/**
 * Возвращает указатель на IncorrectPowerOfPolynomialMistake если распозналась соответствующая ошибка.
 */
std::shared_ptr<Mistake>
retrieveIncorrectPowerOfPolynomialMistake(const Polynomial &lhs_p, const int lhs_n, const Polynomial &rhs) {
    if (lhs_p.pow(lhs_n)->operator!=(rhs)) {
        return std::make_shared<IncorrectSquareOfSumBinomialMistake>("Incorrect power of polynomial mistake");
    }
    return nullptr;
}


std::shared_ptr<Mistake> retrieveMistake(const Polynomial &lhs_p, const int lhs_n, const Polynomial &rhs) {
    static auto recognizers = {
            &retrieveIncorrectSquareOfSumBinomialMistake, // Неверно вычислен квадрат суммы бинома.
            &retrieveIncorrectSquareOfDifBinomialMistake, // Неверно вычислен квадрат разности бинома.
            &retrieveIncorrectCubeOfSumBinomialMistake, // Неверно вычислен куб суммы бинома.
            &retrieveIncorrectCubeOfDifBinomialMistake, // Неверно вычислен куб разности бинома.
            &retrieveIncorrectPowerOfPolynomialMistake, // Случаи неверно вычисленной степени произвольного многочлена.
    };
    std::shared_ptr<Mistake> result = nullptr;
    for (const auto &recognizer : recognizers) {
        if ((result = (*recognizer)(lhs_p, lhs_n, rhs)) != nullptr) {
            return result;
        }
    }
    return result;
}



void testTrueSquareBinomialSum() {
    int *coefficients1 = new int[2];
    coefficients1[0] = 2;
    coefficients1[1] = 4;
    Polynomial polynomial(2, coefficients1, 'x');
    std::cout << "Question : " << polynomial.toString() << " in square" << std::endl;
    int *coefficients2 = new int[3];
    coefficients2[0] = 4;
    coefficients2[1] = 16;
    coefficients2[2] = 16;
    Polynomial result(3, coefficients2, 'x');
    std::cout << "Result from student : " << result.toString() << std::endl;
    std::shared_ptr <Mistake> mistake = retrieveMistake(polynomial, 2, result);
    std::cout << "Expected result: null" << std::endl;
    std::cout << "Actual result: " << ((mistake == nullptr) ? "null" : mistake.get()->getMessage()) << std::endl;
    delete[] coefficients2;
    delete[] coefficients1;
}

void testFalseSquareBinomialSum() {
    int *coefficients1 = new int[2];
    coefficients1[0] = 2;
    coefficients1[1] = 4;
    Polynomial polynomial(2, coefficients1, 'x');
    std::cout << "Question : " << polynomial.toString() << " in square" << std::endl;
    int *coefficients2 = new int[3];
    coefficients2[0] = 4;
    coefficients2[1] = 16;
    coefficients2[2] = 17;
    Polynomial result(3, coefficients2, 'x');
    std::cout << "Result from student : " << result.toString() << std::endl;
    std::shared_ptr <Mistake> mistake = retrieveMistake(polynomial, 2, result);
    std::cout << "Expected result: Incorrect square of sum binomial mistake" << std::endl;
    std::cout << "Actual result: " << ((mistake == nullptr) ? "null" : mistake.get()->getMessage()) << std::endl;
    delete[] coefficients2;
    delete[] coefficients1;
}

void testTrueSquareBinomialDif() {
    int *coefficients1 = new int[2];
    coefficients1[0] = 2;
    coefficients1[1] = -4;
    Polynomial polynomial(2, coefficients1, 'x');
    std::cout << "Question : " << polynomial.toString() << " in square" << std::endl;
    int *coefficients2 = new int[3];
    coefficients2[0] = 4;
    coefficients2[1] = -16;
    coefficients2[2] = 16;
    Polynomial result(3, coefficients2, 'x');
    std::cout << "Result from student : " << result.toString() << std::endl;
    std::shared_ptr <Mistake> mistake = retrieveMistake(polynomial, 2, result);
    std::cout << "Expected result: null" << std::endl;
    std::cout << "Actual result: " << ((mistake == nullptr) ? "null" : mistake.get()->getMessage()) << std::endl;
    delete[] coefficients2;
    delete[] coefficients1;
}

void testFalseSquareBinomialDif() {
    int *coefficients1 = new int[2];
    coefficients1[0] = 2;
    coefficients1[1] = -4;
    Polynomial polynomial(2, coefficients1, 'x');
    std::cout << "Question : " << polynomial.toString() << " in square" << std::endl;
    int *coefficients2 = new int[3];
    coefficients2[0] = 4;
    coefficients2[1] = 16;
    coefficients2[2] = 16;
    Polynomial result(3, coefficients2, 'x');
    std::cout << "Result from student : " << result.toString() << std::endl;
    std::shared_ptr <Mistake> mistake = retrieveMistake(polynomial, 2, result);
    std::cout << "Expected result: Incorrect square of dif binomial mistake" << std::endl;
    std::cout << "Actual result: " << ((mistake == nullptr) ? "null" : mistake.get()->getMessage()) << std::endl;
    delete[] coefficients2;
    delete[] coefficients1;
}

void testTrueCubeBinomialSum() {
    int *coefficients1 = new int[2];
    coefficients1[0] = 2;
    coefficients1[1] = 4;
    Polynomial polynomial(2, coefficients1, 'x');
    std::cout << "Question : " << polynomial.toString() << " in cube" << std::endl;
    int *coefficients2 = new int[4];
    coefficients2[0] = 8;
    coefficients2[1] = 48;
    coefficients2[2] = 96;
    coefficients2[3] = 64;
    Polynomial result(4, coefficients2, 'x');
    std::cout << "Result from student : " << result.toString() << std::endl;
    std::shared_ptr <Mistake> mistake = retrieveMistake(polynomial, 3, result);
    std::cout << "Expected result: null" << std::endl;
    std::cout << "Actual result: " << ((mistake == nullptr) ? "null" : mistake.get()->getMessage()) << std::endl;
    delete[] coefficients2;
    delete[] coefficients1;
}

void testFalseCubeBinomialSum() {
    int *coefficients1 = new int[2];
    coefficients1[0] = 2;
    coefficients1[1] = 4;
    Polynomial polynomial(2, coefficients1, 'x');
    std::cout << "Question : " << polynomial.toString() << " in cube" << std::endl;
    int *coefficients2 = new int[4];
    coefficients2[0] = 9;
    coefficients2[1] = 48;
    coefficients2[2] = 96;
    coefficients2[3] = 64;
    Polynomial result(4, coefficients2, 'x');
    std::cout << "Result from student : " << result.toString() << std::endl;
    std::shared_ptr <Mistake> mistake = retrieveMistake(polynomial, 3, result);
    std::cout << "Expected result: Incorrect cube of sum binomial mistake" << std::endl;
    std::cout << "Actual result: " << ((mistake == nullptr) ? "null" : mistake.get()->getMessage()) << std::endl;
    delete[] coefficients2;
    delete[] coefficients1;
}

void testTrueCubeBinomialDif() {
    int *coefficients1 = new int[2];
    coefficients1[0] = -2;
    coefficients1[1] = 4;
    Polynomial polynomial(2, coefficients1, 'x');
    std::cout << "Question : " << polynomial.toString() << " in cube" << std::endl;
    int *coefficients2 = new int[4];
    coefficients2[0] = -8;
    coefficients2[1] = 48;
    coefficients2[2] = -96;
    coefficients2[3] = 64;
    Polynomial result(4, coefficients2, 'x');
    std::cout << "Result from student : " << result.toString() << std::endl;
    std::shared_ptr <Mistake> mistake = retrieveMistake(polynomial, 3, result);
    std::cout << "Expected result: null" << std::endl;
    std::cout << "Actual result: " << ((mistake == nullptr) ? "null" : mistake.get()->getMessage()) << std::endl;
    delete[] coefficients2;
    delete[] coefficients1;
}

void testFalseCubeBinomialDif() {
    int *coefficients1 = new int[2];
    coefficients1[0] = -2;
    coefficients1[1] = 4;
    Polynomial polynomial(2, coefficients1, 'x');
    std::cout << "Question : " << polynomial.toString() << " in cube" << std::endl;
    int *coefficients2 = new int[4];
    coefficients2[0] = 8;
    coefficients2[1] = 48;
    coefficients2[2] = -96;
    coefficients2[3] = 64;
    Polynomial result(4, coefficients2, 'x');
    std::cout << "Result from student : " << result.toString() << std::endl;
    std::shared_ptr <Mistake> mistake = retrieveMistake(polynomial, 3, result);
    std::cout << "Expected result: Incorrect cube of dif binomial mistake" << std::endl;
    std::cout << "Actual result: " << ((mistake == nullptr) ? "null" : mistake.get()->getMessage()) << std::endl;
    delete[] coefficients2;
    delete[] coefficients1;
}

void testTruePolynomialPower() {
    int *coefficients1 = new int[3];
    coefficients1[0] = -2;
    coefficients1[1] = 4;
    coefficients1[2] = 3;
    Polynomial polynomial(3, coefficients1, 'x');
    std::cout << "Question : " << polynomial.toString() << " in cube" << std::endl;
    int *coefficients2 = new int[5];
    coefficients2[0] = 4;
    coefficients2[1] = -16;
    coefficients2[2] = 4;
    coefficients2[3] = 24;
    coefficients2[4] = 9;
    Polynomial result(5, coefficients2, 'x');
    std::cout << "Result from student : " << result.toString() << std::endl;
    std::shared_ptr <Mistake> mistake = retrieveMistake(polynomial, 2, result);
    std::cout << "Expected result: null" << std::endl;
    std::cout << "Actual result: " << ((mistake == nullptr) ? "null" : mistake.get()->getMessage()) << std::endl;
    delete[] coefficients2;
    delete[] coefficients1;
}

void testFalsePolynomialPower() {
    int *coefficients1 = new int[3];
    coefficients1[0] = 2;
    coefficients1[1] = 4;
    coefficients1[2] = 3;
    Polynomial polynomial(3, coefficients1, 'x');
    std::cout << "Question : " << polynomial.toString() << " in cube" << std::endl;
    int *coefficients2 = new int[5];
    coefficients2[0] = 4;
    coefficients2[1] = -16;
    coefficients2[2] = 4;
    coefficients2[3] = 24;
    coefficients2[4] = 9;
    Polynomial result(5, coefficients2, 'x');
    std::cout << "Result from student : " << result.toString() << std::endl;
    std::shared_ptr <Mistake> mistake = retrieveMistake(polynomial, 2, result);
    std::cout << "Expected result: Incorrect power of polynomial mistake" << std::endl;
    std::cout << "Actual result: " << ((mistake == nullptr) ? "null" : mistake.get()->getMessage()) << std::endl;
    delete[] coefficients2;
    delete[] coefficients1;
}

int main() {
    std::cout << "----------------" << std::endl;
    std::cout << "Test 1" << std::endl;
    testTrueSquareBinomialSum();
    std::cout << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Test 2" << std::endl;
    testFalseSquareBinomialSum();
    std::cout << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Test 3" << std::endl;
    testTrueSquareBinomialDif();
    std::cout << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Test 4" << std::endl;
    testFalseSquareBinomialDif();
    std::cout << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Test 5" << std::endl;
    testTrueCubeBinomialSum();
    std::cout << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Test 6" << std::endl;
    testFalseCubeBinomialSum();
    std::cout << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Test 7" << std::endl;
    testTrueCubeBinomialDif();
    std::cout << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Test 8" << std::endl;
    testFalseCubeBinomialDif();
    std::cout << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Test 9" << std::endl;
    testTruePolynomialPower();
    std::cout << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Test 10" << std::endl;
    testFalsePolynomialPower();
    std::cout << std::endl;
    std::cout << "----------------" << std::endl;

    return 0;
}
