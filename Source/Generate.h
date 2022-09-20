
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

    void sample();

    void processCond();

    void openAndLoad();

    String whereToSave();

    void setTransLoaded(bool newTrans);
    
    File findMidi();

    void setPrimerSeconds(int newValue);

    void requestForDownload(URL& url, File& file);

    std::unique_ptr<URL::DownloadTask> Generate::downloading(const URL& urlToUse,
        const File& targetFileToUse,
        const URL::DownloadTaskOptions& options);

private:

    bool transLoaded = false;
    bool cond = false;
    String pathToSave;
    File midiFile;
    int maxPrimerSeconds = PRIMER_SECONDS;

    //LoadThread loader;
    //SampleThread sampler;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Generate);

};

//trascinare da e verso la daw