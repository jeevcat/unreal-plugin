#include "HttpRequests.h"

#include "GenericPlatform/GenericPlatformHttp.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"

void OnProcessRequestComplete(FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bConnectedSuccessfully,
	const TFunction<void(FHttpResponse)> Callback)
{
	const FHttpResponse HttpResponse{Response};
	Callback(HttpResponse);
}

void HttpRequests::Get(const FString& Url, const TFunction<void(FHttpResponse)> Callback)
{
	const FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindStatic(OnProcessRequestComplete, Callback);
	Request->SetURL(Url);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

// Stolen from Misc/StringFormatter.cpp
void AppendToString(const FStringFormatArg& Arg, FString& StringToAppendTo)
{
	switch (Arg.Type)
	{
		case FStringFormatArg::Int:
			StringToAppendTo.Append(LexToString(Arg.IntValue));
			break;
		case FStringFormatArg::UInt:
			StringToAppendTo.Append(LexToString(Arg.UIntValue));
			break;
		case FStringFormatArg::Double:
			StringToAppendTo.Append(LexToString(Arg.DoubleValue));
			break;
		case FStringFormatArg::String:
		{
			const FString EncodedString = FGenericPlatformHttp::UrlEncode(Arg.StringValue);
			StringToAppendTo.AppendChars(*EncodedString, EncodedString.Len());
			break;
		}
		case FStringFormatArg::StringLiteral:
		{
			const FString EncodedString = FGenericPlatformHttp::UrlEncode(Arg.StringLiteralValue);
			StringToAppendTo.AppendChars(*EncodedString, EncodedString.Len());
			break;
		}
	}
}

FString AddUrlParameters(const FString& BaseUrl, const TMap<FString, FStringFormatArg>& Parameters)
{
	FString Result = BaseUrl;
	if (Parameters.Num() > 0)
	{
		Result += TEXT("?");
		for (auto It = Parameters.CreateConstIterator(); It;)
		{
			Result += FString::Printf(TEXT("%s="), *It->Key);
			AppendToString(It->Value, Result);
			if (++It)
			{
				Result += TEXT("&");
			}
		}
	}

	return Result;
}
