#include "pch.h"
#include "CppUnitTest.h"
#include "../MathTreeConv/MathTreeConv.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestaddSubTree
{
	TEST_CLASS(TestaddSubTree)
	{
	public:
		TEST_METHOD(EmptyArray)
		{
			Node* node = new Node();
			string output = addSubTree(node);
			Assert::AreEqual(output, string("&0"));
		}
		TEST_METHOD(SingleTreeInArray)
		{
			Node* node1 = new Node();
			Node* node2 = new Node();
			addSubTree(node1);
			string output = addSubTree(node2);
			Assert::AreEqual(output, string("&1"));
		}
		TEST_METHOD(ManyTreesInArray)
		{
			Node* node1 = new Node();
			Node* node2 = new Node();
			Node* node3 = new Node();
			addSubTree(node1);
			addSubTree(node2);
			string output = addSubTree(node3);
			Assert::AreEqual(output, string("&2"));
		}
	};
}
