#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "JsonObjectConverter.h"

#include "HttpResponse.generated.h"

/**
 * A response to a submitted request.
 *
 * Wraps a IHttpResponse with convenience functions for deserializing the body, etc.
 */
USTRUCT(BlueprintType)
struct FHttpResponse
{
	GENERATED_BODY()

	FHttpResponse() = default;

	explicit FHttpResponse(const FHttpResponsePtr Response);

	/**
	 * Get the status code of this response.
	 *
	 * @return The status code
	 */
	int32 Status() const;

	/**
	 * Get the full response text.
	 *
	 * @return The text present in the body of the response
	 */
	FString Text() const;

	/**
	 * Deserializes the JSON content of this response to a UStruct
	 * @tparam T The type of UStruct to attempt to deserialize to
	 * @return A new UStruct filled from the JSON content
	 */
	template <class T>
	T Json() const;

	/**
	 * Deserializes the JSON content of this response to an array of UStructs
	 * @tparam T The type of UStruct to attempt to deserialize to
	 * @return A new array of UStructs filled from the JSON content
	 */
	template <class T>
	TArray<T> JsonArray() const;

private:
	FHttpResponsePtr Response;
};

template <class T>
T FHttpResponse::Json() const
{
	T OutData;
	FJsonObjectConverter::JsonObjectStringToUStruct<T>(Text(), &OutData);
	return OutData;
}

template <class T>
TArray<T> FHttpResponse::JsonArray() const
{
	TArray<T> OutData;
	FJsonObjectConverter::JsonArrayStringToUStruct<T>(Text(), &OutData);
	return OutData;
}
