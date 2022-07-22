/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"

//[/Headers]


typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginEditor  : public juce::AudioProcessorEditor
{
public:
    //==============================================================================
    PluginEditor (WritersBlockResolverAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    WritersBlockResolverAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    std::unique_ptr<ButtonAttachment> genUncFileAttachment;

    DragAndDropContainer dad;

    //[/UserVariables]

    File file;

    //==============================================================================
    std::unique_ptr<juce::TextButton> unc_seq_gen;
    std::unique_ptr<juce::Component> midi_unc_file;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

class MidiDrag : public Component
{
public:
    void paint(Graphics& g) override
    {
        g.fillAll(Colours::blue);
        g.setColour(Colours::red);
        g.fillRect(0, 0, 25, 25);
    }

    void mouseDown(const MouseEvent& e) override
    {
        std::cout << "TargetSource::mouseDown():" << std::endl;
    }

    void mouseDrag(const MouseEvent& e) override
    {
        std::cout << "TargetSource::mouseDrag():" << getX() << " " << getY() << " " << e.x << " " << e.y << std::endl;
        juce::DragAndDropContainer* dragC =
            juce::DragAndDropContainer::findParentDragContainerFor(this);
        if (!dragC) {
            std::cout << "TargetSource::mouseDrag(): can't find parent drag container" << std::endl;
        }
        else {
            if (!dragC->isDragAndDropActive())
            {
                dragC->startDragging("TargetSource", this);
            }
        }
    }
};
//[EndFile] You can add extra defines here...
//[/EndFile]

/*class DragAndDropDemo  : public Component,
                         public DragAndDropContainer
{
public:
    DragAndDropDemo()
    {
        setName ("Drag-and-Drop");

        sourceListBox.setModel (&sourceModel);
        sourceListBox.setMultipleSelectionEnabled (true);

        addAndMakeVisible (sourceListBox);
        addAndMakeVisible (target);
    }

    void resized() override
    {
        auto r = getLocalBounds().reduced (8);

        sourceListBox.setBounds (r.withSize (250, 180));
        target       .setBounds (r.removeFromBottom (150).removeFromRight (250));
    }

private:
    //==============================================================================
    struct SourceItemListboxContents  : public ListBoxModel
    {
        // The following methods implement the necessary virtual functions from ListBoxModel,
        // telling the listbox how many rows there are, painting them, etc.
        int getNumRows() override
        {
            return 30;
        }

        void paintListBoxItem (int rowNumber, Graphics& g,
                               int width, int height, bool rowIsSelected) override
        {
            if (rowIsSelected)
                g.fillAll (Colours::lightblue);

            g.setColour (LookAndFeel::getDefaultLookAndFeel().findColour (Label::textColourId));
            g.setFont ((float) height * 0.7f);

            g.drawText ("Draggable Thing #" + String (rowNumber + 1),
                        5, 0, width, height,
                        Justification::centredLeft, true);
        }

        var getDragSourceDescription (const SparseSet<int>& selectedRows) override
        {
            // for our drag description, we'll just make a comma-separated list of the selected row
            // numbers - this will be picked up by the drag target and displayed in its box.
            StringArray rows;

            for (int i = 0; i < selectedRows.size(); ++i)
                rows.add (String (selectedRows[i] + 1));

            return rows.joinIntoString (", ");
        }
    };

    //==============================================================================
    // and this is a component that can have things dropped onto it..
    class DragAndDropDemoTarget : public Component,
                                  public DragAndDropTarget,
                                  public FileDragAndDropTarget,
                                  public TextDragAndDropTarget
    {
    public:
        DragAndDropDemoTarget()    {}

        void paint (Graphics& g) override
        {
            g.fillAll (Colours::green.withAlpha (0.2f));

            // draw a red line around the comp if the user's currently dragging something over it..
            if (somethingIsBeingDraggedOver)
            {
                g.setColour (Colours::red);
                g.drawRect (getLocalBounds(), 3);
            }

            g.setColour (getLookAndFeel().findColour (Label::textColourId));
            g.setFont (14.0f);
            g.drawFittedText (message, getLocalBounds().reduced (10, 0), Justification::centred, 4);
        }

        //==============================================================================
        // These methods implement the DragAndDropTarget interface, and allow our component
        // to accept drag-and-drop of objects from other JUCE components..

        bool isInterestedInDragSource (const SourceDetails& /*dragSourceDetails) override
        {
        // normally you'd check the sourceDescription value to see if it's the
        // sort of object that you're interested in before returning true, but for
        // the demo, we'll say yes to anything..
        return true;
        }

        void itemDragEnter(const SourceDetails& /*dragSourceDetails) override
        {
            somethingIsBeingDraggedOver = true;
            repaint();
        }

        void itemDragMove(const SourceDetails& /*dragSourceDetails) override
        {
        }

        void itemDragExit(const SourceDetails& /*dragSourceDetails) override
        {
            somethingIsBeingDraggedOver = false;
            repaint();
        }

        void itemDropped(const SourceDetails& dragSourceDetails) override
        {
            message = "Items dropped: " + dragSourceDetails.description.toString();

            somethingIsBeingDraggedOver = false;
            repaint();
        }

        //==============================================================================
        // These methods implement the FileDragAndDropTarget interface, and allow our component
        // to accept drag-and-drop of files..

        bool isInterestedInFileDrag(const StringArray& /*files) override
        {
            // normally you'd check these files to see if they're something that you're
            // interested in before returning true, but for the demo, we'll say yes to anything..
            return true;
        }*/

       /* void fileDragEnter(const StringArray& /*files, int x, int y) override
        {
            somethingIsBeingDraggedOver = true;
            repaint();
        }
        ..... demo runner
       */
        