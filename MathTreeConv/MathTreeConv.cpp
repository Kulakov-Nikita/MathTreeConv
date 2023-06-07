#include "MathTreeConv.h"
#include <fstream>
using namespace std;

/*!
*\file
*\brief Файл содержит вызываемые функции программы, а также управляющую функцию.
*\mainpage Документация для программы "MathTreeConv"
Программа должна преобразовывать дерево разбора метематического выражения, раскрывая скобки.

Для функционирования программы необходима операционная система Windows 10 или выше.
Программа будет разработана на языке С++ с применением библиотек <iostream>, <fstream>, <string>, <vector>. Дополнительного программного обеспечения не требуется.
Входные файлы могут быть подготовлены в редакторе Блокнот. Выходные файлы могут быть прочитаны с его помощью.

Стандарт языка ISO C++17 (/std:c++17).
Программа должна получать два параметра командной строки: имя входного файла и имя файла для записи выходных данных.

Пример команды запуска программы:
*\code
MathTreeConv.exe C:\\Documents\input.html C:\\Documents\output.html
*\endcode
*\author Кулаков Никита Сергееич
*\date Май 2023 года
*\version 1.0
*/

//! Контейнер с поддеревьями
vector<Node*> forest;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian"); // Настройка языка консоли
	
	try {
		// Проверяем количество атрибутов
		if (argc < 2) {
			throw invalid_argument("Адресс файла с входными данными не указан.");
		}
		else if (argc < 3)
		{
			throw invalid_argument("Адресс для записи входных данных не указан.");
		}
		else {
			vector<string> input = readSequence(argv[1]); // Считываем данные из файла

			// Если файл пустой, выводим сообщение об этом в консоли
			if (input.size() == 0 or (input.size()==1 and input[0]=="")) {
				throw invalid_argument("Входной файл пуст");
			}

			else
			{
				Node* tree = Node::turnStringVectorToTree(input); // Преобразуем входную последовательность в дерево разбора математического выражения

				tree->updateNode(); // Преобразуем дерево разбора матетматического

				// Преобразуем дерево разбора математического в запись в обратной польской нотации и записываем в файл
				vector<string> output = tree->turnTreeToStringVector();
				writeSequence(argv[2], output);
			}
		}
	}
	catch (invalid_argument err)
	{
		// В случае срабатывания исключения, выводим в консоль соответствующее сообщение и ожидаем нажатие клавиши от пользователя
		int a;
		cout << err.what() << endl;
		cin >> a;
	}
}

Node::Node(Node* n)
{
	// Копируем тип узла
	type = n->type; 

	// Копируем значения соответствующие данному типу узла
	if (type == Num)
	{
		value = n->value;
		name = n->name;
	}
	if (type == Var)
	{
		name = n->name;
	}

	// Рекурсивно копируем всех потомков данного узда
	if (n->left)left = new Node(n->left);
	else left = NULL;
	if (n->right)right = new Node(n->right);
	else right = NULL;
}

Node* Node::turnStringVectorToTree(vector<string> input)
{
	try
	{
		Node* output = new Node(); // Дерево разбора математического выражения
		// Проверяем размер входной последовательности
		if (input.size() == 0)return output;
		if (input.size() == 1 and input[0] == "")return output;
		if (input.size() < 3)throw invalid_argument("Файл содержит оператор с недостаточным количеством аргументов.");

		vector<string> stack;
		int counter = 0;

		// Считываем первый три значения со стека
		stack.push_back(input[counter++]);
		stack.push_back(input[counter++]);
		stack.push_back(input[counter++]);

		// Пока в стеке не останется одно значение
		while (stack.size() > 1)
		{
			if (stack.size() > 2)
			{
				vector<string> triple{ stack[stack.size() - 3], stack[stack.size() - 2],stack[stack.size() - 1] }; // Тройка - Три верхние элемента стэка

				// Если данная трока соответстввует типу (оператор, аргумент, аргумент)
				if (isCorrectTriple(triple))
				{
					// Преобразуем тройку в поддерево
					output = turnTripleToNode(triple);

					// Удаляем соответсвующий кортеж (три элемента) с вершины стэка
					stack.pop_back();
					stack.pop_back();
					stack.pop_back();

					// Добавляем индекс нового поддерева в стек
					stack.push_back(addSubTree(output));
				}
				else
				{
					// Добавляем в стек следующее значение
					stack.push_back(input[counter++]);
				}

			}
			else
			{
				// Добавляем в стек следующее значение
				if (input.size() > counter)stack.push_back(input[counter++]);
				else throw invalid_argument("Файл содержит оператор с недостаточным количеством аргументов.");
			}
		}
		// Если остался только один элемент - этот элемент индекс полученного дерева
		if (stack.size() == 1)
		{
			// Если обработаны не все элементы последовательности, значит последовательность содержит лишние элементы
			if (counter != input.size())
			{
				throw invalid_argument("Файл содержит оператор с исбыточным количеством аргументов. Возможно в конца файла есть лишний символ или пробел");
			}
			// В output хранится последнее созданное дерево, индекс которого хранится в стеке
			return output;
		}
		// Если с теке осталось более одного элемента, значит у одоного или нескольких операторов недостаточно аругментов
		else
		{
			throw invalid_argument("Файл содержит оператор с недостаточным количеством аргументов.");
		}
	}
	catch (invalid_argument err)
	{
		throw err;
	}

}

vector<string> Node::turnTreeToStringVector()
{
	vector<string> output;
	// Копируем переменную name, чтобы скопировынное значение можно было изменять, не меняя оригинал.
	string new_name = name;
	// Добавляем в набор подстрок подстроку соответствующую типу данного узла
	switch (type)
	{
	case Var:
		output.push_back(name); // Добавляем имя переменной
		break;
	case Num:
		for (int i = 0; i < new_name.size(); i++)if (new_name[i] == ',')new_name[i] = '.';
		output.push_back(new_name); 
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
	// Если у данного узла есть левый потомок, вызываем данную функцию для него
	if (left)
	{
		vector<string> add = left->turnTreeToStringVector();
		for (auto a : add)
		{
			output.push_back(a);
		}
	}
	// Если у данного узла есть правый потомок, вызываем данную функцию для него
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
	try
	{
		// Вызов исключений
		if (triple.size() < 3)throw invalid_argument("Для создания поддерева не хватает входных значений.");
		if (triple.size() > 3)throw invalid_argument("Слишком много значений для создания поддерева.");
		if (defNodeType(triple[0]) < Plus or defNodeType(triple[0]) == SubTree)throw invalid_argument("Создание поддерева невозможно, так как отсутствует оператор.");
		if ((defNodeType(triple[1]) != Num and defNodeType(triple[1]) != Var and defNodeType(triple[1]) != SubTree) or
			(defNodeType(triple[2]) != Num and defNodeType(triple[2]) != Var and defNodeType(triple[2]) != SubTree))
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
			// Заменяем запятую в числе на точку, так как функция atof в качестве разделителя дробной части принимает запятую
			for (int i = 0; i < triple[2].size(); i++)if (triple[2][i] == '.')triple[2][i] = ',';
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
			// Заменяем точку в числе на запятую, так как функция atof в качестве разделителя дробной части принимает запятую
			for (int i = 0; i < triple[2].size(); i++)if (triple[2][i] == '.')triple[2][i] = ',';
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
	catch (invalid_argument err)
	{
		throw err;
	}
}

bool Node::updateNode()
{
	// Обновляем узлы в соответствии с соответствующими шаблонами
	
	// Шаблон 1: Произведение (числа/перменной/произведения) и (суммы/разности)
	if (type == Mul and
		(left->type == Var or left->type == Num or left->type == Mul) and
		(right->type == Plus or right->type == Minus))
	{
		// Пример: 5 * (1 + 2) -> (1 + 2) * 5

		// Поменять левого и правого потомка местами
		Node* temp = left;
		left = right;
		right = temp;

		// Рекурсивно обновляем потомков данного узла
		left->updateNode();
		right->updateNode();
		updateNode();
		return true;

	}

	// Шаблон 2: Произведение (суммы/разности) с чем-то ИЛИ Частное (суммы/разности) и чего-то кроме(суммы/разности)
	if ((type == Mul and (left->type == Plus or left->type == Minus)) or
		(type == Div and (left->type == Plus or left->type == Minus) and (not (right->type == Plus or right->type == Minus))))
	{
		// Пример: (1 + 2) / 3 -> 1/3 + 2/3

		// Первый(будующий левый) потомок
		Node* first = new Node(type);
		first->left = new Node(left->left);
		first->right = new Node(right);

		// Второй(будующий правый) потомок
		Node* second = new Node(type);
		second->left = new Node(left->right);
		second->right = new Node(right);

		type = left->type;
		left = first;
		right = second;

		// Рекурсивно обновляем потомков данного узла
		left->updateNode();
		right->updateNode();
		updateNode();
		return true;

	}

	// Шаблон 3: Возведение (произведение/частного) в степень в виде (числа/переменной)
	if (type == Pow and
		(left->type == Mul or left->type == Div) and
		(right->type == Num or right->type == Var))
	{
		// Пример: (5 / 2) ^ 3 -> 5 ^ 3 / 2 ^ 3

		// Первый(будущий левый) потомок
		Node* first = new Node(type);
		first->left = new Node(left->left);
		first->right = new Node(right);

		// Второй(будущий правый) потомок
		Node* second = new Node(type);
		second->left = new Node(left->right);
		second->right = new Node(right);

		type = left->type;
		left = first;
		right = second;

		// Рекурсивно обновляем потомков данного узла
		left->updateNode();
		right->updateNode();
		updateNode();
		return true;
	}

	// Шаблон 4: Возведение (суммы/разности) в степень в виде числа
	if (type == Pow and
		(left->type == Plus or left->type == Minus) and
		right->type == Num)
	{
		// Если степень равна 1
		if(right->value == 1)
		{
			Node* temp = left;
			type = temp->type;
			left = temp->left;
			right = temp->right;

			// Рекурсивно обновляем потомков данного узла
			left->updateNode();
			right->updateNode();
			updateNode();
		}
		else {
			// Если стпень - целое число
			if (float(right->value) - int(right->value) == 0.f)
			{
				// Если степень - чётное число
				if (int(right->value) % 2 == 0)
				{
					// Пример: (1 + 2) ^ 4 = (1 + 2) ^ 2 * (1 + 2) ^ 2

					// Первый(будущий левый) потомок
					Node* first = new Node(Pow);
					first->left = new Node(left);
					first->right = new Node(right->value / 2, to_string(int(right->value / 2)));

					// Второй(будущий правый) потомок
					Node* second = new Node(Pow);
					second->left = new Node(left);
					second->right = new Node(right->value / 2, to_string(int(right->value / 2)));

					type = Mul;
					left = first;
					right = second;

					// Рекурсивно обновляем потомков данного узла
					left->updateNode();
					right->updateNode();
					updateNode();
					return true;
				}
				else
				{
					// Если степень не чётное число
					
					// Пример: (1 + 2) ^ 3 -> (1 + 2) ^ 2 * (1 + 2)

					// Первый(будущий левый) потомок
					Node* first = new Node(Pow);
					first->left = new Node(left);
					first->right = new Node(right->value - 1, to_string(int(right->value - 1)));

					// Второй(будущий правый) потомок
					Node* second = new Node(left);

					type = Mul;
					left = first;
					right = second;

					// Рекурсивно обновляем потомков данного узла
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
	try
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
	catch (invalid_argument err)
	{
		throw err;
	}
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
	if (input[0] == '+' or input[0] == '-' or input[0] == '/' or input[0] == '*' or input[0] == '^')
	{
		if (input[1] == '+' or input[1] == '-' or input[1] == '/' or input[1] == '*' or input[1] == '^')throw invalid_argument("В указанном файле отсутствует пробел между двумя или более операторами");
		else throw invalid_argument("В указанном файле отсутствует пробел между оператором и числом (возможно имелся в виду знак числа). Программа поддерживает только целые положительные числа");
	}
		throw invalid_argument("Файл содержит запрещённые символы.");
	return Unknown;
}