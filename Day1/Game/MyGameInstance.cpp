// Fill out your copyright notice in the Description page of Project Settings.

#include "Day1.h"
#include "MyGameInstance.h"
#if PLATFORM_ANDROID
#include "AndroidApplication.h"
#endif

#if PLATFORM_ANDROID
void AndroidThunkCpp_CallTest();
#endif

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Instance Init!"))

#if PLATFORM_ANDROID
	AndroidThunkCpp_CallTest();
#endif
}

#if PLATFORM_ANDROID
void AndroidThunkCpp_CallTest()
{
	JNIEnv* JEnv = FAndroidApplication::GetJavaEnv();
	if (nullptr != JEnv)
	{
		jclass Class = FAndroidApplication::FindJavaClass("com/epicgames/ue4/GameActivity");
		if (nullptr != Class)
		{
			// JNI rule		// ()V : no parameters, void return
			jmethodID callMethod = JEnv->GetMethodID(Class, "AndroidThunkJava_callTest", "()V");
			if (nullptr != callMethod)
			{
				FJavaWrapper::CallVoidMethod(JEnv, FJavaWrapper::GameActivityThis, callMethod);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No Method Found!"));
			}
			JEnv->DeleteLocalRef(Class);
		}
	}
}
#endif
