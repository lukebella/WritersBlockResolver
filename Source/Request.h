#pragma once
#include <JuceHeader.h>
#include "Parameters.h"
#include "FallbackDownloadTask.h"

class Request
{

public:
    Request();
    ~Request();

    struct Response
    {
        Result result;
        StringPairArray headers;
        var body;
        String bodyAsString;
        int status;

        Response() : result(Result::ok()), status(0) {} // not sure about using Result if we have to initialise it to ok...
    } response;


    Request::Response execute(const String& operation, const String& pathToSave);

    Request::Response execute();

    void setUrl(const String& endpoint);

    URL getUrl();

    void attachParam(const String& paramName, const int& paramValue);

    void attachFile(URL& url, File& file);

    void manageDownload(File& file);

    void init(const String& domain);

    std::unique_ptr<URL::DownloadTask> downloading(const URL& urlToUse,
        const File& targetFileToUse,
        const URL::DownloadTaskOptions& options);

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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Request);

};