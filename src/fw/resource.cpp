#include "fw/resource.h"
#include "fw/logger.h"

Resource::Resource()
: inited_(false)
{}

Resource::~Resource()
{
    inited_ = false;
}

void Resource::init()
{
    inited_ = true;
    LOG_INFO("Resource: init ok");
}

bool Resource::setCpuFreqMhz(uint32_t cpu_freq_mhz)
{
    return setCpuFrequencyMhz(cpu_freq_mhz);
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

void Resource::printInfo()
{
    uint32_t cpuFreqMhz = getCpuFreqMhz();
    uint32_t xtalFreqMhz = getXtalFreqMhz();
    uint32_t apbFreq = getApbFreq();
    LOG_INFO("CPU Freq: %dMHz; Xtal Freq: %dMHz; Apb Freq: %dHz", cpuFreqMhz, xtalFreqMhz, apbFreq);
}