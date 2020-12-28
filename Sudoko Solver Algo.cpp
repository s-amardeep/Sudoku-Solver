#include<iostream>
#include<cmath>
using namespace std;

bool can_we_place_number(int grid[][9],int i,int j,int n,int number)
{
    //Check that number is not present in that row and column
    for(int x=0;x<n;x++)
    {
        if(grid[x][j]==number or grid[i][number]==number)
            return false;
    }
    //Now check number is that sub grid
    int root_n=sqrt(n);
    int start_x=(i/root_n)*root_n;
    int start_y=(j/root_n)*root_n;
    for(int x=start_x;x<start_x+root_n;x++)
    {
        for(int y=start_y;y<start_y+root_n;y++)
        {
            if(grid[x][y]==number)
                return false;
        }
    }
    return true;
}

bool solve_sudoko(int grid[][9],int i,int j,int n)
{
    //Base Case
    //If whole sudoko is solved means i==n then return
    if(i==n)
    {
        //Print the grid and return;
        for(int x=0;x<n;x++)
        {
            for(int y=0;y<n;y++)
                cout<<grid[x][y]<<" ";
            cout<<endl;
        }
        return true;
    }
    //If we are at last column and want to go next row
    if(j==n)
        return solve_sudoko(grid,i+1,0,n);
    //If current cell is pre-filled then jumps to next cell
    if(grid[i][j]!=0)
        return solve_sudoko(grid,i,j+1,n);
    //Recursive Case
    //Fill the current cell with all possible numbers
    for(int number=1;number<=n;number++)
    {
        if(can_we_place_number(grid,i,j,n,number)==1)
        {
            //Assume
            grid[i][j]=number;
            //Check ahead
            bool next_cell = solve_sudoko(grid,i,j+1,n);
            if(next_cell==1)
                return true;
            //else backtrack
        }
    }
    //Backtrack
    grid[i][j]=0;
    return false;
}

int main()
{
    int grid[9][9]=
    {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9},
    };
    solve_sudoko(grid,0,0,9);
    return 0;
}
