/**
 * Rôle    : Implémentation de la base de données (Pokedex).
 * 
 * Fonctionnalités :
 * - Gère l'ouverture, la lecture et le parsing sécurisé du fichier pokedex.csv.
 * - Remplit la liste interne en convertissant les lignes de texte en objets Pokemon.
 * - Implémente la méthode de clonage qui retourne un nouveau Pokémon identique
 *   à celui stocké, empêchant la modification de la base de données originelle.
 */

#include "Pokedex.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// REVIEW : Le chemin dépend du dossier depuis lequel on lance le programme et il n'est
// pas le même que celui déclaré dans Pokedex.hpp. Chez moi le programme ne trouve donc
// pas toujours le CSV selon l'endroit depuis lequel je le lance.
Pokedex& Pokedex::getInstance() {
    static Pokedex instance("../ressources/pokedex.csv"); 
    return instance;
}

Pokedex::Pokedex(string fileName) : SetOfPokemon() {
    

    std::ifstream file(fileName);
    if(!file.is_open()){
        // REVIEW : Ici le programme continue même si le CSV n'a pas été chargé, donc le Pokedex
        // reste vide. Je lancerais plutôt une exception ici pour arrêter proprement l'initialisation.
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

// REVIEW : Si targetId n'existe pas, la fonction arrive à la fin sans return.
// C'est notamment ce qui pose problème quand le CSV n'a pas été chargé.

// REVIEW : Il y a aussi plusieurs ids en double dans le CSV, par exemple 479 pour les
// différentes formes de Rotom. Avec cette recherche, seule la première sera trouvée.
Pokemon Pokedex::getClone(int targetId) const {
    for (const Pokemon& p : pokemonList) {
        if (p.getId() == targetId) {
            return p;
        }
    }
     
}