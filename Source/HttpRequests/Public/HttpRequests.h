#pragma once

#include "CoreMinimal.h"
#include "HttpResponse.h"

namespace HttpRequests
{
	void Get(const FString& Url, TFunction<void(FHttpResponse)> Callback);
}
