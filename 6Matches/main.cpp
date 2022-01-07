#include <iostream>
#include <vector>
#include <iomanip>

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

    for (int i = startIndex; i < endIndex; ++i) {
        cout << text[i];
    }
    cout << endl;

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
    for (int i = 0; i < size_i; ++i) {
        for (int j = 0; j < size_j; ++j) {
            cout << levMatrix[i][j] << " ";
        }
        cout << endl;
    }
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

    nodes = vector<node> (textSize);
    for (int i = 0; i < textSize; ++i) {
        vector<edge> neighbours (1);
        neighbours[0] = {
                i,
                i+1,
                false
        };
        node temp = {
                i,
                false,
                neighbours,
                0,
                0,
        };
        nodes[i] = temp;
    }


    vector<vector<int>> levMatrix = levenshtein();

    vector<vector<char>> substrings;

    for (int i = 1; i < textSize+1; ++i) {
        if (levMatrix[patternSize][i] <= D){
            int startIndex = i-patternSize-D >= 0 ? i-patternSize-D : 0;
            int endIndex = i;
            findSubstrings(startIndex, endIndex, substrings);
        }
    }

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
    }

    return 0;
}