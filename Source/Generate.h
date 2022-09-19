
#pragma once
#include <JuceHeader.h>
#include "Request.h"
#include "Parameters.h"
#include "Thread.h"

class Generate {

public:

    Generate();
    ~Generate();

    void unconditional();

    void sample();//const String& pathToSave)

    void processCond();

    void nullRequest(Request::Response response);

    void openAndLoad();

    void closeConn();

    String whereToSave();

    void setTransLoaded(bool newTrans);
    
    void initialize(const String& domain); 

    File findMidi();

    void setPrimerSeconds(int newValue);

    std::unique_ptr<URL::DownloadTask> Generate::downloading(const URL& urlToUse,
        const File& targetFileToUse,
        const URL::DownloadTaskOptions& options);

private:

    Request request;
    Request::Response response;
    bool transLoaded = false;
    bool cond = false;
    String pathToSave;
    File midiFile;
    int maxPrimerSeconds = PRIMER_SECONDS;

    //LoadThread loader;
    //SampleThread sampler;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Generate);

};


//caricare file midi 
//caricare la risposta 
//trascinare da e verso la daw