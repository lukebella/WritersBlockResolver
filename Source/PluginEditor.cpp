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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"
#include "Parameters.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (WritersBlockResolverAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), processor(p), valueTreeState(vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    sampleButton.reset (new juce::TextButton ("sample_button"));
    addAndMakeVisible (sampleButton.get());
    sampleButton->setButtonText (TRANS("Generate"));
    sampleButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff78850e));

    sampleButton->setBounds (160, 224, 150, 24);

    continueButton.reset (new juce::TextButton ("continue_button"));
    addAndMakeVisible (continueButton.get());
    continueButton->setButtonText (TRANS("Continue"));
    continueButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff6a1156));

    continueButton->setBounds (480, 304, 150, 24);

    maxPrimSecSlider.reset (new juce::Slider ("max_primer_seconds_slider"));
    addAndMakeVisible (maxPrimSecSlider.get());
    maxPrimSecSlider->setRange (0, 10, 0);
    maxPrimSecSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    maxPrimSecSlider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);

    maxPrimSecSlider->setBounds (376, 200, 256, 24);

    juce__component.reset (new juce::Component());
    addAndMakeVisible (juce__component.get());
    juce__component->setName ("new component");

    juce__component->setBounds (288, 320, 150, 24);

    juce__component2.reset (new juce::Component());
    addAndMakeVisible (juce__component2.get());
    juce__component2->setName ("new component");

    juce__component2->setBounds (480, 256, 150, 24);

    loadButton.reset (new juce::TextButton ("Load button"));
    addAndMakeVisible (loadButton.get());
    loadButton->setButtonText (TRANS("Load"));
    loadButton->setColour (juce::TextButton::buttonColourId, juce::Colour (0xffb50202));

    loadButton->setBounds (384, 96, 144, 24);


    //[UserPreSize]
    maxPrimerSecondsAttachment.reset(new SliderAttachment(valueTreeState, NAME_PRIMER_SECONDS, *maxPrimSecSlider));
    generateSampleAttachment.reset(new ButtonAttachment(valueTreeState, NAME_UNC_REQUEST, *sampleButton));
    generateContinuationAttachment.reset(new ButtonAttachment(valueTreeState, NAME_COND_REQUEST, *continueButton));
    loadAttachment.reset(new ButtonAttachment(valueTreeState, NAME_SERVER, *loadButton));

    //[/UserPreSize]

    setSize (750, 500);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]
    maxPrimerSecondsAttachment.reset();
    generateSampleAttachment.reset();
    generateContinuationAttachment.reset();
    loadAttachment.reset();

    sampleButton = nullptr;
    continueButton = nullptr;
    maxPrimSecSlider = nullptr;
    juce__component = nullptr;
    juce__component2 = nullptr;
    loadButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff103446));

    {
        float x = 92.0f, y = 132.0f, width = 264.0f, height = 252.0f;
        juce::Colour fillColour = juce::Colour (0xff15055c);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        float x = 356.0f, y = 132.0f, width = 284.0f, height = 252.0f;
        juce::Colour fillColour = juce::Colour (0xff070f04);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        int x = 116, y = 172, width = 236, height = 44;
        juce::String text (TRANS("Generate a MIDIsequence from zero!"));
            //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setTiledImageFill (cachedImage__1,
                         0 - 116 + x,
                         0 - 172 + y,
                         1.0000f);
        g.setFont (juce::Font ("Yu Gothic UI", 17.00f, juce::Font::plain).withTypefaceStyle ("Regular").withExtraKerningFactor (0.035f));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 388, y = 140, width = 236, height = 44;
        juce::String text (TRANS("Continue your MIDISequence!"));
            //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setTiledImageFill (cachedImage__2,
                         0 - 388 + x,
                         0 - 140 + y,
                         1.0000f);
        g.setFont (juce::Font ("Yu Gothic UI", 17.00f, juce::Font::plain).withTypefaceStyle ("Regular").withExtraKerningFactor (0.035f));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 420, y = 172, width = 200, height = 30;
        juce::String text (TRANS("Max Primer Seconds"));
            //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setTiledImageFill (cachedImage__3,
                         0 - 420 + x,
                         0 - 172 + y,
                         0.5440f);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular").withExtraKerningFactor (0.061f));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 268, y = 292, width = 200, height = 30;
        juce::String text (TRANS("MIDI File generated"));
        juce::Colour fillColour = juce::Colours::antiquewhite;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 444, y = 228, width = 212, height = 36;
        juce::String text (TRANS("Drag Your sequence to continue it:"));
        juce::Colour fillColour = juce::Colour (0xfffbfbfb);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.20f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        float x = 92.0f, y = 92.0f, width = 544.0f, height = 40.0f;
        juce::Colour fillColour = juce::Colour (0xff2aa0a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        int x = 100, y = 92, width = 236, height = 30;
        juce::String text (TRANS("First, you need to load the model:"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public juce::AudioProcessorEditor" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="750" initialHeight="500">
  <BACKGROUND backgroundColour="ff103446">
    <ROUNDRECT pos="92 132 264 252" cornerSize="10.0" fill="solid: ff15055c"
               hasStroke="0"/>
    <ROUNDRECT pos="356 132 284 252" cornerSize="10.0" fill="solid: ff070f04"
               hasStroke="0"/>
    <TEXT pos="116 172 236 44" fill="image: , 1, 0 0" hasStroke="0" text="Generate a MIDIsequence from zero!"
          fontname="Yu Gothic UI" fontsize="17.0" kerning="0.035" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="388 140 236 44" fill="image: , 1, 0 0" hasStroke="0" text="Continue your MIDISequence!"
          fontname="Yu Gothic UI" fontsize="17.0" kerning="0.035" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="420 172 200 30" fill="image: , 0.544, 0 0" hasStroke="0"
          text="Max Primer Seconds" fontname="Default font" fontsize="15.0"
          kerning="0.061" bold="0" italic="0" justification="36"/>
    <TEXT pos="268 292 200 30" fill="solid: fffaebd7" hasStroke="0" text="MIDI File generated"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="444 228 212 36" fill="solid: fffbfbfb" hasStroke="0" text="Drag Your sequence to continue it:"
          fontname="Default font" fontsize="12.2" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <ROUNDRECT pos="92 92 544 40" cornerSize="10.0" fill="solid: ff2aa0a5" hasStroke="0"/>
    <TEXT pos="100 92 236 30" fill="solid: ff000000" hasStroke="0" text="First, you need to load the model:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
  </BACKGROUND>
  <TEXTBUTTON name="sample_button" id="97374ecf0bb81fa0" memberName="sampleButton"
              virtualName="" explicitFocusOrder="0" pos="160 224 150 24" bgColOff="ff78850e"
              buttonText="Generate" connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="continue_button" id="82b68247f459479e" memberName="continueButton"
              virtualName="" explicitFocusOrder="0" pos="480 304 150 24" bgColOff="ff6a1156"
              buttonText="Continue" connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <SLIDER name="max_primer_seconds_slider" id="7f8579cee32a9a22" memberName="maxPrimSecSlider"
          virtualName="" explicitFocusOrder="0" pos="376 200 256 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <GENERICCOMPONENT name="new component" id="64a0133d89220b70" memberName="juce__component"
                    virtualName="" explicitFocusOrder="0" pos="288 320 150 24" class="juce::Component"
                    params=""/>
  <GENERICCOMPONENT name="new component" id="d0de82a323bbca2e" memberName="juce__component2"
                    virtualName="" explicitFocusOrder="0" pos="480 256 150 24" class="juce::Component"
                    params=""/>
  <TEXTBUTTON name="Load button" id="cd580f718e883225" memberName="loadButton"
              virtualName="" explicitFocusOrder="0" pos="384 96 144 24" bgColOff="ffb50202"
              buttonText="Load" connectedEdges="0" needsCallback="0" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

