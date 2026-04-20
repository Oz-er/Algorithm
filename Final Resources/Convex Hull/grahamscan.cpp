#include<bits/stdc++.h>
using namespace std;

struct Point{
    int x;
    int y;
};

Point p0;


//-----------------returning the 2nd top element------------------------
Point nextToTop(vector<Point>& S) {
    Point p = S.back();
    S.pop_back();
    Point res = S.back();
    S.push_back(p);
    return res;
}
//----------------------------------------------------------------------






//-------------------returning the squared distance---------------------
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
//----------------------------------------------------------------------






//---------------------comparing by polar angles--------------------------
//------------------------------------------------------------------------

int orientation(Point p, Point q, Point r) {

    long long val = (long long)(q.x-p.x)*(r.y-p.y)
                  - (long long)(q.y-p.y)*(r.x - p.x);

    if (val == 0)
    return 0; // collinear


    if(val> 0){
    return 2;
    }
    else{
    return 1;
    }
    // 2 = counterclockwise
    // 1 = clockwise
}

bool comparePoints(Point p1, Point p2){


    int o = orientation(p0,p1,p2);


    //o = 2 --> p1 comes before p2 
    //o = 0 --> closer point to p0 comes first

    if(o==0){

    long long dist1 = distSq(p0,p1);
    long long dist2 = distSq(p0,p2);

        if(dist1<dist2){
        return true;
        }

        else{
        return false;
        }
    }

    if(o==2)return true;
    return false;

}

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------





void convexHull(vector<Point> &points){

    int n=points.size();
    if(n<3){
    cout<<"not possible"<<endl;
    return;
    }



//---------finding bottom most point-------------
//---------leftmost if its a tie ----------------

    int ymin = points[0].y;
    int min =0;

    for(int i=1;i<n;i++){

    int y= points[i].y;
    if(y<ymin){
    ymin = points[i].y;
    min=i;
    
    }
    else if(ymin==y){
        //tie
        if(points[i].x < points[min].x){
        ymin=points[i].y;
        min=i;
        }
    }
    }
    swap(points[0],points[min]);
    p0=points[0];
//-------------------------------------------------    
    
    
    sort(points.begin()+1,points.end(),comparePoints);


    vector<Point>mPoints;
    mPoints.push_back(p0);

    for(int i=1;i<n;i++){


//------------- keep avoiding the points------------------------------- 
//------------- while they are on the same line------------------------
//------------- only push the furthest one
    while (i < n - 1 && orientation(p0, points[i], points[i+1]) == 0) {
    i++;
    }
    mPoints.push_back(points[i]);
    }
//---------------------------------------------------------------------
//---------------------------------------------------------------------

    if (mPoints.size() < 3) return;  

    vector<Point> S;
    S.push_back(mPoints[0]);
    S.push_back(mPoints[1]);
    S.push_back(mPoints[2]);


    for(size_t i=3 ;i<mPoints.size();i++){
        while(S.size()>1 && orientation(nextToTop(S),S.back(),mPoints[i])!=2){
        S.pop_back();
        }
        S.push_back(mPoints[i]);
    }

    for (size_t i = 0; i < S.size(); i++) {
        cout << "(" << S[i].x << ", " << S[i].y << ")" << endl;
    }

}




//--------------------------------extra stuff-----------------------------------------
//------------------------------------------------------------------------------------

//================ SEGMENT INTERSECTION =================//

bool onSegment(Point p, Point q, Point r){
    return (q.x <= max(p.x,r.x) && q.x >= min(p.x,r.x) &&
            q.y <= max(p.y,r.y) && q.y >= min(p.y,r.y));
}

bool doIntersect(Point p1, Point p2, Point p3, Point p4){

    int o1 = orientation(p1,p2,p3);
    int o2 = orientation(p1,p2,p4);
    int o3 = orientation(p3,p4,p1);
    int o4 = orientation(p3,p4,p2);

    if(o1 != o2 && o3 != o4) return true;

    if(o1==0 && onSegment(p1,p3,p2)) return true;
    if(o2==0 && onSegment(p1,p4,p2)) return true;
    if(o3==0 && onSegment(p3,p1,p4)) return true;
    if(o4==0 && onSegment(p3,p2,p4)) return true;

    return false;
}
//========================================================//

//================ POINT IN POLYGON =================//

bool isInside(vector<Point>& polygon, Point p){

    int n = polygon.size();
    if(n < 3) return false;

    Point extreme = {1000000000, p.y};

    int count = 0, i = 0;

    do{
        int next = (i+1)%n;

        if(doIntersect(polygon[i], polygon[next], p, extreme)){

            if(orientation(polygon[i], p, polygon[next]) == 0){
                return onSegment(polygon[i], p, polygon[next]);
            }

            count++;
        }

        i = next;

    }while(i != 0);

    return (count % 2 == 1);
}

//================ CONVEX POLYGON CHECK =================//

bool isConvex(vector<Point>& poly){

    int n = poly.size();
    if(n < 3) return false;

    int prev = 0;

    for(int i=0;i<n;i++){
        int o = orientation(poly[i],
                            poly[(i+1)%n],
                            poly[(i+2)%n]);

        if(o != 0){
            if(prev != 0 && o != prev) return false;
            prev = o;
        }
    }

    return true;
}

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------







int main() {
    
    int n;
    
    cout << "Enter the number of points: ";
    cin >> n;

    vector<Point> points;
    int x, y;

   
    cout << "Enter the coordinates (x y) for each point:"<<endl;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;  
        points.push_back({x, y}); 
    }
    
    cout << "\nThe points in the convex hull are: \n";
    convexHull(points);
    
    return 0;
}




// Input: points[][] = [ [0, 0], [1, -4], [-1, -5], [-5, -3], [-3, -1], [-1, -3], 
//                                  [-2, -2], [-1, -1], [-2, -1], [-1, 1]]
// Output: [[-5, -3], [-1, 1], [0, 0], [1, -4], [-1, -5]


// 10
// 0 0
// 1 -4
// -1 -5
// -5 -3
// -3 -1
// -1 -3
// -2 -2 
// -1 -1
// -2 -1
// -1 1
