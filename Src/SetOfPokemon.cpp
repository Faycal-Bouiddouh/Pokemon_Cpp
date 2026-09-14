#include <iostream>
#include "Pokemon.hpp"
#include "SetOfPokemon.hpp"

using namespace std;

Pokemon SetOfPokemon::getPokemonWithId(const Pokemon& p) const {
    for (const Pokemon& pokemon : pokemonList) {
        if (pokemon.getId() == p.getId()) {
            return pokemon;
        }
    }
}

Pokemon SetOfPokemon::getPokemonWithName(const Pokemon& p) const {
    for (const Pokemon& pokemon : pokemonList) {
        if (pokemon.getName() == p.getName()) {
            return pokemon;
        }
    }
}

void SetOfPokemon::displayAllPokemon() const {
    for (const Pokemon& pokemon : pokemonList) {
        pokemon.displayInfo();
    }
}