/**
 * Purpose: Implements the team manager.
 * 
 * Features:
 * - Links the team to the PC through an initializer list.
 * - The constructors transfer Pokemon from the PC into the team.
 * - Enforces a maximum team size of 6 Pokemon.
 * - Implements removal of Pokemon from the team.
 */

#include "PokemonParty.hpp"

#include <algorithm>
#include <stdexcept>

// Initializes a team from Pokemon IDs stored in the PC.
PokemonParty::PokemonParty(const std::vector<int>& sixIndexes, Pokeball& pc) 
    : SetOfPokemon(), linkedPokeball(pc) 
{
    for (int id : sixIndexes) {
        addPokemon(id);
    }
}

// Initializes a team from Pokemon names stored in the PC.
PokemonParty::PokemonParty(const std::vector<std::string>& sixNames, Pokeball& pc) 
    : SetOfPokemon(), linkedPokeball(pc) 
{
    for (const std::string& name : sixNames) {
        addPokemon(name);
    }
}

// Adds a Pokemon to the team by ID, removing it from the PC.
bool PokemonParty::addPokemon(int targetId) {
    if (!hasAvailableSpace()) {
        return false;
    }
    pokemonList.push_back(linkedPokeball.takePokemonById(targetId));
    return true;
}

// Adds a Pokemon to the team by its exact name.
bool PokemonParty::addPokemon(const std::string& name) {
    if (!hasAvailableSpace()) {
        return false;
    }
    pokemonList.push_back(linkedPokeball.takePokemonByName(name));
    return true;
}

// Adds an existing Pokemon instance if the team has space.
bool PokemonParty::addPokemon(const Pokemon& pokemon) {
    if (!hasAvailableSpace()) {
        return false;
    }
    if (std::find_if(pokemonList.begin(), pokemonList.end(), [&pokemon](const Pokemon& candidate) {
            return candidate.getName() == pokemon.getName();
        }) != pokemonList.end()) {
        return false;
    }
    pokemonList.push_back(pokemon);
    return true;
}

// Checks whether the team is below its six-Pokemon limit.
bool PokemonParty::hasAvailableSpace() const {
    return pokemonList.size() < maxPartySize;
}

// Removes a Pokemon from the team by ID and returns it.
Pokemon PokemonParty::takePokemonById(int id) {
    const auto pokemon = std::find_if(pokemonList.begin(), pokemonList.end(), [id](const Pokemon& candidate) {
        return candidate.getId() == id;
    });
    if (pokemon == pokemonList.end()) {
        throw std::runtime_error("Pokemon introuvable dans l'equipe (ID).");
    }
    Pokemon extractedPokemon = *pokemon;
    pokemonList.erase(pokemon);
    return extractedPokemon;
}

// Removes a Pokemon from the team by name and returns it to the caller.
Pokemon PokemonParty::takePokemonByName(const std::string& name) {
    const auto pokemon = std::find_if(pokemonList.begin(), pokemonList.end(), [&name](const Pokemon& candidate) {
        return candidate.getName() == name;
    });
    if (pokemon == pokemonList.end()) {
        throw std::runtime_error("Pokemon introuvable dans l'equipe (nom).");
    }
    Pokemon extractedPokemon = *pokemon;
    pokemonList.erase(pokemon);
    return extractedPokemon;
}