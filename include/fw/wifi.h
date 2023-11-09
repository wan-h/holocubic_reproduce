#ifndef _WIFI_H_
#define _WIFI_H_

#include <WiFi.h>
#include "fw/errorCode.h"

class WifiStation
{
public:
    WifiStation(String ssid, String passwd);
    ~WifiStation();
    ErrorCode init();
    ErrorCode request(String host, int port, String req, String& resp);
private:
    bool checkInit();
    String readResponse();
private:
    String ssid_;
    String passwd_;
    WiFiClient client_;
    bool inited_;
};

#endif