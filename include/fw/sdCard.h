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
    float utilization();
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