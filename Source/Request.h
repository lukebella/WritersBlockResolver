
#pragma once

#include <JuceHeader.h>

class Request {

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


    Request::Response execute(const String operation)
    {
        auto urlRequest = url.getChildURL(endpoint);
        bool hasFields = (fields.getProperties().size() > 0);
        if (hasFields)
        {
            MemoryOutputStream output;

            fields.writeAsJSON(output, 0, false, 20);
            urlRequest = urlRequest.withPOSTData(output.toString());
        }

        std::unique_ptr<InputStream> input(urlRequest.createInputStream(hasFields, nullptr, nullptr, stringPairArrayToHeaderString(headers), 0, &response.headers, &response.status, 5, verb));
        

        //DBG("REQUEST");
        
        response.result = checkInputStream(input);
        if (response.result.failed()) return response;

        
        if (operation.contains("SAMPLE"))
        {
            DBG("init sequence");
            if (midiStreamFile.readFrom(*input))
            {
                file = File("C:/Users/lenovo/Documents/JUCE_Projects/WritersBlockResolver");

                FileOutputStream out(file);
                if (midiStreamFile.writeTo(out))
                {

                    DBG(file.getFullPathName());
                }

            }
        }

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

private:
    URL url;
    StringPairArray headers;
    String verb;
    String endpoint;
    DynamicObject fields;
    String bodyAsString;

    MidiFile midiStreamFile;
    File file;
    //std::unique_ptr<FileOutputStream> out;

    Result checkInputStream(std::unique_ptr<InputStream>& input)
    {
        if (!input) return Result::fail("HTTP request failed");
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