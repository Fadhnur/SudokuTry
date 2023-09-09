
class Board{
	private:
		int cells [9][9];
			
	public:
		Board();
		int getCellatCoordinate (int x, int y);
        bool isCellAvailable (int x, int y);
		void setCellatCoordinate (int x, int y, int value);

		bool checkHorizontal (int index);
		bool checkVertikal (int index);
		bool checkRegional (int index);

		void Print();
};