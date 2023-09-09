#include <iostream>
#include <string>
using namespace std;

class Player{
    private :
    string Name;
    int WinCounter;

    public : 
    Player();
    Player(string name, int WinC);
    void setName (string name);
    string getName();
    void setWinCounter();
    int getWinCounter();
};