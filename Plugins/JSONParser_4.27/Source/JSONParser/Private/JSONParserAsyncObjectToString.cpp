// Copyright 2017 David Romanski(Socke). All Rights Reserved.

#include "JSONParserAsyncObjectToString.h"


UJSONParserAsyncObjectToString* UJSONParserAsyncObjectToString::JsonObjectToStringAsync(struct FSJsonObject mainObject, bool removeLineBreaks, bool addPadding){

	UJSONParserAsyncObjectToString* instance = NewObject<UJSONParserAsyncObjectToString>();
	instance->jobData = new FSJsonThreadJobData();
	instance->jobData->jobType = EJSONThreadJobType::E_ObjectToString;
	instance->jobData->jsonObject = mainObject;
	instance->jobData->removeLineBreaks = removeLineBreaks;
	instance->jobData->addPadding = addPadding;
	instance->jobData->JSONParserAsyncObjectToString= instance;
	instance->AddToRoot();

	//The node is only visible in Blueprints if the function is declared in a UBlueprintAsyncActionBase class. 
	//Therefore an instance of itself is created here.
	return instance;
}

UJSONParserAsyncObjectToString* UJSONParserAsyncObjectToString::JsonObjectToFileAsync(struct FSJsonObject mainObject, EJSONDirectoryType directoryType, FString filePath, bool removeLineBreaks, bool addPadding) {

	UJSONParserAsyncObjectToString* instance = NewObject<UJSONParserAsyncObjectToString>();
	instance->jobData = new FSJsonThreadJobData();
	instance->jobData->jobType = EJSONThreadJobType::E_ObjectToFile;
	instance->jobData->jsonObject = mainObject;
	instance->jobData->directoryType = directoryType;
	instance->jobData->filePath = filePath;
	instance->jobData->removeLineBreaks = removeLineBreaks;
	instance->jobData->addPadding = addPadding;
	instance->jobData->JSONParserAsyncObjectToString = instance;
	instance->AddToRoot();

	return instance;
}

void UJSONParserAsyncObjectToString::Activate(){
	UJSONParserBPLibrary::getJSONParserBPLibrary()->addJobToThread(jobData);
}

void UJSONParserAsyncObjectToString::BeginDestroy(){

	RemoveFromRoot();
	Super::BeginDestroy();
}

void UJSONParserAsyncObjectToString::jobComplete(const FString json, bool successful) {
	
	if (successful) {
		OnSuccess.Broadcast(json);
	}
	else {
		OnFail.Broadcast(json);
	}

	RemoveFromRoot();
}