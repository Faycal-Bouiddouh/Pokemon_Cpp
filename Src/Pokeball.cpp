/**
 * Rôle    : Implémentation de la logique de stockage du PC.
 * 
 * Fonctionnalités :
 * - Implémente la logique d'ajout standard dans le vecteur.
 * - Modifie le comportement de la récupération : lorsqu'un Pokémon est 
 *   retrouvé (par ID ou nom), la méthode le copie, puis utilise un itérateur 
 *   pour l'effacer définitivement (erase) de la Pokeball avant de le renvoyer.
 */

#include "Pokeball.hpp"
#include <iostream>

using namespace std;

Pokeball::Pokeball() : SetOfPokemon() {
}

void Pokeball::addPokemon(const Pokemon& p) {
    pokemonList.push_back(p);
}

// REVIEW : Si la recherche échoue, la méthode renvoie p, donc le Pokémon "Search"
// créé juste pour faire la recherche peut finir dans l'équipe avec toutes ses stats à 0.
// Je mettrais plutôt un std::optional<Pokemon> en retour pour pouvoir signaler
// simplement qu'aucun Pokémon n'a été trouvé.
Pokemon Pokeball::getPokemonWithId(const Pokemon& p) {
    for (auto it = pokemonList.begin(); it != pokemonList.end(); ++it) {
        if (it->getId() == p.getId()) {
            Pokemon foundPokemon = *it; 
            pokemonList.erase(it);      
            return foundPokemon;        
        }
    }
    std::cerr << "Erreur : Pokemon introuvable dans la Pokeball." << std::endl;
    return p;
}

Pokemon Pokeball::getPokemonWithName(const Pokemon& p) {
    for (auto it = pokemonList.begin(); it != pokemonList.end(); ++it) {
        if (it->getName() == p.getName()) {
            Pokemon foundPokemon = *it;
            pokemonList.erase(it);
            return foundPokemon;
        }
    }
    std::cerr << "Erreur : Pokemon introuvable dans la Pokeball." << std::endl;
    return p;
}