#include <iostream>
#include <vector>
#include <iomanip>
#include <bits/stdc++.h>

#define NC "\e[0m"
#define RED "\e[0;31m"

using namespace std;

struct edge {
    int from;
    int to;
    bool direct;
}
;

struct node {
    int name;
    bool visited;
    bool connected;
    vector<edge> neighbours;
    int numberOfSubstrings;
    int numberOfLonelyChars;
};
int numberOfNodes = 0;
vector<char> text;
vector<char> pattern;
int D;
vector<node> nodes;

vector<vector<int>> levenshtein (){
    int size_i = pattern.size()+1;
    int size_j = text.size()+1;

    vector<vector<int>> levenshteinMatrix (size_i, vector<int>(size_j, 0));
    for (int i = 0; i < size_i; ++i) {
        levenshteinMatrix[i][0] = i;
    }

    for (int i = 1; i < size_i; ++i) {
        for (int j = 1; j < size_j; ++j) {
            if(text[j-1] == pattern[i-1]){
                levenshteinMatrix[i][j] = levenshteinMatrix[i-1][j-1];
            } else {
                levenshteinMatrix[i][j] = 1 + std::min(levenshteinMatrix[i-1][j-1],std::min(levenshteinMatrix[i-1][j],levenshteinMatrix[i][j-1]));
            }
        }
    }
    return levenshteinMatrix;
}

void findSubstrings (int startIndex, int endIndex, vector<vector<char>> & substrings){
    int size_i = pattern.size()+1;
    int size_j = endIndex-startIndex+1;
/*
    for (int i = startIndex; i < endIndex; ++i) {
        cout << text[i];
    }
    cout << endl;
*/
    int levMatrix [size_i][size_j];
    for (int i = 0; i < size_i; ++i) {
        levMatrix[i][0] = i;
    }
    for (int i = 0; i < size_j; ++i) {
        levMatrix[0][i] = i;
    }
    for (int i = 1; i < size_i; ++i) {
        for (int j = 1; j < size_j; ++j) {
            int textIndex = endIndex-j;
            int patternIndex = size_i-i-1;
            char textChar = text[textIndex];
            char patternChar = pattern[patternIndex];
            if(textChar == patternChar){
                levMatrix[i][j] = levMatrix[i-1][j-1];
            } else {
                levMatrix[i][j] = 1 + std::min(levMatrix[i-1][j-1],std::min(levMatrix[i-1][j],levMatrix[i][j-1]));
            }
        }
    }
 /*   for (int i = 0; i < size_i; ++i) {
        for (int j = 0; j < size_j; ++j) {
            cout << levMatrix[i][j] << " ";
        }
        cout << endl;
    }*/
    for (int j = 1; j < size_j; ++j) {
        if(levMatrix[size_i-1][j] <= D){
            edge temp {
                    endIndex-(j-1)-1,
                    endIndex-1,
                    true
            };
            nodes[endIndex-(j-1)-1].neighbours.push_back(temp);
        }
    }
}

pair<int, int> dfs (int startIndex, bool direct){
    node * currentNode = &nodes[startIndex];
    if(currentNode->visited){
        if(direct){
            if(!currentNode->connected){
                return make_pair(currentNode->numberOfSubstrings,currentNode->numberOfLonelyChars-1);
            } else {
                pair<int,int> ret = dfs(currentNode->name+1, false);
                //ret.second += 1;
                return ret;
            }
        }
        return make_pair(currentNode->numberOfSubstrings,currentNode->numberOfLonelyChars);
    }
    currentNode->visited = true;
    //int trueIndex = -1;
    //edge e;
    for(int i = 0; i < currentNode->neighbours.size(); i++){
        edge e = currentNode->neighbours[i];
        //if(!nodes[e.to].visited){
        pair<int,int> ret = dfs(e.to, e.direct);

        if(e.direct){
            if(ret.first+1 > currentNode->numberOfSubstrings) {
                currentNode->connected = true;
                currentNode->numberOfSubstrings = ret.first+1;
                currentNode->numberOfLonelyChars = ret.second;

            } else if (ret.first+1 == currentNode->numberOfSubstrings && ret.second < currentNode->numberOfLonelyChars){
                currentNode->connected = true;
                currentNode->numberOfSubstrings = ret.first+1;
                currentNode->numberOfLonelyChars = ret.second;
            }
        } else {
            if(ret.first > currentNode->numberOfSubstrings) {
                currentNode->connected = false;
                currentNode->numberOfSubstrings = ret.first;
                currentNode->numberOfLonelyChars = ret.second+1;

            } else if (ret.first == currentNode->numberOfSubstrings && ret.second+1 < currentNode->numberOfLonelyChars){
                currentNode->connected = false;
                currentNode->numberOfSubstrings = ret.first;
                currentNode->numberOfLonelyChars = ret.second+1;
            }
        }
    }
    /*if(trueIndex != -1){
        nodes[currentNode->neighbours[trueIndex].to].connected = true;
        nodes[currentNode->neighbours[trueIndex].from].connected = true;
    }*/
    return make_pair(currentNode->numberOfSubstrings,currentNode->numberOfLonelyChars);
};

pair<int,int> iterativeDFS (int startIndex){
    stack<int> s;
    for (int i = 0; i < nodes.size(); ++i) {
        s.push(i);
    }
    while(!s.empty()){
        node * currentNode =  &nodes[s.top()];
        s.pop();

        currentNode->visited = true;

        for(int i = 0; i < currentNode->neighbours.size(); i++) {
            edge e = currentNode->neighbours[i];
            //if(!nodes[e.to].visited){
            pair<int,int> ret;
            if(e.direct){
                if(!nodes[e.to].connected){
                    ret = make_pair(nodes[e.to].numberOfSubstrings,nodes[e.to].numberOfLonelyChars-1);
                } else {
                    ret = dfs(nodes[e.to].name+1, false);
                    //ret.second += 1;
                    //return ret;
                }
            } else {
                ret = make_pair(nodes[e.to].numberOfSubstrings,nodes[e.to].numberOfLonelyChars);
            }
            if(e.direct){
                if(ret.first+1 > currentNode->numberOfSubstrings) {
                    currentNode->connected = true;
                    currentNode->numberOfSubstrings = ret.first+1;
                    currentNode->numberOfLonelyChars = ret.second;

                } else if (ret.first+1 == currentNode->numberOfSubstrings && ret.second < currentNode->numberOfLonelyChars){
                    currentNode->connected = true;
                    currentNode->numberOfSubstrings = ret.first+1;
                    currentNode->numberOfLonelyChars = ret.second;
                }
            } else {
                if(ret.first > currentNode->numberOfSubstrings) {
                    currentNode->connected = false;
                    currentNode->numberOfSubstrings = ret.first;
                    currentNode->numberOfLonelyChars = ret.second+1;

                } else if (ret.first == currentNode->numberOfSubstrings && ret.second+1 < currentNode->numberOfLonelyChars){
                    currentNode->connected = false;
                    currentNode->numberOfSubstrings = ret.first;
                    currentNode->numberOfLonelyChars = ret.second+1;
                }
            }
        }
    }
    return make_pair(nodes[0].numberOfSubstrings, nodes[0].numberOfLonelyChars);
}

int main () {
    char c;
    while((c = getchar()) != '\r'){
        text.push_back(c);
    }
    getchar();
    while((c = getchar()) != '\r'){
        pattern.push_back(c);
    }
    getchar();
    scanf("%i", &D);

    int textSize = text.size();
    int patternSize = pattern.size();

    // cout << textSize << endl;
    nodes = vector<node> (textSize);
    int i;
    for (i = 0; i < textSize-1; ++i) {
        vector<edge> neighbours (1);
        neighbours[0] = {
                i,
                i+1,
                false
        };
        node temp = {
                i,
                false,
                false,
                neighbours,
                INT_MIN,
                INT_MAX,
        };
        nodes[i] = temp;
    }
    vector<edge> neighbours (0);
    node temp = {
            i,
            false,
            false,
            neighbours,
            0,
            1,
    };
    nodes[i] = temp;


    vector<vector<int>> levMatrix = levenshtein();

    vector<vector<char>> substrings;

    for (int i = 1; i < textSize+1; ++i) {
        if (levMatrix[patternSize][i] <= D){
            int startIndex = i-patternSize-D >= 0 ? i-patternSize-D : 0;
            int endIndex = i;
            findSubstrings(startIndex, endIndex, substrings);
        }
    }


/*
    cout << setw(2) << "      ";
    for (int j = 0; j < text.size(); ++j) {
        cout << setw(2) << text[j] << " ";
    } cout << endl;
    for (int i = 0; i < levMatrix.size(); ++i) {
        if (i >= 1) cout << setw(2) << pattern[i-1] << " ";
        else cout << "   ";
        for (int j = 0; j < levMatrix[i].size(); ++j) {
            cout << setw(2) << levMatrix[i][j] << " ";
        }
        cout << endl;
    }

    for (node n : nodes) {
        for (edge e : n.neighbours){
            if(e.direct){
                cout << e.from << " -> " << e.to << endl;
            } else {
                cout << RED << e.from << " -> " << e.to << NC << endl;
            }
        }
    }*/


    /*for (int j = 0; j < nodes.size(); ++j) {
        if(!nodes[j].connected){
            blob.second++;
        }
    }*/

    pair<int, int> blob = iterativeDFS(0);
    //pair<int, int> blob = dfs(0, false);
    cout << blob.first << " " << blob.second;

    return 0;
}