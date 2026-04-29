#include<bits/stdc++.h>
using namespace std;

int main(){
    // 1. Load Table and build Reverse Mapping
    ifstream tableFile("table.txt");
    if(!tableFile){
        cerr << "Error: table.txt not found." << endl;
        return 1;
    }

    map<string, char> reverseMapping;
    int asciiVal;
    string code;
    while(tableFile >> asciiVal >> code){
        reverseMapping[code] = (char)asciiVal;
    }
    tableFile.close();

    // 2. Read Compressed Binary
    ifstream inFile("compressed.bin", ios::binary);
    if(!inFile){
        cerr << "Error: compressed.bin not found." << endl;
        return 1;
    }

    int totalChars;
    inFile.read(reinterpret_cast<char*>(&totalChars), sizeof(totalChars));

    // 3. Decompress
    ofstream outFile("decompressed.txt");
    string currentString = "";
    char byte;
    int charsDecoded = 0;

    while(inFile.get(byte)){
        // Read bit by bit from the byte
        for(int i = 7; i >= 0; i--){
            int bit = (byte >> i) & 1;
            
            if(bit == 1) currentString += "1";
            else currentString += "0";

            if(reverseMapping.count(currentString)){
                outFile << reverseMapping[currentString];
                charsDecoded++;
                currentString = "";
                
                if(charsDecoded == totalChars) break;
            }
        }
        if(charsDecoded == totalChars) break;
    }

    inFile.close();
    outFile.close();
}