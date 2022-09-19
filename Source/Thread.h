/*#pragma once
#include <JuceHeader.h>
#include "Generate.h"
#include "Parameters.h"

class LoadThread : public Thread, public Generate {

public:
	LoadThread() : Thread(LOAD) {}; //startThread(); };
	~LoadThread() { stopThread(100); };

	void run() override {
	
		Generate::openAndLoad();
		signalThreadShouldExit();

		//wait(-1);
	}

private:
};


class SampleThread : public Thread, public Generate {

public:
	SampleThread() : Thread(SAMPLE) {}; //startThread(); };
	~SampleThread() { stopThread(100); };

	void run() override {
		LoadThread lt;   //maybe check threadid or name
		ContinueThread ct;
		if (!(lt.isThreadRunning() && ct.isThreadRunning()))
		{
			Generate::unconditional();
			signalThreadShouldExit();
		}
		else
		{
			DBG("Operation in course: wait until it's finished");
			stopThread(100);
		}

		//wait(-1);
	}

private:
};

class ContinueThread : public Thread, public Generate {

public:
	ContinueThread() : Thread(CONTINUATION) {}; //startThread(); };
	~ContinueThread() { stopThread(100); };

	void run() override {

		LoadThread lt;
		SampleThread st;
		if (!(lt.isThreadRunning() && st.isThreadRunning()))
		{
			Generate::processCond();
			signalThreadShouldExit();
		}
		else
		{
			DBG("Operation in course: wait until it's finished");
			stopThread(100);
		}


		//wait(-1);
	}

private:
};*/