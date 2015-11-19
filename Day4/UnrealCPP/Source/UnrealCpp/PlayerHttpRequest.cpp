// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCpp.h"
#include "JsonObjectConverter.h"
#include "PlayerHttpRequest.h"


// Sets default values
APlayerHttpRequest::APlayerHttpRequest()
{
	//// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	if (Host.IsEmpty())
		Host = TEXT("localhost:8000");
	if (URI.IsEmpty())
		URI = TEXT("/");

	RequestType = EHttpRequestType::GET;
	CurrentHttpRequestState = EPlayerHttpRequestStates::START;
}

// Called when the game starts or when spawned
void APlayerHttpRequest::BeginPlay()
{
	Super::BeginPlay();

	//StartRequest();
}

// Called every frame
void APlayerHttpRequest::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APlayerHttpRequest::AddRequestParameter(const FString& key, const FString& value)
{
	if (!RequestParameters.Contains(key))
		RequestParameters.Add(key, value);
}

void APlayerHttpRequest::StartRequest()
{
	UE_LOG(HttpLog, Log, TEXT("StartRequest() called."));

	//FHttpModule	// has a FHttpManager as a member
	//FHttpManager	// we want to use this class' instance

	FHttpModule& HttpModule = FHttpModule::Get();
	FHttpManager& HttpManager = HttpModule.GetHttpManager();
	TSharedRef<IHttpRequest> Requests = HttpModule.CreateRequest();

	FString FullURL = FString::Printf(TEXT("http://%s%s"), *Host, *URI);

	// GET
	switch (RequestType)
	{
	case EHttpRequestType::GET:
		Requests->SetVerb("GET");
		Requests->SetURL(FullURL);
		break;

	case EHttpRequestType::POST:
		{
			Requests->SetVerb("POST");
			Requests->SetURL(FullURL);

			TSharedRef<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
			for (const auto& Entry : RequestParameters)
				JsonObject->SetStringField(Entry.Key, Entry.Value);

			FString JsonContent;
			TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonContent);
			if (!FJsonSerializer::Serialize(JsonObject, JsonWriter))
				return;

			Requests->SetContentAsString(JsonContent);
			Requests->SetHeader("Content-Type", "application/json");
		}
		break;
	}

	Requests->OnProcessRequestComplete().BindUObject(this, &APlayerHttpRequest::OnComplete);
	Requests->ProcessRequest();
	HttpManager.AddRequest(Requests);
}

void APlayerHttpRequest::OnComplete(FHttpRequestPtr HttpRequestPtr, FHttpResponsePtr HttpResponsePtr, bool bSucceed)
{
	FHttpModule& HttpModule = FHttpModule::Get();
	FHttpManager& HttpManager = HttpModule.GetHttpManager();
	HttpManager.RemoveRequest(HttpRequestPtr.ToSharedRef());
	if (bSucceed)
	{
		FString JsonContent = HttpResponsePtr->GetContentAsString();
		UE_LOG(HttpLog, Log, TEXT("SUCCESS! : %s"), *JsonContent);

		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonContent);
		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			switch (CurrentHttpRequestState)
			{
			case EPlayerHttpRequestStates::START:
				{
					FString PlayerName = JsonObject->GetStringField("name");
					UE_LOG(HttpLog, Log, TEXT("Name : %s"), *PlayerName);

					/*CurrentHttpRequestState = EPlayerHttpRequestStates::USERKEY;
					URI = TEXT("/");
					RequestType = EHttpRequestType::POST;
					AddRequestParameter(TEXT("name"), PlayerName);
					StartRequest();*/
					OnUserConnected(PlayerName);
				}
				break;

			case EPlayerHttpRequestStates::USERKEY:
				{
					ItemDataList = JsonObject->GetArrayField(TEXT("itemData"));
					TSharedRef<FJsonObject> FirstItemObject = ItemDataList[0]->AsObject().ToSharedRef();
					FItemData FirstItemData;
					if (FJsonObjectConverter::JsonObjectToUStruct(FirstItemObject, &FirstItemData, 0, 0))
					{
						UE_LOG(HttpLog, Log, TEXT("%s"), *FirstItemData.itemName);
						OnUserDataReceived(FirstItemData);
					}
					CurrentHttpRequestState = EPlayerHttpRequestStates::END;
				}
				break;
			}
		}
	}
	else
	{
		UE_LOG(HttpLog, Log, TEXT("FAILED!"));
	}
}

