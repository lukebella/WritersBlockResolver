
#pragma once
#include <JuceHeader.h>
#include "Generate.h"
#include "Thread.h"

//==============================================================================
/**
*/
class WritersBlockResolverAudioProcessor : public juce::AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    WritersBlockResolverAudioProcessor();
    ~WritersBlockResolverAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    void setLoad(bool value);
    void setSample(bool value);
    void setCont(bool value);

    void setRemote(String newRemote);
    
    void setDragAndDropPath(String path);

private:

    void parameterChanged(const String& paramID, float newValue) override;
    AudioProcessorValueTreeState parameters;
    Generate generate;
    //bool l = false;
    String dragAndDropPath = "";
    String remote = "";
    //String messageToEditor = "";
    //LoadThread loader;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WritersBlockResolverAudioProcessor)
};

