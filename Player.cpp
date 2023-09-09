#include <iostream>
#include "Player.h" //memanggil header
using namespace std;

Player :: Player(){     //tidak perlu menambahkan void
    Name = " ";
    WinCounter = 0;
}

Player :: Player(string name, int WinC){
    Name = name;
    WinCounter = WinC;
}

void Player :: setName(string name){
    Name = name;
}

string Player ::getName(){
    return Name;
}

void Player :: setWinCounter(){
    WinCounter++;
}

int Player :: getWinCounter(){
    return WinCounter;
}