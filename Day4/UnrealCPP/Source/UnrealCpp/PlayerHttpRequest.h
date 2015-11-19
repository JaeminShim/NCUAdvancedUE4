// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Http.h"
#include "Json.h"
#include "GameFramework/Actor.h"
#include "PlayerHttpRequest.generated.h"

UENUM(BlueprintType)
enum class EHttpRequestType : uint8
{
	GET,
	POST,
};

UENUM(BlueprintType)
enum class EPlayerHttpRequestStates : uint8
{
	START,
	USERKEY,
	END,
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	int32 id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	FString itemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	float damage;
};

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

	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void AddRequestParameter(const FString& key, const FString& value);

	UFUNCTION(BlueprintCallable, Category="HTTP")
	void StartRequest();

	UFUNCTION(BlueprintImplementableEvent, Category = "HTTP")
	void OnUserConnected(const FString& userName);

	UFUNCTION(BlueprintImplementableEvent, Category = "HTTP")
	void OnUserDataReceived(const FItemData& userFirstItemData);

private:
	void OnComplete(FHttpRequestPtr HttpRequestPtr, FHttpResponsePtr HttpResponsePtr, bool bSucceed);

private:
	TMap<FString, FString> RequestParameters;
	TArray<TSharedPtr<FJsonValue>> ItemDataList;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HTTP")
	FString URI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HTTP")
	FString Host;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HTTP")
	EHttpRequestType RequestType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HTTP")
	EPlayerHttpRequestStates CurrentHttpRequestState;
};
