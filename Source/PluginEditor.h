#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class GainPluginGoodDSPAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    GainPluginGoodDSPAudioProcessorEditor (GainPluginGoodDSPAudioProcessor&);
    ~GainPluginGoodDSPAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    GainPluginGoodDSPAudioProcessor& audioProcessor;

    juce::Slider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainPluginGoodDSPAudioProcessorEditor)
};
