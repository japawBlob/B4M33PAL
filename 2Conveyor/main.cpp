#include <iostream>
#include <vector>
#include <stack>

struct point {
    int sscMember;
    int lowLink;
    int index;
    bool sscResolved;
    bool inStack;
    std::vector<int> neighbourPoints;
    std::vector<int> childOf;
};
std::vector<std::vector<int>> SSCs;

std::vector<struct point> points;

int numberOfSSCs = 0;

std::stack<int> tarjanStack;

int recuTarjan(int currentPoint/*, std::stack<int>& tarjanStack*/);

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
        points[from].index = 0;
        points[from].sscResolved = false;
        points[from].inStack = false;
        points[from].lowLink = 99999999;
        points[from].neighbourPoints.push_back(to);
        points[to].childOf.push_back(from);
    }


    int lowLink = 1;
    for (int i = 0; i < numberOfPoints; ++i) {
        /*if(!points[i].sscResolved){
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
        }*/
        recuTarjan(i/*, tarjanStack*/);

    }




/*
    for (int i = 0; i < numberOfPoints; ++i) {
        std::cout << i << "   ";
        for (int j = 0; j < points[i].neighbourPoints.size(); ++j) {
            std::cout << points[i].neighbourPoints[j] << " ";
        }
        std::cout << std::endl;
    }
*/
    for (int i = 0; i < numberOfPoints; ++i) {
        std::cout << i << "   ";
        for (int j = 0; j < points[i].neighbourPoints.size(); ++j) {
            std::cout << points[i].neighbourPoints[j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < numberOfPoints; ++i) {
        std::cout << i << " " << points[i].sscMember << std::endl;
    }
    /*int i = 0;
    for (auto vec : SSCs) {
        //std::cout << i++ << "  \n";
        for (auto blob : vec) {
            std::cout << blob << " ";
        }
        std::cout << "\n";
    }*/
    for (int i = 0; i < points.size(); ++i) {
        std::cout << points[i].sscMember << " ";
    } std::cout << std::endl;

    return 0;
}

int recuTarjan(int currentPoint/*, std::stack<int>& tarjanStack*/){
    static int index = 0;
    points[currentPoint].lowLink = index;
    points[currentPoint].index = index;
    tarjanStack.push(currentPoint);
    points[currentPoint].inStack = true;
    index++;

    for (int neighbour : points[currentPoint].neighbourPoints){
        if (points[neighbour].index == 0){
            recuTarjan(neighbour/*, tarjanStack*/);
            points[currentPoint].lowLink = std::min(points[currentPoint].lowLink, points[neighbour].lowLink);
        } else if (points[neighbour].inStack) {
            points[currentPoint].lowLink = std::min(points[currentPoint].lowLink, points[neighbour].index);
        }
    }
    if(points[currentPoint].lowLink == points[currentPoint].index){
        std::vector<int> blob;
        SSCs.push_back(blob);
        int riley;
        do{
            riley = tarjanStack.top();
            tarjanStack.pop();
            if (!points[riley].sscResolved){
                points[riley].sscMember = numberOfSSCs;
                points[riley].sscResolved = true;
            }
            points[riley].inStack = false;
            SSCs[numberOfSSCs].push_back(riley);
        } while (currentPoint != riley);
        if (SSCs[numberOfSSCs].size() > 1){
            for (auto blob : SSCs[numberOfSSCs]) {
                //find(vec.begin(), vec.end(), elem) != vec.end()
                //points[currentPoint]
            }

        }
        numberOfSSCs++;
    }
    return 0;
}