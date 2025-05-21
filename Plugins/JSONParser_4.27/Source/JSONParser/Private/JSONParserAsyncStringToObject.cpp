// Copyright 2017 David Romanski(Socke). All Rights Reserved.

#include "JSONParserAsyncStringToObject.h"


UJSONParserAsyncStringToObject* UJSONParserAsyncStringToObject::JsonStringToObjectAsync(FString json, bool removeAndSavePadding){

	UJSONParserAsyncStringToObject* instance = NewObject<UJSONParserAsyncStringToObject>();
	instance->jobData = new FSJsonThreadJobData();
	instance->jobData->jobType = EJSONThreadJobType::E_StringToObject;
	instance->jobData->jsonString = json;
	instance->jobData->removeAndSavePadding = removeAndSavePadding;
	instance->jobData->JSONParserAsyncStringToObject = instance;
	instance->AddToRoot();
	//The node is only visible in Blueprints if the function is declared in a UBlueprintAsyncActionBase class. 
	//Therefore an instance of itself is created here.
	return instance;
}


UJSONParserAsyncStringToObject* UJSONParserAsyncStringToObject::JsonFileToObjectAsync(EJSONDirectoryType directoryType, FString filePath, bool removeAndSavePadding) {

	UJSONParserAsyncStringToObject* instance = NewObject<UJSONParserAsyncStringToObject>();
	instance->jobData = new FSJsonThreadJobData();
	instance->jobData->jobType = EJSONThreadJobType::E_FileToObject;
	instance->jobData->directoryType = directoryType;
	instance->jobData->filePath = filePath;
	instance->jobData->removeAndSavePadding = removeAndSavePadding;
	instance->jobData->JSONParserAsyncStringToObject = instance;
	instance->AddToRoot();
	return instance;
}

void UJSONParserAsyncStringToObject::Activate(){
	UJSONParserBPLibrary::getJSONParserBPLibrary()->addJobToThread(jobData);
}

void UJSONParserAsyncStringToObject::BeginDestroy(){
	RemoveFromRoot();
	Super::BeginDestroy();
}

void UJSONParserAsyncStringToObject::jobComplete(const struct FSJsonObject jsonObject, bool successful) {
	
	if (successful) {
		OnSuccess.Broadcast(jsonObject);
	}
	else {
		OnFail.Broadcast(jsonObject);
	}

	RemoveFromRoot();
}