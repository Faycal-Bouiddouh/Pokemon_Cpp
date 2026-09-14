#include "Pokeball.hpp"
#include <iostream>

using namespace std;

Pokeball::Pokeball() : SetOfPokemon() {
}

void Pokeball::addPokemon(const Pokemon& p) {
    pokemonList.push_back(p);
}

Pokemon Pokeball::getPokemonWithId(const Pokemon& p) {
    for (auto it = pokemonList.begin(); it != pokemonList.end(); ++it) {
        if (it->getId() == p.getId()) {
            Pokemon foundPokemon = *it; 
            
            pokemonList.erase(it);      
            
            return foundPokemon;        
        }
    }
    std::cerr << "Erreur : Pokemon introuvable dans la Pokeball." << std::endl;
    return p;
}

Pokemon Pokeball::getPokemonWithName(const Pokemon& p) {
    for (auto it = pokemonList.begin(); it != pokemonList.end(); ++it) {
        if (it->getName() == p.getName()) {
            Pokemon foundPokemon = *it;
            pokemonList.erase(it);
            return foundPokemon;
        }
    }
    std::cerr << "Erreur : Pokemon introuvable dans la Pokeball." << std::endl;
    return p;
}