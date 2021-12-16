#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

long long int binaryToDecimal(string n)
{
    string num = n;
    long long int dec_value = 0;
 
    // Initializing base value to 1, i.e 2^0
    long long int base = 1;
 
    long long int len = num.length();
    for (long long int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
 
    return dec_value;
}
string findRate(vector<string> table, string condition = "o2"){

    vector<string> temp = table;
    int counter = 1;
    
    while(temp.size()>1){
        vector<string> temp0, temp1;

        for (string s : temp)
        {
            //cout << "analyze " << s;
            if (s[counter] == '1')
            {
                temp1.push_back(s);
                //cout << " push to temp1" << endl;
            }
            else
            {
                temp0.push_back(s);
                //cout << " push to temp0" << endl;
            }
        }
        
        if(condition == "o2"){
            if(temp1.size() < temp0.size()){
                temp = temp0;
            }
            else{
                temp = temp1;
            }
        }
        else if(condition == "co2"){
            if(temp1.size() < temp0.size()){
                temp = temp1;
            }
            else{
                temp = temp0;
            }
        }
            
        counter++;
    }
    
    return temp[0];

}

int main(){
    ifstream file("binaryDiagnostic.txt");
    string line;
    vector<string> table0, table1;

    while (getline(file, line)){


        if(line[0] == '1'){
            table1.push_back(line);
        }
        else{
            table0.push_back(line);
        }

        
    }
    
    vector<string> o2, co2;
    o2 = table1.size() < table0.size() ? table0 : table1;
    co2 = table1.size() < table0.size() ? table1 : table0;


    long long int o2Dec = binaryToDecimal(findRate(o2));
    long long int co2Dec = binaryToDecimal(findRate(co2, "co2"));

    cout << "oxygen generator rating is " << o2Dec << endl 
    << "CO2 scrubber rating is " << co2Dec << endl
    << "the life support rating of the submarine is " <<  o2Dec * co2Dec << endl;  

    // int bitLength = o2[0].size();

    // for(int i = 1; i < bitLength; i ++){
    //     vector<char> row0, row1;
    //     for (int j = 0; j < o2.size(); j++){
    //         if(o2[j][i] == '1')
    //             row1.push_back(line[i]);
    //         else
    //             row0.push_back(line[i]);
    //     }
    //     // strMaj.push_back((majCounter < 0) ? '0' : '1');
    //     // strMin.push_back((majCounter < 0) ? '1' : '0');
    //     strMaj.push_back((majCounter < o2.size()/2) ? '0' : '1');
    //     strMin.push_back((majCounter < o2.size()/2) ? '1' : '0');
    // }

    // long long int gamma, epsilon;

    // gamma = binaryToDecimal(strMaj);
    // epsilon = binaryToDecimal(strMin);

    // cout << "gamma rate is " << gamma << endl 
    // << "epsilon rate is " << epsilon << endl
    // << "power consumption is " <<  gamma * epsilon << endl;


    return 0;
}
