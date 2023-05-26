#include "MathTreeConv.h"
// Container with subtrees
vector<Node*> forest;

int main()
{
	cout << "Hello world";
	return 0;
}

Node* Node::turnStringVectorToTree(vector<string> input)
{
	return new Node(Var);
}

vector<string> Node::turnTreeToStringVector()
{
	return vector<string>();
}

nodeType Node::getType()const
{
	return type;
}

Node* Node::getLeft()const
{
	return left;
}

Node* Node::getRight()const
{
	return right;
}

bool isCorrectTriple(vector<string> input)
{
	return false;
}