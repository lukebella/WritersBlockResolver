#include "Generate.h"

Generate::Generate() {}
Generate::~Generate() {}


void Generate::unconditional()
{
    if (transLoaded)
    {

        DBG("Starting sample");
        sample();
    }

    else
    {
        DBG("You need to load the module: click on Load Model");
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


void Generate::processCond()
{
        
    //CONTINUATION
    if (transLoaded)
    {
        cond = true;
        pathToSave = whereToSave();
        midiFile = findMidi();
        File file;
        file= File(pathToSave).getChildFile("continuation.mid");
        if (!cond)
        {
            return;
        }
        else
        {
            auto url = URL("http://127.0.0.1:8080");

            url = url.withNewSubPath(CONTINUATION);
            DBG(midiFile.getFileName());
            //DBG("LOAD termined. Starting CONTINUATION...");
            //request.setUrl(CONTINUATION);
            //request.attachFile(request.getUrl(), midiFile);
            MemoryBlock mb = MemoryBlock();

            midiFile.loadFileAsData(mb);
            
            String s = Base64::toBase64(mb.getData(), mb.getSize());
            DBG("Sending file: " << s);

            url = url.withParameter("myfile", s);
            DBG("size: " << mb.getSize());
            url = url.withParameter("max_primer_seconds", String(maxPrimerSeconds));
            DBG(url.toString(true));

            //response = request.execute(CONTINUATION, pathToSave);
            //String risposta = url.readEntireTextStream(true);
            
            URL::DownloadTaskOptions options;
            options.withUsePost(true);
            std::unique_ptr<URL::DownloadTask> downloadptr(downloading(url, file, options));
            if (downloadptr)
            {
                while (downloadptr->isFinished() == false)
                {
                    DBG("Downloading...\n");
                    Thread::sleep(500);
                }

                if (downloadptr->statusCode()==200)
                {
                    DBG("Downloaded ok\n");
                    DBG(downloadptr->getTotalLength());
                }
                else
                {

                    DBG("Download failed: "<<downloadptr->statusCode());
                }
            }
            else
            {
                DBG("No download pointer");
            }

            DBG("/CONTINUATION");
        }
    }
    else
        DBG("You need to load the module: click on Load Model");
}


void Generate::nullRequest(Request::Response response) {

    DBG("Richiesta non eseguita");
    closeConn();
}

std::unique_ptr<URL::DownloadTask> Generate::downloading(const URL& urlToUse,
    const File& targetFileToUse,
    const URL::DownloadTaskOptions& options)
{
    const size_t bufferSize = 0x8000;
    targetFileToUse.deleteFile();
    options.withUsePost(true);

    if (auto outputStream = targetFileToUse.createOutputStream(bufferSize))
    {
        auto stream = std::make_unique<WebInputStream>(urlToUse, true);// options.usePost);
        stream->withExtraHeaders(options.extraHeaders);
        stream->withConnectionTimeout(CONNECTION_TIMEOUT);

        if (stream->connect(nullptr))
            return std::make_unique < FallbackDownloadTask >(std::move(outputStream),
                bufferSize,
                std::move(stream),
                options.listener);
    }
    return nullptr;
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
    else
    {
        //Threadshouldexit?
        cond = false;
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
    if (cond)
    {
        FileChooser explorer("Select a MIDI file to continue", File::getSpecialLocation(File::userHomeDirectory), "*.mid");

        if (explorer.browseForFileToOpen())
        {
            File midifile(explorer.getResult());
            DBG(midifile.getFileName());
            //generate.setTransLoaded(true);
            return midifile;

        }
        else
        {
            //threadShouldexit?
            cond = false;
        }
    }
}

void Generate::setPrimerSeconds(int newValue) {
    maxPrimerSeconds = newValue;
}

//caricare file midi 
//caricare la risposta 
//trascinare da e verso la daw