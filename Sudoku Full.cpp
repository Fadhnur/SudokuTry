#include <iostream>
#include <fstream> // Membaca n mengedit file
#include <vector> // Memasukkan ke dalam array

class SudokuBoard {

private:
    std::vector < std::vector<int>> board;

public:

    //Contructor untuk membaca soal dari file
    SudokuBoard(const std::string& difficulty) {
        std::string filename = "sudoku_" + difficulty + ".txt";   //Mencetak nama file yang dipilih
        std::ifstream inputFile(filename);    //Membaca file yang dipilih
        if (!inputFile.is_open()) {
            std::cout << "Gagal membuka file" << std::endl;
            return;
        }
        //Apabila file berhasil dibuka maka menjalankan kode di sini
        for (int i = 0; i < 9; ++i) {    //menghitung banyak baris ke bawah
            std::vector<int>row;   //mencetak baris masuk ke dalam vector
            for (int j = 0; j < 9; ++j) {
                int num;
                inputFile >> num;   //membaca angka dari file ke dalam variabel num (inputFile merupakan objek dari kelas ifstream)
                row.push_back(num); //menambah angka ke dalam vektor baris
            }
            board.push_back(row);   //menambah baris ke dalam vektor papan
        }
        inputFile.close();
    }

    int GetNumber(int row, int col) const {
        return board[row][col];
    }

    void PlaceNumber(int row, int col, int num) {
        board[row][col] = num;      //menaruh angka pada koordinat
    }

    bool IsMoveValid(int row, int col, int num) const {
        // Periksa baris dan kolom
        for (int i = 0; i < 9; ++i) {
            if (board[row][i] == num || board[i][col] == num) {
                return false; // Ada angka yang sama di baris atau kolom
            }
        }

        // Periksa kotak 3x3
        int startRow = row / 3 * 3;   //mencari koordinat x (baris)
        int startCol = col / 3 * 3;   //mencari koordinat y (kolom)
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[startRow + i][startCol + j] == num) {     //array multidimensi [][] (koordinat pada satu kotak angka) memiliki nilai angka sama dengan "num"
                    return false; // Ada angka yang sama di kotak 3x3 bernilai salah
                }
            }
        }

        return true; // Tidak ada angka yang sama di baris, kolom, atau kotak 3x3
    }
    void PrintBoard() const {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                int num = board[i][j];      //koordinat disimpan pada variabel num
                if (num != 0) {             
                    std::cout << num << " ";    //mencetak angka dan spasi 
                }
                else {
                    std::cout << ". ";          //mencetak dot(.) apabila angka bernilai 0
                }

                if (j == 2 || j == 5) {     //mencetak pembatas setelah index ke 2 atau 5 (secara kolom, agar menjadi kotak)
                    std::cout << "| ";
                }
            }
            std::cout << std::endl;

            if (i == 2 || i == 5) {         //mencetak pembatas setelah index ke 2 atau 5 (secara baris, agar menjadi kotak)
                std::cout << "------+-------+------" << std::endl;
            }
        }
        std::cout << std::endl;
    }

    bool IsSolved() const {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == 0) {
                    return false; // Ada sel kosong, papan belum selesai
                }
            }
        }
        return true; // Tidak ada sel kosong, papan selesai
    }

};

class SudokuGame {
private:
    SudokuBoard board;     //memanggil class "PapanSudoku" dan memberi objek bernama "papan"

public:
    SudokuGame(const std::string& difficulty) : board(difficulty) {}

    void RunGame() {
        int baris, kolom, angka;
        while (!IsSolved()) {   //apabila semua kotak belum terisi maka akan looping terus
            board.PrintBoard();
            std::cout << "Enter baris, kolom, dan angka (0 untuk keluar): " << std::endl;
            std::cout << "Baris : "; std::cin >> baris;
            std::cout << "Kolom : "; std::cin >> kolom;
            std::cout << "Angka : "; std::cin >> angka;

            if (baris == 0 || kolom == 0) {     
                break;      //keluar dari permainan
            }

            if (IsValidMove(baris - 1, kolom - 1, angka)) {     //-1 karena pada baris dan kolom merupakan index yang dimulai dari 0
                board.PlaceNumber(baris - 1, kolom - 1, angka);
                std::cout << "Ok" << std::endl;
            }
            else {
                std::cout << "Salah" << std::endl;
            }
        }

        if (IsSolved()) {
            std::cout << "Congratulations! You solved the Sudoku." << std::endl;
        }
        else {
            std::cout << "Game over. Better luck next time!" << std::endl;
        }

    }

    bool IsValidMove(int baris, int kolom, int angka) {
        if (angka < 1 || angka > 9) {       //apabila angka yang dimasukkan krg dari 1 atau lebih dari 9 maka nilainya salah
            return false;
        }
        return board.IsMoveValid(baris, kolom, angka);  //keadaan benar dimasukkan ke dalam board
    }

    bool IsSolved() {
        return board.IsSolved();
    }


};


class SudokuChecker {
private:
    SudokuBoard& board;

public:
    SudokuChecker(SudokuBoard& sudokuBoard) : board(sudokuBoard) {}

    bool IsSudokuValid() {
        for (int i = 0; i < 9; ++i) {
            if (!IsRowValid(i) || !IsColValid(i) || !IsBoxValid(i)) {
                return false;
            }
        }
        return true;
    }

private:
    bool IsRowValid(int row) {
        std::vector<bool> used(10, false); // Untuk angka 1-9
        for (int i = 0; i < 9; ++i) {
            int num = board.GetNumber(row, i);
            if (num != 0) {
                if (used[num]) {
                    return false;
                }
                used[num] = true;
            }
        }
        return true;
    }

    bool IsColValid(int col) {
        std::vector<bool> used(10, false); // Untuk angka 1-9
        for (int i = 0; i < 9; ++i) {
            int num = board.GetNumber(i, col);
            if (num != 0) {
                if (used[num]) {
                    return false;
                }
                used[num] = true;
            }
        }
        return true;
    }

    bool IsBoxValid(int boxIndex) {
        int startRow = (boxIndex / 3) * 3;
        int startCol = (boxIndex % 3) * 3;
        std::vector<bool> used(10, false); // Untuk angka 1-9
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int num = board.GetNumber(startRow + i, startCol + j);
                if (num != 0) {
                    if (used[num]) {
                        return false;
                    }
                    used[num] = true;
                }
            }
        }
        return true;
    }
};

/*class UserInterface {
public:
    static int GetUserInput(const std::string& prompt) {
        int input;
        std::cout << prompt;
        std::cin >> input;
        return input;
    }

    static void DisplayBoard(const SudokuBoard& board) {
        std::cout << "Sudoku Board:" << std::endl;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                int num = board.GetNumber(i, j);
                if (num != 0) {
                    std::cout << num << " ";
                }
                else {
                    std::cout << ". ";
                }

                if (j == 2 || j == 5) {
                    std::cout << "| ";
                }
            }
            std::cout << std::endl;

            if (i == 2 || i == 5) {
                std::cout << "------+-------+------" << std::endl;
            }
        }
        std::cout << std::endl;
    }

    static void DisplayMessage(const std::string& message) {
        std::cout << message << std::endl;
    }
};*/

class MainProgram {
public:
    void Run() {
        std::cout << "Welcome to Sudoku Game!" << std::endl;

        std::string difficulty = GetDifficulty();
        SudokuGame game(difficulty);

        game.RunGame();

        /*if (game.IsSolved()) {
            std::cout << "Congratulations! You solved the Sudoku." << std::endl;
        }
        else {
            std::cout << "Game over. Better luck next time!" << std::endl;
        }*/
    }

private:
    std::string GetDifficulty() {
        std::cout << "Choose difficulty (mudah, sedang, sulit): ";
        std::string difficulty;
        std::cin >> difficulty;
        return difficulty;
    }


};

int main() {
    MainProgram program;
    program.Run();
    return 0;
}
