// Fill out your copyright notice in the Description page of Project Settings.

#include "JoshComponent.h"
#include "Engine/Engine.h"
#include "Runtime/Core/Public/Misc/Paths.h"

//#include "Runtime/XmlParser/Public/XmlFile.h"
//#include "Runtime/XmlParser/Public/XmlParser.h"


// Sets default values for this component's properties
UJoshComponent::UJoshComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	JsonStr = "[{\"author\":\"Jack\"},{\"age\":\"23\"}]";

	// ...
}


// Called when the game starts
void UJoshComponent::BeginPlay()
{
	Super::BeginPlay();
	//const FString _xmlpath = FPaths::GameDir() + "test.xml";
	//ReadXmlParser(_xmlpath);
	Post();

	// ...
	
}

void UJoshComponent::CreateXmlParser()
{

	FString _XMLContent = "<DocumentElement>\n<Infor>\n< ID>01 </ID >\n<Name>AB</Name>\n<Content>BCD</Content>\n</Infor>\n</DocumentElement>";
	FXmlFile *_WriteXml = new FXmlFile(_XMLContent,EConstructMethod::ConstructFromBuffer);
	if (_WriteXml==nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Red,TEXT("�����ɹ�"));
		return;
	}
	//����xml�ļ�����ǰ����
	_WriteXml->Save(FPaths::GameDir() + "write01.xml");
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("����xml�ļ��ɹ�"));
}



void UJoshComponent::ReadXmlParser(FString  _Xmlpath)
{

	FXmlFile *_XmlFile = new FXmlFile(_Xmlpath);
	FXmlNode *_RootNode = _XmlFile->GetRootNode();
	const TArray<FXmlNode*> _AssetNodes = _RootNode->GetChildrenNodes();
	for (FXmlNode *node:_AssetNodes)
	{
		const TArray<FXmlNode*> _ChildNodes = node->GetChildrenNodes();
		FString _AssetContent = node->GetContent();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, _AssetContent);
		for (FXmlNode* node : _ChildNodes)
		{
			FString _ChildContent = node->GetContent();
			
			//��ӡ_ChildNodes����
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, _ChildContent);
		}
	}
}

void UJoshComponent::OpenFile(FString FileNanme, FString & PassName)
{
	 FString _xmlpath = FPaths::GameDir() + FileNanme;
	 PassName = FileNanme;
	 return;
}

void UJoshComponent::ReadJson()
{

	//�������ڴ洢Json���������
	TArray< TSharedPtr<FJsonValue> > JsonParsed;

	//��ȡJson�ַ���
	TSharedRef< TJsonReader<TCHAR> > JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);
	//����Json������JsonParsed��  
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		//���������ӡ
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("����Json�ɹ���"));
		FString FStringAuthor = JsonParsed[0]->AsObject()->GetStringField("author");
		FString FStringAge = JsonParsed[1]->AsObject()->GetStringField("age");
		FString tempString = "author = " + FStringAuthor + " ,age = " + FStringAge;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, tempString);
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("����ʧ�ܣ�"));
}

void UJoshComponent::WriteJson(FString author, int32 age)
{
	TSharedRef< TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR> > > JSonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR> >::Create(&JsonStr);
	//д��Json���ݿ�ʼ
	JSonWriter->WriteArrayStart();
	JSonWriter->WriteObjectStart();
	FString newAuthor = "Tom";
	JSonWriter->WriteValue(TEXT("author"), author);
	JSonWriter->WriteObjectEnd();
	JSonWriter->WriteObjectStart();
	JSonWriter->WriteValue(TEXT("age"), age);
	JSonWriter->WriteObjectEnd();
	JSonWriter->WriteArrayEnd();
	JSonWriter->Close();
	//д�����
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("д��Json�ɹ���"));
}

void UJoshComponent::Post()
{
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
	HttpRequest->SetURL(TEXT("http://localhost/index.php"));
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetContentAsString(JsonStr);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UJoshComponent::HttpCompleteCallback);
	HttpRequest->ProcessRequest();
	
}

void UJoshComponent::HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

	FString MessageBody = "";

	// If HTTP fails client-side, this will still be called but with a NULL shared pointer!
	if (!Response.IsValid())
	{
		MessageBody = "{\"success\":\"Error: Unable to process HTTP Request!\"}";
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PostFail"));
	}
	else if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		MessageBody = Response->GetContentAsString();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PostFail"));
	}
	else
	{
		MessageBody = FString::Printf(TEXT("{\"success\":\"HTTP Error: %d\"}"), Response->GetResponseCode());
		//GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Red,TEXT("PostFail"));
	}
}


// Called every frame
void UJoshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

