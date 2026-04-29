#include<bits/stdc++.h>
using namespace std;

int main(){


    ifstream tableFile("table.txt");
    if(!tableFile){
        cerr << "Error: table.txt not found. Run generator first." << endl;
        return 1;
    }

    map<char, string> huffmanCode;
    int asciiVal;
    string code;
    while(tableFile >> asciiVal >> code){
        huffmanCode[(char)asciiVal] = code;
    }
    tableFile.close();



    string text = "";
    char c;
    while(cin.get(c)){
        text += c;
    }

    ofstream outFile("compressed.bin", ios::binary);
    
    int totalChars = text.size();
    outFile.write(reinterpret_cast<const char*>(&totalChars), sizeof(totalChars));

    char buffer = 0;
    int count = 0;

    for(char ch : text){
        string currentCode = huffmanCode[ch];
        for(char bit : currentCode){
            buffer = buffer << 1;
            if(bit == '1') {
                buffer = buffer | 1;
            }
            count++;

            if(count == 8){
                outFile.write(&buffer, 1);
                buffer = 0;
                count = 0;
            }
        }
    }

    if(count > 0){
        buffer = buffer << (8 - count);
        outFile.write(&buffer, 1);
    }

    outFile.close();
}