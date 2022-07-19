
#include "PluginProcessor.h"
#include "Parameters.h"
//==============================================================================
WritersBlockResolverAudioProcessor::WritersBlockResolverAudioProcessor() :
    parameters(*this, nullptr, "WBR_parameters", {
        std::make_unique<AudioParameterBool>(NAME_REQUEST, "Generate Unconditional Sequence", DEFAULT_ACTIVE),
        std::make_unique<AudioParameterBool>(NAME_EXPLORE, "Find your module", DEFAULT_ACTIVE),
        })
{
  
    parameters.addParameterListener(NAME_REQUEST, this);

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
    //startServer(args);
    generate.initialize();
}

void WritersBlockResolverAudioProcessor::releaseResources()
{
}


void WritersBlockResolverAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
}

//==============================================================================
bool WritersBlockResolverAudioProcessor::hasEditor() const
{
    return false; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WritersBlockResolverAudioProcessor::createEditor()
{
    //return new WritersBlockResolverAudioEditor(*this, parameters);
    return nullptr;

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
   

   if (paramID == NAME_REQUEST)
      generate.process(newValue);

   /*if (paramID == NAME_EXPLORE)
       explorer.findTransformer();*/

    
}

void WritersBlockResolverAudioProcessor::startServer(const ArgumentList& args)  //int argc, char* argv[]
{
    app.addDefaultCommand({ "python -m writers_block_resolver.server ./Transformer/unconditional_model_16.ckpt" });
    app.findAndRunCommand(args);

    DBG("Server is switched-on");

}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WritersBlockResolverAudioProcessor();
}
