//
//  main.cpp
//  Dijkstra
//
//  Created by Lore Ang and Yulisa Medina on 10/21/19.
//  Copyright © 2019 Lore Ang. All rights reserved.
//

#include <iostream>
#include <string>
#include <limits.h>
using namespace std;

// Global variables
int iNodes = 20;
int MatConnections[20][20];

// Function to initialize the matrix with INT_MAX values
void inicializeMat(int MatConnections[20][20])
{
    for (int i = 0; i < iNodes; i++)
    {
        for (int j = 0; j < iNodes; j++)
        {
            MatConnections[i][j] = INT_MAX;
        }
    }
}

// Function to calculate the minimum distance
int calcMinDistance(int pathDistance[], bool shortestPath[], int iQNodes)
{
    int minDistance = INT_MAX;
    int minAt = 0;
    
    for(int currNode = 0; currNode < iQNodes; ++currNode){
        if(!shortestPath[currNode] && pathDistance[currNode] <= minDistance)
        {
            minDistance = pathDistance[currNode];
            minAt = currNode;
        }
    }
    return minAt;
}

// Function to print the shortes path with arrows showing cost
void printShortestPath(int jumpCost[], int path[], int currAt)
{
    if (path[currAt] == -1)
    {
        cout << char(currAt + 65);
        return;
    }
    
    printShortestPath(jumpCost, path, path[currAt]);
    
    cout << " --" << jumpCost[currAt] << "--> " << char(currAt + 65);
}

// Function to print the costs and the path
void printCostsAndPath(int jumpCost[], int distances[], int path[], int iQNodes)
{
    cout << endl << "Paths" << endl;
    
    /*
    // Print every path from origin to another node
    for(int i = 1; i < iQNodes; ++i)
    {
        printShortestPath(distances, path, i);
        cout << " = " << distances[i] << endl;
    }
    */
    
    // Print only path from origin to last node and consider that our objective could have no edges
    if (distances[iQNodes - 1] == INT_MAX)
    {
        cout << "No possible path: Node is inaccessible :(" << endl;
    }
    else
    {
        printShortestPath(jumpCost, path, iQNodes - 1);
        cout << " = " << distances[iQNodes - 1] << endl;
    }
}

void dijkstra(int MatConnections[20][20], int iQNodes)
{
    // For cumulative cost of path
    int pathDistance[iQNodes];
    // For the individual jump cost between nodes of the path
    int jumpCost[iQNodes];
    // Verifier of nodes included in path
    bool shortestPath[iQNodes];
    // Shortest path
    int answers[iQNodes];
    
    // Fill paths with dummy values
    for(int i = 0; i < iQNodes; i++)
    {
        pathDistance[i] = INT_MAX;
        shortestPath[i] = false;
        jumpCost[i] = INT_MAX;
    }
    
    // Identify origin by marking it -1
    answers[0] = -1;
    
    // Origin does not have any cost
    pathDistance[0] = 0;
    
    // Check which is the shortest cumulative cost of connected nodes in regards to current node
    int minDistanceAt;
    for (int currShortest = 0; currShortest < iQNodes - 1; currShortest++)
    {
        minDistanceAt = calcMinDistance(pathDistance, shortestPath, iQNodes);
        shortestPath[minDistanceAt] = true;
        for (int currNode = 0; currNode < iQNodes; currNode++)
        {
            // Check if current node is not included, and the distance between it and the next one is the lowest so that it can be added to the path
            if(!shortestPath[currNode] && (MatConnections[minDistanceAt][currNode] != INT_MAX) && (pathDistance[minDistanceAt] + MatConnections[minDistanceAt][currNode] < pathDistance[currNode]))
            {
                pathDistance[currNode] = pathDistance[minDistanceAt] + MatConnections[minDistanceAt][currNode];
                answers[currNode] = minDistanceAt;
                jumpCost[currNode] = MatConnections[minDistanceAt][currNode];
            }
        }
    }
    printCostsAndPath(jumpCost, pathDistance, answers,iQNodes);
}

int main()
{
    int iOption, iConnections;
    string sConnection;
    /*
     0 [0, 1, 2, 3]
     1 [0, 1, 2, 3]
     2 [0, 1, 2, 3]
     3 [0, 1, 2, 3]
     A B 3   A B 10
     */
    
    do
    {
        cout << "\nDijkstra Algorithm\n";
        cout << "1. Find out minimum cost route\n";
        cout << "2. Finish\n";
        cout << "Select an option: ";
        cin >> iOption;
        cout << endl;
        
        switch (iOption)
        {
            case 1:
                inicializeMat(MatConnections);
                cout << "Amount of nodes (maximum 20): ";
                cin >> iNodes;
                cout << "Amount of connections: ";
                cin >> iConnections;
                cin.ignore();
                cout << "\nType all the connections, one per line, in a 'origin node' 'destination node' 'cost' format\n";
                cout << "For example: \nA B 3\nA C 10\nB C 1\n\n";
                
                // Store values in matrix
                for (int i = 0; i < iConnections; i++)
                {
                    cout << "Connection " << i + 1 << ": ";
                    getline(cin, sConnection);
                    int i1 = sConnection[0] - 65;
                    int i2 = sConnection[2] - 65;
                    int iN = sConnection.length() - 4;
                    MatConnections[i1][i2] = stoi(sConnection.substr(4,iN));
                }
                
                dijkstra(MatConnections, iNodes);
                break;
                
            case 2:
                cout << "Thank you.\n";
                break;
                
            default:
                cout << "Error, select a valid option.\n";
                break;
        }
    } while (iOption != 2);
    
    return 0;
}
