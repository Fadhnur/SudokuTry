#include "Board.cpp"
#include "Player.h"

using namespace std;

class GameManager{
    private :
        Player p;
        Board brd;

    public :
        GameManager(Player plyr, Board brd);
        void setPlayer(Player player);
        Player getPlayer();
        void setBoard (Board brd);
        Board getBoard();

        void play();
        void save();
        void load();

        bool checkWin();
};

int main(){
    Player p1;
    Board br;

    GameManager game(p1, br);
    game.play();
}