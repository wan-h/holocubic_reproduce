#include "fw/logger.h"

Logger::Logger(unsigned long baud, LogLevel logLevel)
: baud_(baud)
, level_(logLevel)
{}

Logger::~Logger()
{}

Logger* Logger::get() {
    static Logger ins;
    return &ins;
}

void Logger::init() {
    Serial.begin(baud_);
}