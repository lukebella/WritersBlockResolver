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
#include "Explore.h"

//[/Headers]


typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginEditor : public juce::AudioProcessorEditor, 
                     public Button::Listener,
                     public FileDragAndDropTarget,
                     public ComponentListener

{
public:
    //==============================================================================
    PluginEditor(WritersBlockResolverAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint(juce::Graphics& g) override;
    void resized() override;
    void buttonClicked(Button* b) override;

    Image smallCircleImage(
        juce::Colour colour,
        int imageWidth,
        int imageHeight,
        float radius,
        bool clearImage,
        juce::Image::PixelFormat format);

    bool PluginEditor::isInterestedInFileDrag(const StringArray& files) override;
    void PluginEditor::filesDropped(const StringArray& files, int x, int y) override;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]
    WritersBlockResolverAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    std::unique_ptr<SliderAttachment> maxPrimSecAttachment;

    //==============================================================================
    std::unique_ptr<juce::Slider> maxPrimSecSlider;
    std::unique_ptr<juce::Component> juce__component;
    std::unique_ptr<juce::Component> dragAndDropIn;
    std::unique_ptr<juce::ImageButton> loadButton;
    std::unique_ptr<juce::Label> labelLoadButton;
    std::unique_ptr<juce::Label> labelSampleButton;
    std::unique_ptr<juce::Label> labelContButton;
    std::unique_ptr<juce::TextEditor> message;
    std::unique_ptr<juce::TextEditor> serverURL;
    std::unique_ptr<juce::ImageButton> sampleButton;
    std::unique_ptr<juce::ImageButton> cont_button;
    juce::Image cachedImage__1;

    Explore* e;
    bool active = true;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

