/**
 * Represents the player's active team.
 *
 * This class stores the Pokemon currently selected for play. It is linked to
 * the PC to transfer Pokemon to and from the team, which can hold up to 6 members.
 */

#ifndef POKEMONPARTY_HPP
#define POKEMONPARTY_HPP

#include "SetOfPokemon.hpp"
#include "Pokeball.hpp"
#include <cstddef>
#include <vector>
#include <string>

class PokemonParty : public SetOfPokemon {
private:
    static constexpr std::size_t maxPartySize = 6;
    Pokeball& linkedPokeball;

    // Checks whether the team has an available slot.
    bool hasAvailableSpace() const;

public:
    // Initializes a team using Pokemon IDs stored in the PC.
    PokemonParty(const std::vector<int>& sixIndexes, Pokeball& pc);

    // Initializes a team using Pokemon names stored in the PC.
    PokemonParty(const std::vector<std::string>& sixNames, Pokeball& pc);

    // Adds a Pokemon to the team by ID.
    bool addPokemon(int targetId);

    // Adds a Pokemon to the team by name.
    bool addPokemon(const std::string& name);

    // Adds an existing Pokemon instance directly to the team.
    bool addPokemon(const Pokemon& pokemon);

    // Removes a Pokemon from the team by ID.
    Pokemon takePokemonById(int id);

    // Removes a Pokemon from the team by name.
    Pokemon takePokemonByName(const std::string& name);
};

#endif 