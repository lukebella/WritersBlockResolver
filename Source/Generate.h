
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
            nullRequest(response);
        }
    }

    void sample()
    {
        DBG("LOAD termined. Starting SAMPLE...");
        request.setUrl(SAMPLE);
        response = request.execute(SAMPLE);
        DBG("/SAMPLE");
        /*if (response.result.failed())
            nullRequest(response);*/
    }


    void processCond(File& midiFile)
    {

        //CONTINUATION
        DBG(int(transLoaded));
        if (transLoaded)
        {
            DBG(midiFile.getFileName());
            DBG("LOAD termined. Starting CONTINUATION...");
            request.setUrl(CONTINUATION);
            request.attachFile(request.getUrl(), midiFile);
            response = request.execute(CONTINUATION);
            DBG("CONTINUATION");

            if (response.result == Result::ok()) {
                DBG("CONTINUATION termined. Starting SHUTDOWN...");
                closeConn();
            }
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


private:

    Request request;
    Request::Response response;
    bool transLoaded = false;

};


//caricare file midi 
//caricare la risposta 
//trascinare da e verso la daw