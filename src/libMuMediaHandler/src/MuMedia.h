/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUMEDIA_H
#define MUMEDIA_H

#include <memory>
#include <string>
#include "libMuMediaHandler_Global.h"

class MuMediaPrivate;
class MuMediaData;
class MUMEDIAHANDLERSHARED_EXPORT MuMedia
{
    Mu_DECLARE_PRIVATE(MuMedia)

public:
    MuMedia(const std::string fileName = "");
    ~MuMedia();
    void setMediaFileName(const std::string &fileName);
    std::string audioFile() const;
    std::string audioDir() const;
    std::string audioTitle() const;
    std::string audioAlbum() const;
    std::string audioArtist() const;
    int64_t duration() const;
    int64_t bitRate() const;
    int64_t fileSize() const;
    std::pair<uint8_t *, int> attchedPic() const;
    bool isValid() const;

protected:
    MuMediaData *d_ptr;
};

#endif // MUMEDIA_H
