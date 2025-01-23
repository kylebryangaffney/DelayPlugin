/*
  ==============================================================================

    RotaryKnob.h
    Created: 23 Jan 2025 12:44:44pm
    Author:  kyleb

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class RotaryKnob : public juce::Component
{
public:
    RotaryKnob(const juce::String& text,
        juce::AudioProcessorValueTreeState& apvts,
        const juce::ParameterID& parameterID);
    ~RotaryKnob() override;

    void resized() override;

    juce::AudioProcessorValueTreeState::SliderAttachment attachment;


private:
    juce::Slider slider;
    juce::Label label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryKnob)
};

