#ifndef _WIFI_H_
#define _WIFI_H_

#include <WiFi.h>
#include "fw/errorCode.h"

class WifiStation
{
public:
    WifiStation(std::string ssid, std::string passwd);
    ~WifiStation();
    ErrorCode init();
private:
    bool checkInit();
private:
    std::string ssid_;
    std::string passwd_;
    WiFiClient* client_;
    bool inited_;
};

#endif