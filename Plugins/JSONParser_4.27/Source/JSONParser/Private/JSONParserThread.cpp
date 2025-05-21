// Copyright 2017 David Romanski(Socke). All Rights Reserved.

#include "JSONParserThread.h"

FJSONParserThread::~FJSONParserThread(){
	delete thread;
}

uint32 FJSONParserThread::Run(){
	FThreadSafeBool* runPtr = &run;
	while (run) {
		while (jobDataQueue.IsEmpty() == false) {
			FSJsonThreadJobData* jobData = nullptr;
			jobDataQueue.Dequeue(jobData);
			if (jobData == nullptr) {
				continue;
			}
			switch (jobData->jobType)
			{
			case EJSONThreadJobType::E_StringToObject:
			{
				bool successful = false;
				struct FSJsonObject jsonObject = UJSONParserBPLibrary::getJSONParserBPLibrary()->JsonStringToObject(jobData->jsonString, jobData->removeAndSavePadding, successful);
				if (jobData->JSONParserAsyncStringToObject != nullptr) {
					AsyncTask(ENamedThreads::GameThread, [runPtr, jobData, jsonObject, successful]() {
						if (!runPtr) {
							return;
						}
						jobData->JSONParserAsyncStringToObject->jobComplete(jsonObject, successful);
						jobData->JSONParserAsyncObjectToString = nullptr;
						jobData->JSONParserAsyncStringToObject = nullptr;
						delete jobData;
					});
				}
			}
			break;
			case EJSONThreadJobType::E_FileToObject:
			{
				FString jsonString = FString();
				struct FSJsonObject jsonObject;
				bool successful = UJSONParserBPLibrary::getJSONParserBPLibrary()->readStringFromFile(jobData->directoryType, jobData->filePath, jsonString);
				if (successful) {
					jsonObject = UJSONParserBPLibrary::getJSONParserBPLibrary()->JsonStringToObject(jsonString, jobData->removeAndSavePadding, successful);
				}
				if (jobData->JSONParserAsyncStringToObject != nullptr) {
					AsyncTask(ENamedThreads::GameThread, [runPtr, jobData, jsonObject, successful]() {
						if (!runPtr) {
							return;
						}
						jobData->JSONParserAsyncStringToObject->jobComplete(jsonObject, successful);
						jobData->JSONParserAsyncObjectToString = nullptr;
						jobData->JSONParserAsyncStringToObject = nullptr;
						delete jobData;
						});
				}
			}
			break;
			case EJSONThreadJobType::E_ObjectToString:
			{
				bool successful = false;
				FString jsonString = UJSONParserBPLibrary::getJSONParserBPLibrary()->JsonObjectToString(successful, jobData->jsonObject, jobData->removeLineBreaks, jobData->addPadding);
				if (jobData->JSONParserAsyncObjectToString != nullptr) {;
					AsyncTask(ENamedThreads::GameThread, [runPtr, jobData, jsonString, successful]() {
						if (!runPtr) {
							return;
						}
						jobData->JSONParserAsyncObjectToString->jobComplete(jsonString, successful);
						jobData->JSONParserAsyncObjectToString = nullptr;
						jobData->JSONParserAsyncStringToObject = nullptr;
						delete jobData;
						});
				}
			}
			break;
			case EJSONThreadJobType::E_ObjectToFile:
			{
				bool successful = false;
				FString jsonString = UJSONParserBPLibrary::getJSONParserBPLibrary()->JsonObjectToString(successful, jobData->jsonObject, jobData->removeLineBreaks, jobData->addPadding);
				if (successful) {
					successful = UJSONParserBPLibrary::writeStringToFile(jobData->directoryType, jsonString, jobData->filePath);
				}
				if (jobData->JSONParserAsyncObjectToString != nullptr) {;
					AsyncTask(ENamedThreads::GameThread, [runPtr, jobData, jsonString, successful]() {
						if (!runPtr) {
							return;
						}
						jobData->JSONParserAsyncObjectToString->jobComplete(jsonString, successful);
						jobData->JSONParserAsyncObjectToString = nullptr;
						jobData->JSONParserAsyncStringToObject = nullptr;
						delete jobData;
					});
				}
			}
			break;
			}
		}


		pauseThread(true);
		//workaround. suspend do not work on all platforms. lets sleep
		while (paused && run) {
			FPlatformProcess::Sleep(0.01);
		}
	}

	thread = nullptr;
	return 0;
}

void FJSONParserThread::pauseThread(bool pause) {
	paused = pause;
	if (thread != nullptr)
		thread->Suspend(pause);
}

void FJSONParserThread::addJob(FSJsonThreadJobData* jobData){
	jobDataQueue.Enqueue(jobData);
	pauseThread(false);
}

void FJSONParserThread::stopThread(){
	run = false;
	pauseThread(false);
}
