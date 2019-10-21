//
//  main.cpp
//  Dijkstra
//
//  Created by Lore Ang and Yulisa Medina on 10/21/19.
//  Copyright © 2019 Lore Ang. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int iNodes = 20;

void inicializeMat(int MatConnections[20][20])
{
    for (int i = 0; i < iNodes; i++)
    {
        for (int j = 0; j < iNodes; j++)
        {
            MatConnections[i][j] = 0;
        }
    }
}

void dijkstra(int MatConnections[20][20])
{
    // Not programmed yet
}

int main()
{
    int iOption, iConnections;
    int MatConnections[20][20];
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
                for (int i = 0; i < iConnections; i++)
                {
                    cout << "Connection " << i + 1 << ": ";
                    getline(cin, sConnection);
                    int j = sConnection[2] - 41;
                    int iN = sConnection.length() - 4;
                    MatConnections[i][j] = stoi(sConnection.substr(4,iN));
                }
                dijkstra(MatConnections);
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
