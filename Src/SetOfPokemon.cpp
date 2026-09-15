/**
 * Rôle    : Implémentation des comportements par défaut des listes de Pokémon.
 * 
 * Fonctionnalités :
 * - Contient la logique de base pour rechercher un Pokémon par ID ou par nom.
 * - Parcourt le vecteur interne pour afficher tous les Pokémon de la liste 
 *   (displayAllPokemon).
 */

#include <iostream>
#include "Pokemon.hpp"
#include "SetOfPokemon.hpp" 

using namespace std;

Pokemon SetOfPokemon::getPokemonWithId(const Pokemon& p){
    for (const Pokemon& pokemon : pokemonList) {
        if (pokemon.getId() == p.getId()) {
            return pokemon;
        }
    }
}

Pokemon SetOfPokemon::getPokemonWithName(const Pokemon& p){
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