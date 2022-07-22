
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
            if (!transLoaded)
            {
                DBG(request.getUrl().getDomain());
                DBG("Starting LOAD");
                response = request.execute("LOAD");
                if (response.result == Result::ok())
                    transLoaded = true;
                //se modulo già caricato dirlo con un flag
                // 
            }
            // 
            // 
            //DBG("LOAD");
            //String var_dbg = static_cast<String>(request.getUrl());

            //SAMPLING
            if (response.result == Result::ok())
            {

                DBG("LOAD termined. Starting SAMPLE...");
                request.setUrl("http://127.0.0.1:8080/sample");
                response = request.execute("SAMPLE");
                DBG("/SAMPLE");

                /*/if (response.result == Result::ok()) {
                    DBG("SAMPLE termined. Starting SHUTDOWN...");
                    request.setUrl("http://127.0.0.1:8080/shutdown");
                    response = request.execute("SHUTDOWN");
                    //DBG("SHUTDOWN");
                }*/
                    /*else
                    {
                        nullRequest(request);
                    }*/
                

                
                    /*else
                    {
                        nullRequest(request);
                    }*/
                
            }
            else
            {
                nullRequest(request);
            }

        }
    }


    void processCond(float newValue)
    {
        if (newValue)
        {
            if (!transLoaded)
            {
                DBG(request.getUrl().getDomain());
                DBG("Starting LOAD");
                response = request.execute("LOAD");
                if (response.result == Result::ok())
                    transLoaded = true;
                //se modulo già caricato dirlo con un flag
                // 
            }

            //CONTINUATION
            if (response.result == Result::ok())
            {
                DBG("LOAD termined. Starting CONTINUATION...");
                request.setUrl("http://127.0.0.1:8080/continuation");
                response = request.execute("CONTINUATION");
                DBG("SAMPLE");

                if (response.result == Result::ok()) {
                    DBG("CONTINUATION termined. Starting SHUTDOWN...");
                    request.setUrl("http://127.0.0.1:8080/shutdown");
                    response = request.execute("SHUTDOWN");
                    transLoaded = false;

                    //DBG("SHUTDOWN");
                }
            }
            else
            {
                nullRequest(request);
            }
        }
    }



    /*/void process(juce::MidiFile midiFile, int max_primer_seconds) {
        request.execute();
    }*/

    void initialize() {
        request.setUrl("http://127.0.0.1:8080/load");
        //?ckpt_path='C:/Users/lenovo/Documents/JUCE_Projects/WritersBlockResolver/Transformer/unconditional_model_16.ckpt'
    }

    void nullRequest(Request request) {

        DBG("Richiesta non eseguita");
        request.setUrl("http://127.0.0.1:8080/shutdown");
        auto nullResponse = request.execute("SHUTDOWN");
        transLoaded = false;
        DBG("SHUTDOWN");
    }


private:

    Request request;
    Request::Response response;
    bool transLoaded = false;

};


//caricare file midi 
//caricare la risposta 
//trascinare da e verso la daw