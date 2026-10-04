#include "PokemonAttack.hpp"

#include <algorithm>
#include <stdexcept>

// Creates a battle team from IDs stored in the PC.
PokemonAttack::PokemonAttack(Pokeball& pc, const std::vector<int>& sixIndexes)
    : PokemonParty(sixIndexes, pc) {
}

// Creates a battle team from Pokemon names stored in the PC.
PokemonAttack::PokemonAttack(Pokeball& pc, const std::vector<std::string>& sixNames)
    : PokemonParty(sixNames, pc) {
}

// Prepares up to six Pokemon selected from a larger team.
void PokemonAttack::buildFromParty(const PokemonParty& party) {
    pokemonList.clear();
    for (const Pokemon& pokemon : party.getPokemonList()) {
        if (pokemonList.size() >= 6) {
            break;
        }
        if (std::find_if(pokemonList.begin(), pokemonList.end(), [&pokemon](const Pokemon& candidate) {
                return candidate.getName() == pokemon.getName();
            }) == pokemonList.end()) {
            pokemonList.push_back(pokemon);
        }
    }
}

// Returns the active selection to the main team after battle.
void PokemonAttack::reintegrateToParty(PokemonParty& party) {
    for (const Pokemon& pokemon : pokemonList) {
        if (party.getPokemonList().size() >= 6) {
            break;
        }
        party.addPokemon(pokemon);
    }
    pokemonList.clear();
}

// Checks whether the battle team is full and ready to fight.
bool PokemonAttack::isFull() const {
    return pokemonList.size() >= 6;
}
