#include "PluginProcessor.h"
#include "PluginEditor.h"

GainPluginGoodDSPAudioProcessor::GainPluginGoodDSPAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (BusesProperties()
                        .withInput ("Input", juce::AudioChannelSet::stereo(), true)
                        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      parameters(*this, nullptr, juce::Identifier("Parameters"),
      {
          std::make_unique<juce::AudioParameterFloat>("gain", "Gain", 0.0f, 2.0f, 1.0f)
      })
#endif
{
}

GainPluginGoodDSPAudioProcessor::~GainPluginGoodDSPAudioProcessor() {}

const juce::String GainPluginGoodDSPAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainPluginGoodDSPAudioProcessor::acceptsMidi() const { return false; }
bool GainPluginGoodDSPAudioProcessor::producesMidi() const { return false; }
bool GainPluginGoodDSPAudioProcessor::isMidiEffect() const { return false; }
double GainPluginGoodDSPAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int GainPluginGoodDSPAudioProcessor::getNumPrograms() { return 1; }
int GainPluginGoodDSPAudioProcessor::getCurrentProgram() { return 0; }
void GainPluginGoodDSPAudioProcessor::setCurrentProgram (int) {}
const juce::String GainPluginGoodDSPAudioProcessor::getProgramName (int) { return {}; }
void GainPluginGoodDSPAudioProcessor::changeProgramName (int, const juce::String&) {}

void GainPluginGoodDSPAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    smoothGain.reset(sampleRate, 0.05); //  50ms smoothing time
}

void GainPluginGoodDSPAudioProcessor::releaseResources() {}

void GainPluginGoodDSPAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    //  Update the smoothing target at the start of each block
    smoothGain.setTargetValue(*parameters.getRawParameterValue("gain"));

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            float gain = smoothGain.getNextValue(); //  Smoothly moving value
            channelData[sample] *= gain;
        }
    }
}

bool GainPluginGoodDSPAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* GainPluginGoodDSPAudioProcessor::createEditor()
{
    return new GainPluginGoodDSPEditor(*this);
}

void GainPluginGoodDSPAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto xml = parameters.copyState().createXml())
        copyXmlToBinary(*xml, destData);
}

void GainPluginGoodDSPAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xmlState = getXmlFromBinary(data, sizeInBytes))
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

// 🔥 Must-have for JUCE plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainPluginGoodDSPAudioProcessor();
}
