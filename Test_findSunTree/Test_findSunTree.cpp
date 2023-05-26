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
			try
			{
				string input = "&0";
				findSubTree(input);
			}
			catch (string err)
			{
				Assert::AreEqual(err, string("Массив поддеревьев пуст"));
			}
			Assert::Fail();
		}
		TEST_METHOD(TreeIsNotFound)
		{
			Node* node = new Node();
			addSubTree(node);
			try
			{
				string input = "&1";
				findSubTree(input);
			}
			catch (string err)
			{
				Assert::AreEqual(err, string("Искомое поддерево не найдено"));
			}
			Assert::Fail();
		}
		TEST_METHOD(TypicalCase)
		{
			Node* node = new Node();
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
