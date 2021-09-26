#include "HttpRequests.h"

#include "Misc/AutomationTest.h"

BEGIN_DEFINE_SPEC(FHttpRequestsSpec, "UnrealPlugin.HttpRequests",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
END_DEFINE_SPEC(FHttpRequestsSpec)

void FHttpRequestsSpec::Define()
{
	Describe("Get",
		[this]
		{
			LatentIt("should perform a get request", EAsyncExecution::ThreadPool,
				[this](const FDoneDelegate TestDone)
				{
					HttpRequests::Get(TEXT("https://jsonplaceholder.typicode.com/posts/1"),
						[this, TestDone](const FHttpResponse Response)
						{
							AddInfo(Response.Content);
							TestTrue("Content", Response.Content.Contains(
													"sunt aut facere repellat provident occaecati excepturi optio reprehenderit"));
							TestDone.Execute();
						});
				});
		});
}
