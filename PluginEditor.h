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
#include "ButtonEvent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginEditor : public juce::AudioProcessorEditor
{
public:
    //==============================================================================
    PluginEditor(WritersBlockResolverAudioProcessor& p);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint(juce::Graphics& g) override;
    void resized() override;


    Image smallCircleImage(
        juce::Colour colour,
        int imageWidth,
        int imageHeight,
        float radius,
        bool clearImage,
        juce::Image::PixelFormat format);


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]
    WritersBlockResolverAudioProcessor& processor;

    //==============================================================================
    std::unique_ptr<juce::Slider> maxPrimSecSlider;
    std::unique_ptr<juce::Component> juce__component;
    std::unique_ptr<juce::Component> juce__component2;
    std::unique_ptr<juce::ImageButton> loadButton;
    std::unique_ptr<juce::TextEditor> message;
    std::unique_ptr<juce::TextEditor> serverURL;
    std::unique_ptr<juce::ImageButton> sampleButton;
    std::unique_ptr<juce::ImageButton> contButton;
    std::unique_ptr<juce::ImageButton> cont_button;
    juce::Image cachedImage__1;

    ButtonEvent be;
    bool turnNext = true;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

