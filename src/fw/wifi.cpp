#include "fw/wifi.h"
#include "fw/logger.h"

WifiStation::WifiStation(std::string ssid, std::string passwd)
: ssid_(ssid)
, passwd_(passwd)
, inited_(false)
{}

WifiStation::~WifiStation()
{
    inited_ = false;
}

ErrorCode WifiStation::init()
{
    WiFi.begin(ssid_.c_str(), passwd_.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        LOG_INFO("WifiStation: Connecting ...");
    }

    LOG_INFO("WifiStation: IP address [%s]", WiFi.localIP());
    LOG_INFO("WifiStation: init ok");
    return CODE_OK;
}

bool WifiStation::checkInit()
{
    if (!inited_) {
        LOG_ERROR("WifiStation: Please init first");
    }
    return inited_;
}