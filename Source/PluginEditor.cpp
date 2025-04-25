#include "PluginEditor.h"

GainPluginGoodDSPEditor::GainPluginGoodDSPEditor (GainPluginGoodDSPAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    gainSlider.setSliderStyle(juce::Slider::Rotary);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(gainSlider);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "gain", gainSlider
    );

    setSize (300, 300);
}

GainPluginGoodDSPEditor::~GainPluginGoodDSPEditor() {}

void GainPluginGoodDSPEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawFittedText ("Good DSP Gain", getLocalBounds(), juce::Justification::centred, 1);
}

void GainPluginGoodDSPEditor::resized()
{
    gainSlider.setBounds(getLocalBounds().reduced(50));
}
