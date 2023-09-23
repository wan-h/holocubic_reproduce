
#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <Arduino.h>
#include "fw/errorCode.h"

typedef enum LogLevel {
    LEVEL_NONE = 0,
    LEVEL_TRACE,
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR
} LogLevel;

#define LOGGER Logger::get

class Logger {
public:
    static Logger* get();
public:
    Logger(unsigned long baud = 9600, LogLevel logLevel = LEVEL_INFO);
    ~Logger();
    ErrorCode init();
    LogLevel getLevel() { return level_; };
    void setLevel(LogLevel level) { level_ = level; };
    unsigned long getBaud() { return baud_; };
    void setBaud(unsigned long baud) { baud_ = baud; };
private:
    unsigned long baud_;
    LogLevel level_;
    bool inited_;
};

#define LOG_ERROR(...)                                                                            \
    do {                                                                                          \
        if (LOGGER()->getLevel() <= LEVEL_ERROR) {                                                \
            Serial.printf("[ERROR]%s %s(Line %d): ", __FILE__, __FUNCTION__, __LINE__);           \
            Serial.printf(__VA_ARGS__);                                                           \
            Serial.print("\n");                                                                   \
        }                                                                                         \
    } while (0)

#define LOG_WARNING(...)                                                                          \
    do {                                                                                          \
        if (LOGGER()->getLevel() <= LEVEL_WARNING) {                                              \
            Serial.printf("[WARNING]%s %s(Line %d): ", __FILE__, __FUNCTION__, __LINE__);         \
            Serial.printf(__VA_ARGS__);                                                           \
            Serial.print("\n");                                                                   \
        }                                                                                         \
    } while (0)

#define LOG_INFO(...)                                                                             \
    do {                                                                                          \
        if (LOGGER()->getLevel() <= LEVEL_INFO) {                                                 \
            Serial.printf("[INFO]%s %s(Line %d): ", __FILE__, __FUNCTION__, __LINE__);            \
            Serial.printf(__VA_ARGS__);                                                           \
            Serial.print("\n");                                                                   \
        }                                                                                         \
    } while (0)

#define LOG_DEBUG(...)                                                                            \
    do {                                                                                          \
        if (LOGGER()->getLevel() <= LEVEL_DEBUG) {                                                \
            Serial.printf("[DEBUG]%s %s(Line %d): ", __FILE__, __FUNCTION__, __LINE__);           \
            Serial.printf(__VA_ARGS__);                                                           \
            Serial.print("\n");                                                                   \
        }                                                                                         \
    } while (0)

#define LOG_TRACE(...)                                                                            \
    do {                                                                                          \
        if (LOGGER()->getLevel() <= LEVEL_TRACE) {                                                \
            Serial.printf("[TRACE]%s %s(Line %d): ", __FILE__, __FUNCTION__, __LINE__);           \
            Serial.printf(__VA_ARGS__);                                                           \
            Serial.print("\n");                                                                   \
        }                                                                                         \
    } while (0)

#endif // !_LOGGER_H_