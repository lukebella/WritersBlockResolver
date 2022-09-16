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

//#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]
/*
//==============================================================================
PluginEditor::PluginEditor ()
{
    //[Constructor_pre] You can add your own custom stuff here..

    file = File("C:/Users/lenovo/Documents/JUCE_Projects/WritersBlockResolver/tt-942969/midi_unc_seq.mid");
    //[/Constructor_pre]

    unc_seq_gen.reset (new juce::TextButton ("unc_seq_gen"));
    addAndMakeVisible (unc_seq_gen.get());
    unc_seq_gen->setButtonText (TRANS("Generate"));
    unc_seq_gen->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff59204d));

    unc_seq_gen->setBounds (280, 192, 150, 24);

    midi_unc_file.reset (new juce::Component());
    addAndMakeVisible (midi_unc_file.get());
    midi_unc_file->setName ("midi_unc_file");

    midi_unc_file->setBounds (216, 280, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..



    //
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..

    genUncFileAttachment.reset();

    //[/Destructor_pre]

    unc_seq_gen = nullptr;
    midi_unc_file = nullptr;


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
        int x = 124, y = 44, width = 472, height = 392;
        juce::Colour fillColour = juce::Colour (0xff151411);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = 220, y = 140, width = 276, height = 30;
        juce::String text (TRANS("Generate Unconditional Sequence"));
        juce::Colour fillColour = juce::Colour (0xffe7e7e9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Cascadia Mono", 17.00f, juce::Font::bold | juce::Font::italic).withExtraKerningFactor (0.009f));
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
*/
//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public juce::AudioProcessorEditor" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="124 44 472 392" fill="solid: ff151411" hasStroke="0"/>
    <TEXT pos="220 140 276 30" fill="solid: ffe7e7e9" hasStroke="0" text="Generate Unconditional Sequence"
          fontname="Cascadia Mono" fontsize="17.0" kerning="0.008999999999999999"
          bold="1" italic="1" justification="36" typefaceStyle="Bold Italic"/>
  </BACKGROUND>
  <TEXTBUTTON name="unc_seq_gen" id="875a9e9b309af5e1" memberName="unc_seq_gen"
              virtualName="" explicitFocusOrder="0" pos="280 192 150 24" bgColOff="ff59204d"
              buttonText="Generate" connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <GENERICCOMPONENT name="midi_unc_file" id="889b5b2f7642b757" memberName="midi_unc_file"
                    virtualName="" explicitFocusOrder="0" pos="216 280 150 24" class="juce::Component"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

