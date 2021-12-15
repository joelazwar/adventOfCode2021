#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main(){
    ifstream file("sonarSweep.txt");
    string line;
    vector<int> measurements;
    int counter = 0;

    while (getline(file, line)){
        measurements.push_back(stoi(line));
    }

    // int prevMeasure = measurements[0];

    // for(int i = 1; i<measurements.size(); i++){
    //     if (prevMeasure < measurements[i])
    //         counter++;

    //     prevMeasure = measurements[i];
            
    // }
    for(int i = 2 ; i < measurements.size()-1; i++){
        if(measurements[i-2] + measurements[i-1] + measurements[i] < measurements[i-1] + measurements[i] + measurements[i+1])
            counter++;

    };

    cout << "There are " << counter << " sums that are larger than the previous sums" << std::endl;

    cout << std::endl << "Press Enter to exit";

    cin.ignore();

    return 0;
}