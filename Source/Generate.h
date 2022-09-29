
#pragma once
#include <JuceHeader.h>
#include "Parameters.h"
#include "FallbackDownloadTask.h"
#include "Thread.h"

class Generate : public Component{

public:

    Generate();
    ~Generate();

    void unconditional();

    void processCond(String dragAndDropPath);

    void openAndLoad();

    String whereToSave();

    void setTransLoaded(bool newTrans);

    File findMidi();

    void setPrimerSeconds(int newValue);

    void requestForDownload(URL& url, File& file);

    std::unique_ptr<URL::DownloadTask> Generate::downloading(const URL& urlToUse,
        const File& targetFileToUse,
        const URL::DownloadTaskOptions& options);

    URL getUrl();

    void setURL(String newURL);

private:

    bool transLoaded = false;
    bool cond = false;
    String pathToSave;
    File midiFile;
    int maxPrimerSeconds = PRIMER_SECONDS;
    URL url = URL();
    //LoadThread loader;
    //SampleThread sampler;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Generate);

};

//trascinare da e verso la daw