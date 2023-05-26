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
			Assert::IsTrue(node->getType() == Plus && node->getLeft()->getType() == Var && node->getRight()->getType() == Var);
		}
		TEST_METHOD(EmptyVector)
		{
			vector<string> input{ "" };
			try {
				Node* node = Node::turnTripleToNode(input);
			}
			catch (string err)
			{
				Assert::AreEqual(err, string("Для создания поддерева нахватает входных значений."));
			}
			Assert::Fail();
		}
		TEST_METHOD(MoreThanThree)
		{
			vector<string> input{ "+","1","+","2","3"};
			try {
				Node* node = Node::turnTripleToNode(input);
			}
			catch (string err)
			{
				Assert::AreEqual(err, string("Слишком много значений для создания поддерева."));
			}
			Assert::Fail();
		}
		TEST_METHOD(OnlyArguments)
		{
			vector<string> input{ "1","2","3" };
			try {
				Node* node = Node::turnTripleToNode(input);
			}
			catch (string err)
			{
				Assert::AreEqual(err, string("Создание поддерева невозможно, так как отсутствует оператор."));
			}
			Assert::Fail();
		}
		TEST_METHOD(OnlyOperators)
		{
			vector<string> input{ "+","+","+" };
			try {
				Node* node = Node::turnTripleToNode(input);
			}
			catch (string err)
			{
				Assert::AreEqual(err, string("Создание поддерева невозможно, так как отсутствуют аргументы."));
			}
			Assert::Fail();
		}
		TEST_METHOD(SubTree)
		{
			vector<string> input{ "+","1","&0" };
			try {
				addSubTree(new Node());
				Node* node = Node::turnTripleToNode(input);
				Assert::IsTrue(node->getType() == Plus && node->getLeft()->getType() == Var && node->getRight());
			}
			catch (string err)
			{
				Assert::Fail();
			}
		}
	};
}
