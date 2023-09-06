
#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <Arduino.h>

#define LOG_LENGTH 100

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
    void init();
    void setLevel(LogLevel level) { level_ = level; };
    LogLevel getLevel() { return level_; };
    void setBaud(unsigned long baud) { baud_ = baud; };
private:
    unsigned long baud_;
    LogLevel level_;
};

#define LOG_ERROR(...)                                                                            \
    do {                                                                                          \
        if (LOGGER()->getLevel() >= LEVEL_ERROR) {                                                \
            char header[LOG_LENGTH];                                                              \
            sprintf(header, "[ERROR]%s %s(Line %d): ", __FILE__, __FUNCTION__, __LINE__);         \
            Serial.print(header);                                                                 \
            char info[LOG_LENGTH];                                                                \
            sprintf(info, __VA_ARGS__);                                                           \
            Serial.print(info);                                                                   \
            Serial.print("\n");                                                                   \
        }                                                                                         \
    } while (0)

#define LOG_WARNING(...)                                                                          \
    do {                                                                                          \
        if (LOGGER()->getLevel() >= LEVEL_WARNING) {                                              \
            char header[LOG_LENGTH];                                                              \
            sprintf(header, "[WARNING]%s %s(Line %d): ", __FILE__, __FUNCTION__, __LINE__);       \
            Serial.print(header);                                                                 \
            char info[LOG_LENGTH];                                                                \
            sprintf(info, __VA_ARGS__);                                                           \
            Serial.print(info);                                                                   \
            Serial.print("\n");                                                                   \
        }                                                                                         \
    } while (0)

#define LOG_INFO(...)                                                                             \
    do {                                                                                          \
        if (LOGGER()->getLevel() >= LEVEL_INFO) {                                                 \
            char header[LOG_LENGTH];                                                              \
            sprintf(header, "[INFO]%s %s(Line %d): ", __FILE__, __FUNCTION__, __LINE__);          \
            Serial.print(header);                                                                 \
            char info[LOG_LENGTH];                                                                \
            sprintf(info, __VA_ARGS__);                                                           \
            Serial.print(info);                                                                   \
            Serial.print("\n");                                                                   \
        }                                                                                         \
    } while (0)

#define LOG_DEBUG(...)                                                                            \
    do {                                                                                          \
        if (LOGGER()->getLevel() >= LEVEL_DEBUG) {                                                \
            char header[LOG_LENGTH];                                                              \
            sprintf(header, "[DEBUG]%s %s(Line %d): ", __FILE__, __FUNCTION__, __LINE__);         \
            Serial.print(header);                                                                 \
            char info[LOG_LENGTH];                                                                \
            sprintf(info, __VA_ARGS__);                                                           \
            Serial.print(info);                                                                   \
            Serial.print("\n");                                                                   \
        }                                                                                         \
    } while (0)

#define LOG_TRACE(...)                                                                            \
    do {                                                                                          \
        if (LOGGER()->getLevel() >= LEVEL_TRACE) {                                                \
            char header[LOG_LENGTH];                                                              \
            sprintf(header, "[TRACE]%s %s(Line %d): ", __FILE__, __FUNCTION__, __LINE__);         \
            Serial.print(header);                                                                 \
            char info[LOG_LENGTH];                                                                \
            sprintf(info, __VA_ARGS__);                                                           \
            Serial.print(info);                                                                   \
            Serial.print("\n");                                                                   \
        }                                                                                         \
    } while (0)

#endif // !_LOGGER_H_