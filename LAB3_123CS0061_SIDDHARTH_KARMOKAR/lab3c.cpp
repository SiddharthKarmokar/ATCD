#include<bits/stdc++.h>
using namespace std;

map<int, string> mp;
void makeMP()
{
    mp[1] = "A";
    mp[10] = "B";
    mp[100] = "C";
    mp[1000] = "D";
    mp[11] = "AB";
    mp[101] = "AC";
    mp[110] = "BC";
    mp[111] = "ABC";
    mp[1001] = "AD";
    mp[1010] = "BD";
    mp[1100] = "CD";
    mp[1011] = "ABD";
    mp[1101] = "ACD";
    mp[1110] = "BCD";
    mp[1111] = "ABCD";
}

int solve(int currstate, map<pair<int, int>, int> nfa, int curralpha)
{
    if(currstate == 11) // 1 & 10
    {
        int a = nfa[{1, curralpha}];
        int b = nfa[{10, curralpha}];
        return a + b;
    }
    else if(currstate == 101)
    {
        int a = nfa[{1, curralpha}];
        int b = nfa[{100, curralpha}];
        return a + b;
    }
    else if(currstate == 110)
    {
        int a = nfa[{100, curralpha}];
        int b = nfa[{10, curralpha}];
        return a + b;
    }
    else if(currstate == 111)
    {
        int a = nfa[{100, curralpha}];
        int b = nfa[{11, curralpha}];
        return a + b;
    }
    else if(currstate == 1001)
    {
        int a = nfa[{1000, curralpha}];
        int b = nfa[{1, curralpha}];
        return a + b;
    }
    else if(currstate == 1010)
    {
        int a = nfa[{1000, curralpha}];
        int b = nfa[{10, curralpha}];
        return a + b;
    }
    else if(currstate == 1011)
    {
        int a = nfa[{1000, curralpha}];
        int b = nfa[{11, curralpha}];
        return a + b;
    }
    else if(currstate == 1100)
    {
        int a = nfa[{1000, curralpha}];
        int b = nfa[{100, curralpha}];
        return a + b;
    }
    else if(currstate == 1101)
    {
        int a = nfa[{1000, curralpha}];
        int b = nfa[{101, curralpha}];
        return a + b;
    }
    else if(currstate == 1110)
    {
        int a = nfa[{1000, curralpha}];
        int b = nfa[{110, curralpha}];
        return a + b;
    }
    else if(currstate == 1111)
    {
        int a = nfa[{1000, curralpha}];
        int b = nfa[{111, curralpha}];
        return a + b;
    }
    return 0;
}

void createDFA(map<pair<int, int>, int> &nfa, set<int> &s, int t, int states)
{
    for(auto &p : nfa)
    {
        if(s.find(p.second) == s.end())
        {
            int currstate = p.second, curralpha = 0;
            for(int i = 0; i < t; i++)
            {
                nfa[{currstate, curralpha}] = solve(currstate, nfa, curralpha);
                curralpha++;
            }
            s.insert(currstate);
        }
    }

    cout<<"\n\nOur Current DFA Table : \n\n";
    for(auto &p : nfa)
    {
        pair<int, int> initial = p.first;
        int final = p.second;

        cout<<initial.first<<" "<<initial.second<<" --> "<<final<<endl;
    }
    
    bool flag = true;

    for(auto &p : nfa)
    {
        if(s.find(p.second) == s.end())
        {
            flag = false;
            break;
        }
    }

    if(flag) return;
    else createDFA(nfa, s, t, states);
}


int main()
{

    cout<<"NOTE : \nStates : 1, 10, 100, 1000, ...\nAlphabets : 0, 1, 2, 3, ...\n";
    cout<<"If transition state is {A,B}, expected input is 1 + 10 = 11\n";
    cout<<endl;
    cout<<endl;

    int states;
    cout<<"Number of states : ";
    cin>>states;

    int st = 1;
    set<int> s;
    s.insert(0);
    for(int i = 0; i < states; i++)
    {
        s.insert(st);
        st *= 10;
    }
 

    int t;
    cout<<"Number of alphabets : ";
    cin>>t;

    
    // constructing transition tables for NFA:
    map<pair<int, int>, int> nfa; // basically {state i, alphabet j} --> state k

    int currstate = 1;

    for(int i = 0; i < states; i++)
    {
        int curralpha = 0;
        for(int j = 0; j < t; j++)
        {
            int x;
            cout<<"For state "<<currstate<<" and alphabet "<<curralpha<<" the next state is : ";
            cin>>x;
            nfa[{currstate, curralpha}] = x;
            curralpha += 1;
        }
        currstate *= 10;
    }


    cout<<"\n\nOur NFA Table : \n\n";
    for(auto &p : nfa)
    {
        pair<int, int> initial = p.first;
        int final = p.second;

        cout<<initial.first<<" "<<initial.second<<" --> "<<final<<endl;
    }

    createDFA(nfa, s, t, states);

    bool flag = true;

    for(auto &p : nfa)
    {
        if(s.find(p.second) == s.end())
        {
            flag = false;
            break;
        }
    }

    if(!flag) createDFA(nfa, s, t, states);

}

// Our given input will be a transition table for all the initial states

// Assign the states values like 1, 10, 100, 1000, 10000 ... so that union can be detected easily
// Assign values of 0 to phi