#ifndef RETRIEVEMISTAKE_RETRIEVEMISTAKEEXCEPTION_H
#define RETRIEVEMISTAKE_RETRIEVEMISTAKEEXCEPTION_H


#include <bits/exception.h>

/**
 * Класс исключений при распознавании ошибок.
 */
class RetrieveMistakeException : public std::exception {
private:
    const char *message;
public:
    explicit RetrieveMistakeException(const char *message);

    [[nodiscard]] const char *getMessage() const;
};


#endif //RETRIEVEMISTAKE_RETRIEVEMISTAKEEXCEPTION_H
