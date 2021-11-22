#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <algorithm>
#include <queue>

struct point {
    int sscMember;
    int lowLink;
    int index;
    int cost;
    bool visited;
    bool sscResolved;
    bool inStack;
    std::vector<int> neighbourPoints;
    std::vector<int> childOf;
};
std::vector<std::vector<int>> SSCs;

std::vector<struct point> points;

int numberOfSSCs = 0;

std::stack<int> tarjanStack;

int recuTarjan(int currentPoint);

int main (){
    int numberOfPoints, numberOfConveyors, centralStorePoint;

    scanf("%i %i %i", &numberOfPoints, &numberOfConveyors, &centralStorePoint);

    struct point newPoint;
    points.assign(numberOfPoints, newPoint);
    for (int i = 0; i < numberOfPoints; ++i) {
        points[i].sscMember = -1;
        points[i].index = 0;
        points[i].sscResolved = false;
        points[i].inStack = false;
        points[i].visited = false;
        points[i].cost = 999999;
        points[i].lowLink = 99999999;
    }

    for (int i = 0; i < numberOfConveyors; ++i) {
        int from, to;
        scanf("%i %i", &from, &to);

        points[from].neighbourPoints.push_back(to);
        points[to].childOf.push_back(from);
    }
    /// Computing SSCs using Tarjan algorithm and replacing them with single points
    for (int i = 0; i < numberOfPoints; ++i) {
        recuTarjan(i);
    }
    /// Using pair where the first element is cost and second element is point name
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> prioQueue;
    points[centralStorePoint].cost = 0;
    prioQueue.push(std::make_pair(0,centralStorePoint));
    /// Dijkstra
    while (!prioQueue.empty()) {
        auto currentNode = prioQueue.top();
        prioQueue.pop();
        points[currentNode.second].visited = true;
        for (int neighbour : points[currentNode.second].neighbourPoints) {
            if (points[neighbour].cost > points[currentNode.second].cost) {
                points[neighbour].cost = points[currentNode.second].cost;
                prioQueue.push(std::make_pair(points[neighbour].cost, neighbour));
            }
        }
        for (int neighbour : points[currentNode.second].childOf) {
            if (points[neighbour].cost > points[currentNode.second].cost + 1) {
                points[neighbour].cost = points[currentNode.second].cost+1;
                prioQueue.push(std::make_pair(points[neighbour].cost, neighbour));
            }
        }
    }
    int hmmYesCost = 0;
    /// Computing cost of end points
    for (auto point : points) {
        if (point.visited && point.childOf.empty()){
            hmmYesCost+=point.cost;
        }
    }
    std::cout << hmmYesCost << "\n";

    return 0;
}

int recuTarjan(int currentPoint){
    static int index = 0;
    points[currentPoint].lowLink = index;
    points[currentPoint].index = index;
    tarjanStack.push(currentPoint);
    points[currentPoint].inStack = true;
    index++;

    for (int neighbour : points[currentPoint].neighbourPoints){
        if (points[neighbour].index == 0){
            recuTarjan(neighbour);
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

        /// Replacing SSCs with single point
        if (SSCs[numberOfSSCs].size() > 1){
           auto newMainNode = SSCs[numberOfSSCs][0];
            std::unordered_set<int> newNeighbours;
            std::unordered_set<int> newChildrenOf;
            for (auto currentPoint : SSCs[numberOfSSCs]) {
                for (auto neighbour : points[currentPoint].neighbourPoints) {
                    if(points[neighbour].sscMember != numberOfSSCs){
                        newNeighbours.insert(neighbour);
                        for (unsigned i = 0; i < points[neighbour].childOf.size(); ++i) {
                            if(points[neighbour].childOf[i] == currentPoint){
                                points[neighbour].childOf[i] = newMainNode;
                                break;
                            }
                        }
                    }
                }
                for (auto child : points[currentPoint].childOf) {
                    if(points[child].sscMember != numberOfSSCs){
                        newChildrenOf.insert(child);
                        for (unsigned i = 0; i < points[child].neighbourPoints.size(); ++i) {
                            if(points[child].neighbourPoints[i] == currentPoint){
                                points[child].neighbourPoints[i] = newMainNode;
                                break;
                            }
                        }

                    }
                }
            }
            std::vector<int> newTempNeighbs(newNeighbours.begin(), newNeighbours.end());
            std::vector<int> newTempChild(newChildrenOf.begin(), newChildrenOf.end());
            points[newMainNode].neighbourPoints = newTempNeighbs;
            points[newMainNode].childOf = newTempChild;
        }
        numberOfSSCs++;
    }
    return 0;
}