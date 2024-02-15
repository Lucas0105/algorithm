#include<iostream>
#include<vector>

using namespace std;

vector<vector<char>> superDNA;
vector<vector<char>> DNA;
int N, M;

vector<char> Merge(vector<char> dna1, vector<char> dna2)
{
	vector<char> resultDNA;

	if (dna1.size() == 0 || dna2.size() == 0)
		return {};

	for (int i = 0; i < M; i++)
	{
		if (dna1[i] == '.')
			resultDNA.push_back(dna2[i]);
		else if (dna2[i] == '.')
			resultDNA.push_back(dna1[i]);
		else if (dna1[i] == dna2[i])
			resultDNA.push_back(dna1[i]);
		else
			return {};
	}
	
	return resultDNA;
}


void MakeSuperDNA(int pos)
{
	int loc = 0;
	int tmpPos = pos;
	while (tmpPos % 2 == 0)
	{
		loc += 1;
		tmpPos /= 2;
	}

	superDNA.push_back(Merge(DNA[loc], superDNA[pos - pow(2, loc)]));
}

int main() {

	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		vector<char> tmpArr;
		for (int j = 0; j < M; j++)
		{
			char tmp;
			cin >> tmp;
			tmpArr.push_back(tmp);
		}

		DNA.push_back(tmpArr);

	}

	vector<char> initDNA;
	for (int i = 0; i < M; i++)
		initDNA.push_back('.');
	superDNA.push_back(initDNA);

	for (int i = 1; i < pow(2, N); i++)
	{
		MakeSuperDNA(i);
	}

	for (int i = 0; i < pow(2, N); i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (superDNA[i].empty())
				break;
			cout << superDNA[i][j];
		}
		cout << "\n";
	}
}
