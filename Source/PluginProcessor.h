
#pragma once


#include <JuceHeader.h>
#include "Generate.h"
#include "Explore.h"

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



private:

    void parameterChanged(const String& paramID, float newValue) override;

    void startServer(const ArgumentList& args);  //int argc, char* argv[]

    AudioProcessorValueTreeState parameters;

    ConsoleApplication app;

    Generate generate;
    Explore explorer;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WritersBlockResolverAudioProcessor)
};
