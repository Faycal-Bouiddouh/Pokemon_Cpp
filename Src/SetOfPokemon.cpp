/**
 * Rôle    : Implémentation des comportements par défaut des listes de Pokémon.
 * 
 * Fonctionnalités :
 * - Contient la logique de base pour rechercher un Pokémon par ID ou par nom.
 * - Parcourt le vecteur interne pour afficher tous les Pokémon de la liste 
 *   (displayAllPokemon).
 */

#include <iostream>
#include <algorithm>
#include "Pokemon.hpp"
#include "SetOfPokemon.hpp" 

using namespace std;

// REVIEW : Si le Pokémon n'est pas trouvé, la fonction arrive à la fin sans return.
// g++ le signale avec "control reaches end of non-void function".
// Même problème pour getPokemonWithName juste en dessous.
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

// AJOUT REVUE : méthode ajoutée pour permettre de trier la liste avec un comparateur.
void SetOfPokemon::sortBy(const std::function<bool(const Pokemon&, const Pokemon&)>& comparator) {
    std::sort(pokemonList.begin(), pokemonList.end(), comparator);
}
