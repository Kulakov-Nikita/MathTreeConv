enum nodeType{Unknown,Var,Num,Plus,Minus,Mul,Div,Pow};

class Node 
{
	nodeType type; // ��� ����
	float value; // �������� ����� (���� ��� ���� - �����)
	string name; // ��� ���������� (���� ��� ���� - ����������)
	Node *left, *right; // ������ �� �������� ����
};
