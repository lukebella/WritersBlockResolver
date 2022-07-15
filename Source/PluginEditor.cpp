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


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    unc_seq_generate.reset (new juce::TextButton ("unc_seq_button"));
    addAndMakeVisible (unc_seq_generate.get());
    unc_seq_generate->setButtonText (TRANS("Generate"));
    unc_seq_generate->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff320929));

    unc_seq_generate->setBounds (152, 192, 150, 24);

    unc_seq_file.reset (new juce::Component::DragAndDropContainer());
    addAndMakeVisible (unc_seq_file.get());
    unc_seq_file->setName ("unc_seq_file");

    unc_seq_file->setBounds (152, 272, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    unc_seq_generate = nullptr;
    unc_seq_file = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    {
        float x = 348.0f, y = 116.0f, width = 228.0f, height = 220.0f;
        juce::Colour fillColour = juce::Colour (0xffa52a31);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        float x = 112.0f, y = 116.0f, width = 228.0f, height = 220.0f;
        juce::Colour fillColour = juce::Colour (0xffa52aa4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        int x = 100, y = 116, width = 252, height = 68;
        juce::String text (TRANS("Generate Unconditional Sequence"));
        juce::Colour fillColour = juce::Colour (0xff140e0e);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.90f, juce::Font::plain).withTypefaceStyle ("Regular").withExtraKerningFactor (-0.018f));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 364, y = 132, width = 200, height = 30;
        juce::String text (TRANS("Generate Continuation"));
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
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44">
    <ROUNDRECT pos="348 116 228 220" cornerSize="10.0" fill="solid: ffa52a31"
               hasStroke="0"/>
    <ROUNDRECT pos="112 116 228 220" cornerSize="10.0" fill="solid: ffa52aa4"
               hasStroke="0"/>
    <TEXT pos="100 116 252 68" fill="solid: ff140e0e" hasStroke="0" text="Generate Unconditional Sequence"
          fontname="Default font" fontsize="15.9" kerning="-0.018" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="364 132 200 30" fill="solid: ff000000" hasStroke="0" text="Generate Continuation"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
  </BACKGROUND>
  <TEXTBUTTON name="unc_seq_button" id="99ae15c226300914" memberName="unc_seq_generate"
              virtualName="" explicitFocusOrder="0" pos="152 192 150 24" bgColOff="ff320929"
              buttonText="Generate" connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <GENERICCOMPONENT name="unc_seq_file" id="9119c621220e21e0" memberName="unc_seq_file"
                    virtualName="" explicitFocusOrder="0" pos="152 272 150 24" class="juce::Component::DragAndDropContainer"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

