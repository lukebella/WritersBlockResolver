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
PluginEditor::PluginEditor(WritersBlockResolverAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), processor(p), valueTreeState(vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    maxPrimSecSlider.reset(new juce::Slider("max_primer_seconds_slider"));
    addAndMakeVisible(maxPrimSecSlider.get());
    maxPrimSecSlider->setRange(1, 120, 0);
    maxPrimSecSlider->setSliderStyle(juce::Slider::LinearHorizontal);
    maxPrimSecSlider->setTextBoxStyle(juce::Slider::TextBoxLeft, false, 80, 20);
    //p.setPrimerSeconds(static_cast<int>(maxPrimSecSlider->getValue()));

    maxPrimSecSlider->setBounds(376, 200, 256, 24);

    juce__component.reset(new juce::Component());
    addAndMakeVisible(juce__component.get());
    juce__component->setName("new component");

    juce__component->setBounds(272, 424, 150, 24);

    dragAndDropIn.reset(new juce::Component());
    addAndMakeVisible(dragAndDropIn.get());
    dragAndDropIn->setName("new component");
    dragAndDropIn->setBounds(480, 256, 150, 24);
    juce::Colour dragAndDropInColour = juce::Colour(0xff15055c);
    if (dragAndDropIn->isMouseOverOrDragging())
        dragAndDropIn->addComponentListener(this);

    loadButton.reset(new juce::ImageButton("Load Button"));
    addAndMakeVisible(loadButton.get());
    loadButton->setButtonText(TRANS("Load"));
    
    labelLoadButton.reset(new juce::Label());
    addAndMakeVisible(labelLoadButton.get());
    labelLoadButton->setText("LOAD", juce::NotificationType::dontSendNotification);
    labelLoadButton->setBounds(364, 70, 44, 12);
    auto offColour = getLookAndFeel().findColour(juce::Slider::ColourIds::textBoxHighlightColourId);
    auto onColour = getLookAndFeel().findColour(juce::Slider::ColourIds::textBoxOutlineColourId);
    float lineThick = 80.0f;

    lineThick *= 7.5f;
    auto onImg = smallCircleImage(onColour, 300, 300, lineThick, false, Image::PixelFormat::RGB);
    auto offImg = smallCircleImage(offColour, 300, 300, lineThick, false, Image::PixelFormat::RGB);

    loadButton->setImages(
        true, false, true, offImg, 1.0f, {}, onImg, 0.333f, {}, onImg, 1.0f, {}, 0.9f);

    loadButton->setBounds(344, 64, 88, 24);
    loadButton->addListener(this);
    //loadButton->onClick = [1,loadButtonget()]() { p.setLoad(true); };


    loadButton->setRadioGroupId(1);
    message.reset(new juce::TextEditor("Message"));
    addAndMakeVisible(message.get());
    message->setMultiLine(false);
    message->setReturnKeyStartsNewLine(false);
    message->setReadOnly(false);
    message->setScrollbarsShown(true);
    message->setCaretVisible(true);
    message->setPopupMenuEnabled(true);
    message->setText(juce::String());
    message->setReadOnly(true);

    message->setBounds(272, 376, 150, 24);

    serverURL.reset(new juce::TextEditor("Server URL"));
    addAndMakeVisible(serverURL.get());
    serverURL->setMultiLine(false);
    serverURL->setReturnKeyStartsNewLine(false);
    serverURL->setReadOnly(false);
    serverURL->setScrollbarsShown(true);
    serverURL->setCaretVisible(true);
    serverURL->setPopupMenuEnabled(true);
    serverURL->setText(juce::String("http://127.0.0.1:8080"));

    serverURL->setBounds(464, 96, 150, 24);
    p.setRemote(serverURL->getText());

    sampleButton.reset(new juce::ImageButton("Sample Button"));
    addAndMakeVisible(sampleButton.get());
    sampleButton->setButtonText(TRANS("Generate"));
    labelSampleButton.reset(new juce::Label());
    addAndMakeVisible(labelLoadButton.get());
    labelSampleButton->setText("SAMPLE", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(labelSampleButton.get());
    labelSampleButton->setBounds(200, 220, 100, 18);
    sampleButton->setImages(
        true, false, true, offImg, 1.0f, {}, onImg, 0.333f, {}, onImg, 1.0f, {}, 0.9f);

    sampleButton->setBounds(160, 216, 150, 24);
    sampleButton->setRadioGroupId(1);
    sampleButton->addListener(this);


    cont_button.reset(new juce::ImageButton("Cont Button"));
    addAndMakeVisible(cont_button.get());
    cont_button->setButtonText(TRANS("Generate"));
    labelContButton.reset(new juce::Label());
    addAndMakeVisible(labelContButton.get());
    labelContButton->setText("CONTINUATION", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(labelContButton.get());
    labelContButton->setBounds(452, 305, 130, 20);
    cont_button->setImages(
        true, false, true, offImg, 1.0f, {}, onImg, 0.333f, {}, onImg, 1.0f, {}, 0.9f);
    cont_button->setBounds(432, 304, 150, 24);
    cont_button->setRadioGroupId(1);
    cont_button->addListener(this);


    //[UserPreSize]
    maxPrimSecAttachment.reset(new SliderAttachment(valueTreeState, NAME_PRIMER_SECONDS, *maxPrimSecSlider));
    /*generateSampleAttachment.reset(new ButtonAttachment(valueTreeState, NAME_UNC_REQUEST, *sampleButton));
    generateContinuationAttachment.reset(new ButtonAttachment(valueTreeState, NAME_COND_REQUEST, *continueButton));
    loadAttachment.reset(new ButtonAttachment(valueTreeState, NAME_SERVER, *loadButton));*/

    //[/UserPreSize]

    setSize(750, 500);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    maxPrimSecAttachment.reset();

    //[/Destructor_pre]


    maxPrimSecSlider = nullptr;
    juce__component = nullptr;
    dragAndDropIn = nullptr;
    loadButton = nullptr;
    message = nullptr;
    serverURL = nullptr;
    sampleButton = nullptr;
    cont_button = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint(juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll(juce::Colour(0xff103446));

    {
        float x = 92.0f, y = 132.0f, width = 264.0f, height = 228.0f;
        juce::Colour fillColour = juce::Colour(0xff15055c);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.fillRoundedRectangle(x, y, width, height, 10.000f);
    }

    {
        float x = 356.0f, y = 132.0f, width = 284.0f, height = 228.0f;
        juce::Colour fillColour = juce::Colour(0xff070f04);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.fillRoundedRectangle(x, y, width, height, 10.000f);
    }

    {
        int x = 116, y = 172, width = 236, height = 44;
        juce::String text(TRANS("Generate a MIDIsequence from zero!"));
        juce::Colour fillColour = juce::Colours::aliceblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.setFont(juce::Font("Yu Gothic UI", 17.00f, juce::Font::plain).withTypefaceStyle("Regular").withExtraKerningFactor(0.035f));
        g.drawText(text, x, y, width, height,
            juce::Justification::centred, true);
    }

    {
        int x = 388, y = 140, width = 236, height = 44;
        juce::String text(TRANS("Continue your MIDISequence!"));
        juce::Colour fillColour = juce::Colours::aliceblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.setFont(juce::Font("Yu Gothic UI", 17.00f, juce::Font::plain).withTypefaceStyle("Regular").withExtraKerningFactor(0.035f));
        g.drawText(text, x, y, width, height,
            juce::Justification::centred, true);
    }

    {
        int x = 420, y = 172, width = 200, height = 30;
        juce::String text(TRANS("Max Primer Seconds"));
        //[UserPaintCustomArguments] Customize the painting arguments here..
    //[/UserPaintCustomArguments]
        g.setTiledImageFill(cachedImage__1,
            0 - 420 + x,
            0 - 172 + y,
            0.5440f);
        g.setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular").withExtraKerningFactor(0.061f));
        g.drawText(text, x, y, width, height,
            juce::Justification::centred, true);
    }

    {
        int x = 444, y = 228, width = 212, height = 36;
        juce::String text(TRANS("Drag Your sequence to continue it:"));
        juce::Colour fillColour = juce::Colour(0xfffbfbfb);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.setFont(juce::Font(12.20f, juce::Font::plain).withTypefaceStyle("Regular"));
        g.drawText(text, x, y, width, height,
            juce::Justification::centred, true);
    }

    {
        float x = 92.0f, y = 52.0f, width = 544.0f, height = 76.0f;
        juce::Colour fillColour = juce::Colour(0xff2aa0a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.fillRoundedRectangle(x, y, width, height, 10.000f);
    }

    {
        int x = 100, y = 60, width = 236, height = 30;
        juce::String text(TRANS("First, you need to load the model:"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
        g.drawText(text, x, y, width, height,
            juce::Justification::centred, true);
    }

    {
        float x = 92.0f, y = 364.0f, width = 548.0f, height = 92.0f;
        juce::Colour fillColour = juce::Colour(0xff43a52a);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.fillRoundedRectangle(x, y, width, height, 10.000f);
    }

    {
        int x = 132, y = 372, width = 200, height = 30;
        juce::String text(TRANS("Message:"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
        g.drawText(text, x, y, width, height,
            juce::Justification::centred, true);
    }

    {
        int x = 324, y = 92, width = 200, height = 30;
        juce::String text(TRANS("Server URL:"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
        g.drawText(text, x, y, width, height,
            juce::Justification::centred, true);
    }

    {
        int x = 100, y = 420, width = 200, height = 30;
        juce::String text(TRANS("MIDI Generated File:"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.setFont(juce::Font(15.00f, juce::Font::plain).withTypefaceStyle("Regular"));
        g.drawText(text, x, y, width, height,
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

juce::Image PluginEditor::smallCircleImage(
    juce::Colour colour,
    int imageWidth,
    int imageHeight,
    float radius,
    bool clearImage,
    juce::Image::PixelFormat format)
{
    juce::Image img(format, imageWidth, imageHeight, clearImage);
    juce::Graphics g(img);

    g.setColour(colour);
    g.fillEllipse(
        imageWidth / 2.0f - radius,
        imageHeight / 2.0f - radius,
        2 * radius,
        2 * radius);

    return img;
}

void PluginEditor::buttonClicked(Button* b) 
{
    if (b == loadButton.get())
    {
        DBG("LOAD");
        processor.setLoad(true);
    }
    if (b == sampleButton.get())
    {
        processor.setSample(true);
    }
    if (b == cont_button.get())
    {
        processor.setCont(true);
    }
}

bool PluginEditor::isInterestedInFileDrag(const StringArray& files)  
{
    auto file_to_continue = files[0];
    if (file_to_continue.contains("*.mid"))
    {
        return true;
    }

    return false;
}

//for continuation(dragging from DAW to component)
void PluginEditor::filesDropped(const StringArray& files, int x, int y)
{
    if (isInterestedInFileDrag(files))
    {
        processor.setDragAndDropPath(files[0]);
    }
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
                 fixedSize="0" initialWidth="750" initialHeight="500">
  <BACKGROUND backgroundColour="ff103446">
    <ROUNDRECT pos="92 132 264 228" cornerSize="10.0" fill="solid: ff15055c"
               hasStroke="0"/>
    <ROUNDRECT pos="356 132 284 228" cornerSize="10.0" fill="solid: ff070f04"
               hasStroke="0"/>
    <TEXT pos="116 172 236 44" fill="solid: fff0f8ff" hasStroke="0" text="Generate a MIDIsequence from zero!"
          fontname="Yu Gothic UI" fontsize="17.0" kerning="0.035" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="388 140 236 44" fill="solid: fff0f8ff" hasStroke="0" text="Continue your MIDISequence!"
          fontname="Yu Gothic UI" fontsize="17.0" kerning="0.035" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="420 172 200 30" fill="image: , 0.544, 0 0" hasStroke="0"
          text="Max Primer Seconds" fontname="Default font" fontsize="15.0"
          kerning="0.061" bold="0" italic="0" justification="36"/>
    <TEXT pos="444 228 212 36" fill="solid: fffbfbfb" hasStroke="0" text="Drag Your sequence to continue it:"
          fontname="Default font" fontsize="12.2" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <ROUNDRECT pos="92 52 544 76" cornerSize="10.0" fill="solid: ff2aa0a5" hasStroke="0"/>
    <TEXT pos="100 60 236 30" fill="solid: ff000000" hasStroke="0" text="First, you need to load the model:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <ROUNDRECT pos="92 364 548 92" cornerSize="10.0" fill="solid: ff43a52a"
               hasStroke="0"/>
    <TEXT pos="132 372 200 30" fill="solid: ff000000" hasStroke="0" text="Message:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="324 92 200 30" fill="solid: ff000000" hasStroke="0" text="Server URL:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="100 420 200 30" fill="solid: ff000000" hasStroke="0" text="MIDI Generated File:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
  </BACKGROUND>
  <SLIDER name="max_primer_seconds_slider" id="7f8579cee32a9a22" memberName="maxPrimSecSlider"
          virtualName="" explicitFocusOrder="0" pos="376 200 256 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <GENERICCOMPONENT name="new component" id="64a0133d89220b70" memberName="juce__component"
                    virtualName="" explicitFocusOrder="0" pos="272 424 150 24" class="juce::Component"
                    params=""/>
  <GENERICCOMPONENT name="new component" id="d0de82a323bbca2e" memberName="juce__component2"
                    virtualName="" explicitFocusOrder="0" pos="480 256 150 24" class="juce::Component"
                    params=""/>
  <IMAGEBUTTON name="Load Button" id="fdfb421ea19b70a9" memberName="loadButton"
               virtualName="" explicitFocusOrder="0" pos="344 64 88 24" buttonText="Load"
               connectedEdges="0" needsCallback="0" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1.0" colourNormal="0" resourceOver=""
               opacityOver="1.0" colourOver="0" resourceDown="" opacityDown="1.0"
               colourDown="0"/>
  <TEXTEDITOR name="Message" id="11b147f69063570b" memberName="message" virtualName=""
              explicitFocusOrder="0" pos="272 376 150 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="Server URL" id="ee1f8e761be0ffe3" memberName="serverURL"
              virtualName="" explicitFocusOrder="0" pos="464 96 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <IMAGEBUTTON name="Sample Button" id="72b39d3202d2f7b0" memberName="sampleButton"
               virtualName="" explicitFocusOrder="0" pos="160 216 150 24" buttonText="Generate"
               connectedEdges="0" needsCallback="0" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1.0" colourNormal="0" resourceOver=""
               opacityOver="1.0" colourOver="0" resourceDown="" opacityDown="1.0"
               colourDown="0"/>
  <IMAGEBUTTON name="Cont Button" id="c4b479cc75d89064" memberName="contButton"
               virtualName="" explicitFocusOrder="0" pos="432 304 150 24" buttonText="Generate"
               connectedEdges="0" needsCallback="0" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1.0" colourNormal="0" resourceOver=""
               opacityOver="1.0" colourOver="0" resourceDown="" opacityDown="1.0"
               colourDown="0"/>
  <IMAGEBUTTON name="Cont Button" id="fef61c3239b80c23" memberName="cont_button"
               virtualName="" explicitFocusOrder="0" pos="432 304 150 24" buttonText="Generate"
               connectedEdges="0" needsCallback="0" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1.0" colourNormal="0" resourceOver=""
               opacityOver="1.0" colourOver="0" resourceDown="" opacityDown="1.0"
               colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

