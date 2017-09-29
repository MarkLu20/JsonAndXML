// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/XmlParser/Public/XmlParser.h"
#include "Json.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Private/HttpTests.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"
#include "JoshComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JSONRW_API UJoshComponent : public UActorComponent
{
	GENERATED_BODY()
	void HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

public:	
	// Sets default values for this component's properties
	UJoshComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	FString JsonStr;
public:
	UFUNCTION(BlueprintCallable, Category = "XML")
		void CreateXmlParser();
	UFUNCTION(BlueprintCallable, Category = "Xml")
		void ReadXmlParser( FString _Xmlpath);
	UFUNCTION(BlueprintCallable)
		void OpenFile(FString FileNanme, FString &PassName);
	UFUNCTION(BlueprintCallable, Category = "JSson")
		void ReadJson();
	UFUNCTION(BlueprintCallable, Category = "JSon")
		void WriteJson(FString author, int32 age);
	UFUNCTION(BlueprintCallable, Category = "JSon")
		void Post();
	//UFUNCTION(BlueprintCallable, Category = "JSon")
		//void HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
