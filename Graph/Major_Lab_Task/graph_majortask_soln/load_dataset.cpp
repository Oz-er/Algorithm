#include<bits/stdc++.h>
using namespace std;



struct Node
{
    double lon,lat;
};





void load_roadmap(string filename){

    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"could not open file lol "<<filename<<endl;
        exit(1);
    }

   
    string line;
    while(getline(file,line)){

        if(line.empty()){
            continue;
        }


        stringstream ss(line);
        string token;
        vector<string>tokens;



        while(getline(ss,token,',')){
            tokens.push_back(token);
        }
        if(tokens.size() < 5){
            continue;
        }



        vector<Node>roadPoints;
        for(int i=1;i<tokens.size()-2;i+=2){
            double lon = stod(tokens[i]);
            double lat = stod(tokens[i+1]);
            roadPoints.push_back({lon,lat});
        }
    }


}