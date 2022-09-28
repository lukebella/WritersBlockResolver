#include "Generate.h"

Generate::Generate() {}
Generate::~Generate() {}


void Generate::unconditional()
{
    if (transLoaded)
    {
        DBG("Starting sample");
        cond = true;
        pathToSave = whereToSave();
        DBG("LOAD termined. Starting SAMPLE...");
        File file;
        file = File(pathToSave).getChildFile("continuation.mid");
        if (!cond)
        {
            return;
        }
        else
        {
            setURL("http://127.0.0.1:8080");
            url = url.withNewSubPath(SAMPLE);
            requestForDownload(url, file);
            DBG("/SAMPLE");
        }
    }

    else
    {
        DBG("You need to load the module: click on Load Model");
        // nullRequest(response);
    }
}
 


void Generate::processCond(String dragAndDropPath)
{
        
    //CONTINUATION
    if (transLoaded)
    {
        cond = true;
        pathToSave = whereToSave();
        if (dragAndDropPath.contains(""))
            midiFile = findMidi();
        else
            midiFile = dragAndDropPath;
        File file;
        file= File(pathToSave).getChildFile("continuation.mid");
        if (!cond)
        {
            return;
        }
        else
        {
            setURL("http://127.0.0.1:8080");
            url = url.withNewSubPath(CONTINUATION);
            DBG(midiFile.getFileName());
            MemoryBlock mb = MemoryBlock();
            midiFile.loadFileAsData(mb);  
            String s = Base64::toBase64(mb.getData(), mb.getSize());
            DBG("Sending file: " << s);
            url = url.withParameter("myfile", s);
            DBG("size: " << mb.getSize());
            url = url.withParameter("max_primer_seconds", String(maxPrimerSeconds));
            DBG(url.toString(true));
          
            requestForDownload(url, file);

            DBG("/CONTINUATION");
        }
    }
    else
        DBG("You need to load the module: click on Load Model");
}






void Generate::requestForDownload(URL& url, File& file) {

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

        if (downloadptr->statusCode() == 200)
        {
            DBG("Downloaded ok\n");
            DBG(downloadptr->getTotalLength());
        }
        else
        {

            DBG("Download failed: " << downloadptr->statusCode());
        }
    }
    else
    {
        DBG("No download pointer");
    }

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
        setURL("http://127.0.0.1:8080");
        url = url.withNewSubPath(LOAD);
        DBG(url.getDomain());
        DBG("Starting LOAD");
        url = url.readEntireTextStream();
        setTransLoaded(true);
    }
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


void Generate::setTransLoaded(bool newTrans)
{
    transLoaded = newTrans;
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

URL Generate::getUrl()
{
    return url;
}

void Generate::setURL(String newURL)
{
    url = URL(newURL);
}


//caricare file midi 
//caricare la risposta 
//trascinare da e verso la daw