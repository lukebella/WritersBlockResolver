//con GUI non parte la generazione(com'è possibile?)
    //riuscire a creare un componente in cui compaia la file http response e trascinarlo nella daw

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"
//==============================================================================
WritersBlockResolverAudioProcessor::WritersBlockResolverAudioProcessor():
    parameters(*this, nullptr, "WBRParameters", {

        std::make_unique<AudioParameterInt>(NAME_PRIMER_SECONDS, "Max Primer Seconds", 1, 120, PRIMER_SECONDS),
        })
{  

    parameters.addParameterListener(NAME_PRIMER_SECONDS, this);
}

WritersBlockResolverAudioProcessor::~WritersBlockResolverAudioProcessor()
{
}

//==============================================================================
const juce::String WritersBlockResolverAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WritersBlockResolverAudioProcessor::acceptsMidi() const
{
    return true;
}

bool WritersBlockResolverAudioProcessor::producesMidi() const
{
    return false;
}

bool WritersBlockResolverAudioProcessor::isMidiEffect() const
{
    return false;
}

double WritersBlockResolverAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WritersBlockResolverAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WritersBlockResolverAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WritersBlockResolverAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String WritersBlockResolverAudioProcessor::getProgramName(int index)
{
    return {};
}

void WritersBlockResolverAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void WritersBlockResolverAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
}

void WritersBlockResolverAudioProcessor::releaseResources()
{
   
}
void WritersBlockResolverAudioProcessor::setRemote(String newRemote)
{
    remote = newRemote;
}

void WritersBlockResolverAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
}

//==============================================================================
bool WritersBlockResolverAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WritersBlockResolverAudioProcessor::createEditor()
{
    return new PluginEditor(*this, parameters);

}

//==============================================================================
void WritersBlockResolverAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void WritersBlockResolverAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}

void WritersBlockResolverAudioProcessor::parameterChanged(const String& paramID, float newValue)
{      

   if (paramID == NAME_PRIMER_SECONDS)
   {
       generate.setPrimerSeconds(int(newValue));
   }
     
}

void WritersBlockResolverAudioProcessor::setLoad(bool value)
{
    generate.setURL(remote);
    if (value)
      generate.openAndLoad();
}
void WritersBlockResolverAudioProcessor::setSample(bool value)
{
    generate.setURL(remote);
    if (value)
        generate.unconditional();
}
void WritersBlockResolverAudioProcessor::setCont(bool value)
{
    generate.setURL(remote);
    if (value)
        generate.processCond(dragAndDropPath);
}

void WritersBlockResolverAudioProcessor::setDragAndDropPath(String newPath)
{
    dragAndDropPath = newPath;
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WritersBlockResolverAudioProcessor();
}
