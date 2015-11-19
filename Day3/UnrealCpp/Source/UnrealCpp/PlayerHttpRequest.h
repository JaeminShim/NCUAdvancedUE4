// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Http.h"
#include "GameFramework/Actor.h"
#include "PlayerHttpRequest.generated.h"

UCLASS()
class UNREALCPP_API APlayerHttpRequest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerHttpRequest();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category="HTTP")
	void StartRequest();

private:
	void OnComplete(FHttpRequestPtr HttpRequestPtr, FHttpResponsePtr HttpResponsePtr, bool bSucceed);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HTTP")
	FString URI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HTTP")
	FString Host;

};
