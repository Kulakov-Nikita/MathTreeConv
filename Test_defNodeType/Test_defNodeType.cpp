#include "pch.h"
#include "CppUnitTest.h"
#include "../MathTreeConv/MathTreeConv.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestdefNodeType
{
	TEST_CLASS(TestdefNodeType)
	{
	public:
		
		TEST_METHOD(plus)
		{
			string input = "+";
			try {
				nodeType output = defNodeType(input);
				Assert::IsTrue(output == Plus);
			}
			catch (string err)
			{
				Assert::Fail();
			}
		}
		TEST_METHOD(minus)
		{
			string input = "-";
			try {
				nodeType output = defNodeType(input);
				Assert::IsTrue(output == Minus);
			}
			catch (string err)
			{
				Assert::Fail();
			}
		}
		TEST_METHOD(mul)
		{
			string input = "*";
			try {
				nodeType output = defNodeType(input);
				Assert::IsTrue(output == Mul);
			}
			catch (string err)
			{
				Assert::Fail();
			}
		}
		TEST_METHOD(div)
		{
			string input = "/";
			try {
				nodeType output = defNodeType(input);
				Assert::IsTrue(output == Div);
			}
			catch (string err)
			{
				Assert::Fail();
			}
		}
		TEST_METHOD(_pow)
		{
			string input = "^";
			try {
				nodeType output = defNodeType(input);
				Assert::IsTrue(output == Pow);
			}
			catch (string err)
			{
				Assert::Fail();
			}
		}
		TEST_METHOD(num)
		{
			string input = "5";
			try {
				nodeType output = defNodeType(input);
				Assert::IsTrue(output == Num);
			}
			catch (string err)
			{
				Assert::Fail();
			}
		}
		TEST_METHOD(var)
		{
			string input = "a";
			try {
				nodeType output = defNodeType(input);
				Assert::IsTrue(output == Var);
			}
			catch (string err)
			{
				Assert::Fail();
			}
		}
		TEST_METHOD(subtree)
		{
			string input = "&0";
			try {
				Node* node = new Node(Plus);
				addSubTree(node);
				nodeType output = defNodeType(input);
				Assert::IsTrue(output == SubTree);
			}
			catch (string err)
			{
				Assert::Fail();
			}
		}
		TEST_METHOD(IncorrectType)
		{
			string input = "!";
			//nodeType output = defNodeType(input);

			Assert::ExpectException<std::invalid_argument>([]() {
				defNodeType(string("!"));
				});
		}
	};
}
