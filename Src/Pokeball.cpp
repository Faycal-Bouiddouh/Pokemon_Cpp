/**
 * Purpose: Implements the PC storage logic.
 * 
 * Features:
 * - Adds Pokemon to the underlying vector.
 * - Removes a Pokemon from the PC when retrieving it by ID or name.
 */

#include "Pokeball.hpp"
#include <algorithm>
#include <stdexcept>

using namespace std;

// Initializes an empty PC ready to store Pokemon.
Pokeball::Pokeball() : SetOfPokemon() {
}

// Adds a Pokemon to the player's storage without checking for duplicate names.
void Pokeball::addPokemon(const Pokemon& p) {
    pokemonList.push_back(p);
}

// Removes and returns the Pokemon matching the given ID.
Pokemon Pokeball::takePokemonById(int id) {
    const auto pokemon = std::find_if(pokemonList.begin(), pokemonList.end(), [id](const Pokemon& candidate) {
        return candidate.getId() == id;
    });
    if (pokemon == pokemonList.end()) {
        throw std::runtime_error("Pokemon not found in the PC (ID).");
    }
    Pokemon extractedPokemon = *pokemon;
    pokemonList.erase(pokemon);
    return extractedPokemon;
}

// Removes and returns the Pokemon matching the given name.
Pokemon Pokeball::takePokemonByName(const string& name) {
    const auto pokemon = std::find_if(pokemonList.begin(), pokemonList.end(), [&name](const Pokemon& candidate) {
        return candidate.getName() == name;
    });
    if (pokemon == pokemonList.end()) {
        throw std::runtime_error("Pokemon not found in the PC (name).");
    }
    Pokemon extractedPokemon = *pokemon;
    pokemonList.erase(pokemon);
    return extractedPokemon;
}