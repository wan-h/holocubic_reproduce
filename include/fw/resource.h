#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <Arduino.h>
#include "fw/errorCode.h"
#include "fw/logger.h"

class Resource
{
public:
    Resource(unsigned long baud, LogLevel logLevel);
    ~Resource();
    ErrorCode init();
    ErrorCode setCpuFreqMhz(uint32_t cpu_freq_mhz);
    uint32_t getCpuFreqMhz();
    uint32_t getXtalFreqMhz();
    uint32_t getApbFreq();
    ErrorCode printInfo();
private:
    unsigned long baud_; 
    LogLevel logLevel_;
    bool inited_;
};

#endif // !_RESOURCE_H_