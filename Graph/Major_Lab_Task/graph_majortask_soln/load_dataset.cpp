#include<bits/stdc++.h>
using namespace std;


struct Node
{
    double lon,lat;
};


map<Node,int>nodeToID;
vector<Node>idToNode;






int getID(Node p){
    
    if(nodeToID.count(p)){
        return nodeToID[p];
    }

    int id = nodeToID.size();
    nodeToID[p] = id;
    idToNode.push_back(p);
}







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

 
        for(int k=0; k<roadPoints.size(); k++){
            Node u = roadPoints[k];
            Node v = roadPoints[k];

            int u = getID(u);
            int v = getID(v);
            double w = haversine(u,v);
        }
    }






}