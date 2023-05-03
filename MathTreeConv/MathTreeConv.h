enum nodeType{Unknown,Var,Num,Plus,Minus,Mul,Div,Pow};

class Node 
{
	nodeType type; // Тип узла
	float value; // Значение числа (если тип узла - число)
	string name; // Имя переменной (если тип узла - переменная)
	Node *left, *right; // Ссылки на потомков узла
};
