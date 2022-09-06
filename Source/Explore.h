
#pragma once
#include <JuceHeader.h>
#include "Generate.h"

class Explore : public FileDragAndDropTarget
{

public:

    Explore() {}
    ~Explore() {}

    



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
    
    //for continuation(dragging from DAW to component)
    void filesDropped(const StringArray& files, int x, int y) override
    {
        if (isInterestedInFileDrag(files))
        {

        }
    }


    void seqDragAndDrop(const var& sourceDescription, Component* sourceComponent)
    {
        recipient.startDragging(sourceDescription /*"MIDI generated file"*/, sourceComponent);
    }

private:

    DragAndDropContainer recipient;

};