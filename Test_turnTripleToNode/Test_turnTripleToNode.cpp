#include "pch.h"
#include "CppUnitTest.h"
#include "../MathTreeConv/MathTreeConv.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestturnTripleToNode
{
	TEST_CLASS(TestturnTripleToNode)
	{
	public:
		TEST_METHOD(TypicalCase)
		{
			vector<string> input{ "+","1","2" };
			Node* node = Node::turnTripleToNode(input);
			Assert::IsTrue(node->getType() == Plus && node->getLeft()->getType() == Num && node->getRight()->getType() == Num);
		}
		TEST_METHOD(EmptyVector)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				Node::turnTripleToNode({ "" });
				});
			
		}
		TEST_METHOD(MoreThanThree)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				Node::turnTripleToNode({ "+","1","+","2","3" });
				});
		}
		TEST_METHOD(OnlyArguments)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				Node::turnTripleToNode({ "1","2","3" });
				});
		}
		TEST_METHOD(OnlyOperators)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				Node::turnTripleToNode({ "+","+","+" });
				});
		}
		TEST_METHOD(SubTree)
		{
			vector<string> input{ "+","1","&0" };
			try {
				clearForest();
				addSubTree(new Node());
				Node* node = Node::turnTripleToNode(input);
				Assert::IsTrue(node->getType() == Plus && node->getLeft()->getType() == Num && node->getRight());
			}
			catch (string err)
			{
				Assert::Fail();
			}
		}
	};
}
