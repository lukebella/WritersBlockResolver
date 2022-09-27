#pragma once
#include <JuceHeader.h>"

class ButtonEvent : public Button::Listener
{

public:
	void buttonClicked(Button* b)
	{
		return;
	}


private:
	WritersBlockResolverAudioProcessor* p;
	enum type{load, sample, continuation};
};