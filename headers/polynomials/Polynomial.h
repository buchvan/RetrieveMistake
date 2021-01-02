#ifndef RETRIEVEMISTAKE_POLYNOMIAL_H
#define RETRIEVEMISTAKE_POLYNOMIAL_H

#include <string>
#include <memory>

/**
 * Класс всех полиномов.
 */
class Polynomial {
private:
    const int n; // Число коэффициентов, или степень полинома минус один.
    const int *coefficients; // Массив коэффициентов полинома от младшей степени к старшей.
    const char var; // Символ переменной.
    [[nodiscard]] std::string
    coefficientWithVarToString(
            int i) const; // Взять строковое представление i-ого (счёт с нуля) коэффициента, умноженного на var в i-ую степени.

    static void
    getTail(int *array, int i, int n,
            const int *coefficients); // Положить коэффициенты начиная с i-ого номера в массив.
public:
    Polynomial(int n, const int *coefficients, char var);

    [[nodiscard]] int getN() const;

    [[nodiscard]] const int *getCoefficients() const;

    [[nodiscard]] char getVar() const;

    [[nodiscard]] std::string toString() const;

    std::unique_ptr<Polynomial> operator+(const Polynomial &polynomial) const;

    std::unique_ptr<Polynomial> operator*(const Polynomial &polynomial) const;

    [[nodiscard]] std::unique_ptr<Polynomial> pow(int pow) const;

    [[nodiscard]] bool isBinomial() const;

    [[nodiscard]] bool isClearSum() const;

    bool operator!=(const Polynomial &polynomial) const;

    bool operator==(const Polynomial &polynomial) const;
};


#endif //RETRIEVEMISTAKE_POLYNOMIAL_H
