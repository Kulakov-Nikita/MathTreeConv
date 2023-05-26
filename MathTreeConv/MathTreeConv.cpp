#include "MathTreeConv.h"
#include <fstream>
using namespace std;

// Container with subtrees
vector<Node*> forest;

int main(int argc, char* argv[])
{
	string link1 = "e://Институт/in.txt";
	string link2 = "e://Институт/out.txt";
	vector<string> s = readSequence(link1);
	writeSequence(link2, s);
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

Node* Node::turnTripleToNode(vector<string> triple)
{
	return new Node(Var);
}

void Node::updateNode()
{

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

vector<string> readSequence(string link)
{
	ifstream file(link);
	string f;
	vector<string> output;
	while (!file.eof())
	{
		file >> f;
		output.push_back(f);
	}
	file.close();
	return output;
}

void writeSequence(string link, vector<string> output)
{
	ofstream file(link);
	for (auto i : output)
	{
		file << i << " ";
	}
	file.close();
}

bool isCorrectTriple(vector<string> input)
{
	return false;
}

string addSubTree(Node* input)
{
	return "&";
}

Node* findSubTree(string input)
{
	return new Node();
}

nodeType defNodeType(string input)
{
	return Unknown;
}