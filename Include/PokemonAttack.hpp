/**
 * Represents a battle team limited to 6 Pokemon.
 *
 * This class distinguishes the battle lineup from the player's main team.
 * It prepares an active battle selection without changing the application's
 * overall structure.
 */

#ifndef POKEMON_ATTACK_HPP
#define POKEMON_ATTACK_HPP

#include "PokemonParty.hpp"

#include <vector>

class PokemonAttack : public PokemonParty {
public:
    // Builds a battle team from IDs stored in the PC.
    explicit PokemonAttack(Pokeball& pc, const std::vector<int>& sixIndexes = {});

    // Builds a battle team from Pokemon names stored in the PC.
    explicit PokemonAttack(Pokeball& pc, const std::vector<std::string>& sixNames);

    // Copies up to 6 Pokemon from a larger team for battle.
    void buildFromParty(const PokemonParty& party);

    // Returns the active Pokemon to a larger team after battle.
    void reintegrateToParty(PokemonParty& party);

    // Checks whether the battle team is full.
    bool isFull() const;
};

#endif
