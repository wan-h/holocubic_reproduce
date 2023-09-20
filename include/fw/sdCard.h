#ifndef _SD_CARD_H_
#define _SD_CARD_H_

#include "FS.h"
#include "SD.h"
#include "SD_MMC.h"

class SDCard
{
public:
    SDCard(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t ss);
    ~SDCard();
    void init();
    // float getUsage();
    void listDir(const std::string path);
    void createDir(const std::string path);
    void removeDir(const std::string path);
    void readFile(const std::string path);
    void writeFile(const std::string path, const std::string message, const char* mode = 'w');
    void renameFile(const std::string path, const std::string newName);
    void deleteFile(const std::string path);
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