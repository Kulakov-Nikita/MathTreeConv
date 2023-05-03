enum nodeType{Unknown,Var,Num,Plus,Minus,Mul,Div,Pow};

class Node 
{
	nodeType type; // Тип узла
	float value; // Значение числа (если тип узла - число)
	string name; // Имя переменной (если тип узла - переменная)
	Node *left, *right; // Ссылки на потомков узла

	// Convert the tree to a sequence of substrings
	vector<string> turnTreeToStringVector();

	// Convert the sequence of substrings to a tree
	Node* turnStringVectorToTree(vector<string> input);

	// Convert the sequence of three substrings to a node
	Node* turnTripleToNode(vector<string> triple);

	// Change node according to arithmetic precedence
	Node* updateNode(Node* input);
};

// Container with subtrees
vector<Node*> forest;

// Read a sequence from the file
vector<string> readSequence(string link);

// Write the sequence in the file
void writeSequence(string link, vector<string> output);

// Check if the sequence of three substring correct
bool isCorrectTriple(vector<string> input);

// Add the subtree to the forest
string addSubTree(Node* input);

// Find the subtree in the forest
Node* findSubTree(string input);

// Determine the type of the received element
nodeType defNodeType(string input);