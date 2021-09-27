#pragma once
#include "CoreMinimal.h"
#include "HttpResponse.h"

/**
 * A builder to construct the properties of an IHttpRequest.
 *
 * Generally you won't instantiate this directly, but use the convenience functions in the HttpRequests namespace.
 */
class FRequestBuilder
{
public:
	explicit FRequestBuilder(const FString& Verb, const FString& Url);

	/**
	 * Set the request body.
	 *
	 * @param Text The text to be inserted into the body of the request
	 * @return Builder to continue creating a request
	 */
	FRequestBuilder& Body(const FString& Text);

	/**
	 * Overwrites the query string of the URL.
	 *
	 * Modifies the URL of this request, overwriting anything that was previously set.
	 *
	 * @param Query A map of key-value pairs
	 * @return Builder to continue creating a request
	 */
	FRequestBuilder& Query(const FStringFormatNamedArguments& Query);

	/**
	 * Add a body to the request formatted as JSON.
	 *
	 * @tparam T Input struct type
	 * @param Struct Will be serialized as JSON in the body of the request
	 * @return Builder to continue creating a request
	 */
	template <class T>
	FRequestBuilder& Json(const T& Struct);

	/**
	 * Send a HTTP request to the target URL, calling the callback when a response is received.
	 *
	 * @param Callback A function to be called when the response is received
	 */
	void Send(TFunction<void(FHttpResponse)> Callback);

private:
	FHttpRequestPtr Request;
};

template <class T>
FRequestBuilder& FRequestBuilder::Json(const T& Struct)
{
	FString JsonBody;
	FJsonObjectConverter::UStructToJsonObjectString(Struct, JsonBody);
	Request->SetContentAsString(JsonBody);
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	return *this;
}
