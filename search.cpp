#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "kyonkyon3.h"
#define U64 unsigned long long

using namespace std;

void kyonkyon3::alphabeta(int DEPTH) {
    
    vector<int> deepSearch(40, 0);
    int* id = new int[100];
    int* alpha = new int[100];
    int* alphadash = new int[100];
    int* beta = new int[100];
    int* childIndex = new int[100];
    int* bestchild = new int[100];
    int* depthToRead = new int[100];
    int** moveOrdering = new int* [100];
    for (int i = 0; i < 100; i++) {
        moveOrdering[i] = new int[100];
    }

    int currentId = 0;
    int currentAlpha = -2*maxValue;
    int currentBeta = 2*maxValue;
    int currentDepth = 0;
    int currentchildIndex = -1;
    int currentDepthToRead = DEPTH;

    int currentbestchild=0;
    int currentAlphadash = -maxValue;

    id[0] = currentId;
    alpha[0] = currentAlpha;
    alphadash[0] = currentAlphadash;
    beta[0] = currentBeta;
    childIndex[0] = currentchildIndex;
    bestchild[0] = currentbestchild;
    depthToRead[0] = currentDepthToRead;

    bool search = true;

    while (search and edge <Maxnode-100) {

       
        currentId = id[currentDepth];//‚±‚Ì‚Ö‚ñ–³‘Ê‚ª‘½‚¢
        currentAlpha = alpha[currentDepth];
        currentAlphadash = alphadash[currentDepth];
        currentBeta = beta[currentDepth];
        currentchildIndex = childIndex[currentDepth];
        currentbestchild = bestchild[currentDepth];
        currentDepthToRead = depthToRead[currentDepth];
        
        //if (currentDepth == DEPTH) {
        if (currentDepthToRead == 0) {
            
            getvalue(currentId);
            /*
            if (value[currentId]<-maxValue || value[currentId]>maxValue) {
                cout << "error:value is out of maxValue\n";
                cout << "value:" << value[currentId] << "\n"<<flush;
                print(currentId);
            }*/
            currentDepth = currentDepth - 1;
           
            continue;
        }
        else {
           

            if (childnum[currentId] == 0) {//if not have child
                


                deepSearch[DEPTH - currentDepth]++;
                generatechild(currentId);
            }
            if (currentchildIndex == -1) {
                


                for (int i = 0; i < childnum[currentId]; i++) {
                    moveOrdering[currentDepth][i] = i;
                }
                std::sort(moveOrdering[currentDepth]
                    , moveOrdering[currentDepth] + childnum[currentId]
                    , [&](int a, int b) { return (value[child[currentId] + a] < value[child[currentId] + b]); });
/*
                for (int i = 0; i < childnum[currentId]; i++) {
                    value[child[currentId] + i] = 0;
                }*/
                currentchildIndex = 0;
                childIndex[currentDepth] = currentchildIndex;

                id[currentDepth + 1] = child[currentId] + moveOrdering[currentDepth][0];
                alpha[currentDepth + 1] = -currentBeta;
                alphadash[currentDepth + 1] = -maxValue;
                beta[currentDepth + 1] = -currentAlpha;
                childIndex[currentDepth + 1] = -1;
                depthToRead[currentDepth + 1] = currentDepthToRead - 1;
                currentDepth = currentDepth + 1;
                continue;
            }
            else if (currentchildIndex<(childnum[currentId]-1)) {
                

                currentAlpha = max(currentAlpha, - value[child[currentId] + moveOrdering[currentDepth][currentchildIndex]]);
                currentAlphadash = max(currentAlphadash, -value[child[currentId] + moveOrdering[currentDepth][currentchildIndex]]);

                if (currentAlpha >= currentBeta ) {
                    /*
                    if (currentDepth == 0) {
                        cout << "error:beta cut was occurred where depth is 0.\n";
                        cout << "id:" << currentId;
                        cout << "alpha=" << currentAlpha << "\n" << flush;
                        cout << "beta=" << currentBeta << "\n"<<flush;
                        print(currentId);
                        int a;
                        cin >> a;
                    }*/


                    if (currentDepth == 1) {
                        value[currentId] = currentAlpha+1;
                    }
                    else {
                        value[currentId] = currentAlpha+1;
                    }
                    currentDepth = currentDepth - 1;
                    

                    continue;
                }
                else {
                    

                    id[currentDepth] = currentId;//–³‘Ê‚©‚à
                    alpha[currentDepth] = currentAlpha;
                    alphadash[currentDepth] = currentAlphadash;
                    beta[currentDepth] = currentBeta;
                  
                    childIndex[currentDepth] = currentchildIndex+1;

                    id[currentDepth + 1] = child[currentId] + moveOrdering[currentDepth][currentchildIndex + 1];

                    alpha[currentDepth + 1] = -currentBeta;
                    alphadash[currentDepth + 1] = -2*maxValue;
                    beta[currentDepth + 1] = -currentAlpha;
                    childIndex[currentDepth + 1] = -1;
                   

                    //depthToRead[currentDepth + 1] = DEPTHDECISION->getDepth(currentDepthToRead-1,
                        //std::max(0,value[child[currentId] + moveOrdering[currentDepth][currentchildIndex+1]]
                          //  - value[child[currentId] + moveOrdering[currentDepth][0]]));
                    depthToRead[currentDepth + 1] = currentDepthToRead - 1;

                    currentDepth = currentDepth + 1;
  
                    continue;
                }
            }
            else {
                

                currentAlpha = max(currentAlpha,  -value[child[currentId] + moveOrdering[currentDepth][currentchildIndex]]);
                currentAlphadash = max(currentAlphadash,  -value[child[currentId] + moveOrdering[currentDepth][currentchildIndex]]);

                value[currentId] = min(currentAlpha, currentAlphadash);
                if (currentDepth == 0) {
                    search = false;
                }
                else {
                    currentDepth = currentDepth - 1;
                }
            }
        }
    }
    

    std::cout << "depth: "<<right<<setw(2) << DEPTH<<std::flush;
    std::cout << " node:" << right << setw(10) << edge << std::flush;
    std::cout << " value:" << right << setw(4) << value[0] << std::flush;

    lastvalue_leaf = value_leaf;
    value_leaf = value[0];

    int id_now = 0;
    junban_leaf = true;
    while (childnum[id_now] > 0) {
        junban_leaf = !junban_leaf;
        int bestchild_ = 0;
        for (int i = 0; i < childnum[id_now]; i++) {
            if (value[child[id_now] + bestchild_] > value[child[id_now] + i])bestchild_ = i;
        }
        U64 move = (player[child[id_now] + bestchild_] | opponent[child[id_now] + bestchild_])
            & (~(player[id_now] | opponent[id_now]));
        
        int move88 = -1;
        for (int i = 0; i < 64; i++) {
            if (move & (1ULL << i))move88 = i;
        }
        if (move88 == -1) {
            std::cout << "pass" << std::flush;
        }
        else {
            std::cout << "[" << move88 / 8 + 1 << "," << move88 % 8 + 1 << "]" << std::flush;
        }
        if (id_now == 0) {
            lastans = ans;
            ans = move88;
        }
        id_now = child[id_now] + bestchild_;
    }
    //Å‘P‰žŽè—ñ‚Ì––’[‚Ì‹Ç–Ê‚ð•Û‘¶
    lastplayer_leaf = player_leaf;
    lastopponent_leaf = opponent_leaf;
    player_leaf = player[id_now];
    opponent_leaf = opponent[id_now];
    lastjunban_leaf = junban_leaf;
    std::cout << "\n";

    delete[] id ;
    delete[] alpha;
    delete[] alphadash ;
    delete[] beta ;
    delete[] childIndex;
    delete[] bestchild ;
    delete[] depthToRead;
    for (int i = 0; i < 100; i++) {
        delete[] moveOrdering[i];
    }
    delete[] moveOrdering;
   
}

void kyonkyon3::search() {
    int DEPTH = 1;
    int i = 0;
    while (edge < Maxnode-100 && DEPTH<24 && i<5) {
        alphabeta(DEPTH);
        DEPTH+=1;
        //i++;
    }
    //printTree(0, 0, 3);
    
}

bool kyonkyon3::train_equal_leaf() {
    return lastjunban_leaf;
}
int kyonkyon3::getleafvalue() {
    return lastvalue_leaf;
}

void kyonkyon3::printTree(int id,int space,int depth) {
    for (int c = 0; c < childnum[id]; c++) {
        U64 move = (player[child[id] + c] | opponent[child[id] + c])
            & (~(player[id] | opponent[id]));

        int move88 = -1;
        for (int i = 0; i < 64; i++) {
            if (move & (1ULL << i))move88 = i;
        }
        if (c > 0) {
            std::cout << "\n";
            for (int i = 0; i < space; i++)std::cout << "           " << std::flush;
        }
        std::cout << "[" << move88 / 8 + 1 << "," << move88 % 8 + 1 << "]" << std::flush;
        std::cout <<  right << setw(6) << value[child[id]+c];
        if(depth>1)printTree(child[id] + c, space + 1, depth - 1);
    }
}