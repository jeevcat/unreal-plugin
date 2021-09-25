#include "HttpRequests.h"

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
