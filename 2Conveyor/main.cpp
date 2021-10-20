#include <iostream>
#include <vector>
#include <stack>

struct point {
    int sscMember;
    int lowLink;
    bool sscResolved;
    std::vector<int> neighbourPoints;
};

std::vector<struct point> points;

int main (){
    std::cout << "hello this is my second pal program\n";

    int numberOfPoints, numberOfConveyors, centralStorePoint;

    scanf("%i %i %i", &numberOfPoints, &numberOfConveyors, &centralStorePoint);

    struct point newPoint;
    points.assign(numberOfPoints, newPoint);

    for (int i = 0; i < numberOfConveyors; ++i) {
        int from, to;
        scanf("%i %i", &from, &to);
        points[from].sscMember = -1;
        points[from].sscResolved = false;
        points[from].lowLink = 99999999;
        points[from].neighbourPoints.push_back(to);
    }

    std::stack<int> tarjanStack;
    int lowLink = 1;
    for (int i = 0; i < numberOfPoints; ++i) {
        if(!points[i].sscResolved){
            points[i].lowLink = lowLink++;
            tarjanStack.push(i);
            while (!tarjanStack.empty()){
                int currentPoint = tarjanStack.top();
                int lowestNeighbourNumber = 999999;
                for (int neighbour : points[currentPoint].neighbourPoints) {
                    if(!points[neighbour].sscResolved){
                        if (points[neighbour].lowLink <= points[currentPoint].lowLink){
                            lowestNeighbourNumber = points[neighbour].lowLink;
                            continue;
                        }
                        points[neighbour].lowLink = lowLink++;
                        tarjanStack.push(neighbour);
                    }
                }
            }
        }
    }





    for (int i = 0; i < numberOfPoints; ++i) {
        std::cout << i << "   ";
        for (int j = 0; j < points[i].neighbourPoints.size(); ++j) {
            std::cout << points[i].neighbourPoints[j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

int recuTarjan(int currentPoint){
    for (int neighbour : points[currentPoint].neighbourPoints){
        if(!points[neighbour].sscResolved && points[neighbour].sscMember != -1){
            currentPoint
        }
    }
    return 0;
}