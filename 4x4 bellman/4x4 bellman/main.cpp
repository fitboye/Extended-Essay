//
//  main.cpp
//  4x4 bellman
//
//  Created by Jerry Cheng on 5/17/21.
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

int realgrid[4][4];
int backupgrid[4][4], gameover = 0;
int n = 4;
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
        x = rand() % n;
        y = rand() % n;
    }
    realgrid[x][y] = 2;
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

//combines tiles
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

// completes one full move
vector<int> movecycle(char direction, vector<int> a){
    a = shifttiles(direction, a);
    a = updategrid(direction, a);
    a = shifttiles(direction, a);
    return a;
}

vector<int> movecyclefast(char direction, vector<int> a){
    int grid[n][n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            grid[i][j] = a[i*n + j];
        }
    }
    
    //shifttiles
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
    
    //update grid
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
    
    //shifttiles
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

map<int, int> scorecalc;
int findscoreNorm(vector<int> temp){
    int sum = 0;
    for (int i = 0; i < temp.size(); i++){
        sum += scorecalc[temp[i]];
    }
    return sum;
}

// amended version
int incentive[16] = {1000, 500, 100, 50,
    500, 100, 50, 10,
    100, 50, 10, 5,
    50, 10, 5, 1};
int findscore(vector<int> temp){
    int sum = 0;
    for (int i = 0; i < temp.size(); i++){
        sum += incentive[i]*scorecalc[temp[i]];
        //sum += scorecalc[temp[i]];
    }
    return sum;
}

// check for game over
bool checkstate (vector<int> a){
    int grid[n][n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            grid[i][j] = a[i*n + j];
        }
    }
    a = movecyclefast('w', a);
    a = movecyclefast('a', a);
    a = movecyclefast('s', a);
    a = movecyclefast('d', a);
    
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

// moves actual game grid
bool gameend = false;
void gamemove(char direction){
    vector<int> a;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            backupgrid[i][j] = realgrid[i][j];
            a.push_back(realgrid[i][j]);
        }
    }
    a = movecyclefast(direction, a);
    
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
        generatetile();
    }
    if (checkstate(a)){
        cout << "Game over" << endl;
        gameend = true;
        return;
    }
    cout << "Score: " << findscoreNorm(a) << endl;
    stateout();
}

map<vector<int>, double> rewards;
int optimalDirection;
char moves[4] = {'w', 'a', 's', 'd'};
double discount = 1.0;
double search(vector<int> current, int d){
    if (d == 5){
        return 0;
    }
    
    double maxval = -9999999;
    int deadcheck = 0;
    for (int i = 0; i < 4; i++){
        vector<int> newgrid;
        newgrid = movecyclefast(moves[i], current);
        if (newgrid != current){
            double rsum = 0;
            int emptyspaces = 0;
            if (rewards.count(newgrid) == 0){
                for (int i = 0; i < newgrid.size(); i++){
                    if (newgrid[i] == 0){
                        newgrid[i] = 2;
                        rsum += discount * search(newgrid, d + 1);
                        newgrid[i] = 0;
                        emptyspaces++;
                    }
                }
                if (emptyspaces == 0){
                    rewards[newgrid] = findscore(newgrid);
                }else{
                    rewards[newgrid] = (rsum + findscore(newgrid))/emptyspaces;
                }
            }
            //cout << rsum << ' ' << emptyspaces << ' ' << findscore(newgrid) << endl;
            if (d == 0){
                cout <<'a' << i << ' ' << rewards[newgrid] << endl;
                if (rewards[newgrid] > maxval){
                    optimalDirection = i;
                }
            }
            maxval = max(maxval, rewards[newgrid]);
        }else{
            deadcheck++;
        }
    }
    if (deadcheck == 4){
        bool x = false;
        for (int i = 0; i < current.size(); i++){
            if (current[i] == 2048){
                x = true;
            }
        }
        if (x){
            return findscore(current);
        }
        return -findscore(current);
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
    
    
    vector<int> a;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            realgrid[i][j] = 0;
        }
    }
    //a[0] = 2;
    //a[1] = 2;
    generatetile();
    generatetile();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            a.push_back(realgrid[i][j]);
        }
    }
    stateout();
    cout << search(a, 0) << endl;
    cout << optimalDirection << endl;
    //a = {16, 4, 0, 0};
    //cout << rewards.count(a) << ' ' << rewards[a] << endl;
    gamemove(moves[optimalDirection]);
    
    // actual game loop
    while (!gameend){
        a.clear();
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                a.push_back(realgrid[i][j]);
            }
        }
        rewards.clear();
        optimalDirection = 0;
        search(a, 0);
        cout << moves[optimalDirection] << endl;
        cout << rewards.size() << endl;
        gamemove(moves[optimalDirection]);
     }
    
    return 0;
}

