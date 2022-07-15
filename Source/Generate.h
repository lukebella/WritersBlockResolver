
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
            auto response = request.execute();
            //String var_dbg = static_cast<String>(request.getUrl());
            if (response.result == Result::ok())
            {
                DBG("SAMPLE");
                request.setUrl("http://127.0.0.1:8080/sample");
                auto response = request.execute();
                DBG("SHUTDOWN");
                request.setUrl("http://127.0.0.1:8080/shutdown");
                response = request.execute();
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
private:

    Request request;
     

};


//caricare file midi 
//caricare la risposta 
//trascinare da e verso la daw