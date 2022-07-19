
#pragma once
#include <JuceHeader.h>
#include "Request.h"

class Generate {

public:

    Generate() {}
    ~Generate() {}


    void process(float newValue) {
        if (newValue)
        {
            
            DBG(request.getUrl().getDomain());
            auto response = request.execute("LOAD");
            //DBG("LOAD");
            //String var_dbg = static_cast<String>(request.getUrl());
            if (response.result == Result::ok())
            {
                DBG("LOAD termined. Starting SAMPLE...");
                request.setUrl("http://127.0.0.1:8080/sample");
                auto response = request.execute("SAMPLE");
                //DBG("SAMPLE");
                
                if (response.result == Result::ok()) {
                    DBG("SAMPLE termined. Starting SHUTDOWN...");
                    request.setUrl("http://127.0.0.1:8080/shutdown");
                    response = request.execute("SHUTDOWN");
                    //DBG("SHUTDOWN");
                }
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
        DBG("SHUTDOWN");
    }
private:

    Request request;
     

};


//caricare file midi 
//caricare la risposta 
//trascinare da e verso la daw