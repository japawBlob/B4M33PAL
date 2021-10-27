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
    //std::cout << "hello this is my second pal program\n";

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
        points[from].visited = false;
        points[from].cost = 999999;
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

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> prioQueue;
    points[centralStorePoint].cost = 0;
    prioQueue.push(std::make_pair(0,centralStorePoint));
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
//
//    prioQueue.push(std::make_pair(0,centralStorePoint));
//    points[centralStorePoint].cost = 0;
//    int totalCost = 0;
//    while(!prioQueue.empty()){
//        auto currentNode = prioQueue.top();
//        prioQueue.pop();
//        //
//        if(points[currentNode.second].visited){
//            continue;
//        }
//        //totalCost += currentNode.first;
//        points[currentNode.second].visited = true;
//        for (int neighbour : points[currentNode.second].neighbourPoints) {
//            if (!points[neighbour].visited) {
//                points[neighbour].cost = currentNode.first;
//                prioQueue.push(std::make_pair(currentNode.first, neighbour));
//            }
//        }
//        for (int neighbour : points[currentNode.second].childOf) {
//            if (!points[neighbour].visited/*points[neighbour].cost > currentNode.first+1*/) {
//                points[neighbour].cost = currentNode.first+1;
//                prioQueue.push(std::make_pair(points[neighbour].cost, neighbour));
//            }
//        }
//    }
    /*for (auto point : points) {
        std::cout << point.index << " ";
    }std::cout << "\n";*/
    int hmmYesCost = 0;
    for (auto point : points) {
        if (point.visited && point.childOf.empty()){
            //std::cout << " Hmm yes cost: "<< hmmYesCost << "\n";
            hmmYesCost+=point.cost;
        }
    }
    //std::cout << " Hmm yes cost: "<< hmmYesCost << "\n";
    std::cout << hmmYesCost << "\n";

    //std::cout << " Total cost: "<< totalCost << "\n";





/*
    for (int i = 0; i < numberOfPoints; ++i) {
        std::cout << i << "   ";
        for (int j = 0; j < points[i].neighbourPoints.size(); ++j) {
            std::cout << points[i].neighbourPoints[j] << " ";
        }
        std::cout << std::endl;
    }
*/
    /*for (int i = 0; i < numberOfPoints; ++i) {
        std::cout << i << "   ";
        for (int j = 0; j < points[i].neighbourPoints.size(); ++j) {
            std::cout << points[i].neighbourPoints[j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < numberOfPoints; ++i) {
        std::cout << i << " " << points[i].sscMember << std::endl;
    }*/
    /*int i = 0;
    for (auto vec : SSCs) {
        //std::cout << i++ << "  \n";
        for (auto blob : vec) {
            std::cout << blob << " ";
        }
        std::cout << "\n";
    }*/
    /*for (int i = 0; i < points.size(); ++i) {
        std::cout << points[i].sscMember << " ";
    } std::cout << std::endl;
    std::cout << "-----------------------------------------------------------------------------" << std::endl;
    for (int i = 0; i < points.size(); ++i) {
        std::cout << i << "\n";
        std::cout << "Neighbours:" << "\n";
        for (int j = 0; j < points[i].neighbourPoints.size(); ++j) {
            std::cout << points[i].neighbourPoints[j] << " ";
        } std::cout << "\n";
        std::cout << "Children:" << "\n";
        for (int j = 0; j < points[i].childOf.size(); ++j) {
            std::cout << points[i].childOf[j] << " ";
        } std::cout << "\n";
    } std::cout << std::endl;
*/
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
           /*std::cout << numberOfSSCs << " *****************\n";
           for (int i = 0; i < SSCs[numberOfSSCs].size(); ++i) {
               std::cout << points[SSCs[numberOfSSCs][i]].sscMember << " ";
           } std::cout << "\n****************\n";*/

           /*std::cout << currentPoint << "\n";
           std::cout << numberOfSSCs << "\n";*/
            auto newMainNode = SSCs[numberOfSSCs][0];
            std::unordered_set<int> newNeighbours;
            std::unordered_set<int> newChildrenOf;
            for (auto currentPoint : SSCs[numberOfSSCs]) {
                for (auto neighbour : points[currentPoint].neighbourPoints) {
                    if(points[neighbour].sscMember != numberOfSSCs){
                        newNeighbours.insert(neighbour);
                        auto it = find(points[neighbour].childOf.begin(), points[neighbour].childOf.end(), currentPoint);
                        int index = it - points[neighbour].childOf.begin();
                        points[neighbour].childOf[index] = newMainNode;
                    }
                }
                for (auto child : points[currentPoint].childOf) {
                    if(points[child].sscMember != numberOfSSCs){
                        newChildrenOf.insert(child);
                        auto it = find(points[child].neighbourPoints.begin(), points[child].neighbourPoints.end(), currentPoint);
                        int index = it - points[child].neighbourPoints.begin();
                        points[child].neighbourPoints[index] = newMainNode;
                    }
                }
            }
            std::vector<int> newTempNeighbs(newNeighbours.begin(), newNeighbours.end());
           std::vector<int> newTempChild(newChildrenOf.begin(), newChildrenOf.end());
           points[newMainNode].neighbourPoints = newTempNeighbs;
           points[newMainNode].childOf = newTempChild;
           //points[newMainNode].neighbourPoints.insert(points[newMainNode].neighbourPoints.begin(), newNeighbours.begin(), newNeighbours.end());
           //points[newMainNode].childOf.insert(points[newMainNode].childOf.begin(), newChildrenOf.begin(), newChildrenOf.end());
       }
/*for (int i = 1; i < SSCs[numberOfSSCs].size(); i++) {
    points[currentPoint].neighbourPoints.insert(points[currentPoint].neighbourPoints.end(), points[i].neighbourPoints.begin(),points[i].neighbourPoints.end());
}*/
            /*std::cout << currentPoint << "\n";
            for (int i : points[currentPoint].neighbourPoints) {
                std::cout << i << " ";
            }std::cout << "\n";

            std::unordered_set<int> s;
            auto end = std::remove_if(points[currentPoint].neighbourPoints.begin(), points[currentPoint].neighbourPoints.end(),
                                      [&s](int const &i) {
                                          return !s.insert(i).second;
                                      });

            points[currentPoint].neighbourPoints.erase(end, points[currentPoint].neighbourPoints.end());*/
        //}
        numberOfSSCs++;
    }
    return 0;
}