#include"iostream"
#include "vector"
using namespace std;
struct OperatorOrder{
	int operatorNo;
	int cellNo1;
	int cellNo2;
};
class lattice
{
	friend istream& operator>>(istream&, lattice&);
	friend ostream& operator<<(ostream&, lattice&);
public:
	lattice();
	lattice(istream &is){ is >> *this; }

private:
	int cellNo;
	int operatorNo;
	vector<OperatorOrder> operatorOrder;
	vector<int> cellWeight;
	const int maxSection(int &sectionBegin, int &sectionEnd);
	const int sumSectiom(int &sectionBegin, int &sectionEnd);
	void modify(int &latticeNo, int &newWeight);

protected:
};

const int lattice::sumSectiom(int &sectionBegin, int &sectionEnd)
{
	int sum = 0;
	for (int i = sectionBegin-1; i <= sectionEnd-1; i++)
		sum += cellWeight[i];
	return sum;
}
const int lattice::maxSection(int &sectionBegin, int &sectionEnd)
{
	int maxS = 0;
	for (int i = sectionBegin-1; i <= sectionEnd-1;i++)
	if (cellWeight[i] > maxS)
		maxS = cellWeight[i];
	return maxS;
}
void lattice::modify(int &latticeNo, int &newWeight)
{
	cellWeight[latticeNo - 1] = newWeight;
}

istream& operator>>(istream& in, lattice& l)
{
	in >> l.cellNo >> l.operatorNo;
	int cellWeight;
	for (int i = 0; i < l.cellNo; i++)
	{
		in >> cellWeight;
		l.cellWeight.push_back(cellWeight);
	}
	OperatorOrder operatorOrder;
	for (int i = 0; i < l.operatorNo; i++)
	{
		in >> operatorOrder.operatorNo >> operatorOrder.cellNo1 >> operatorOrder.cellNo2;
		l.operatorOrder.push_back(operatorOrder);
	}
	return in;
}
ostream& operator<<(ostream& out, lattice& l)
{
	for (int i = 0; i < l.operatorNo;i++)
	{
		switch (l.operatorOrder[i].operatorNo)
		{
		case 1: 
			l.modify(l.operatorOrder[i].cellNo1, l.operatorOrder[i].cellNo2);
			break;
		case 2:
			out << l.sumSectiom(l.operatorOrder[i].cellNo1, l.operatorOrder[i].cellNo2)<<endl;
			break;
		case 3:
			out << l.maxSection(l.operatorOrder[i].cellNo1, l.operatorOrder[i].cellNo2) << endl;
			break;
		default:
			break;
		}
	}
	return out;
	
}

int main()
{
	lattice latticeTest(cin);
	cout << latticeTest;
	return 0;
}
