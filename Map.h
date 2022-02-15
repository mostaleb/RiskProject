#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Player.h"

class Territory {
public:
    Territory(std::string, std::string, Player*, int);
    ~Territory();
    void setContinent(std::string);
    void setCountry(std::string);
    std::string getContinent();
    std::string getCountry();
    Player* getTerritoryOwner();
    int* getArmyCount();
    static int id;
    int getID();

private:
    int terr_id;
    std::string country, continent;
    Player* territoryOwner;
    int* armyCount;
};

class Edge {
public:
    Edge(Territory*, Territory*);
    ~Edge();

public:
    std::pair<Territory*, Territory*> AdjacencyEdges;
};

class Map {

public:
    Map();
    ~Map();
    bool validate();

public:
    std::vector<Territory*> Nodes; // Nodes is a pointer similar to how an array gives a pointer to the first element - Assigning a pointer value will result in **
    std::vector<Edge*> Edges; // Edges is a pointer similar to how an array gives a pointer to the first element - Assigning a pointer value will result in **
};


class MapLoader {
public:
    Map* readMap(std::string);
};