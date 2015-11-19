// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealCpp.h"
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
}

// Called when the game starts or when spawned
void APlayerHttpRequest::BeginPlay()
{
	Super::BeginPlay();

	StartRequest();
}

// Called every frame
void APlayerHttpRequest::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APlayerHttpRequest::StartRequest()
{
	UE_LOG(LogTemp, Log, TEXT("StartRequest() called."));

	//FHttpModule	// has a FHttpManager as a member
	//FHttpManager	// we want to use this class' instance

	FHttpModule& HttpModule = FHttpModule::Get();
	FHttpManager& HttpManager = HttpModule.GetHttpManager();
	TSharedRef<IHttpRequest> Requests = HttpModule.CreateRequest();

	FString FullURL = FString::Printf(TEXT("http://%s%s"), *Host, *URI);
	Requests->SetVerb("GET");
	Requests->SetURL(FullURL);
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
		UE_LOG(LogTemp, Log, TEXT("SUCCESS!"))
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("FAILED!"))
	}
}

