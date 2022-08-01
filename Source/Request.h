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
        bool hasFields = (fields.getProperties().size() > 0);
        if (hasFields)
        {
            MemoryOutputStream output;

            fields.writeAsJSON(output, 0, false, 20);
            url = url.withPOSTData(output.toString());
        }


       /* if (operation.compare("STORE") == 0)
        {
            DBG("Trying to send a file");
            std::unique_ptr<InputStream> input(urlRequest.createInputStream(hasFields, nullptr, nullptr, stringPairArrayToHeaderString(headers), 0, &response.headers, &response.status, 5, verb));
            response.result = checkInputStream(input);
            if (response.result.failed()) return response;

            DBG("File Stored");

            return response;

        }*/


        //SAMPLING
        /*if (operation.compare(SAMPLE) == 0)
        {
            DBG("init sequence");
            file = File(PATH).getChildFile("midi_unc_seq.mid");
            std::unique_ptr<InputStream> inputSample(url.createInputStream(hasFields, nullptr, nullptr, stringPairArrayToHeaderString(headers), 0, &response.headers, &response.status, 5, verb));
            response.result = checkInputStream(inputSample);

            

            file.deleteFile();
            manageDownload(file);
            return response;
        }*/


        if (operation.compare(CONTINUATION) == 0 || operation.compare(SAMPLE) == 0)
        {
            DBG("init "+ operation);
            file = File(PATH).getChildFile(operation+".mid");
            //DBG("input");
            std::unique_ptr<InputStream> input(url.createInputStream(hasFields, nullptr, nullptr, stringPairArrayToHeaderString(headers), 0, &response.headers, &response.status, 5, verb));
            //DBG("checkinput");
            response.result = checkInputStream(input);

            if (response.result.failed())
            {
                DBG(response.result.getErrorMessage());
                return response;
            }
            //DBG("bodyasstring");

            response.bodyAsString = input->readEntireStreamAsString();
            //DBG("parse");

            response.result = JSON::parse(response.bodyAsString, response.body);
            //response = req(hasFields, response);
            //DBG("deletefile");

            file.deleteFile();
            //DBG("download");

            manageDownload(file);

            return response;
        }

        else
        {
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
            //response = req(hasFields, response);
        }
    }


    /*Request::Response req(bool hasFields, Request::Response response)
    {
        std::unique_ptr<InputStream> input(url.createInputStream(hasFields, nullptr, nullptr, stringPairArrayToHeaderString(headers), 0, &response.headers, &response.status, 5, verb));
        response.result = checkInputStream(input);

        if (response.result.failed()) return response;

        response.bodyAsString = input->readEntireStreamAsString();
        response.result = JSON::parse(response.bodyAsString, response.body);

        return response;
    }*/

    void setUrl(const String& endpoint) {
        url = url.withNewSubPath(endpoint);
    }


    URL getUrl() {
        return url;
    }

    void attachFile(URL& url, File& file)
    {
        DBG("Uploading file ");
        //url.withFileToUpload(file.getFileName(), file, "audio/midi");
        DBG(file.getFileName());
        MemoryBlock mb = MemoryBlock();
        /*if (url.readEntireBinaryStream(mb)) {
            url.withDataToUpload("myfile", file.getFileName(), mb, "audio/midi");
            DBG(getUrl().getDomain());
            DBG(getUrl().getParameterNames()[1]);
            DBG("FILE SENT");
        }*/
       

        if (file.loadFileAsData(mb))
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
        }
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