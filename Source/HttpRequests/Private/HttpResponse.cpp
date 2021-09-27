#include "HttpResponse.h"

#include "Interfaces/IHttpResponse.h"

FHttpResponse::FHttpResponse(const FHttpResponsePtr Response) : Response(Response)
{
}

int32 FHttpResponse::Status() const
{
	return Response->GetResponseCode();
}

FString FHttpResponse::Text() const
{
	return Response->GetContentAsString();
}
