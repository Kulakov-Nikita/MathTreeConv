#include<iostream>
#include<string>
#include<string.h>
#include<vector>
using namespace std;
enum nodeType{Unknown,Var,Num,Plus,Minus,Mul,Div,Pow};

void foo(int);

class Node
{
private:
	nodeType type; // Тип узла
	float value; // Значение числа (если тип узла - число)
	string name; // Имя переменной (если тип узла - переменная)
	Node* left, * right; // Ссылки на потомков узла
public:
	Node() :type(Unknown), left(NULL), right(NULL) {}
	Node(nodeType Type) :type(Type), left(NULL), right(NULL) {}

	/*
	* \Convert the tree to a sequence of substrings
	* return - sequence of substrings
	*/
	vector<string> turnTreeToStringVector();

	/*
	* \Convert the sequence of substrings to a tree
	* \param[in] - convertable sequence of substrings
	* return - recieved tree
	* throw - if number of substrings is incorrect
	*/
	static Node* turnStringVectorToTree(vector<string> input);

	/*
	* \Convert the sequence of three substrings to a node
	* \param[in] triple - convertable sequence of three substring
	* \return - recieved subtree
	* \throw - if creating this subtree is imposible
	*/
	static Node* turnTripleToNode(vector<string> triple);

	/*
	* \Change node according to arithmetic precedence
	* \param[in] input - the subtree which could be changed
	* \return - recieved subtree
	*/
	void updateNode();

	nodeType getType()const;

	Node* getLeft()const;

	Node* getRight()const;
};

/*
* \Read a sequence from the file
* \param[in] link - adress of readable file
* \return - sequence of substrings
* \throw - throws exceptions in case of read errors
*/
vector<string> readSequence(string link);

/*
* \Write the sequence in the file
* \param[in] link - adress of recordable file
* \param[in] output - sequence of substring
* \throw - throws exceptions in case of write errors
*/
void writeSequence(string link, vector<string> output);

/*
* \Check if the sequence of three substring correct
* \param[in] input - test sequence
* \return - is the sequence correct
*/
bool isCorrectTriple(vector<string> input);

/*
* \Add the subtree to the forest
* \param[in] input - addable subtree
* \return - id of added subtree
*/
string addSubTree(Node* input);

/*
* Find the subtree in the forest
* param[in] - id of subtree
* return - subtree (or 0 if subtree is not found)
*/
Node* findSubTree(string input);

/*
* \Determine the type of the received element
* \param[in] input - test substring
* \return - type of the node
* \throw - if the input is incorrect
*/
nodeType defNodeType(string input);

void clearForest();