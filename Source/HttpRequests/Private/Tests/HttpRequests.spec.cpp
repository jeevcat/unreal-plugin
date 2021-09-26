#include "HttpRequests.h"

#include "Misc/AutomationTest.h"

BEGIN_DEFINE_SPEC(FHttpRequestsSpec, "UnrealPlugin.HttpRequests",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
const int32 TotalSimultaneousRequests = 20;
TArray<FHttpResponse> SimultaneousResponses;
END_DEFINE_SPEC(FHttpRequestsSpec)

void FHttpRequestsSpec::Define()
{
	Describe("Get",
		[this]
		{
			LatentIt("should return 200 and body", EAsyncExecution::ThreadPool,
				[this](const FDoneDelegate TestDone)
				{
					HttpRequests::Get(TEXT("https://jsonplaceholder.typicode.com/posts/1"),
						[this, TestDone](const FHttpResponse Response)
						{
							AddInfo(Response.Content);
							TestEqual("Response code", Response.ResponseCode, 200);
							TestTrue("Content", Response.Content.Contains(
													"sunt aut facere repellat provident occaecati excepturi optio reprehenderit"));
							TestDone.Execute();
						});
				});

			LatentIt("simultaneous requests should all return", EAsyncExecution::ThreadPool,
				[this](const FDoneDelegate TestDone)
				{
					for (int32 i = 0; i < TotalSimultaneousRequests; ++i)
					{
						HttpRequests::Get(FString::Printf(TEXT("https://jsonplaceholder.typicode.com/posts/%d"), i + 1),
							[this, TestDone](const FHttpResponse Response)
							{
								TestEqual("Response code", Response.ResponseCode, 200);

								SimultaneousResponses.Add(Response);
								if (SimultaneousResponses.Num() == TotalSimultaneousRequests)
								{
									TestDone.Execute();
								}
							});
					}
				});
		});
}
