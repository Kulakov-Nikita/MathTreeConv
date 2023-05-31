#include "MathTreeConv.h"
#include <fstream>
using namespace std;

// Container with subtrees
vector<Node*> forest;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	try {
		if (argc < 2) {
			throw invalid_argument("Адресс файла с входными данными не указан.");
		}
		else if (argc < 3)
		{
			throw invalid_argument("Адресс для записи входных данных не указан.");
		}
		else {
			vector<string> input = readSequence(argv[1]);
			if (input.size() == 0 or (input.size()==1 and input[0]=="")) {
				throw invalid_argument("Входной файл пуст");
			}
			else
			{
				Node* tree = Node::turnStringVectorToTree(input);;
				tree->updateNode();
				vector<string> output = tree->turnTreeToStringVector();
				writeSequence(argv[2], output);
			}
		}
	}
	catch (invalid_argument err)
	{
		int a;
		cout << err.what() << endl;
		cin >> a;
	}
}

Node::Node(Node* n)
{
	type = n->type;
	if (type == Num)
	{
		value = n->value;
		name = n->name;
	}
	if (type == Var)
	{
		name = n->name;
	}
	if (n->left)left = new Node(n->left);
	else left = NULL;
	if (n->right)right = new Node(n->right);
	else right = NULL;
}

Node* Node::turnStringVectorToTree(vector<string> input)
{
	Node* output = new Node();

	if (input.size() == 0)return output;
	if (input.size() == 1 and input[0] == "")return output;
	if (input.size() < 3)throw invalid_argument("Файл содержит оператор с исбыточным количеством аргументов. Возможно в конца файла есть лишний символ или пробел");

	vector<string> stack;
	int counter = 0;

	stack.push_back(input[counter++]);
	stack.push_back(input[counter++]);
	stack.push_back(input[counter++]);

	while (stack.size() > 1)
	{
		if (stack.size() > 2)
		{
			vector<string> triple{ stack[stack.size() - 3], stack[stack.size() - 2],stack[stack.size() - 1] }; // Три верхние элемента стэка
			if (isCorrectTriple(triple))
			{
				output = turnTripleToNode(triple); 

				// Удаляем соответсвующий кортеж (три элемента) с вершины стэка
				stack.pop_back();
				stack.pop_back();
				stack.pop_back();

				stack.push_back(addSubTree(output));
			}
			else
			{
				stack.push_back(input[counter++]);
			}

		}
		else
		{
			stack.push_back(input[counter++]);
		}
	}
	if (stack.size() == 1)
	{
		if (counter != input.size())
		{
			throw invalid_argument("Файл содержит оператор с исбыточным количеством аргументов. Возможно в конца файла есть лишний символ или пробел");
		}
		return output;
	}
	else
	{
		throw invalid_argument("Файл содержит оператор с недостаточным количеством аргументов.");
	}

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
	case Unknown:
		output.push_back("");
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
		root->left->value = atof(triple[1].c_str());
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

bool Node::updateNode()
{
	// Тип 1
	if (type == Mul and
		(left->type == Var or left->type == Num or left->type == Mul) and
		(right->type == Plus or right->type == Minus))
	{
		// Поменять левого и правого потомка местами
		Node* temp = left;
		left = right;
		right = temp;

		left->updateNode();
		right->updateNode();
		updateNode();
		return true;

	}

	// Тип 2
	if ((type == Mul and (left->type == Plus or left->type == Minus)) or
		(type == Div and (left->type == Plus or left->type == Minus) and (not (right->type == Plus or right->type == Minus))))
	{
		Node* first = new Node(type);
		first->left = new Node(left->left);
		first->right = new Node(right);

		Node* second = new Node(type);
		second->left = new Node(left->right);
		second->right = new Node(right);

		type = left->type;
		left = first;
		right = second;

		left->updateNode();
		right->updateNode();
		updateNode();
		return true;

	}

	// Тип 3
	if (type == Pow and
		(left->type == Mul or left->type == Div) and
		(right->type == Num or right->type == Var))
	{
		Node* first = new Node(type);
		first->left = new Node(left->left);
		first->right = new Node(right);

		Node* second = new Node(type);
		second->left = new Node(left->right);
		second->right = new Node(right);

		type = left->type;
		left = first;
		right = second;

		left->updateNode();
		right->updateNode();
		updateNode();
		return true;
	}

	// Тип 4
	if (type == Pow and
		(left->type == Plus or left->type == Minus) and
		right->type == Num)
	{
		if(right->value == 1)
		{
			Node* temp = left;
			type = temp->type;
			left = temp->left;
			right = temp->right;

			left->updateNode();
			right->updateNode();
			updateNode();
		}
		else {
			if (right->value - int(right->value) == 0)
			{
				if (int(right->value) % 2 == 0)
				{
					Node* first = new Node(Pow);
					first->left = new Node(left);
					first->right = new Node(right->value / 2, to_string(int(right->value / 2)));

					Node* second = new Node(Pow);
					second->left = new Node(left);
					second->right = new Node(right->value / 2, to_string(int(right->value / 2)));

					type = Mul;
					left = first;
					right = second;

					left->updateNode();
					right->updateNode();
					updateNode();
					return true;
				}
				else
				{
					Node* first = new Node(Pow);
					first->left = new Node(left);
					first->right = new Node(right->value - 1, to_string(int(right->value - 1)));

					Node* second = new Node(left);

					type = Mul;
					left = first;
					right = second;

					left->updateNode();
					right->updateNode();
					updateNode();
					return true;
				}
			}
		}
	}

	// Запустить функцию рекурсивно для потомков
	if (left)
	{
		if (left->updateNode())
			updateNode();
	}
	if (right) 
	{
		if(right->updateNode())
			updateNode();
	}
	return false;
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
	if (not file.is_open())throw invalid_argument("Неверно указан файл с входными данными. Возможно, указанный файл не существует.");
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
	if (not file.is_open())throw invalid_argument("Неверно указан файл для выходных данных. Возможно, указанного расположения не существует или нет прав на запись.");
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