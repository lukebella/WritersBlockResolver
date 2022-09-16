#include "Request.h"

Request::Request() {}
Request::~Request() {}


Request::Response Request::execute(const String& operation, const String& pathToSave)
{
    File file;
    DBG("init " + operation);
    file = File(pathToSave).getChildFile(operation + ".mid");
    manageDownload(file);
    return response;

}

Request::Response Request::execute()
{
    bool hasFields = (fields.getProperties().size() > 0);
    if (hasFields)
    {
        MemoryOutputStream output;

        fields.writeAsJSON(output, 0, false, 20);
        url = url.withPOSTData(output.toString());
    }
    std::unique_ptr<InputStream> input(url.createInputStream(hasFields, nullptr, nullptr, stringPairArrayToHeaderString(headers), 0, &response.headers, &response.status, 5, verb));
    response.result = checkInputStream(input);

    if (response.result.failed())
    {
        DBG(response.result.getErrorMessage());
        return response;
    }
    response.bodyAsString = input->readEntireStreamAsString();
    response.result = JSON::parse(response.bodyAsString, response.body);

    return response;
}


void Request::setUrl(const String& endpoint) {
    url = url.withNewSubPath(endpoint);
}


URL Request::getUrl() {
    return url;
}

void Request::attachParam(const String& paramName, const int& paramValue ) {
    DBG("Attach parameters...");
    url = url.withParameter(paramName, String(paramValue));
}

void Request::attachFile(URL& url, File& file)
{
    DBG("Uploading file ");
    //url = url.withFileToUpload("myfile", file, "audio/midi");
    DBG(file.getFileName());
    MemoryBlock mb = MemoryBlock();

    if (file.loadFileAsData(mb))
    {
        url = url.withDataToUpload("myfile", file.getFileName(), mb, "audio/midi");
        DBG(mb.toString());
        DBG(mb.getSize());
        DBG("FILE SENT");
    }
    else
    {
        DBG("Error in copying file into the buffer");
    }
}

void Request::manageDownload(File& file) {//, bool hasFields) {

    URL::DownloadTaskOptions options;
    //std::unique_ptr<URL::DownloadTask> downloadptr (url.downloadToFile(file)); // , options.withUsePost(hasFields));// , options.withUsePost(true));
        
    std::unique_ptr<URL::DownloadTask> downloadptr(downloading(url, file, options));
        

    if (downloadptr)
    {
        while (downloadptr->isFinished() == false)
        {
            DBG("Downloading...\n");
            Thread::sleep(500);
        }

        if (!downloadptr->hadError())
        {
            DBG("Downloaded ok\n");
        }
        else
            DBG("Download failed\n");
    }
    else
    {
        DBG("No download pointer");
    }
}


void Request::init(const String& domain)
{
    url = URL(domain);

}

std::unique_ptr<URL::DownloadTask> Request::downloading(const URL& urlToUse,
    const File& targetFileToUse,
    const URL::DownloadTaskOptions& options)
{
    const size_t bufferSize = 0x8000;
    targetFileToUse.deleteFile();

    if (auto outputStream = targetFileToUse.createOutputStream(bufferSize))
    {
        auto stream = std::make_unique<WebInputStream>(urlToUse, options.usePost);
        stream->withExtraHeaders(options.extraHeaders);
        stream->withConnectionTimeout(CONNECTION_TIMEOUT);


        if (stream->connect(nullptr))
            return std::make_unique < FallbackDownloadTask > (std::move(outputStream),
                bufferSize,
                std::move(stream),
                options.listener);
    }

    return nullptr;
}

