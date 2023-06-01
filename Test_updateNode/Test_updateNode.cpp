#include "pch.h"
#include "CppUnitTest.h"
#include "../MathTreeConv/MathTreeConv.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestupdateNode
{
	TEST_CLASS(TestupdateNode)
	{
	public:
		
		TEST_METHOD(EmptyTree)
		{
			Node* node = new Node();
			node->updateNode();
			Assert::IsTrue(node->getType() == Unknown && !node->getLeft() && !node->getRight());
		}
		TEST_METHOD(OnlyRoot)
		{
			Node* node = new Node(Plus);
			node->updateNode();
			Assert::IsTrue(node->getType() == Plus && !node->getLeft() && !node->getRight());
		}
		TEST_METHOD(SumOfNumAndSum)
		{
			vector<string> input{ "+","1","+","2","3" };
			Node* node = Node::turnStringVectorToTree(input);
			node->updateNode();
			vector<string> output = node->turnTreeToStringVector();
			Assert::IsTrue(output == input);
		}
		TEST_METHOD(MultipliesOfNumAndSum)
		{
			vector<string> input{ "*","1","+","2","3" };
			Node* node = Node::turnStringVectorToTree(input);
			node->updateNode();
			vector<string> output = node->turnTreeToStringVector();
			vector<string> correctAnser{ "+","*","2","1","*","3","1" };
			Assert::IsTrue(output == correctAnser);
		}
		TEST_METHOD(MultipliesOfSumAndSum)
		{
			vector<string> input{ "*","+","1","2","+","3","4"};
			Node* node = Node::turnStringVectorToTree(input);
			node->updateNode();
			vector<string> output = node->turnTreeToStringVector();
			vector<string> correctAnser{ "+","+","*","3","1","*","4","1","+","*","3","2","*","4","2"};
			Assert::IsTrue(output == correctAnser);
		}
		TEST_METHOD(MultipliesOfSumAndSub)
		{
			vector<string> input{ "*","+","1","2","-","3","4" };
			Node* node = Node::turnStringVectorToTree(input);
			node->updateNode();
			vector<string> output = node->turnTreeToStringVector();
			vector<string> correctAnser{ "+","-","*","3","1","*","4","1","-","*","3","2","*","4","2" };
			Assert::IsTrue(output == correctAnser);
		}
		TEST_METHOD(MultipliesOfNumAndMultiplies)
		{
			vector<string> input{ "*","1","*","2","3" };
			Node* node = Node::turnStringVectorToTree(input);
			node->updateNode();
			vector<string> output = node->turnTreeToStringVector();
			Assert::IsTrue(output == input);
		}
		TEST_METHOD(DivNumBySum)
		{
			vector<string> input{ "/","1","/","2","3" };
			Node* node = Node::turnStringVectorToTree(input);
			node->updateNode();
			vector<string> output = node->turnTreeToStringVector();
			Assert::IsTrue(output == input);
		}
		TEST_METHOD(DivSumByNum)
		{
			vector<string> input{ "/","+","1","2","3"};
			Node* node = Node::turnStringVectorToTree(input);
			node->updateNode();
			vector<string> output = node->turnTreeToStringVector();
			vector<string> correctAnser{ "+","/","1","3","/","2","3" };
			Assert::IsTrue(output == correctAnser);
		}
		TEST_METHOD(PowMultipliesByNum)
		{
			vector<string> input{ "^","*","1","2","3" };
			Node* node = Node::turnStringVectorToTree(input);
			node->updateNode();
			vector<string> output = node->turnTreeToStringVector();
			vector<string> correctAnser{ "*","^","1","3","^","2","3" };
			Assert::IsTrue(output == correctAnser);
		}
		TEST_METHOD(PowDivByNum)
		{
			vector<string> input{ "^","/","1","2","3" };
			Node* node = Node::turnStringVectorToTree(input);
			node->updateNode();
			vector<string> output = node->turnTreeToStringVector();
			vector<string> correctAnser{ "/","^","1","3","^","2","3" };
			Assert::IsTrue(output == correctAnser);
		}
		TEST_METHOD(PowSumByNum)
		{
			vector<string> input{ "^","+","1","2","2" };
			Node* node = Node::turnStringVectorToTree(input);
			node->updateNode();
			vector<string> output = node->turnTreeToStringVector();
			vector<string> correctAnser{ "+","+","*","1","1","*","2","1","+","*","1","2","*","2","2" };
			Assert::IsTrue(output == correctAnser);
		}
		TEST_METHOD(PowSumByNotNum)
		{
			vector<string> input{ "^","+","1","2","A" };
			Node* node = Node::turnStringVectorToTree(input);
			node->updateNode();
			vector<string> output = node->turnTreeToStringVector();
			Assert::IsTrue(output == input);
		}
		TEST_METHOD(ComplexCase)
		{
			vector<string> input{ "^","/","-","+","5","3","1","7","2" };
			Node* node = Node::turnStringVectorToTree(input);
			node->updateNode();
			vector<string> output = node->turnTreeToStringVector();
			//vector<string> correctAnser{ "+","+","+","+","*","/","5","7","/","5","7","*","/","3","7","/","5","7","+","*","/","1","7","/","5","7","*","/","5","7","/","3","7","+","+","*","/","3","7","/","3","7","*","/","1","7","/","3","7","+","*","/","5","7","/","1","7","*","/","3","7","/","1","7","*","/","1","7","/","1","7"};
			vector<string> correctAnser{ "-", "+", "-", "+", "/", "*", "5", "5", "^", "7", "2", "/", "*", "3", "5", "^", "7", "2", "/", "*", "1", "5", "^", "7", "2", "-", "+", "/", "*", "5", "3", "^", "7", "2", "/", "*", "3", "3", "^", "7", "2", "/", "*", "1", "3", "^", "7", "2", "-", "+", "/", "*", "5", "1", "^", "7", "2", "/", "*", "3", "1", "^", "7", "2", "/", "*", "1", "1", "^", "7", "2" };
			
			Assert::IsTrue(output == correctAnser);
		}
	};
}
