#pragma once

#include <JuceHeader.h>

class GainPluginGoodDSPAudioProcessor  : public juce::AudioProcessor
{
public:
    GainPluginGoodDSPAudioProcessor();
    ~GainPluginGoodDSPAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState parameters; //  public so editor can access

private:
    juce::LinearSmoothedValue<float> smoothGain; //  NEW: smoothing object

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainPluginGoodDSPAudioProcessor)
};
