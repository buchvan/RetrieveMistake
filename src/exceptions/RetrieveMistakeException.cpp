#include "../../headers/exceptions/RetrieveMistakeException.h"

RetrieveMistakeException::RetrieveMistakeException(const char *message) : exception(), message(message) {}

const char *RetrieveMistakeException::getMessage() const {
    return message;
}
