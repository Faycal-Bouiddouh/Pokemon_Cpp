/**
 * Purpose: Implements the default behavior for Pokemon collections.
 * 
 * Features:
 * - Provides the basic search logic for Pokemon IDs and names.
 * - Displays all Pokemon in the internal collection.
 */

#include <stdexcept>
#include <algorithm>
#include "Display.hpp"
#include "SetOfPokemon.hpp" 

using namespace std;

// Finds a Pokemon by ID and returns it if present.
Pokemon SetOfPokemon::findPokemonById(int id) const {
    const auto pokemon = std::find_if(pokemonList.begin(), pokemonList.end(), [id](const Pokemon& candidate) {
        return candidate.getId() == id;
    });
    if (pokemon == pokemonList.end()) {
        throw std::runtime_error("Pokemon introuvable dans la collection (ID).");
    }
    return *pokemon;
}

// Finds a Pokemon by its exact name in the current collection.
Pokemon SetOfPokemon::findPokemonByName(const string& name) const {
    const auto pokemon = std::find_if(pokemonList.begin(), pokemonList.end(), [&name](const Pokemon& candidate) {
        return candidate.getName() == name;
    });
    if (pokemon == pokemonList.end()) {
        throw std::runtime_error("Pokemon introuvable dans la collection (nom).");
    }
    return *pokemon;
}

// Provides read-only access to the collection.
const vector<Pokemon>& SetOfPokemon::getPokemonList() const {
    return pokemonList;
}

// Displays the Pokemon in this collection using the display utilities.
void SetOfPokemon::displayAllPokemon() const {
    displayPokemonCollection(pokemonList);
}

// Sorts the collection using a comparison function supplied by the caller.
void SetOfPokemon::sortBy(const std::function<bool(const Pokemon&, const Pokemon&)>& comparator) {
    std::sort(pokemonList.begin(), pokemonList.end(), comparator);
}