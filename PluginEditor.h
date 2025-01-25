/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Parameters.h"
#include "RotaryKnob.h"


//==============================================================================

class DelayPluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    DelayPluginAudioProcessorEditor(DelayPluginAudioProcessor&);
    ~DelayPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    DelayPluginAudioProcessor& audioProcessor;
    RotaryKnob gainKnob;

    juce::AudioProcessorValueTreeState::SliderAttachment attachment
    {
            audioProcessor.apvts, gainParamID.getParamID(), gainKnob.slider
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DelayPluginAudioProcessorEditor)
};