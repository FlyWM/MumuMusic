#ifndef MUMEDIA_P_H
#define MUMEDIA_P_H

#include <string>
#include <map>
#include "libMuMediaHandler_Global.h"

class MUMEDIAHANDLERSHARED_EXPORT MuMediaData
{
public:
    enum MediaType
    {
        AudioMedia,
        VideoMedia,
    };

    // file, dir, title, album, artist, duration, timestamp, bitrate, filesize, ignored
    std::string mediaFileName;
    std::map<std::string, std::string> audioBrief;
    int64_t duration;
    int64_t bitRate;
    std::pair<uint8_t *, int> attachedPic;
    int64_t fileSize;
    bool isValid;
    MediaType mediaType;
};

struct AVFormatContext;
class MUMEDIAHANDLERSHARED_EXPORT MuMediaPrivate : public MuMediaData
{
public:
    MuMediaPrivate();

    void setMediaFileName(const std::string &fileName);

protected:
    AVFormatContext *m_pFormatCtx;
};

#endif // MUMEDIA_P_H
