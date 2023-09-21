#include "fw/logger.h"

Logger::Logger(unsigned long baud, LogLevel logLevel)
: baud_(baud)
, level_(logLevel)
, inited_(false)
{}

Logger::~Logger()
{
    inited_ = true;
}

Logger* Logger::get() 
{
    static Logger ins;
    return &ins;
}

ErrorCode Logger::init() 
{
    if (inited_) return CODE_OK;
    Serial.begin(baud_);
    return CODE_OK;
}