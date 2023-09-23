#include "fw/resource.h"

Resource::Resource(unsigned long baud, LogLevel logLevel)
: baud_(baud)
, logLevel_(logLevel)
, inited_(false)
{}

Resource::~Resource()
{
    inited_ = false;
}

ErrorCode Resource::init()
{
    if (inited_) return CODE_OK;
    // 初始化logger
    LOGGER()->init();
    LOGGER()->setBaud(baud_);
    LOGGER()->setLevel(logLevel_);

    inited_ = true;
    LOG_INFO("Resource: init ok");
    return CODE_OK;
}

ErrorCode Resource::setCpuFreqMhz(uint32_t cpu_freq_mhz)
{
    if(setCpuFrequencyMhz(cpu_freq_mhz)) {
        return CODE_OK;
    }
    return CODE_ERROR;
}

uint32_t Resource::getCpuFreqMhz()
{
    return getCpuFrequencyMhz();
}

uint32_t Resource::getXtalFreqMhz()
{
    return getXtalFrequencyMhz();
}

uint32_t Resource::getApbFreq()
{
    return getApbFrequency();
}

ErrorCode Resource::printInfo()
{
    uint32_t cpuFreqMhz = getCpuFreqMhz();
    uint32_t xtalFreqMhz = getXtalFreqMhz();
    uint32_t apbFreq = getApbFreq();
    LOG_INFO("CPU Freq: %dMHz; Xtal Freq: %dMHz; Apb Freq: %dHz", cpuFreqMhz, xtalFreqMhz, apbFreq);
    return CODE_OK;
}