#include "PluginProcessor.h"
#include "PluginEditor.h"

GainPluginGoodDSPAudioProcessor::GainPluginGoodDSPAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
    addParameter(gainParam = new juce::AudioParameterFloat("gain", "Gain", 0.0f, 4.0f, 1.0f));
}

GainPluginGoodDSPAudioProcessor::~GainPluginGoodDSPAudioProcessor() {}

const juce::String GainPluginGoodDSPAudioProcessor::getName() const { return JucePlugin_Name; }
bool GainPluginGoodDSPAudioProcessor::acceptsMidi() const { return false; }
bool GainPluginGoodDSPAudioProcessor::producesMidi() const { return false; }
bool GainPluginGoodDSPAudioProcessor::isMidiEffect() const { return false; }
double GainPluginGoodDSPAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int GainPluginGoodDSPAudioProcessor::getNumPrograms() { return 1; }
int GainPluginGoodDSPAudioProcessor::getCurrentProgram() { return 0; }
void GainPluginGoodDSPAudioProcessor::setCurrentProgram (int) {}
const juce::String GainPluginGoodDSPAudioProcessor::getProgramName (int) { return {}; }
void GainPluginGoodDSPAudioProcessor::changeProgramName (int, const juce::String&) {}
void GainPluginGoodDSPAudioProcessor::prepareToPlay (double, int) {}
void GainPluginGoodDSPAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainPluginGoodDSPAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == layouts.getMainInputChannelSet();
}
#endif

void GainPluginGoodDSPAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    float gain = gainParam->get();

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            channelData[sample] *= gain;
    }
}

bool GainPluginGoodDSPAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* GainPluginGoodDSPAudioProcessor::createEditor()
{
    return new GainPluginGoodDSPAudioProcessorEditor(*this);
}

void GainPluginGoodDSPAudioProcessor::getStateInformation (juce::MemoryBlock&) {}
void GainPluginGoodDSPAudioProcessor::setStateInformation (const void*, int) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainPluginGoodDSPAudioProcessor();
}
