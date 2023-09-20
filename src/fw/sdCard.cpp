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

    cardSize_ = SD.cardSize() / (1024 * 1024 );
    LOG_INFO("SDCard: Type[%s], Size[%llu MB]", cardType.c_str(), cardSize_);
    LOG_INFO("SDCard: init ok");
    inited_ = true;
}

bool SDCard::checkInit()
{
    if (!inited_) {
        LOG_ERROR("SDCard: Please init first");
    }
    return inited_;
}

void SDCard::createDir(const std::string path)
{
    if (!checkInit) return;
    if (SD.mkdir(path.c_str())) {
        LOG_TRACE("SDCard: Create dir %s", path.c_str());
    } else {
        LOG_ERROR("SDCard: Create dir %s failed", path.c_str());
    }
}

void SDCard::removeDir(const std::string path)
{
    if (!checkInit) return;
    if (SD.rmdir(path.c_str())) {
        LOG_TRACE("SDCard: Delete dir %s", path.c_str());
    } else {
        LOG_ERROR("SDCard: Delete dir %s failed", path.c_str());
    }
}

void SDCard::listDir(const std::string path)
{
    if (!checkInit) return;
    File root = SD.open(path.c_str());
    if(!root){
        LOG_ERROR("SDCard: Failed to open directory %s for list", path.c_str());
        return;
    }
    if(!root.isDirectory()){
        LOG_ERROR("SDCard: List directory %s is not a directory", path.c_str());
        return;
    }

    File file = root.openNextFile();
    std::string info = "";
    while(file) {
        if(file.isDirectory()){
            info += "\n[D] " + std::string(file.name());
        } else {
            info += "\n[F] " + std::string(file.name()) + " " + std::to_string(file.size()) + "bytes";
        }
        file = root.openNextFile();
    }
}

void SDCard::readFile(const std::string path)
{
    if (!checkInit) return;
    File file = SD.open(path.c_str());
    if(!file) {
        LOG_ERROR("SDCard: Failed to open file %s for reading", path.c_str());
        return;
    }
    while(file.available()) {
        LOG_INFO("SDCard: Read data [%c]", file.read());
    }
    file.close();
}

void SDCard::writeFile(const std::string path, const std::string message, const char* mode)
{
    if (!checkInit) return;

    if (strcmp(mode, FILE_WRITE) != 0  && strcmp(mode, FILE_APPEND) != 0) {
        LOG_ERROR("SDCard: File write only support [%c] and [%c] mode", FILE_WRITE, FILE_APPEND);
        return;
    }

    File file = SD.open(path.c_str(), FILE_WRITE);
    if(!file) {
        LOG_ERROR("SDCard: Failed to open file %s for writing", path.c_str());
        return;
    }
    if (file.print(message.c_str())) {
        LOG_TRACE("SDCard: Write %s to file %s", message.c_str(), path.c_str());
    } else {
        LOG_ERROR("SDCard: Write to file %s failed", path.c_str());
    }
    file.close();
}

void SDCard::renameFile(const std::string path, const std::string newName)
{
    if (!checkInit) return;
    if (!SD.exists(path.c_str())) {
        LOG_ERROR("SDCard: Failed to find file %s for rename", path.c_str());
        return;
    }
    if (SD.rename(path.c_str(), newName.c_str())) {
        LOG_TRACE("SDCard: Rename %s to %s", path.c_str(), newName.c_str());
    } else {
        LOG_ERROR("SDCard: Rename %s to %s failed", path.c_str(), newName.c_str());
    }
}

void SDCard::deleteFile(const std::string path)
{
    if (!checkInit) return;
    if (!SD.exists(path.c_str())) {
        LOG_WARNING("SDCard: Failed to find file %s for delete", path.c_str());
        return;
    }
    if (SD.remove(path.c_str())) {
        LOG_TRACE("SDCard: Delete file %s", path.c_str());
    } else {
        LOG_ERROR("SDCard: Delete file %s failed", path.c_str());
    }
}

// TODO：这个库函数会hang
// float SDCard::getUsage()
// {
//     uint64_t total = SD.totalBytes();
//     uint64_t used = SD.usedBytes();
//     float utilization = used * 1.0 / used;
//     LOG_TRACE("SDCard: Total[%llu MB], Used[%llu MB], Utilization[]%.3f", total / (1024 * 1024), used / (1024 * 1024), utilization);
//     return utilization;
// }