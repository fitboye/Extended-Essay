//
//  main.cpp
//  monte carlo
//
//  Created by Jerry Cheng on 6/5/21.
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
        //sum += incentive[i]*scorecalc[temp[i]];
        sum += scorecalc[temp[i]];
    }
    return sum;
}

// check for game over
char moves[4] = {'w', 'a', 's', 'd'};
bool checkstate (vector<int> a){
    vector<int> temp = a;
    bool blocksmoved = false;
    for (int j = 0; j < 4; j++){
        a = movecyclefast(moves[j], temp);
        for (int i = 0; i < a.size(); i++){
            if (a[i] != temp[i]){
                blocksmoved = true;
            }
        }
    }
    
    //cout << 'b' << blocksmoved << endl;
    return !blocksmoved;
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
double discount = 0.95;
bool unviable;
double search(vector<int> current, char move){
    // initate search based on inital move
    vector<int> temp = current;
    current = movecyclefast(move, current);
    // if the move is not possible, return a reward of 0
    if (temp == current){
        unviable = true;
        return 0;
    }else{
        int y = rand() % 16, attempts = 0;
        while (current[y] != 0){
            y = rand() % 16;
            attempts++;
        }
        current[y] = 2;
    }
    
    double average_r = 0;
    // for two hundred attempts from current game state
    for (int i = 0; i < 200; i++){
        double score = 0, extended_discount = 1;
        // for next one hundred moves
        for (int j = 0; j < 100; j++){
            // pick a random move and execute it
            int x = rand() % 4;
            vector<int> previous = current;
            current = movecyclefast(moves[x], current);
            
            //generate new tile
            if (previous != current){
                int y = rand() % 16, attempts = 0;
                while (current[y] != 0){
                    y = rand() % 16;
                    attempts++;
                }
                current[y] = 2;
            }
            
            // if game over, penalize with negative reward and end current attempt
            if (checkstate(current)){
                score += -findscore(current) * extended_discount;
                break;
            // else, game is not over, add discounted reward
            }else{
                score += findscore(current) * extended_discount;
                extended_discount = extended_discount * discount;
            }
        }
        // return game state back to original state before the one hundred random moves
        current = movecyclefast(move, temp);
        // update average reward
        average_r += score/600;
    }
    
    return average_r;
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
            a.push_back(0);
        }
    }
    //a[6] = 2;
    //a[9] = 2;
    generatetile();
    generatetile();
    stateout();
    
    // actual game loop
    while (!gameend){
        a.clear();
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                a.push_back(realgrid[i][j]);
            }
        }
        double max = -99999999;
        int optimal;
        for (int j = 0; j < 4; j++){
            unviable = false;
            double x = search(a, moves[j]);
            if (!unviable){
                cout << j << ' ' << x << endl;
                if (x > max){
                    max = x;
                    optimal = j;
                }
            }
        }
        cout << optimal << endl;
        gamemove(moves[optimal]);
    }
    
    return 0;
}


