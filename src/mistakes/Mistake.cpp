#include "../../headers/mistakes/Mistake.h"

Mistake::Mistake(const char *message) : message(message) {}

const char *Mistake::getMessage() const {
    return message;
}
