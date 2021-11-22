#include <iostream>
#include <vector>
#include <set>

struct state {
    int name;
    int* neighbours;
};

int numberOfStates;
int alphabetSize;
int numberOfFinalStates;
int positiveCount;
int negativeCount;
int uniformLength;

std::vector<struct state*> states;
std::vector<char *> positiveWords;
std::vector<char *> negativeWords;

void freeMem(){
    for (struct state* node : states) {
        delete[] node->neighbours;
        delete node;
    }
    for (char * blob : positiveWords){
        delete[] blob;
    }
    for (char * blob : negativeWords) {
        delete[] blob;
    }
}

int main () {
    scanf("%i %i %i %i %i %i" ,&numberOfStates, &alphabetSize, &numberOfFinalStates, &positiveCount, &negativeCount, &uniformLength);
    for (int i = 0; i < numberOfStates; ++i) {
        struct state* blob = new struct state;
        blob->neighbours = new int [alphabetSize];
        scanf("%i", &blob->name);
        for (int j = 0; j < alphabetSize; ++j) {
            int neighbour;
            scanf("%i", &neighbour);

            blob->neighbours[j] = neighbour;
        }
        states.push_back(blob);
    }
    for (int i = 0; i < positiveCount; ++i) {
        char * blob = new char [uniformLength];
        for (int j = 0; j < uniformLength; ++j) {
            char temp;
            scanf(" %c", &temp);
            temp -= 97;
            blob[j] = temp;
        }
        positiveWords.push_back(blob);
    }
    for (int i = 0; i < negativeCount; ++i) {
        char * blob = new char [uniformLength+1];
        for (int j = 0; j < uniformLength; ++j) {
            char temp;
            scanf(" %c", &temp);
            temp -= 97;
            blob[j] = temp;
        }
        negativeWords.push_back(blob);

    }

    for (int start = 0; start < numberOfStates; start++) {
        std::set<int> possibleEnds;
        for (int i = 0; i < positiveCount; ++i) {
            struct state * currentState = states[start];
            for (int j = 0; j < uniformLength; ++j) {
                char transition = positiveWords[i][j];
                currentState = states[currentState->neighbours[transition]];
            }
            possibleEnds.insert(currentState->name);
            if(possibleEnds.size() > numberOfFinalStates){
                break;
            }
        }
        if (possibleEnds.size() == numberOfFinalStates){
            printf("%i", start);
            for (int i : possibleEnds) {
                printf(" %i", i);
            }
            printf("\n");

        }
    }




/*
    std::cout << "============================\n";

    for (struct state* node : states) {
        std::cout << node->name << " ";
        for (int i = 0; i<alphabetSize; i++){
            std::cout << node->neighbours[i] << " ";
        }
        std::cout <<  "\n";
    }
    for (char * str : positiveWords) {
        for (int i = 0; i < uniformLength; ++i) {
            printf("%d", str[i]);
        }
        printf("\n");
    }
    for (char * str : negativeWords) {
        for (int i = 0; i < uniformLength; ++i) {
            printf("%d", str[i]);
        }
        printf("\n");
    }
*/
    freeMem();

    return 0;
}
