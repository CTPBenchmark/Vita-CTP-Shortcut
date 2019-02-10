#ifndef CTP_SHORTCUT_CTPAPI_HH
#define CTP_SHORTCUT_CTPAPI_HH

#include <malloc.h>
#include <string>
#include <vector>

#include <psp2/sysmodule.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/libssl.h>
#include <psp2/net/http.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <psp2/kernel/threadmgr.h>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <jansson.h>

#include "Config.hh"
#include "Singleton.h"

#define CTPAPI_UA "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:61.0) Gecko/20100101 Firefox/61.0"
#define CTPAPI_URL "https://api.customprotocol.com/?data=posts"
#define CTPAPI_PATH "ux0:data/CTP/posts.json"

typedef enum CTPApiStatus {
    CTPAPI_STATUS_NOT_LAUNCH,
    CTPAPI_STATUS_DOWNLOAD,
    CTPAPI_STATUS_DOWNLOADED,
    CTPAPI_STATUS_LOADED,
    CTPAPI_STATUS_ERROR,
} CTPApiStatus;

typedef struct CTPApiPost {
    std::string     title;
    std::string     excerpt;
    std::string     url;
    std::string     author;
    std::string     publi_date;
    int             views;
} CTPApiPost;

class CTPApi : public Singleton<CTPApi> {
    friend class Singleton<CTPApi>;
private:
    json_t *apiJson;
    json_error_t error;
    std::vector<CTPApiPost> posts;
    size_t indexArray;
    json_t *valueArray;
    CTPApiStatus status;

    void initNet();
    void terminateNet();
    void download(std::string url, std::string dest);
    void readPostsFile();
public:
    CTPApi();
    void getPostsByApi();
    std::vector<CTPApiPost> getPosts();

    CTPApiStatus getStatus() const;
};


#endif //CTP_SHORTCUT_CTPAPI_HH
