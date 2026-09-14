#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <string>

using std::string;

class Pokemon {
private: 
    int id;
    string name;
    string type1;
    string type2;
    double Total;
    double hitPoint;
    double attack;
    double defense;
    double specialAttack;
    double specialDefense;
    double speed;
    int generation;
    bool legendary;
    static int NumberOfPokemon;

public:
    Pokemon(int i,string n,string t1,string t2,double total,double h,double a,double d,double sa,double sd,double s,int g, bool l);

    Pokemon(const Pokemon& anotherPokemon);

    static int getNumberOfPokemon();

    double getAttack() const;
    double getDefense() const;
    double getHitPoint() const;
    int getId() const;
    string getName() const;
    double getSpecialAttack() const;
    double getSpecialDefense() const;
    double getSpeed() const;
    string getType1() const;
    string getType2() const;

    void displayInfo() const;

    void Battle(Pokemon& target);

    ~Pokemon();

};

#endif