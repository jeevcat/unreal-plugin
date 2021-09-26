#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"

#include "HttpResponse.generated.h"

USTRUCT(BlueprintType)
struct FHttpResponse
{
	GENERATED_BODY()

	FHttpResponse() = default;

	explicit FHttpResponse(const FHttpResponsePtr Response);

	template <class T>
	T Json()
	{
		return {};
	}

	UPROPERTY(BlueprintReadOnly)
	int32 ResponseCode;

	UPROPERTY(BlueprintReadOnly)
	FString Content;
};
