#include "HttpResponse.h"

#include "Interfaces/IHttpResponse.h"

FHttpResponse::FHttpResponse(const FHttpResponsePtr Response) : Content(Response->GetContentAsString())

{
}
