// Copyright 2017 David Romanski(Socke). All Rights Reserved.
#pragma once

#include "JSONParser.h"
//#include "JSONParserThead.generated.h"

class JSONPARSER_API FJSONParserThread : public FRunnable {

public:

	FJSONParserThread() {
		FString threadName = "FJSONParserThread" + FGuid::NewGuid().ToString();
		thread = FRunnableThread::Create(this, *threadName, 0, EThreadPriority::TPri_Normal);
	}
	~FJSONParserThread();

	virtual uint32 Run() override;

	void pauseThread(bool pause);
	void addJob(FSJsonThreadJobData* jobData);

	void stopThread();

protected:
	TQueue<FSJsonThreadJobData*> jobDataQueue;
	FRunnableThread* thread = nullptr;
	FThreadSafeBool	run = true;
	FThreadSafeBool	paused = false;
	//FThreadSafeBool isAlive = true;
};