#pragma once
#include <JuceHeader.h>
#include "Generate.h"
#include "Parameters.h"

class LoadThread : public Thread {

public:
	LoadThread() : Thread(LOAD) { startThread(); };
	~LoadThread() { stopThread(100); };

	void run() override {
	
		loader.openAndLoad();

		//wait(-1);
	}

private:
	Generate loader;
};