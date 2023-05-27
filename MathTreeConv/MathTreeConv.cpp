#include "MathTreeConv.h"
#include <fstream>
using namespace std;

// Container with subtrees
vector<Node*> forest;

int main(int argc, char* argv[])
{
	isCorrectTriple({ "+", "+","1" });
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
	if (defNodeType(input[0]) == Plus or defNodeType(input[0]) == Minus or defNodeType(input[0]) == Mul or defNodeType(input[0]) == Div or defNodeType(input[0]) == Pow)
	{
		if (defNodeType(input[1]) == Var or defNodeType(input[1]) == Num or defNodeType(input[1]) == SubTree)
		{
			if (defNodeType(input[2]) == Var or defNodeType(input[2]) == Num or defNodeType(input[2]) == SubTree)
			{
				return true;
			}
		}
	}
	return false;
}

string addSubTree(Node* input)
{
	forest.push_back(input);
	char* c;
	return "&" + to_string(forest.size() - 1);
}

Node* findSubTree(string input)
{
	string index;
	for (auto i : input)
	{
		if (isdigit(i))index.push_back(i);
	}
	if(forest.size() == 0)throw invalid_argument("Массив поддеревьев пуст");
	if(forest.size() <= atoi(index.c_str()))throw invalid_argument("Искомое поддерево не найдено");
	return forest[atoi(index.c_str())];
}

void clearForest()
{
	forest.clear();
}

nodeType defNodeType(string input)
{
	// Если введённая строка + - * / ^ , вернуть соответствующий тип
	if (input == "+")return Plus;
	if (input == "-")return Minus;
	if (input == "*")return Mul;
	if (input == "/")return Div;
	if (input == "^")return Pow;

	//Если строка начинается с &, вернуть тип корня поддерева с указанным индексом
	if (input[0] == '&')return SubTree;

	// Проверить является ли строка, представлением числа
	bool isDigit = true;
	for (auto i : input)
	{
		isDigit *= isdigit(i);
	}
	if (isDigit)return Num;

	// Проверить является ли сторка, названием переменной
	bool isVarName = true;
	if (not (isalpha(input[0]) or input[0] == '_'))isVarName = false;
	for (auto i : input)
	{
		isVarName *= isalpha(i) or isdigit(i) or i == '_';
	}
	if (isVarName)return Var;

	throw invalid_argument("test");

	return Unknown;
}