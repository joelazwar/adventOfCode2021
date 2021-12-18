#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

struct Grid{
    int value_;
    bool marked_;

    Grid():value_(0), marked_(false){};

    Grid(int value, bool mark=false)
    :value_(value), marked_(mark){};

    void print(){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        if(marked_){
            SetConsoleTextAttribute(hConsole, 112);
            cout << setfill(' ') << setw(2) << value_ << " ";
            SetConsoleTextAttribute(hConsole, 15);
        }
        else{
            cout << setfill(' ') << setw(2) << value_ << " ";
        }
    }

    void mark(){
        marked_=true;
    }
};

struct Board{
    vector<vector<Grid>> rowCol;
    int numMarked;

    Board():rowCol(), numMarked(0){};

    void push(vector<Grid> row){
        rowCol.push_back(row);
    }

    void print(){
        for(vector<Grid> row : rowCol){
            for(Grid g : row){
                g.print();
            }
            cout << endl;
        }
        cout << endl;
    }
    //return true if marked, return false otherwise
    bool markGrid(int grid){
        for(int i = 0; i<5; i++){
            for(int j = 0; j<5; j++){
                if(rowCol[i][j].value_ == grid){
                    rowCol[i][j].marked_ = true;
                    numMarked++;
                    return true;
                }
            }
        }
        return false;
    }

    bool checkBoard(){
        bool row[5] = {true, true, true, true, true};
        bool col[5] = {true, true, true, true, true};

        for(int i = 0; i <5; i++){
            for(int j = 0; j <5; j++){
                Grid g = rowCol[i][j];
                if(row[i] || col[j]){
                    if(!g.marked_){
                        row[i]= false;
                        col[j]= false;
                    }
                }
            }
        }
        

        for(int i = 0; i < 5; i++){
            if(row[i]|| col[i])
                return true;
        }

        
        


        return false;
    }

    int calculate(){
        int sum = 0;
        for(vector<Grid> grids: rowCol){
            for(Grid g: grids){
                if(!g.marked_)
                    sum += g.value_;
            }
        }

        return sum;
    }
};

int main(){//GET INPUT START
    ifstream file("giantSquid.txt");
    vector<int> number;
    string line;
    vector<Board> boards;

    getline(file, line);

    stringstream numbers(line);

    while (getline(numbers, line, ',')){
        number.push_back(stoi(line));
    }

    while(getline(file, line)){
        Board board;
        int i = 0;

        while(i<5){
            int j = 0;
            vector<Grid> row;
            getline(file, line);
            stringstream grid(line);
            string gridStr;
            while(j < 5){
                gridStr = "";
                while(gridStr == "")
                    getline(grid, gridStr, ' ');

                row.push_back(Grid(stoi(gridStr)));
                j++;
            }
            board.push(row);
            i++;
        }

        boards.push_back(board);
    }
    //GET INPUT END

    
    for(int i: number){
        cout << i << ", ";
    }

    vector<Board> boardsCopy(boards);
    Board theBoard;//to store answer
    int lastNum = 0;// to store final num
    int increment = 5;
    bool loop = true;
    for (int i = 0; i < number.size() && boards.size()>0; i++){//increment through numbers
        for (int j = 0; j < boards.size(); j++)//increment through board
        {
            boards[j].markGrid(number[i]);

            if (boards[j].checkBoard())
            {   
                cout <<endl;
                boards[j].print();

                if(boards.size() == 1){
                    theBoard = boards[0];
                }

                boards.erase(boards.begin()+j);
                j--;
            }
        }

        if(boards.size()==0){
            lastNum = number[i];
        }
    }

    int answer = theBoard.calculate()*lastNum;

    cout << endl;

    cout << "BINGO!!!!!!!!" << endl << endl;

    theBoard.print();

    cout << "Sum of unmarked is "<< theBoard.calculate();

    cout << " and the last number is " << lastNum<< endl;

    cout << "the answer is " << answer << endl;

    cout << "Press enter to exit";

    cin.ignore();

    return 0;



}