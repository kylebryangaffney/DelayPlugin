/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 26 Jan 2025 10:29:25am
    Author:  kyleb

  ==============================================================================
*/

#include "LookAndFeel.h"

const juce::Typeface::Ptr Fonts::typeface = juce::Typeface::createSystemTypefaceFor(
    BinaryData::LatoMedium_ttf, BinaryData::LatoMedium_ttfSize);

juce::Font Fonts::getFont(float height)
{
    return juce::FontOptions(typeface)
        .withMetricsKind(juce::TypefaceMetricsKind::legacy)
        .withHeight(height);
}


RotaryKnobLookAndFeel::RotaryKnobLookAndFeel()
{
    setColour(juce::Label::textColourId, Colors::Knob::label);
    setColour(juce::Slider::textBoxTextColourId, Colors::Knob::label);
    setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
}

juce::Font RotaryKnobLookAndFeel::getLabelFont([[maybe_unused]] juce::Label& label)
{
    return Fonts::getFont();
}

void RotaryKnobLookAndFeel::drawRotarySlider(
    juce::Graphics& g, 
    int x, int y, int width, [[maybe_unused]] int height,
    float sliderPos, float rotaryStartAngle,
    float rotaryEndAngle, 
    juce::Slider& slider)
{
    auto bounds = juce::Rectangle<int>(x, y, width, width).toFloat();
    auto knobRect = bounds.reduced(10.f, 10.f);

    auto path = juce::Path();
    path.addEllipse(knobRect);
    dropShadow.drawForPath(g, path);

    g.setColour(Colors::Knob::outline);
    g.fillEllipse(knobRect);

    juce::Rectangle<float> innerRect = knobRect.reduced(2.f, 2.f);
    juce::ColourGradient gradient = juce::ColourGradient(
        Colors::Knob::gradientTop, 0.f, innerRect.getY(),
        Colors::Knob::gradientBottom, 0.f, innerRect.getBottom(), false
    );
    g.setGradientFill(gradient);
    g.fillEllipse(innerRect);

    auto center = bounds.getCentre();
    auto radius = bounds.getWidth() / 2.f;
    auto lineWidth = 3.f;
    auto arcRadius = radius - lineWidth / 2.f;

    juce::Path backgroundArc;
    backgroundArc.addCentredArc(center.x,
        center.y,
        arcRadius,
        arcRadius,
        0.f,
        rotaryStartAngle,
        rotaryEndAngle,
        true);

    auto strokeType = juce::PathStrokeType(
        lineWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded);
    g.setColour(Colors::Knob::trackBackground);
    g.strokePath(backgroundArc, strokeType);

    auto dialRadius = innerRect.getHeight() / 2.f - lineWidth;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    juce::Point<float> dialStart(center.x + 10.f * std::sin(toAngle), 
                                 center.y - 10.f * std::cos(toAngle));
    juce::Point<float> dialEnd(center.x + dialRadius * std::sin(toAngle),
                               center.y - dialRadius * std::cos(toAngle));

    juce::Path dialPath;
    dialPath.startNewSubPath(dialStart);
    dialPath.lineTo(dialEnd);
    g.setColour(Colors::Knob::dial);
    g.strokePath(dialPath, strokeType);

    setColour(juce::Slider::rotarySliderFillColourId, Colors::Knob::trackActive);

    if (slider.isEnabled())
    {
        float fromAngle = rotaryStartAngle;
        if (slider.getProperties()["drawFromMiddle"])
        {
            fromAngle += (rotaryEndAngle - rotaryStartAngle) / 2.f;
        }

        juce::Path valueArc;
        valueArc.addCentredArc(center.x,
                               center.y,
                               arcRadius,
                               arcRadius,
                               0.f,
                               fromAngle,
                               toAngle,
                               true);
        g.setColour(slider.findColour(juce::Slider::rotarySliderFillColourId));
        g.strokePath(valueArc, strokeType);


    }
}


MainLookAndFeel::MainLookAndFeel()
{
    setColour(juce::GroupComponent::textColourId, Colors::Group::label);
    setColour(juce::GroupComponent::outlineColourId, Colors::Group::outline);
}
juce::Font MainLookAndFeel::getLabelFont([[maybe_unused]] juce::Label& label)
{
    return Fonts::getFont();
}