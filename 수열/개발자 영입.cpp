
#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

struct Developer {
    int pid, salary, C, J, P;
};

vector<Developer> DeV;

int pid, salary, C, J, P, flag, X;

void RegisterPid()
{
    cin >> pid >> salary >> C >> J >> P;

    Developer newDeveloper{ pid, salary, C, J, P };

    DeV.push_back(newDeveloper);
}

void CancelPid()
{
    cin >> pid;

    for (int i = 0; i < DeV.size(); i++)
    {
        if (DeV[i].pid == pid) {
            DeV[i] = DeV.back();
            DeV.pop_back();
            break;
        }
    }
}

void UpdatePid()
{
    cin >> pid >> flag >> X;
    for (vector<Developer>::iterator it = DeV.begin(); it != DeV.end(); ++it)
    {
        if (it->pid == pid)
        {
            if (flag == 0)
                it->C = X;
            else if (flag == 1)
                it->J = X;
            else
                it->P = X;

            break;
        }
    }
}

bool HireMinComp(Developer l, Developer r)
{
    if (l.salary != r.salary)
        return l.salary < r.salary;
    return l.pid < r.pid;
}

bool HireMaxComp(Developer l, Developer r)
{
    int SumL = l.C + l.J + l.P;
    int SumR = r.C + r.J + r.P;

    if (SumL != SumR)
        return SumL > SumR;
    return l.pid > r.pid;
}

void HireMin()
{
    partial_sort(DeV.begin(), DeV.begin() + 1, DeV.end(), HireMinComp);
    cout << DeV.front().pid << "\n";
    DeV[0] = DeV.back();
    DeV.pop_back();
}

void HireMax()
{
    partial_sort(DeV.begin(), DeV.begin() + 3, DeV.end(), HireMaxComp);
    cout << DeV[0].pid << " " << DeV[1].pid << " " << DeV[2].pid << "\n";
    DeV[0] = DeV.back();
    DeV[1] = DeV.at(DeV.size() - 2);
    DeV[2] = DeV.at(DeV.size() - 3);
    DeV.pop_back();
    DeV.pop_back();
    DeV.pop_back();
}

int main()
{
    FILE* stream;
    freopen_s(&stream, "개발자 영입.txt", "r", stdin);
    int Q;
    string cmd;
    cin >> Q;

    for (int i = 0; i < Q; i++)
    {
        cin >> cmd;

        if (cmd == "register")
            RegisterPid();
        else if (cmd == "cancel")
            CancelPid();
        else if (cmd == "update")
            UpdatePid();
        else if (cmd == "hire_min")
            HireMin();
        else if (cmd == "hire_max")
            HireMax();
    }

    return 0;
}
