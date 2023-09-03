
#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <Arduino.h>

#define LOG_ERROR(...)                                                                  \
    do {                                                                                \
        char header[100];                                                               \
        sprintf(header, "[ERROR]%s %s(Line %d): ", __FILE__, __FUNCTION__, __LINE__);   \
        Serial.print(header);                                                           \
        char info[100];                                                                 \
        sprintf(info, __VA_ARGS__);                                                     \
        Serial.print(info);                                                             \
        Serial.print("\n");                                                             \
    } while (0)

#endif // !_LOGGER_H_