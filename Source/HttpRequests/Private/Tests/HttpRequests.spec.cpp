#include "HttpRequests.h"

#include "JsonPlaceholderPost.h"
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
					HttpRequests::Get(TEXT("https://jsonplaceholder.typicode.com/posts/1"))
						.Send(
							[this, TestDone](const FHttpResponse Response)
							{
								AddInfo(Response.Text());
								TestEqual("Response code", Response.Status(), 200);
								TestTrue("Text", Response.Text().Contains(
													 "sunt aut facere repellat provident occaecati excepturi optio reprehenderit"));
								TestDone.Execute();
							});
				});

			LatentIt("simultaneous requests should all return", EAsyncExecution::ThreadPool,
				[this](const FDoneDelegate TestDone)
				{
					for (int32 i = 0; i < TotalSimultaneousRequests; ++i)
					{
						HttpRequests::Get(FString::Printf(TEXT("https://jsonplaceholder.typicode.com/posts/%d"), i + 1))
							.Send(
								[this, TestDone](const FHttpResponse Response)
								{
									TestEqual("Response code", Response.Status(), 200);

									SimultaneousResponses.Add(Response);
									if (SimultaneousResponses.Num() == TotalSimultaneousRequests)
									{
										TestDone.Execute();
									}
								});
					}
				});

			LatentIt("should deserialize JSON", EAsyncExecution::ThreadPool,
				[this](const FDoneDelegate TestDone)
				{
					HttpRequests::Get(TEXT("https://jsonplaceholder.typicode.com/posts/1"))
						.Send(
							[this, TestDone](const FHttpResponse Response)
							{
								TestEqual("Response code", Response.Status(), 200);

								const auto [UserId, Id, Title, Body] = Response.Json<FJsonPlaceholderPost>();

								TestEqual("UserId", UserId, 1);
								TestEqual("Id", Id, 1);
								TestEqual("Title", Title,
									TEXT("sunt aut facere repellat provident occaecati excepturi optio reprehenderit"));
								TestEqual("Body", Body,
									TEXT("quia et suscipit\n"
										 "suscipit recusandae consequuntur expedita et cum\n"
										 "reprehenderit molestiae ut ut quas totam\n"
										 "nostrum rerum est autem sunt rem eveniet architecto"));

								TestDone.Execute();
							});
				});

			LatentIt("should filter using query", EAsyncExecution::ThreadPool,
				[this](const FDoneDelegate TestDone)
				{
					constexpr int32 UserId = 1;
					HttpRequests::Get(TEXT("https://jsonplaceholder.typicode.com/posts"))
						.Query({{TEXT("userId"), UserId}})
						.Send(
							[=](const FHttpResponse Response)
							{
								TestEqual("Response code", Response.Status(), 200);

								const TArray<FJsonPlaceholderPost> Posts = Response.JsonArray<FJsonPlaceholderPost>();
								for (const FJsonPlaceholderPost& Post : Posts)
								{
									TestEqual("UserId", Post.UserId, UserId);
								}

								TestDone.Execute();
							});
				});
		});

	Describe("Post",
		[this]
		{
			LatentIt("should return 201 and new resource", EAsyncExecution::ThreadPool,
				[this](const FDoneDelegate TestDone)
				{
					constexpr int32 FakeUserId = 11;
					const FString FakeTitle = TEXT("Foo");
					const FString FakeBody = TEXT("Bar");
					HttpRequests::Post(TEXT("https://jsonplaceholder.typicode.com/posts"))
						.Json(FJsonPlaceholderPost{FakeUserId, -1, FakeTitle, FakeBody})
						.Send(
							[=](const FHttpResponse Response)
							{
								AddInfo(Response.Text());
								TestEqual("Response code", Response.Status(), 201);

								const auto [UserId, Id, Title, Body] = Response.Json<FJsonPlaceholderPost>();

								TestEqual("UserId", UserId, FakeUserId);
								TestEqual("Id", Id, 101);
								TestEqual("Title", Title, FakeTitle);
								TestEqual("Body", Body, FakeBody);

								TestDone.Execute();
							});
				});
		});

	Describe("Put",
		[this]
		{
			LatentIt("should return 200 and updated resource", EAsyncExecution::ThreadPool,
				[this](const FDoneDelegate TestDone)
				{
					constexpr int32 FakeId = 1;
					constexpr int32 FakeUserId = 11;
					const FString FakeTitle = TEXT("Foo");
					const FString FakeBody = TEXT("Bar");
					HttpRequests::Put(TEXT("https://jsonplaceholder.typicode.com/posts/1"))
						.Json(FJsonPlaceholderPost{FakeUserId, FakeId, FakeTitle, FakeBody})
						.Send(
							[=](const FHttpResponse Response)
							{
								AddInfo(Response.Text());
								TestEqual("Response code", Response.Status(), 200);

								const auto [UserId, Id, Title, Body] = Response.Json<FJsonPlaceholderPost>();

								TestEqual("UserId", UserId, FakeUserId);
								TestEqual("Id", Id, FakeId);
								TestEqual("Title", Title, FakeTitle);
								TestEqual("Body", Body, FakeBody);

								TestDone.Execute();
							});
				});
		});

	Describe("Delete",
		[this]
		{
			LatentIt("should return 200", EAsyncExecution::ThreadPool,
				[this](const FDoneDelegate TestDone)
				{
					HttpRequests::Delete(TEXT("https://jsonplaceholder.typicode.com/posts/1"))
						.Send(
							[=](const FHttpResponse Response)
							{
								AddInfo(Response.Text());
								TestEqual("Response code", Response.Status(), 200);

								TestDone.Execute();
							});
				});
		});
}
