//
//  main.cpp
//  2x2
//
//  Created by Jerry Cheng on 1/18/21.
//  Copyright © 2021 Jerry Cheng. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cmath>
#include <map>
#include <vector>
#include <iomanip>
using namespace std;

int realgrid[2][2];
int backupgrid[2][2], gameover = 0;
int n = 2;
int score = 0, p = 0;

//outputs what the game state currently looks like
void stateout(){
    //cout << grid[0][0] << ' ' << grid[0][1] << endl << grid[1][0] << ' ' << grid[1][1] << endl << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << realgrid[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

// decides whether a tile will be 2 or 4
int newtilenum(){
    int x = rand() % 10;
    if (x == 0){
        return 4;
    }else{
        return 2;
    }
}

//generates new tile in empty spot
void generatetile(){
    int x = rand() % n, y = rand() % n;
    while (realgrid[x][y] != 0){
        x = rand() % 2;
        y = rand() % 2;
    }
    realgrid[x][y] = newtilenum();
}

//moves tiles in desired direction
vector<int> shifttiles(char direction, vector<int> g){
    int grid[n][n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            grid[i][j] = g[i*n + j];
        }
    }
    
    if (direction == 'w'){
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                if(!grid[j][i]){
                    for(int k=j+1;k<n;k++)
                        if(grid[k][i]){
                            grid[j][i]=grid[k][i];
                            grid[k][i]=0;
                            break;
                        }
                }
                
            }
    }else if (direction == 's'){
        for(int i=0;i<n;i++)
            for(int j=n-1;j>=0;j--){
                if(!grid[j][i]){
                    for(int k=j-1;k>=0;k--)
                        if(grid[k][i]){
                            grid[j][i]=grid[k][i];
                            grid[k][i]=0;
                            break;
                        }
                }
            }
    }else if (direction == 'a'){
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            {
                if(!grid[i][j])
                {
                    for(int k=j+1;k<n;k++)
                        if(grid[i][k])
                        {
                            grid[i][j]=grid[i][k];
                            grid[i][k]=0;
                            break;
                        }
                }
                
            }
    }else if (direction == 'd'){
        for(int i=0;i<n;i++)
            for(int j=n-1;j>=0;j--){
                if(!grid[i][j]){
                    for(int k=j-1;k>=0;k--)
                        if(grid[i][k]){
                            grid[i][j]=grid[i][k];
                            grid[i][k]=0;
                            break;
                        }
                }
                
            }
    }
    
    vector<int> temp;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            temp.push_back(grid[i][j]);
        }
    }
    return temp;
}

vector<int> updategrid(char direction, vector<int> g){
    int grid[n][n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            grid[i][j] = g[i*n + j];
        }
    }
    
    p=0;
    gameover=1;
    
    switch(direction)
    {
        case 'w':
            for(int i=0;i<n;i++)
                for(int j=0;j<n-1;j++)
                {
                    if(grid[j][i]&&grid[j][i]==grid[j+1][i])
                    {
                        gameover=0;
                        grid[j][i]+=grid[j+1][i];
                        grid[j+1][i]=0;
                        p+=(((log2(grid[j][i]))-1)*grid[j][i]);
                        //score+=(((log2(grid[j][i]))-1)*grid[j][i]);
                        score+=grid[j][i];
                    }
                }break;
            
        case 's':
            for(int i=0;i<n;i++)
                for(int j=n-1;j>0;j--)
                {
                    if(grid[j][i]&&grid[j][i]==grid[j-1][i])
                    {
                        gameover=0;
                        grid[j][i]+=grid[j-1][i];
                        grid[j-1][i]=0;
                        p+=(((log2(grid[j][i]))-1)*grid[j][i]);
                        //score+=(((log2(grid[j][i]))-1)*grid[j][i]);
                        score+=grid[j][i];
                    }
                }break;
            
        case 'a':
            for(int i=0;i<n;i++)
                for(int j=0;j<n-1;j++)
                {
                    if(grid[i][j]&&grid[i][j]==grid[i][j+1])
                    {
                        gameover=0;
                        grid[i][j]+=grid[i][j+1];
                        grid[i][j+1]=0;
                        p+=((log2(grid[i][j]))-1)*grid[i][j];
                        //score+=((log2(grid[i][j]))-1)*grid[i][j];
                        score+=grid[i][j];
                    }
                }break;
            
        case 'd':
            for(int i=0;i<n;i++)
                for(int j=n-1;j>0;j--)
                {
                    if(grid[i][j]&&grid[i][j]==grid[i][j-1])
                    {
                        gameover=0;
                        grid[i][j]+=grid[i][j-1];
                        grid[i][j-1]=0;
                        p+=((log2(grid[i][j]))-1)*grid[i][j];
                        //score+=(((log2(grid[i][j]))-1)*grid[i][j]);
                        score+=grid[i][j];
                    }
                }break;
    }
    vector<int> temp;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            temp.push_back(grid[i][j]);
        }
    }
    return temp;
}

vector<int> movecycle(char direction, vector<int> a){
    a = shifttiles(direction, a);
    a = updategrid(direction, a);
    a = shifttiles(direction, a);
    return a;
}

map<int, int> scorecalc;
int findscore(vector<int> temp){
    int sum = 0;
    for (int i = 0; i < temp.size(); i++){
        sum += scorecalc[temp[i]];
    }
    return sum;
}

bool checkstate (vector<int> a){
    int grid[n][n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            grid[i][j] = a[i*n + j];
        }
    }
    a = movecycle('w', a);
    a = movecycle('a', a);
    a = movecycle('s', a);
    a = movecycle('d', a);
    
    bool blocksmoved = false;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (backupgrid[i][j] != realgrid[i][j]){
                blocksmoved = true;
            }
        }
    }
    if (!blocksmoved){
        return true;
    }
    return false;
}

bool gameend = false;
void gamemove(char direction){
    vector<int> a;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            backupgrid[i][j] = realgrid[i][j];
            a.push_back(realgrid[i][j]);
        }
    }
    a = movecycle(direction, a);

    //cout << p << endl;
    //score-=p;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            realgrid[i][j] = a[i*n + j];
        }
    }
    
    bool blocksmoved = false;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (backupgrid[i][j] != realgrid[i][j]){
                blocksmoved = true;
            }
        }
    }
    if (blocksmoved){
        //generatetile();
    }
    if (checkstate(a)){
        cout << "Game over" << endl;
        gameend = true;
        return;
    }
    cout << "Score: " << findscore(a) << endl;
    stateout();
}

map<vector<int>, double> rewards;
int optimalDirection;
char moves[4] = {'w', 'a', 's', 'd'};
double discount = 0.9;
double search(vector<int> current, int d){
    if (d == 4){
        //return 0;
    }
    
    double maxval = -9999999;
    int deadcheck = 0;
    // For all four possible move directions
    for (int i = 0; i < 4; i++){
        vector<int> newgrid;
        // update grid according to move selected by loop
        newgrid = movecycle(moves[i], current);
        // if the grid actually changes and the move is thus valid
        if (newgrid != current){
            double rsum = 0;
            int emptyspaces = 0;
            // if this game state has not been evaluated yet
            if (rewards.count(newgrid) == 0){
                // calculate reward from all gamestaets reachable from the current gamestate
                for (int i = 0; i < newgrid.size(); i++){
                    if (newgrid[i] == 0){
                        newgrid[i] = 2;
                        rsum += discount * search(newgrid, d + 1);
                        newgrid[i] = 0;
                        emptyspaces++;
                    }
                }
                // add reward from current gamestate to all reachable gamestates
                if (emptyspaces == 0){
                    rewards[newgrid] = findscore(newgrid);
                }else{
                    rewards[newgrid] = (rsum + findscore(newgrid))/emptyspaces;
                }
            }
            if (d == 0){
                cout << i << ' ' << rewards[newgrid] << endl;
                optimalDirection = i;
            }
            maxval = max(maxval, rewards[newgrid]);
        }else{
            deadcheck++;
        }
    }
    //check if gameover
    if (deadcheck == 4){
        int x = 200;
        for (int i = 0; i < current.size(); i++){
            if (current[i] == 16){
                x = 0;
            }
        }
        return findscore(current) - x;
    }
    return maxval;
}

int main() {
    //random seed
    srand ((int)time(NULL));
    int num = 2;
    for (int i = 0; i < 10; i++){
        scorecalc[num] = num * i;
        num = num * 2;
    }
    cout << setprecision(10);
    
    realgrid[0][0] = 0;
    realgrid[0][1] = 2;
    realgrid[1][0] = 0;
    realgrid[1][1] = 2;
    map<vector<int>, int> test;
    
    stateout();
    vector<int> a;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            a.push_back(realgrid[i][j]);
        }
    }
    cout << search(a, 0) << endl;
    cout << optimalDirection << endl;
    a = {16, 4, 0, 0};
    cout << rewards.count(a) << ' ' << rewards[a] << endl;
    gamemove('a');
    gamemove('w');
    /*
    while (!gameend){
        char x;
        cin >> x;
        gamemove(x);
    }
     */
    return 0;
}
//8 4
//0 2
