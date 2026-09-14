#include "Pokedex.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Pokedex& Pokedex::getInstance() {
    static Pokedex instance("../ressources/pokedex.csv"); 
    return instance;
}

Pokedex::Pokedex(string fileName) : SetOfPokemon() {
    

    std::ifstream file(fileName);
    if(!file.is_open()){
        std::cerr << "File " << fileName << " not found " << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::stringstream inputstringstream(line);
        std::string cell;
        std::vector<std::string> lineData;

        while(std::getline(inputstringstream, cell, ',')){
            lineData.push_back(cell);
        }
        
        int id = std::stoi(lineData.at(0));
        double hitPoint = std::stod(lineData.at(5));
        double attackValue = std::stod(lineData.at(6));
        double defenseValue = std::stod(lineData.at(7));
        int generation = std::stoi(lineData.at(11));
        string type1 = lineData.at(2);
        string type2 = lineData.at(3);
        double total = std::stod(lineData.at(4));
        double specialAttack = std::stod(lineData.at(8));
        double specialDefense = std::stod(lineData.at(9));
        double speed = std::stod(lineData.at(10));
        bool legendary = (lineData.at(12) == "True" || lineData.at(12) == "true");


        pokemonList.push_back(Pokemon(id, lineData.at(1), type1, type2, total, hitPoint, attackValue, defenseValue, specialAttack, specialDefense, speed, generation, legendary));
    }
}

Pokemon Pokedex::getClone(int targetId) const {
    for (const Pokemon& p : pokemonList) {
        if (p.getId() == targetId) {
            return p;
        }
    }
     
}