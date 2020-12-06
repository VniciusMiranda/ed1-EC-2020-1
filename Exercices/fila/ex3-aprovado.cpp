#include <iostream>
#include <list>

using namespace std;

int main(){
    list<int> fila;
    list<int>::iterator it;

    int n, id;

    cin >> n;

    while(n--)
    {
        cin >> id;
        fila.push_back(id);
    }

    cin >> n;

    while(n--)
    {
        cin >> id;
        fila.remove(id);
    }

    for(it = fila.begin(); it != fila.end(); ++it) 
        cout << *it << " ";

    return 0;
}


