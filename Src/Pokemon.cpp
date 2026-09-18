/**
 * Rôle    : Implémentation de la logique de la classe Pokemon.
 * 
 * Fonctionnalités :
 * - Contient le code effectif des constructeurs pour initialiser les attributs.
 * - Définit la logique des combats entre deux Pokémon (méthode Battle).
 * - Gère le formatage du texte pour l'affichage des informations (displayInfo).
 */


#include <iostream>
#include <string>
#include "Pokemon.hpp"

using namespace std;

int Pokemon::NumberOfPokemon = 0;

Pokemon::Pokemon(int i,string n,string t1,string t2,double total,double h,double a,double d,double sa,double sd,double s,int g, bool l):
id(i),name(n),type1(t1),type2(t2),Total(total),hitPoint(h),attack(a),defense(d),specialAttack(sa),specialDefense(sd),speed(s),generation(g),legendary(l){
    ++NumberOfPokemon;
}

// REVIEW : Le constructeur de copie n'incrémente pas NumberOfPokemon alors que le
// destructeur le décrémente. Avec toutes les copies faites dans les vector, le compteur
// finit donc par devenir négatif. Chez moi il arrivait à -1026.
// Ajouter ++NumberOfPokemon; ici devrait régler le problème.

// REVIEW : L'ordre de la liste d'initialisation ne correspond pas à l'ordre de déclaration
// des attributs. Ça fonctionne quand même, mais g++ le signale avec -Wreorder.
Pokemon::Pokemon(const Pokemon& anotherPokemon):
name(anotherPokemon.name),id(anotherPokemon.id),type1(anotherPokemon.type1),type2(anotherPokemon.type2),Total(anotherPokemon.Total),hitPoint(anotherPokemon.hitPoint),attack(anotherPokemon.attack),defense(anotherPokemon.defense),specialAttack(anotherPokemon.specialAttack),specialDefense(anotherPokemon.specialDefense),speed(anotherPokemon.speed),generation(anotherPokemon.generation),legendary(anotherPokemon.legendary){
    
}

int Pokemon::getNumberOfPokemon(){
    return NumberOfPokemon;
}

double Pokemon::getAttack() const{
    return attack;
}

double Pokemon::getDefense() const{
    return defense;
}

double Pokemon::getHitPoint() const{
    return hitPoint;
}

int Pokemon::getId() const{
    return id;
}

string Pokemon::getName() const{
    return name;
}

string Pokemon::getType1() const{
    return type1;
}

string Pokemon::getType2() const{
    return type2;
}

double Pokemon::getSpecialAttack() const{
    return specialAttack;
}

double Pokemon::getSpecialDefense() const{
    return specialDefense;
}

double Pokemon::getSpeed() const{
    return speed;
}

void Pokemon::Battle(Pokemon& target){
    cout << "****** BATTLE ******" << endl;
    if(this->speed > target.getSpeed())
    {
        cout << this->name << " est plus rapide que " << target.name << endl;
        if(this->attack > target.getDefense())
        {
            cout << this->name << " attaque " << target.name << endl;
            cout << target.name << " perd " << this->attack - target.getDefense() << " points de vie" << endl;
            target.hitPoint -= this->attack - target.getDefense();
            if(target.hitPoint < 0)
            {
                target.hitPoint = 0;
            }
            cout << target.name << " a maintenant " << target.getHitPoint() << " points de vie" << endl;
        }
        else
        {
            cout << this->name << " attaque " << target.name << endl;
            cout << target.name << " se protège et ne perd pas de points de vie" << endl;
        }

        if(target.getHitPoint() <= 0)
        {
            cout << target.name << " est KO" << endl;
        }
    }
    else
    {
        cout << target.name << " est plus rapide que " << this->name << endl;
        if(target.getAttack() > this->defense)
        {
            cout << target.name << " attaque " << this->name << endl;
            cout << this->name << " perd " << target.getAttack() - this->defense << " points de vie" << endl;
            this->hitPoint -= target.getAttack() - this->defense;
            if(this->hitPoint < 0)
            {
                this->hitPoint = 0;
            }
            cout << this->name << " a maintenant " << this->getHitPoint() << " points de vie" << endl;
        }
        else
        {
            cout << target.name << " attaque " << this->name << endl;
            cout << this->name << " se protège et ne perd pas de points de vie" << endl;
        }

        if(this->getHitPoint() <= 0)
        {
            cout << this->name << " est KO" << endl;
        }
    }
}


void Pokemon::displayInfo() const{
    cout << "****** " << name << " ******" << endl;
    cout << "Id : " << id << endl;
    cout << "Type 1 : " << type1 << endl;
    cout << "Type 2 : " << type2 << endl;
    cout << "HitPoint : " << hitPoint << endl;
    cout << "Attack : " << attack << endl;
    cout << "Defense : " << defense << endl;
    cout << "Special Attack : " << specialAttack << endl;
    cout << "Special Defense : " << specialDefense << endl;
    cout << "Speed : " << speed << endl;
    cout << "Generation : " << generation << endl;
    cout << "Legendary : " << (legendary ? "Yes" : "No") << endl;

}

Pokemon::~Pokemon(){
    --NumberOfPokemon;    
}