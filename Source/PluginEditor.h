#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class GainPluginGoodDSPEditor : public juce::AudioProcessorEditor
{
public:
    GainPluginGoodDSPEditor (GainPluginGoodDSPAudioProcessor&);
    ~GainPluginGoodDSPEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    GainPluginGoodDSPAudioProcessor& audioProcessor;

    juce::Slider gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainPluginGoodDSPEditor)
};
