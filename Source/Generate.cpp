#include "Generate.h"

Generate::Generate() {}
Generate::~Generate() {}


void Generate::unconditional(float newValue)
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

void Generate::sample()//const String& pathToSave)
{

    DBG("LOAD termined. Starting SAMPLE...");
    request.setUrl(SAMPLE);
    pathToSave = whereToSave();
    response = request.execute(SAMPLE, pathToSave);
    DBG("/SAMPLE");
    /*if (response.result.failed())
        nullRequest(response);*/
}


void Generate::processCond(float newValue)
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


void Generate::nullRequest(Request::Response response) {

    DBG("Richiesta non eseguita");
    closeConn();
}


void Generate::openAndLoad()
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


void Generate::closeConn()
{
    request.setUrl(SHUTDOWN);
    auto nullResponse = request.execute();
    setTransLoaded(false);
    DBG("SHUTDOWN");
}
   

String Generate::whereToSave()
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

void Generate::setTransLoaded(bool newTrans)
{
    transLoaded = newTrans;
}

void Generate::initialize(const String& domain) {
    request.init(domain);
    //?ckpt_path='C:/Users/lenovo/Documents/JUCE_Projects/WritersBlockResolver/Transformer/unconditional_model_16.ckpt'
}

File Generate::findMidi()
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

void Generate::setPrimerSeconds(int newValue) {
    maxPrimerSeconds = newValue;
}

//caricare file midi 
//caricare la risposta 
//trascinare da e verso la daw