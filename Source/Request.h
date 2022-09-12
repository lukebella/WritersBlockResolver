#pragma once
#include <JuceHeader.h>
#include "Parameters.h"
#include "FallbackDownloadTask.h"
//#include "juce_core/network/juce_URL.h"

class Request
{

public:
    Request() {}
    ~Request() {}

    struct Response
    {
        Result result;
        StringPairArray headers;
        var body;
        String bodyAsString;
        int status;

        Response() : result(Result::ok()), status(0) {} // not sure about using Result if we have to initialise it to ok...
    } response;


    Request::Response execute(const String& operation, const String& pathToSave)
    {
        //int test  = fields.getProperties().size();
        bool hasFields = (fields.getProperties().size() > 0);
        //non ho capito perchè senza questa dichiarazione, anche se hasFields non viene implementato in manageDownload, non funziona il download.
        //Ho provato ad assegnarlo a withUsePost di downloadToFile, ma non funziona ugualmente...

        File file;

        DBG("init " + operation);
        file = File(pathToSave).getChildFile(operation + ".mid");

        manageDownload(file);
        //delete file;

        return response;

    }

    Request::Response execute()
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


    void setUrl(const String& endpoint) {
        url = url.withNewSubPath(endpoint);
    }


    URL getUrl() {
        return url;
    }

    void attachParam(const String& paramName, const int& paramValue ) {
        DBG("Attach parameters...");
        url = url.withParameter(paramName, String(paramValue));
    }

    void attachFile(URL& url, File& file)
    {
        DBG("Uploading file ");
        url = url.withFileToUpload("myfile", file, "audio/midi");
        DBG(file.getFileName());
        /*MemoryBlock mb = MemoryBlock();

        if (file.loadFileAsData(mb))
        {
            url = url.withDataToUpload("myfile", file.getFileName(), mb, "audio/midi");
            DBG("FILE SENT");
        }
        else
        {
            DBG("Error in copying file into the buffer");
        }*/
    }

    void manageDownload(File& file) {//, bool hasFields) {

        URL::DownloadTaskOptions options;
        //std::unique_ptr<URL::DownloadTask> downloadptr (url.downloadToFile(file)); // , options.withUsePost(hasFields));// , options.withUsePost(true));
        
        std::unique_ptr<URL::DownloadTask> downloadptr(downloading(url, file, options));
        
        //gestire con un pop-up


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


    void init(const String& domain)
    {
        url = URL(domain);

    }

    std::unique_ptr<URL::DownloadTask> downloading(const URL& urlToUse,
        const File& targetFileToUse,
        const URL::DownloadTaskOptions& options)
    {
        const size_t bufferSize = 0x8000;
        targetFileToUse.deleteFile();

        if (auto outputStream = targetFileToUse.createOutputStream(bufferSize))
        {
            auto stream = std::make_unique<WebInputStream>(urlToUse, options.usePost);
            stream->withExtraHeaders(options.extraHeaders);
            stream->withConnectionTimeout(30000);


            if (stream->connect(nullptr))
                return std::make_unique < FallbackDownloadTask > (std::move(outputStream),
                    bufferSize,
                    std::move(stream),
                    options.listener);
        }

        return nullptr;
    }

protected:

    URL url;
    //URL::InputStreamOptions options;
    StringPairArray headers;
    String verb;
    DynamicObject fields;
    String bodyAsString;


    
    Result checkInputStream(std::unique_ptr<InputStream>& input)
    {
        if (!input)
        {
            return Result::fail("HTTP request failed");
        }
        return Result::ok();
    }

    static String stringPairArrayToHeaderString(StringPairArray stringPairArray)
    {
        String result;
        for (auto key : stringPairArray.getAllKeys())
        {
            result += key + ": " + stringPairArray.getValue(key, "") + "\n";
        }
        return result;
    }
};