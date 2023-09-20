#ifndef _SD_CARD_H_
#define _SD_CARD_H_

#include "FS.h"
#include "SD.h"
#include "SD_MMC.h"
#include "fw/errorCode.h"

class SDCard
{
public:
    SDCard(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t ss);
    ~SDCard();
    ErrorCode init();
    // float getUsage();
    ErrorCode listDir(const std::string path);
    ErrorCode createDir(const std::string path);
    ErrorCode removeDir(const std::string path);
    ErrorCode readFile(const std::string path);
    ErrorCode writeFile(const std::string path, const std::string message);
    ErrorCode appendFile(const std::string path, const std::string message);
    ErrorCode renameFile(const std::string path1, const std::string path2);
    ErrorCode deleteFile(const std::string path);
private:
    bool checkInit();
private:
    uint8_t clk_;
    uint8_t miso_;
    uint8_t mosi_;
    uint8_t ss_;
    uint8_t cardType_;
    uint64_t cardSize_;
    bool inited_;
};

#endif