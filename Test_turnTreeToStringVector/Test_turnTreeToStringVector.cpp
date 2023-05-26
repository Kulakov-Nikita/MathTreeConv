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
			Node* node = Node::turnStringVectorToTree(input);
			vector<string> output = node->turnTreeToStringVector();
			Assert::IsTrue(output == input);
		}
		TEST_METHOD(SimpleTree)
		{
			vector<string> input{ "+","1","2" };
			try {
				Node* node = Node::turnStringVectorToTree(input);
				vector<string> output = node->turnTreeToStringVector();
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
			try {
				Node* node = Node::turnStringVectorToTree(input);
				vector<string> output = node->turnTreeToStringVector();
				Assert::IsTrue(output == input);
			}
			catch (string err)
			{
				Assert::Fail();
			}

		}
	};
}
