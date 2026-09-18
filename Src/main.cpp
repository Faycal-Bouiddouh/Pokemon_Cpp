#include <iostream>
#include <vector>
// REVIEW : windows.h était inclus directement, donc ça bloquait la compilation sous Linux.
// J'ai simplement ajouté cette garde pour garder le comportement Windows sans bloquer Linux.
#ifdef _WIN32
#include <windows.h>
#endif

#include "Pokedex.hpp"
#include "Pokeball.hpp"
#include "PokemonParty.hpp"
#include "Pokemon.hpp"

using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    cout << "========== PHASE 1 : CHARGEMENT DU POKEDEX ==========" << endl;
    Pokedex& pokedex = Pokedex::getInstance();


    cout << "\n========== PHASE 2 : REMPLISSAGE DU PC (POKEBALL) ==========" << endl;
    Pokeball monPC;
    
    monPC.addPokemon(pokedex.getClone(1));  
    monPC.addPokemon(pokedex.getClone(4));  
    monPC.addPokemon(pokedex.getClone(7)); 
    monPC.addPokemon(pokedex.getClone(25)); 

    cout << "Contenu initial du PC (4 Pokemon) :" << endl;
    monPC.displayAllPokemon();


    cout << "\n========== PHASE 3 : CREATION DE L'EQUIPE ==========" << endl;
    vector<int> mesFavoris = {1, 7};
    
    PokemonParty monEquipe(mesFavoris, monPC);

    cout << "\nContenu de mon Equipe (Doit contenir Bulbizarre et Carapuce) :" << endl;
    monEquipe.displayAllPokemon();


    cout << "\n========== PHASE 4 : VERIFICATION DU PC ==========" << endl;
    cout << "Contenu du PC apres transfert (Bulbizarre et Carapuce ont disparu) :" << endl;
    monPC.displayAllPokemon();

    cout << "\n========== PHASE 5 : TRI DE L'EQUIPE (methode proposee) ==========" << endl;
    // La lambda ci-dessous est le comparateur passé à sortBy : ordre de vitesse
    // décroissante, soit l'ordre dans lequel les Pokémon frapperaient en combat.
    monEquipe.sortBy([](const Pokemon& a, const Pokemon& b) {
        return a.getSpeed() > b.getSpeed();
    });
    cout << "Equipe triee par vitesse decroissante :" << endl;
    monEquipe.displayAllPokemon();

    return 0;
}