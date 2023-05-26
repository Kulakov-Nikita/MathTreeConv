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
			vector<string> input{ "+","1"};
			try {
				Node* node = Node::turnStringVectorToTree(input);
			}
			catch (string err)
			{
				Assert::AreEqual(err, string("Файл содержит оператор с недостаточным количеством аргументов"));
			}
			Assert::Fail();
		}
		TEST_METHOD(TooManyArgument)
		{
			vector<string> input{ "+","1","2","3"};
			try {
				Node* node = Node::turnStringVectorToTree(input);
			}
			catch (string err)
			{
				Assert::AreEqual(err, string("Файл содержит оператор с избыточным количеством аргументов"));
			}
			Assert::Fail();
		}
		TEST_METHOD(NoOperator)
		{
			vector<string> input{ "1","2","3"};
			try {
				Node* node = Node::turnStringVectorToTree(input);
			}
			catch (string err)
			{
				Assert::AreEqual(err, string("Файл не содержит операторов"));
			}
			Assert::Fail();
		}
		TEST_METHOD(SimpleTree)
		{
			vector<string> input{ "+","1","2"};
			try {
				Node* node = Node::turnStringVectorToTree(input);
				Assert::IsTrue(node->getType() == Plus && node->getLeft()->getType() == Var && node->getRight()->getType() == Var);
			}
			catch (string err)
			{
				Assert::Fail();
			}
			
		}

		TEST_METHOD(ComplexTree)
		{
			vector<string> input{ "*","+","1","2","/","3","^","4","5"};
			try {
				Node* node = Node::turnStringVectorToTree(input);
				Assert::IsTrue(node->getType() == Mul && node->getLeft()->getType() == Plus && node->getRight()->getType() == Div && 
					node->getLeft()->getLeft()->getType() == Var && node->getLeft()->getRight()->getType() == Var &&
					node->getRight()->getLeft()->getType() == Var && node->getRight()->getRight()->getType() == Pow &&
					node->getRight()->getRight()->getLeft()->getType() == Var && node->getRight()->getRight()->getRight()->getType() == Var
				);
			}
			catch (string err)
			{
				Assert::Fail();
			}

		}

		TEST_METHOD(StickyArgumentOperator)
		{
			vector<string> input{ "+1","2" };
			try {
				Node* node = Node::turnStringVectorToTree(input);
			}
			catch (string err)
			{
				Assert::AreEqual(err, string("Файл содержит оператор с недостаточным количеством аргументов"));
			}
			Assert::Fail();
		}
	};
}
