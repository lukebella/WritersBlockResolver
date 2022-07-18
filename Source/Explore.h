
#pragma once
#include <JuceHeader.h>

class Explore : public FileDragAndDropTarget
{

public:

    Explore() {}
    ~Explore() {}

    void findTransformer()
    {
        FileChooser explorer("Select Module for Generate a MIDI sequence", File::getSpecialLocation(File::userDesktopDirectory), "*.ckpt");

        if (explorer.browseForFileToOpen())
        {
            File transformer;

            transformer = explorer.getResult();

            //read the file
            AudioFormatReader* reader = formatManager.createReaderFor(transformer);

        }
    }


    // for continuation (dragging from DAW to component)
    bool isInterestedInFileDrag(const StringArray& files) override
    {
        auto file_to_continue = files[0];
        if (file_to_continue.contains("*.mid"))
            {
               return true;
            }
        
        return false;
    }
    
    /* for continuation(dragging from DAW to component)
    void filesDropped(const StringArray& files, int x, int y) override
    {
        if (isInterestedInFileDrag(files))
        {

        }
    }*/


    void seqDragAndDrop(const var& sourceDescription, Component* sourceComponent)
    {
        recipient.startDragging(sourceDescription /*"MIDI generated file"*/, sourceComponent);
    }

private:

    AudioFormatManager formatManager;
    DragAndDropContainer recipient;
    std::unique_ptr<AudioFormatReaderSource> playSource;
    AudioTransportSource transport;

};