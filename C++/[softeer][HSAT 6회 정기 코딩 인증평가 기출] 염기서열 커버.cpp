#include<iostream>
#include<vector>
#include<cstring>
#include<math.h>

using namespace std;

vector<vector<char>> superDNA;
vector<vector<char>> DNA;
int N, M;
int* answer;

int GetAnswer(int index)
{
	vector<int>bit;

	if (answer[index] < N + 1)
		return answer[index];

	int number1 = 0;
	int number2 = index;
	int tmpIndex = index;
	for (int i = 0; i < N; i++)
	{
		if (tmpIndex % 2 == 1)
			bit.push_back(i);

		tmpIndex /= 2;
	}

	int* digit = (int*)malloc(sizeof(int) * bit.size());
	memset(digit, 0, sizeof(int) * bit.size());

	for (int i = 1; i < pow(2, bit.size() - 1); i++)
	{
		for (int j = 0; j < bit.size(); j++)
		{
			if (digit[j] == 0)
			{
				digit[j] = 1;
				int tmp = pow(2, bit[j]);
				number1 += tmp;
				number2 -= tmp;
				break;
			}
			else {
				digit[j] = 0;
				int tmp = pow(2, bit[j]);
				number1 -= tmp;
				number2 += tmp;
			}
		}
		int tmpResult = GetAnswer(number1) + GetAnswer(number2);

		if (answer[index] > tmpResult)
			answer[index] = tmpResult;
	}
	free(digit);
	return answer[index];
}

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

	answer = (int*)malloc(sizeof(int) * pow(2, N));
	answer[0] = 0;

	for (int i = 1; i < pow(2, N); i++)
	{
		answer[i] = N + 1;
	}

	for (int i = 1; i < pow(2, N); i++)
	{
		if (superDNA[i].empty())
			GetAnswer(i);
		else
			answer[i] = 1;
	}

	cout << answer[(int)pow(2, N) - 1];
}
