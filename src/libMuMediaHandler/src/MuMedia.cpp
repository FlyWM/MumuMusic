// Utf-8 BOM

#include <string>
#include <iostream>
#include <fstream>
#include "MuMedia.h"
#include "MuMedia_p.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libswresample/swresample.h>
#include <dsound.h>
#include <stdio.h>
#include <io.h>
}

MuMediaPrivate::MuMediaPrivate()
    : m_pFormatCtx(nullptr)
{
//    attachedPic = nullptr;
}

void MuMediaPrivate::setMediaFileName(const std::string &fileName)
{
    mediaFileName = fileName;
    if (fileName.empty())
        return;

    if (avformat_open_input(&m_pFormatCtx, fileName.data(), nullptr, nullptr) != 0) {
        std::cout << ("Couldn't open the file ! ") << fileName << std::endl;
        isValid = false;
        return;
    }

    if (avformat_find_stream_info(m_pFormatCtx, nullptr) < 0) {
        std::cout << ("Couldn't find stream information !") << std::endl;
        isValid = false;
        return;
    }

    AVDictionaryEntry *pDictEntry = nullptr;
    std::string strKey;
    while (pDictEntry = av_dict_get(m_pFormatCtx->metadata, "", pDictEntry, AV_DICT_IGNORE_SUFFIX)) {
        strKey = pDictEntry->key;
//        std::cout << "key::: " << pDictEntry->key << std::endl;
        if (strKey == "album")
            audioBrief["album"] = pDictEntry->value;
        if (strKey == "title")
            audioBrief["title"] = pDictEntry->value;
        if (strKey == "artist")
            audioBrief["artist"] = pDictEntry->value;
    }
    duration = m_pFormatCtx->duration;
    bitRate = m_pFormatCtx->bit_rate;

    // 获取图片
    int streamsCount = m_pFormatCtx->nb_streams;
    for (int i=0; i<streamsCount; ++i) {
        if (m_pFormatCtx->streams[i]->disposition & AV_DISPOSITION_ATTACHED_PIC) {
            AVPacket packet = m_pFormatCtx->streams[i]->attached_pic;
            uint8_t *pic = new uint8_t[packet.size];
            memcpy(pic, packet.data, packet.size);
            attachedPic.first = pic;
            attachedPic.second = packet.size;
        }
    }

    av_free(m_pFormatCtx);

    std::ifstream f;
    f.open(mediaFileName);
    f.seekg(0, std::ios::end);
    long size = f.tellg();
    fileSize = size;
    f.close();

    audioBrief["file"] = mediaFileName.data();
    std::size_t pos = mediaFileName.find("/", 3);
    audioBrief["dir"] = mediaFileName.substr(0, pos);
}

MuMedia::MuMedia(const std::string fileName)
    : d_ptr(new MuMediaPrivate)
{
    Mu_D(MuMedia);
    setMediaFileName(fileName);
}

MuMedia::~MuMedia()
{
    delete d_ptr;
    d_ptr = nullptr;
}

void MuMedia::setMediaFileName(const std::string &fileName)
{
    Mu_D(MuMedia);
    d->setMediaFileName(fileName);
}

std::string MuMedia::audioFile() const
{
    Mu_D(const MuMedia);
    return d->audioBrief.at("file");
}

std::string MuMedia::audioDir() const
{
    Mu_D(const MuMedia);
    return d->audioBrief.at("dir");
}

std::string MuMedia::audioArtist() const
{
    Mu_D(const MuMedia);
	if (d->audioBrief.find("artist") != d->audioBrief.end())
		return d->audioBrief.at("artist");
	else return std::string();
}

std::string MuMedia::audioTitle() const
{
    Mu_D(const MuMedia);
	if (d->audioBrief.find("title") != d->audioBrief.end())
		return d->audioBrief.at("title");
	else return std::string();
}

std::string MuMedia::audioAlbum() const
{
    Mu_D(const MuMedia);
	if (d->audioBrief.find("album") != d->audioBrief.end())
		return d->audioBrief.at("album");
	else return std::string();
}

int64_t MuMedia::duration() const
{
    Mu_D(const MuMedia);
    return d->duration;
}

int64_t MuMedia::bitRate() const
{
    Mu_D(const MuMedia);
    return d->bitRate;
}

int64_t MuMedia::fileSize() const
{
    Mu_D(const MuMedia);
    return d->fileSize;
}

std::pair<uint8_t *, int> MuMedia::attchedPic() const
{
    Mu_D(const MuMedia);
    return d->attachedPic;
}

bool MuMedia::isValid() const
{
    Mu_D(const MuMedia);
    return d->isValid;
}
