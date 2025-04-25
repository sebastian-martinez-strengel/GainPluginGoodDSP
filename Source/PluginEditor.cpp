#include "PluginEditor.h"

GainPluginGoodDSPAudioProcessorEditor::GainPluginGoodDSPAudioProcessorEditor (
    GainPluginGoodDSPAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    gainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    gainSlider.setRange(0.0f, 2.0f, 0.01f);
    gainSlider.setValue(*audioProcessor.gainParam);
    gainSlider.onValueChange = [this]()
    {
        *audioProcessor.gainParam = gainSlider.getValue();
    };

    addAndMakeVisible(gainSlider);
    setSize (300, 300);
}

GainPluginGoodDSPAudioProcessorEditor::~GainPluginGoodDSPAudioProcessorEditor() {}

void GainPluginGoodDSPAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Gain", getLocalBounds(), juce::Justification::centredTop, 1);
}

void GainPluginGoodDSPAudioProcessorEditor::resized()
{
    gainSlider.setBounds(getLocalBounds().reduced(50));
}
