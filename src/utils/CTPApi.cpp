#include "CTPApi.hh"


//#region WriterFileClass

class WriterFileClass
{
public:
    explicit WriterFileClass(std::string dest);

    ~WriterFileClass() {
        if(m_fd >= 0) {
            sceIoClose(m_fd);
        }
    }

    size_t WriterFileClassCallback(char* ptr, size_t size, size_t nmemb)
    {
        int ret = sceIoWrite(m_fd, ptr, size*nmemb);
        if (ret < 0)
            cURLpp::raiseException(std::runtime_error("Network: Couldn't write data"));

        return ret;
    }

    int rewind() {
        return sceIoLseek(m_fd, 0, SCE_SEEK_SET);
    }

private:
    int m_fd = -1;
};

WriterFileClass::WriterFileClass(std::string dest) {
    m_fd = sceIoOpen(dest.c_str(), SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0777);

    if (m_fd < 0)
        cURLpp::raiseException(std::runtime_error("Network: Couldn't write data"));
}

//#endregion


CTPApi::CTPApi() {
    status = CTPAPI_STATUS_NOT_LAUNCH;
}

void CTPApi::initNet() {
    sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
    SceNetInitParam netInitParam;
    int size = 4*1024*1024;
    netInitParam.memory = malloc(size);
    netInitParam.size = size;
    netInitParam.flags = 0;
    sceNetInit(&netInitParam);
    sceNetCtlInit();
    sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);
    sceHttpInit(4*1024*1024);
    cURLpp::initialize();
}

void CTPApi::terminateNet() {
    curl_global_cleanup();
    sceHttpTerm();
    sceSysmoduleUnloadModule(SCE_SYSMODULE_HTTP);
    sceNetCtlTerm();
    sceNetTerm();
    cURLpp::terminate();
}

std::vector<CTPApiPost> CTPApi::getPosts() {
    return posts;
}

void CTPApi::download(std::string url, std::string dest) {
    try {
        status = CTPAPI_STATUS_DOWNLOAD;
        curlpp::Easy request;

        request.setOpt(new curlpp::options::Url(url));
        request.setOpt(new curlpp::options::UserAgent(CTPAPI_UA));
        request.setOpt(new curlpp::options::SslVerifyHost(0L));
        request.setOpt(new curlpp::options::SslVerifyPeer(false));

        request.setOpt(new curlpp::options::ConnectTimeout(10L));
        request.setOpt(new curlpp::options::FollowLocation(true));
        request.setOpt(new curlpp::options::MaxRedirs(8L));
        request.setOpt(new curlpp::options::FailOnError(true));

        using namespace std::placeholders;

        WriterFileClass mWriterChunk(dest);

        curlpp::types::WriteFunctionFunctor writeFunctor = std::bind(&WriterFileClass::WriterFileClassCallback, &mWriterChunk, _1, _2, _3);
        request.setOpt(new curlpp::options::WriteFunction(writeFunctor));

        for (unsigned int retries=1; retries <= 3; retries++) {
            try {
                request.perform();
                status = CTPAPI_STATUS_DOWNLOADED;
                break;
            } catch (curlpp::RuntimeError &e) {
                if (retries == 3) {
                    status = CTPAPI_STATUS_ERROR;
                }
                mWriterChunk.rewind();
                sceKernelDelayThread(retries * 500 * 1000);
                continue;
            }
        }

    } catch (curlpp::RuntimeError &e) {
        status = CTPAPI_STATUS_ERROR;
    }


}

void CTPApi::getPostsByApi() {
    sceIoRemove(CTPAPI_PATH);
    this->initNet();
    this->download(CTPAPI_URL, CTPAPI_PATH);
    this->terminateNet();
    this->readPostsFile();
}

void CTPApi::readPostsFile() {
    SceUID fh = sceIoOpen(CTPAPI_PATH, SCE_O_RDONLY, 0777);

    if (fh > -1) {
        sceIoClose(fh);
        apiJson = json_load_file(CTPAPI_PATH, 0, &error);

        if (apiJson) {
            CTPApiPost ctpApiPost;
            posts.clear();

            json_array_foreach(apiJson, indexArray, valueArray) {
                ctpApiPost.title = json_string_value(json_object_get(valueArray, "title"));
                ctpApiPost.excerpt = json_string_value(json_object_get(valueArray, "excerpt"));
                ctpApiPost.url = json_string_value(json_object_get(valueArray, "url"));
                ctpApiPost.publi_date = json_string_value(json_object_get(valueArray, "publi_date"));
                ctpApiPost.views = (int) json_integer_value(json_object_get(valueArray, "views"));
                ctpApiPost.author = json_string_value(json_object_get(valueArray, "author"));


                posts.emplace(posts.begin(), ctpApiPost);
            }
            status = CTPAPI_STATUS_LOADED;
        }
        else {
            status = CTPAPI_STATUS_ERROR;
        }
    }
    else {
        status = CTPAPI_STATUS_ERROR;
        sceIoClose(fh);
    }

}

CTPApiStatus CTPApi::getStatus() const {
    return status;
}

