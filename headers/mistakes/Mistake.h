#ifndef RETRIEVEMISTAKE_MISTAKE_H
#define RETRIEVEMISTAKE_MISTAKE_H

/**
 * Абстрактный класс, от которого наследуются все ошибки.
 */
class Mistake {
private:
    const char *message; // Сообщение об ошибке.

public:
    explicit Mistake(const char *message);

    [[nodiscard]] const char *getMessage() const;
};


#endif //RETRIEVEMISTAKE_MISTAKE_H
