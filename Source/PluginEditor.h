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

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
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
    //[/UserVariables]
    WritersBlockResolverAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    std::unique_ptr<SliderAttachment> maxPrimerSecondsAttachment;
    std::unique_ptr<ButtonAttachment> generateSampleAttachment;
    std::unique_ptr<ButtonAttachment> generateContinuationAttachment;
    std::unique_ptr<ButtonAttachment> loadAttachment;

    //==============================================================================
    std::unique_ptr<juce::TextButton> sampleButton;
    std::unique_ptr<juce::TextButton> continueButton;
    std::unique_ptr<juce::Slider> maxPrimSecSlider;
    std::unique_ptr<juce::Component> juce__component;
    std::unique_ptr<juce::Component> juce__component2;
    std::unique_ptr<juce::TextButton> loadButton;
    juce::Image cachedImage__1;
    juce::Image cachedImage__2;
    juce::Image cachedImage__3;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

