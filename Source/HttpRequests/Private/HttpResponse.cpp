#include "HttpResponse.h"

#include "Interfaces/IHttpResponse.h"

FHttpResponse::FHttpResponse(const FHttpResponsePtr Response)
	: ResponseCode(Response->GetResponseCode()), Content(Response->GetContentAsString())

{
}
