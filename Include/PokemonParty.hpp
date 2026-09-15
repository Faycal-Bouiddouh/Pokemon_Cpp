/**
 * Rôle    : Déclaration de la classe PokemonParty (l'équipe active du joueur).
 * 
 * Fonctionnalités :
 * - Hérite de SetOfPokemon pour représenter une équipe limitée.
 * - Déclare une référence privée (linkedPokeball) reliant l'équipe au PC.
 * - Déclare des constructeurs prenant des listes d'IDs ou de noms.
 * - Signale la redéfinition des méthodes de récupération.
 */

#ifndef POKEMONPARTY_HPP
#define POKEMONPARTY_HPP

#include "SetOfPokemon.hpp"
#include "Pokeball.hpp"
#include <vector>
#include <string>

class PokemonParty : public SetOfPokemon {
private:
    Pokeball& linkedPokeball;

public:
    PokemonParty(const std::vector<int>& sixIndexes, Pokeball& pc);

    PokemonParty(const std::vector<std::string>& sixNames, Pokeball& pc);

    void addPokemon(int targetId);

    Pokemon getPokemonWithId(const Pokemon& p) override;
    Pokemon getPokemonWithName(const Pokemon& p) override;
};

#endif 