
#pragma once
#include <JuceHeader.h>
#include "Request.h"
#include "Parameters.h"

class Generate {

public:

    Generate() {}
    ~Generate() {}


    void unconditional(float newValue)
    {
        if (newValue && transLoaded)
        {
            DBG("Starting sample");
            sample();
        }

        else
        {
            DBG("Error sample");
           // nullRequest(response);
        }
    }

    void sample()//const String& pathToSave)
    {
        DBG("LOAD termined. Starting SAMPLE...");
        request.setUrl(SAMPLE);
        pathToSave = whereToSave();
        response = request.execute(SAMPLE, pathToSave);
        DBG("/SAMPLE");
        /*if (response.result.failed())
            nullRequest(response);*/
    }


    void processCond(float newValue)
    {
        
        //CONTINUATION
        if (transLoaded)
        {
            pathToSave = whereToSave();
            midiFile = findMidi();
            DBG(midiFile.getFileName());
            DBG("LOAD termined. Starting CONTINUATION...");
            request.setUrl(CONTINUATION);
            request.attachParam("max_primer_seconds", maxPrimerSeconds);
            DBG(request.getUrl().toString(true));
            
            request.attachFile(request.getUrl(), midiFile);
            DBG(request.getUrl().toString(true));
            response = request.execute(CONTINUATION, pathToSave);
            DBG("CONTINUATION");
        }
        else
            nullRequest(response);
    }


    void nullRequest(Request::Response response) {

        DBG("Richiesta non eseguita");
        closeConn();
    }


    void openAndLoad()
    {
        if (!transLoaded)
        {
            request.setUrl(LOAD);
            DBG(request.getUrl().getDomain());
            DBG("Starting LOAD");
            response = request.execute();
            //se modulo caricato dirlo con un flag
            // 
            if (response.result == Result::ok())
                setTransLoaded(true);
        }
    }


    void closeConn()
    {
        request.setUrl(SHUTDOWN);
        auto nullResponse = request.execute();
        setTransLoaded(false);
        DBG("SHUTDOWN");
    }
   

    String whereToSave()
    {
        FileChooser explorer("Select where you want to save the file", File::getSpecialLocation(File::userHomeDirectory), "");

        if (explorer.browseForDirectory())
        {
            File dirSave(explorer.getResult());
            DBG(dirSave.getFullPathName());
            return dirSave.getFullPathName();
        }

    }
    /*void sendFile(File& midiFile)
    {
        request.setUrl("http://127.0.0.1:8080/store");
        request.attachFile(request.getUrl(), midiFile);
        DBG(midiFile.getFileName());
        response = request.execute("STORE");
        if (response.result == Result::ok())
            DBG("File sent.");
        else
            nullRequest(response);
    }
    */

    void setTransLoaded(bool newTrans)
    {
        transLoaded = newTrans;
    }

    void initialize(const String& domain) {
        request.init(domain);
        //?ckpt_path='C:/Users/lenovo/Documents/JUCE_Projects/WritersBlockResolver/Transformer/unconditional_model_16.ckpt'
    }

    File findMidi()
    {
        FileChooser explorer("Select a MIDI file to continue", File::getSpecialLocation(File::userHomeDirectory), "*.mid");

        if (explorer.browseForFileToOpen())
        {
            File midifile(explorer.getResult());
            DBG(midifile.getFileName());
            //generate.setTransLoaded(true);
            return midifile;

        }
        
    }

    void setPrimerSeconds(int newValue) {
        maxPrimerSeconds = newValue;
    }
private:

    Request request;
    Request::Response response;
    bool transLoaded = false;
    String pathToSave;
    File midiFile;
    int maxPrimerSeconds = PRIMER_SECONDS;
};


//caricare file midi 
//caricare la risposta 
//trascinare da e verso la daw