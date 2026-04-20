class Solution {
public:


    void dfs(vector<vector<int>>& image,int r,int c,int color,int newcolor,int m,int n) {


        if(r<0 || r>=m || c<0 || c>=n)return;
        if(image[r][c] != color)return;

        
        image[r][c]=newcolor;

        

        dfs(image,r+1,c,color,newcolor,m,n);
        dfs(image,r-1,c,color,newcolor,m,n);
        dfs(image,r,c+1,color,newcolor,m,n);
        dfs(image,r,c-1,color,newcolor,m,n);

    }


    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {

        int prev = image[sr][sc];
        int m = image.size();
        int n=image[0].size();


        if(prev == color){
            return image;
        }


        dfs(image,sr,sc,prev,color,m,n);

        return image;
    }
};

