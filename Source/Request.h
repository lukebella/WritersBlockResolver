#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

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


    Request::Response execute(const String& operation)
    {
        DBG("init " + operation);
        file = File(PATH).getChildFile(operation + ".mid");
        file.deleteFile();
        manageDownload(file);

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

    void attachFile(URL& url, File& file)
    {
        DBG("Uploading file ");
        /*url.withFileToUpload(file.getFileName(), File(file.getFullPathName()), "audio/midi");
        DBG(file.getFileName());*/
        MemoryBlock mb = MemoryBlock();


        url.withDataToUpload(file.getFileName(), file.getFullPathName(), mb, "audio/midi");
        DBG(getUrl().getQueryString());
        DBG(getUrl().getParameterNames()[1]);
        DBG("FILE SENT");




        /*if (file.loadFileAsData(mb))
        {
            url = url.withDataToUpload("Midi File to continue", file.getFileName(), mb, "audio/midi");
            DBG(String(mb.getSize()));
            DBG(file.getFileName());
            DBG(getUrl().getDomain());
            DBG(getUrl().getParameterNames()[1]);
            DBG("FILE SENT");

        }
        else
        {
            DBG("Error in copying file into the buffer");
        }*/
    }

    void manageDownload(File& file) {
        std::unique_ptr<URL::DownloadTask> downloadptr = url.downloadToFile(file);

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

    URL attachtransPath(URL& url, const String& path)
    {
        return url.withParameter("ckpt_path", path);
    }

    void init(const String& domain)
    {
        url = URL(domain);

    }

protected:

    URL url;
    //URL::InputStreamOptions options;
    StringPairArray headers;
    String verb;
    DynamicObject fields;
    String bodyAsString;

    File file;

    
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