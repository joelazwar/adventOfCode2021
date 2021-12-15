#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Movement{
    string dir_;
    int mag_;

    Movement(string dir, int mag)
    : dir_(dir), mag_(mag){};
};

int main(){
    ifstream file("dive.txt");
    string line;
    vector<Movement> movements;
    int counter = 0;
    string dir;
    int mag;

    while (getline(file, line)){
        dir = line.substr(0, line.length()-2);
        mag =line[line.length()-1]-'0';

        movements.push_back(Movement(dir, mag));
    }

    int x, y, aim;
    x = y = aim = 0;

    for (Movement m : movements){
        //part 1 commented out
        if (m.dir_ == "forward"){
            //x += m.mag_;
            x += m.mag_;
            y += aim*m.mag_;
        }
        else if(m.dir_ == "down"){
            //y += m.mag_;
            aim += m.mag_;
        }
        else if(m.dir_ == "up"){
            //y -= m.mag_;
            aim -= m.mag_;
        }

    }

    cout << "horizontal position of "<< x 
    << ", a depth of " << y << ", and an aim of " << aim << endl;

    cout << "Multiplying these together produces " << x*y << endl;
}