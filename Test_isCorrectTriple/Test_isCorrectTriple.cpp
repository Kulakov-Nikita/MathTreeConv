#include "pch.h"
#include "CppUnitTest.h"
#include "../MathTreeConv/MathTreeConv.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestisCorrectTriple
{
	TEST_CLASS(TestisCorrectTriple)
	{
	public:
		
		TEST_METHOD(CorrectForm)
		{
			vector<string> input{ "+","1","2" };
			Assert::IsTrue(isCorrectTriple(input));
		}
		TEST_METHOD(TwoOperator)
		{
			vector<string> input{ "+","+","1" };
			Assert::IsFalse(isCorrectTriple(input));
		}
		TEST_METHOD(OnlyArguments)
		{
			vector<string> input{ "1","2","3" };
			Assert::IsFalse(isCorrectTriple(input));
		}
		TEST_METHOD(SubTree)
		{
			vector<string> input{ "+","1","&1" };
			Assert::IsTrue(isCorrectTriple(input));
		}
	};
}
