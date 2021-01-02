#include "../../headers/polynomials/Polynomial.h"
#include "../../headers/exceptions/RetrieveMistakeException.h"

Polynomial::Polynomial(const int n, const int *coefficients, const char var) : n(n), coefficients(coefficients),
                                                                               var(var) {
    if (n <= 0) {
        throw RetrieveMistakeException("Degree of polynomial <= 0 is impossible!");
    } /// else
    if (coefficients[n - 1] == 0) {
        throw RetrieveMistakeException("Older coefficient of polynomial is zero!");
    }
}

int Polynomial::getN() const {
    return n;
}

const int *Polynomial::getCoefficients() const {
    return coefficients;
}

char Polynomial::getVar() const {
    return var;
}

std::string Polynomial::toString() const {
    std::string str;
    str.append(coefficientWithVarToString(n - 1));
    int i;
    for (i = n - 2; i >= 0; i--) {
        if (coefficients[i] == 0) {
            continue;
        } /// else
        if (coefficients[i] > 0) {
            str.append("+");
        }
        str.append(coefficientWithVarToString(i));
    }
    return str;
}

std::string Polynomial::coefficientWithVarToString(int i) const {
    std::string str;
    str.append(std::to_string(coefficients[i]));
    if (i == 0) {
        return str;
    } /// else
    str.append("*").append(std::string(1, var));
    if (i == 1) {
        return str;
    } /// else
    return str.append("^(")
            .append(std::to_string(i))
            .append(")");
}

std::unique_ptr<Polynomial> Polynomial::operator+(const Polynomial &polynomial) const {
    int resultN = 0;
    int minN = 0;
    int *resultCoefficients;
    if (n > polynomial.n) {
        resultN = n;
        minN = polynomial.n;
        resultCoefficients = new int[resultN];
        getTail(resultCoefficients, minN, resultN, coefficients);
    } else {
        resultN = polynomial.n;
        minN = n;
        resultCoefficients = new int[resultN];
        getTail(resultCoefficients, minN, resultN, polynomial.coefficients);
    }
    for (int i = 0; i < minN; i++) {
        resultCoefficients[i] = coefficients[i] + polynomial.coefficients[i];
    }
    return std::make_unique<Polynomial>(resultN, resultCoefficients, this->var);
}

void Polynomial::getTail(int *array, int i, int n, const int *coefficients) {
    for (int j = i; j < n; j++) {
        array[j] = coefficients[j];
    }
}

std::unique_ptr<Polynomial> Polynomial::operator*(const Polynomial &polynomial) const {
    const int resultN = n + polynomial.n - 1;
    int *resultCoefficients = new int[resultN];
    for (int i = 0; i < resultN; i++) {
        resultCoefficients[i] = 0;
        const int minN = std::min(i, n - 1);
        for (int j = 0; j <= minN; j++) {
            const int k = i - j;
            if (k >= polynomial.n) {
                continue;
            } /// else
            resultCoefficients[i] += coefficients[j] * polynomial.coefficients[k];
        }
    }
    return std::make_unique<Polynomial>(resultN, resultCoefficients, var);
}

std::unique_ptr<Polynomial> Polynomial::pow(int pow) const {
    std::unique_ptr<Polynomial> polynomial = std::make_unique<Polynomial>(*this);
    for (int i = 1; i < pow; i++) {
        polynomial = polynomial->operator*(*this);
    }
    return polynomial;
}

bool Polynomial::isBinomial() const {
    return n == 2;
}

bool Polynomial::isClearSum() const {
    bool isPositive = coefficients[n - 1] > 0;
    for (int i = 0; i < n - 1; i++) {
        const bool isNonNegativeI = coefficients[i] > 0;
        if ((!isPositive && isNonNegativeI) || (!isNonNegativeI && isPositive)) {
            return false;
        }
    }
    return true;
}

bool Polynomial::operator!=(const Polynomial &polynomial) const {
    if (n != polynomial.n) {
        return true;
    }
    for (int i = 0; i < n; i++) {
        if (coefficients[i] != polynomial.coefficients[i]) {
            return true;
        }
    }
    return false;
}

bool Polynomial::operator==(const Polynomial &polynomial) const {
    return !this->operator!=(polynomial);
}
