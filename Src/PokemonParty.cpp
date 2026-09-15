/**
 * Rôle    : Implémentation du gestionnaire d'équipe.
 * 
 * Fonctionnalités :
 * - Relie physiquement l'équipe au PC via une liste d'initialisation.
 * - Automatise le transfert : le constructeur demande directement les Pokémon 
 *   à la Pokeball, ce qui déclenche leur suppression du PC et leur ajout ici.
 * - Assure une limite de capacité (maximum 6 Pokémon par équipe).
 * - Implémente la logique de suppression lors du retrait d'un Pokémon de l'équipe.
 */

#include "PokemonParty.hpp"
#include <iostream>

using namespace std;

PokemonParty::PokemonParty(const std::vector<int>& sixIndexes, Pokeball& pc) 
    : SetOfPokemon(), linkedPokeball(pc) 
{
    std::cout << "*** Initialisation de l'equipe ***" << std::endl;
    for (int id : sixIndexes) {
        addPokemon(id);
    }
}

PokemonParty::PokemonParty(const std::vector<std::string>& sixNames, Pokeball& pc) 
    : SetOfPokemon(), linkedPokeball(pc) 
{
    std::cout << "*** Initialisation de l'equipe ***" << std::endl;
    for (const std::string& name : sixNames) {
        Pokemon dummySearch(0, name, "", "", 0, 0, 0, 0, 0, 0, 0, 0, false); 
        Pokemon extracted = linkedPokeball.getPokemonWithName(dummySearch);
        pokemonList.push_back(extracted);
    }
}

void PokemonParty::addPokemon(int targetId) {
    if (pokemonList.size() >= 6) {
        std::cout << "Attention : L'equipe est deja pleine (6 Pokemon max) !" << std::endl;
        return;
    }
    
    Pokemon dummySearch(targetId, "Search", "", "", 0, 0, 0, 0, 0, 0, 0, 0, false);
    
    Pokemon extracted = linkedPokeball.getPokemonWithId(dummySearch);
    pokemonList.push_back(extracted);
}

Pokemon PokemonParty::getPokemonWithId(const Pokemon& p) {
    for (auto it = pokemonList.begin(); it != pokemonList.end(); ++it) {
        if (it->getId() == p.getId()) {
            Pokemon foundPokemon = *it;
            pokemonList.erase(it);
            return foundPokemon;
        }
    }
    std::cerr << "Erreur : Pokemon introuvable dans l'equipe." << std::endl;
    return p;
}

Pokemon PokemonParty::getPokemonWithName(const Pokemon& p) {
    for (auto it = pokemonList.begin(); it != pokemonList.end(); ++it) {
        if (it->getName() == p.getName()) {
            Pokemon foundPokemon = *it;
            pokemonList.erase(it); 
            return foundPokemon;
        }
    }
    std::cerr << "Erreur : Pokemon introuvable dans l'equipe." << std::endl;
    return p;
}