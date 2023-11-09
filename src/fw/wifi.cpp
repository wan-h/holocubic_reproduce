#include "fw/wifi.h"
#include "fw/logger.h"

WifiStation::WifiStation(String ssid, String passwd)
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
    inited_ = true;
    LOG_INFO("WifiStation: IP address [%s]", WiFi.localIP().toString().c_str());
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

#define TIMEOUT 5000
String WifiStation::readResponse()
{
    unsigned long timeout = millis();
    while(client_.available() == 0) {
        if(millis() - timeout > 5000) {
            LOG_ERROR("WifiStation: Client response timeout");
            client_.stop();
            return "";
        }
    }
    return client_.readString();
}

ErrorCode WifiStation::request(String host, int port, String req, String& resp)
{
    if (!checkInit()) return CODE_ERROR_INIT_CHECK;
    if (!client_.connect(host.c_str(), port)) {
        LOG_ERROR("WifiStation: Client connect to %s:%d failed", host.c_str(), port);
        return CODE_ERROR;
    }

    String footer = String(" HTTP/1.1\r\n") + "Host: " + String(host) + "\r\n" + "Connection: close\r\n\r\n";
    String reqString = req + footer;
    LOG_DEBUG("WifiStation: Request => %s", reqString.c_str());
    client_.print(reqString);
    resp = readResponse();
    if (resp.isEmpty()) {
        return CODE_ERROR;
    }
    LOG_DEBUG("WifiStation: Response => %s", resp.c_str());
    return CODE_OK;
}