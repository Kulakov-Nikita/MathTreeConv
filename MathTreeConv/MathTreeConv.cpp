#include "MathTreeConv.h"
#include <fstream>
using namespace std;

// Container with subtrees
vector<Node*> forest;

int main(int argc, char* argv[])
{
	Node* node = Node::turnTripleToNode({ "+","1","2" });
	vector<string> output = node->turnTreeToStringVector();
	for (auto o : output)
	{
		cout << o << " ";
	}
	return 0;
}

Node* Node::turnStringVectorToTree(vector<string> input)
{
	return new Node(Var);
}

vector<string> Node::turnTreeToStringVector()
{
	vector<string> output;
	switch (type)
	{
	case Var:
		output.push_back(name);
		break;
	case Num:
		output.push_back(name);
		break;
	case Plus:
		output.push_back("+");
		break;
	case Minus:
		output.push_back("-");
		break;
	case Mul:
		output.push_back("*");
		break;
	case Div:
		output.push_back("/");
		break;
	case Pow:
		output.push_back("^");
		break;
	default:break;
	}
	if (left)
	{
		vector<string> add = left->turnTreeToStringVector();
		for (auto a : add)
		{
			output.push_back(a);
		}
	}
	if (right)
	{
		vector<string> add = right->turnTreeToStringVector();
		for (auto a : add)
		{
			output.push_back(a);
		}
	}
	return output;
}

Node* Node::turnTripleToNode(vector<string> triple)
{
	// Вызов исключений
	if(triple.size() < 3)throw invalid_argument("Для создания поддерева не хватает входных значений.");
	if(triple.size() > 3)throw invalid_argument("Слишком много значений для создания поддерева.");
	if(defNodeType(triple[0])<Plus or defNodeType(triple[0]) == SubTree)throw invalid_argument("Создание поддерева невозможно, так как отсутствует оператор.");
	if( (defNodeType(triple[1]) != Num and defNodeType(triple[1]) != Var and defNodeType(triple[1]) != SubTree) or 
		(defNodeType(triple[2]) != Num and defNodeType(triple[2]) != Var and defNodeType(triple[2]) != SubTree) )
		throw invalid_argument("Создание поддерева невозможно, так как отсутствуют аргументы.");

	// Создаём корень
	Node* root = new Node(defNodeType(triple[0]));

	// добавляем левого потомка
	switch (defNodeType(triple[1]))
	{
	case SubTree:
		root->left = findSubTree(triple[1]);
		break;
	case Num:
		root->left = new Node(Num);
		root->right->value = atof(triple[1].c_str());
		root->left->name = triple[1];
		break;
	case Var:
		root->left = new Node(Var);
		root->left->name = triple[1];
	default:break;
	}

	// Добавляем правого потомка
	switch (defNodeType(triple[2]))
	{
	case SubTree:
		root->right = findSubTree(triple[2]);
		break;
	case Num:
		root->right = new Node(Num);
		root->right->value = atof(triple[2].c_str());
		root->right->name = triple[2];
		break;
	case Var:
		root->right = new Node(Var);
		root->right->name = triple[2];
	default:break;
	}

	return root;
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
		isDigit *= (isdigit(i) or i == '.');
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