#include "fw/sdCard.h"
#include "fw/logger.h"

SDCard::SDCard(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t ss)
: clk_(clk)
, miso_(miso)
, mosi_(mosi)
, ss_(ss)
, cardType_(CARD_NONE)
, cardSize_(0)
, inited_(false)
{}

SDCard::~SDCard()
{
    inited_ = false;
}

void SDCard::init()
{
    SPIClass* sd_spi = new SPIClass(HSPI);
    sd_spi->begin(clk_, miso_, mosi_, ss_);
    while (!SD.begin(ss_, *sd_spi, 8000000)) {
        LOG_ERROR("SDCard: Mount failed, retry ...");
    }

    cardType_ = SD.cardType();
    if(cardType_ == CARD_NONE) {
        LOG_ERROR("SDCard: No SD card attached");
        return;
    }
    std::string cardType;
    switch (cardType_) {
        case CARD_MMC:
            cardType = "MMC";
            break;
        case CARD_SD:
            cardType = "SDSC";
            break;
        case CARD_SDHC:
            cardType = "SDHC";
            break;
        default:
            cardType = "UNKNOWN";
            break;
    }

    cardSize_ = SD.cardSize() / (1024 * 1024);
    LOG_INFO("SDCard: Type[%s] Size[%dM]", cardType, cardSize_);
    LOG_INFO("SDCard: init ok");
    inited_ = true;
}