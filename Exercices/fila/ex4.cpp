#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

typedef enum { jack, john, jade } Competidor_t; 

void show(list<int> l){
    for(auto s : l) cout << s << " ";
    cout << endl;
}


int solve_problems( Competidor_t comp, list<int> problems, int duration, int* problems_solve){


    switch(comp){
        case john:
            // do nothing
            break;
        case jack:
            problems.sort();
            break;
        case jade:
            problems.sort(greater<int>());
            break;
    }


    int points;
    *problems_solve = 0;
    list<int>::iterator it = problems.begin();

    for(points = 0; points <= duration && it != problems.end(); points += *it) 
    {
        (*problems_solve)++;
        it++;
    }

    return points;
}

Competidor_t getWinner(list<int> problems, int duration, int* points, int* problems_solve){
    Competidor_t winner;
    int i = 0, aux = 0, solved;
    *points = 0;

    while (i < 3)
    {
        aux = solve_problems((Competidor_t)i, problems, duration, &solved);

        if (aux > *points)
        {
            winner = (Competidor_t)i;
            *points = aux;
            *problems_solve = solved;
        }
        i++;
    }

    return winner;
}

int main(){

    int n, competition_duration, num_problems, problem;
    int points, problems_solve;
    list<int> problems; 

    cin >> n;

    while(n--)
    { 
        cin >> competition_duration >> num_problems;

        while(num_problems--)
        {
            cin >> problem;
            problems.push_back(problem);
        }

        switch(getWinner(problems, competition_duration, &points, &problems_solve)){
            case john:
                cout << "john ";
                break;
            case jack:
                cout << "jack ";
                break;
            case jade:
                cout << "jade ";
                break;
        }
         cout << problems_solve << " " << points << endl;

        problems.clear();
    }

    return 0;
}


