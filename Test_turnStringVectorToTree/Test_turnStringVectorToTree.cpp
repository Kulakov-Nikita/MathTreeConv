#include "pch.h"
#include "CppUnitTest.h"
#include "../MathTreeConv/MathTreeConv.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestturnStringVectorToTree
{
	TEST_CLASS(TestturnStringVectorToTree)
	{
	public:
		
		TEST_METHOD(EmptyVector)
		{
			vector<string> input{ "" };
			Node *node = Node::turnStringVectorToTree(input);
			Assert::IsTrue(node->getType() == Unknown);
		}
		TEST_METHOD(OneArgument)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				Node::turnStringVectorToTree({ "+","1" });
				});
		}
		TEST_METHOD(TooManyArgument)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				Node::turnStringVectorToTree({ "+","1","2","3" });
				});
		}
		TEST_METHOD(TooManyOperations)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				Node::turnStringVectorToTree({ "+","+","+","1" });
				});
		}
		TEST_METHOD(WordHello)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				Node::turnStringVectorToTree({ "Hello" });
				});
		}
		TEST_METHOD(NoPolandNotation)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				Node::turnStringVectorToTree({ "5","+","1" });
				});
		}
		TEST_METHOD(NoOperator)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				Node::turnTripleToNode({ "1","2","3" });
				});
		}
		TEST_METHOD(SimpleTree)
		{
			vector<string> input{ "+","1","2"};
			Node* node = Node::turnStringVectorToTree(input);
			Assert::IsTrue(node->getType() == Plus && node->getLeft()->getType() == Num && node->getRight()->getType() == Num);

			
		}

		TEST_METHOD(ComplexTree)
		{
			vector<string> input{ "*","+","1","2","/","3","^","4","5"};
				Node* node = Node::turnStringVectorToTree(input);
				Assert::IsTrue(node->getType() == Mul && node->getLeft()->getType() == Plus && node->getRight()->getType() == Div && 
					node->getLeft()->getLeft()->getType() == Num && node->getLeft()->getRight()->getType() == Num &&
					node->getRight()->getLeft()->getType() == Num && node->getRight()->getRight()->getType() == Pow &&
					node->getRight()->getRight()->getLeft()->getType() == Num && node->getRight()->getRight()->getRight()->getType() == Num
				);

		}

		TEST_METHOD(StickyArgumentOperator)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				Node::turnTripleToNode({ "+1","2" });
				});
		}
	};
}
