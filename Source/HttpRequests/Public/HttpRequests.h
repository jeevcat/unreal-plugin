#pragma once

#include "CoreMinimal.h"
#include "RequestBuilder.h"

namespace HttpRequests
{
/**
 * Convenience method to make a GET request to a URL.
 *
 * @param Url The URL for the request
 * @return Builder to continue creating a request before sending
 */
FRequestBuilder Get(const FString& Url);

/**
 * Convenience method to make a POST request to a URL.
 *
 * @param Url The URL for the request
 * @return Builder to continue creating a request before sending
 */
FRequestBuilder Post(const FString& Url);

/**
 * Convenience method to make a PUT request to a URL.
 *
 * @param Url The URL for the request
 * @return Builder to continue creating a request before sending
 */
FRequestBuilder Put(const FString& Url);

/**
 * Convenience method to make a PATCH request to a URL.
 *
 * @param Url The URL for the request
 * @return Builder to continue creating a request before sending
 */
FRequestBuilder Patch(const FString& Url);

/**
 * Convenience method to make a DELETE request to a URL.
 *
 * @param Url The URL for the request
 * @return Builder to continue creating a request before sending
 */
FRequestBuilder Delete(const FString& Url);
}	 // namespace HttpRequests
