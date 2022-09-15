
#pragma once
#include <JuceHeader.h>
#include "Request.h"
#include "Parameters.h"

class Generate {

public:

    Generate();
    ~Generate();

    void unconditional(float newValue);

    void sample();//const String& pathToSave)

    void processCond(float newValue);

    void nullRequest(Request::Response response);

    void openAndLoad();

    void closeConn();

    String whereToSave();

    void setTransLoaded(bool newTrans);
    
    void initialize(const String& domain); 

    File findMidi();

    void setPrimerSeconds(int newValue);

private:

    Request request;
    Request::Response response;
    bool transLoaded = false;
    String pathToSave;
    File midiFile;
    int maxPrimerSeconds = PRIMER_SECONDS;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Generate);

};


//caricare file midi 
//caricare la risposta 
//trascinare da e verso la daw