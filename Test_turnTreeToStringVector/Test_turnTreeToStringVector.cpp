#include "pch.h"
#include "CppUnitTest.h"
#include "../MathTreeConv/MathTreeConv.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestturnTreeToStringVector
{
	TEST_CLASS(TestturnTreeToStringVector)
	{
	public:
		
		TEST_METHOD(EmptyVector)
		{
			vector<string> input{ "" };
			list<string> input1{ "" };
			Node* node = Node::turnStringVectorToTree(input);
			list<string> output;
			node->turnTreeToStringVector(output);
			Assert::IsTrue(output == input1);
		}
		TEST_METHOD(SimpleTree)
		{
			list<string> input{ "+","1","2" };
			vector<string> input1{ "+","1","2" };
			try {
				Node* node = Node::turnStringVectorToTree(input1);
				list<string> output;
				node->turnTreeToStringVector(output);
				Assert::IsTrue(output == input);
			}
			catch (string err)
			{
				Assert::Fail();
			}

		}
		TEST_METHOD(ComplexTree)
		{
			vector<string> input{ "*","+","1","2","/","3","^","4","5" };
			list<string> input1{ "*","+","1","2","/","3","^","4","5" };
			try {
				Node* node = Node::turnStringVectorToTree(input);
				list<string> output;
				node->turnTreeToStringVector(output);
				Assert::IsTrue(output == input1);
			}
			catch (string err)
			{
				Assert::Fail();
			}

		}
	};
}
