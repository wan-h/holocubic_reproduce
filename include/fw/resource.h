#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <Arduino.h>

class Resource
{
public:
    Resource();
    ~Resource();
    void init();
    bool setCpuFreqMhz(uint32_t cpu_freq_mhz);
    uint32_t getCpuFreqMhz();
    uint32_t getXtalFreqMhz();
    uint32_t getApbFreq();
    void printInfo();
private:
    bool inited_;
};

#endif // !_RESOURCE_H_