#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

struct Pipe{
    int startX_;
    int startY_;
    int stopX_;
    int stopY_;

    Pipe():startX_(0), startY_(0), stopX_(0), stopY_(0){};

    Pipe(int x1, int y1, int x2, int y2)
    :startX_(x1), startY_(y1), stopX_(x2), stopY_(y2){};

    void print(){
        cout << startX_ << "," << startY_ << " -> "
        <<stopX_ << "," << stopY_ << endl;
    }
};

struct Diagram{
    vector<vector<int>> table;
    int overlap;

    Diagram():table(), overlap(0){};

    Diagram(vector<vector<int>> other){
        table = other;
        overlap = 0;
    };

    void addPipe(Pipe pipe){
        int x1,y1,x2,y2;

        if(pipe.startX_< pipe.stopX_){
            x1 = pipe.startX_;
            x2 = pipe.stopX_;
        }
        else{
            x1 = pipe.stopX_;
            x2 = pipe.startX_;
        }

        if(pipe.startY_< pipe.stopY_){
            y1 = pipe.startY_;
            y2 = pipe.stopY_;
        }
        else{
            y1 = pipe.stopY_;
            y2 = pipe.startY_;
        }


        if(pipe.startX_==pipe.stopX_){
            for(int i = y1; i <= y2; i++){
                if(++table[i][x1] == 2){
                    overlap++;
                }
            }
        }else if(pipe.startY_==pipe.stopY_){
            for(int i = x1; i <= x2; i++){
                if(++table[y1][i] == 2){
                    overlap++;
                }
            }
        }else{
            if((pipe.stopX_-pipe.startX_)/(pipe.stopY_-pipe.startY_) > 0){
                for(int i = 0; i <= (x2-x1); i++){
                    if(++table[y1+i][x1+i] == 2){
                        overlap++;
                    }
                }
            }
            else{
                for(int i = 0; i <= (x2-x1); i++){
                    if(++table[y2-i][x1+i] == 2){
                        overlap++;
                    }
                }
            }
        }

        // cout << endl;
        // print();
        // cout << endl;
    }

    void print(){
        for (vector<int> row: table){
            for(int grid: row){
                if(grid == 0){
                    cout <<".";
                }
                else{
                    cout << grid;
                }
            }
            cout << endl;
        }
    }
};

int main(){//GET INPUT START
    ifstream file("hydrothermalVenture.txt");
    vector<Pipe> pipes;
    string line;
    int x,y;
    x = y = 0;

    while(getline(file, line)){
        int x1,y1,x2,y2;
        stringstream ss(line);

        char comma, space, misc;

        ss >> x1 >> comma >> y1 >> space >> misc
        >> x2 >> comma >> y2;

        if(x < x1 || x < x2){
            x = x1<x2? x2: x1;
        }

        if(y < y1 || y < y2){
            y = y1<y2? y2: y1;
        }

        pipes.push_back(Pipe(x1,y1,x2,y2));
    }
    //GET INPUT FINISH

    Diagram diagram(vector<vector<int>>(y+1, vector<int>(x+1)));

    for(Pipe p : pipes){
        p.print();
        diagram.addPipe(p);
    }

    // cout << endl;

    // diagram.print();

    // cout <<endl;

    cout << "The number of points where at least 2 lines over lap is " << diagram.overlap << endl;

    cout << "Press Enter to exit";

    cin.ignore();

    return 0;
}