#include "pch.h"
#include "CppUnitTest.h"
#include "../MathTreeConv/MathTreeConv.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestfindSunTree
{
	TEST_CLASS(TestfindSunTree)
	{
	public:
		TEST_METHOD(EmptyArray)
		{
			clearForest();
			Assert::ExpectException<std::invalid_argument>([]() {
				findSubTree(string("&0"));
				});
		}
		TEST_METHOD(TreeIsNotFound)
		{
			Node* node = new Node();
			clearForest();
			addSubTree(node);
			Assert::ExpectException<std::invalid_argument>([]() {
				findSubTree(string("&1"));
				});
		}
		TEST_METHOD(TypicalCase)
		{
			Node* node = new Node();
			clearForest();
			addSubTree(node);
			try
			{
				string input = "&0";
				Node* output = findSubTree(input);
				Assert::IsTrue(output == node);
			}
			catch (string err)
			{
				Assert::Fail();
			}
		}
	};
}
