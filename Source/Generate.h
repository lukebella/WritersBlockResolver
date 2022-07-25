
#pragma once
#include <JuceHeader.h>
#include "Request.h"
#include "Parameters.h"

class Generate {

public:

    Generate() {}
    ~Generate() {}


    void processUnc(float newValue) {

        if (newValue)
        {
            openAndLoad();
            
            //SAMPLING
            if (response.result == Result::ok())
            {
                DBG("LOAD termined. Starting SAMPLE...");
                request.setUrl("http://127.0.0.1:8080/sample");
                response = request.execute("SAMPLE");
                DBG("/SAMPLE");
            }
            else
            {
                nullRequest(response);
            }

        }
    }


    void processCond()
    {

        //CONTINUATION
        if (response.result == Result::ok())
        {
            DBG("LOAD termined. Starting CONTINUATION...");
            request.setUrl("http://127.0.0.1:8080/continuation");
            response = request.execute("CONTINUATION");
            DBG("CONTINUATION");

            if (response.result == Result::ok()) {
                DBG("CONTINUATION termined. Starting SHUTDOWN...");
                closeConn();
            }
        }
        else
        {
            nullRequest(response);
        }
    }


    void continuation(File& midiFile)
    {
        sendFile(midiFile);
        openAndLoad();
        processCond();

    }

    /*/void process(juce::MidiFile midiFile, int max_primer_seconds) {
        request.execute();
    }*/

    void initialize() {
        request.setUrl("http://127.0.0.1:8080");
        //?ckpt_path='C:/Users/lenovo/Documents/JUCE_Projects/WritersBlockResolver/Transformer/unconditional_model_16.ckpt'
    }

    void nullRequest(Request::Response response) {

        DBG("Richiesta non eseguita");
        closeConn();
    }


    void openAndLoad()
    {
        if (!transLoaded)
        {
            request.setUrl("http://127.0.0.1:8080/load");
            DBG(request.getUrl().getDomain());
            DBG("Starting LOAD");
            response = request.execute("LOAD");
            if (response.result == Result::ok())
                transLoaded = true;
            else
            {   
                nullRequest(response);
            }
            //se modulo già caricato dirlo con un flag
            // 
        }
    }


    void closeConn()
    {
        request.setUrl("http://127.0.0.1:8080/shutdown");
        auto nullResponse = request.execute("SHUTDOWN");
        transLoaded = false;
        DBG("SHUTDOWN");
    }

    void sendFile(File& midiFile)
    {
        request.setUrl("http://127.0.0.1:8080/store");
        request.attachFile(request.getUrl(), midiFile);
        response = request.execute("STORE");
        if (response.result == Result::ok())
            DBG("File sent.");
        else
        {
            nullRequest(response);
        }

    }

private:

    Request request;
    Request::Response response;
    bool transLoaded = false;

};


//caricare file midi 
//caricare la risposta 
//trascinare da e verso la daw