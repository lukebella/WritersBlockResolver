#pragma once
#include <JuceHeader.h>

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
        auto urlRequest = url.getChildURL(endpoint);
        bool hasFields = (fields.getProperties().size() > 0);
        if (hasFields)
        {
            MemoryOutputStream output;

            fields.writeAsJSON(output, 0, false, 20);
            urlRequest = urlRequest.withPOSTData(output.toString());
        }
        
        /*DBG(operation);
        String str = static_cast<String>(operation.compare("SAMPLE"));
        DBG(str);*/


        if (operation.compare("STORE") == 0)
        {
            DBG("Trying to send a file");
            std::unique_ptr<InputStream> input(urlRequest.createInputStream(hasFields, nullptr, nullptr, stringPairArrayToHeaderString(headers), 0, &response.headers, &response.status, 5, verb));

            DBG("File Stored");
                
            return response;
            
        }


        //SAMPLING
        if (operation.compare("SAMPLE")== 0) 
        {
            DBG("init sequence");
            file = File("C:/Users/lenovo/Documents/JUCE_Projects/WritersBlockResolver/tt-942969/midi_unc_seq.mid");
            file.getChildFile("midi_unc_seq.mid");
           
            std::unique_ptr<InputStream> input(urlRequest.createInputStream(hasFields, nullptr, nullptr, stringPairArrayToHeaderString(headers), 0, &response.headers, &response.status, 5, verb));
            file.deleteFile();
            
            manageDownload(file);

            return response;
        }


        //CONTINUATION
        if (operation.compare("CONTINUATION") == 0)
        {
            DBG("init continuation");
            file = File("C:/Users/lenovo/Documents/JUCE_Projects/WritersBlockResolver/tt-942969/midi_cont_seq.mid");
            file.getChildFile("midi_cont_seq.mid");

            std::unique_ptr<InputStream> input(urlRequest.createInputStream(hasFields, nullptr, nullptr, stringPairArrayToHeaderString(headers), 0, &response.headers, &response.status, 5, verb));
            file.deleteFile();

            manageDownload(file);

            return response;
        }
        
        std::unique_ptr<InputStream> input(urlRequest.createInputStream(hasFields, nullptr, nullptr, stringPairArrayToHeaderString(headers), 0, &response.headers, &response.status, 5, verb));
        

        //DBG("REQUEST");
        
        response.result = checkInputStream(input);
        if (response.result.failed()) return response;


        response.bodyAsString = input->readEntireStreamAsString();
        response.result = JSON::parse(response.bodyAsString, response.body);
        

        return response;
    }


    void setUrl(String newUrl) {
        url = newUrl;
    }


    URL getUrl() {
        return url;
    }

    void attachFile(URL& url,File& file)
    {
        MemoryBlock mb = MemoryBlock();

        if (file.loadFileAsData(mb))
        {
            url.withDataToUpload("Midi File to continue",file.getFileName(), mb, "audio/midi");
            DBG("Uploading file ");
            DBG(file.getFileName());
        }
        else
        {
            DBG("Error in copying file into the buffer");
        }
        //return url.withFileToUpload("Midi File to continue", file, "audio/midi");
    }

    URL attachtransPath(URL& url, const String& path)
    {
        return url.withParameter("ckpt_path", path);
    }

    

protected:
    
    URL url;

    StringPairArray headers;
    String verb;
    String endpoint;
    DynamicObject fields;
    String bodyAsString;
    
    File file;

    void manageDownload(File file) {
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

    Result checkInputStream(std::unique_ptr<InputStream>& input)
    {
        if (!input) 
            return Result::fail("HTTP request failed");
        
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