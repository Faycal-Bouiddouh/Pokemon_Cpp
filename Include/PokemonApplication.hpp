/**
 * Main application and game rendering engine.
 *
 * This class coordinates all screens and SFML interactions. It manages the
 * Pokedex, PC storage, team building, and battle system while delegating
 * screen behavior to the state machine.
 */

#ifndef POKEMON_APPLICATION_HPP
#define POKEMON_APPLICATION_HPP

#include "GameState.hpp"
#include "Pokedex.hpp"
#include "Pokeball.hpp"
#include "PokemonParty.hpp"

#include <SFML/Graphics.hpp>

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class PokemonApplication {
    friend class StarterSelectionState;
    friend class PokedexState;
    friend class TeamState;
    friend class StorageState;
    friend class BattleState;

public:
    // Initializes the application and prepares the first game screen.
    PokemonApplication();

    // Runs the main application loop until the window is closed.
    int run();

    enum class View {
        StarterSelection,
        Pokedex,
        Team,
        Storage,
        Battle
    };

private:
    // Active screen state, replaced polymorphically when navigating between screens.
    std::unique_ptr<GameState> state;

    Pokedex& pokedex;
    sf::RenderWindow window;
    sf::Font font;
    std::vector<Pokemon> draftChoices;
    Pokeball storage;
    PokemonParty team;
    std::vector<Pokemon> battleTeam;
    std::vector<Pokemon> opponentTeam;
    View currentView = View::StarterSelection;
    std::size_t draftRound = 0;
    std::size_t dexSelection = 0;
    std::size_t dexOffset = 0;
    std::size_t storageSelection = 0;
    std::size_t storageOffset = 0;
    std::size_t teamSelection = 0;
    std::vector<AttackResult> lastRound;
    std::size_t opponentSelection = 0;
    bool battleFinished = false;
    bool battleWon = false;
    bool rewardClaimed = false;
    std::size_t rewardSelection = 0;
    std::unordered_map<std::string, sf::Texture> spriteCache;
    sf::Vector2i mousePosition{0, 0};
    std::string statusMessage;

    // Loads the font used by the interface.
    void loadFont();

    // Changes the active screen and replaces the current state object.
    void setState(View nextView);

    // Processes SFML events collected during one iteration of the main loop.
    void processEvents();

    // Processes window events and mouse input.
    void processEvent(const sf::Event& event);

    // Handles a mouse click and triggers the corresponding action.
    void processClick(sf::Vector2i position);

    // Selects a Pokemon offered on the initial screen.
    void chooseDraftPokemon(std::size_t index);

    // Transfers the selected Pokemon from the PC to the team.
    void addSelectedStoragePokemon();

    // Returns a Pokemon from the team to the PC.
    void returnTeamPokemonToStorage(std::size_t index);

    // Starts a battle between the player's team and a random opponent team.
    void startBattle();

    // Generates a new random opponent team for the next battle.
    void chooseRandomOpponent();

    // Adds a defeated Pokemon to the player's storage after a victory.
    void claimOpponentPokemon();

    // Changes the active Pokemon selected for battle.
    void switchActivePokemon(std::size_t index);

    // Executes a full battle turn, taking speed and hit points into account.
    void runBattle();

    // Draws the complete application scene for the current state.
    void draw();

    // Draws the initial selection screen.
    void drawStarterSelection();

    // Draws the header shared by all screens.
    void drawHeader();

    // Draws the Pokedex screen.
    void drawPokedex();

    // Draws the active team screen.
    void drawTeam();

    // Draws the PC storage screen.
    void drawStorage();

    // Draws the battle arena and battle information.
    void drawBattle();

    // Draws a detailed Pokemon summary.
    void drawPokemonDetails(const Pokemon& pokemon, sf::Vector2f position);

    // Draws a Pokemon sprite inside its display area.
    void drawPokemonSprite(const Pokemon& pokemon, sf::FloatRect bounds);

    // Draws text with the application's active font.
    void drawText(const std::string& value, sf::Vector2f position, unsigned int size,
                  sf::Color color = sf::Color::White);

    // Draws a rectangular panel with an optional outline.
    void drawPanel(sf::FloatRect bounds, sf::Color color, sf::Color outline = sf::Color::Transparent);

    // Draws an interactive button, optionally emphasized.
    void drawButton(sf::FloatRect bounds, const std::string& label, bool emphasized = false);

    // Checks whether a mouse position lies inside a rectangle.
    bool contains(sf::FloatRect bounds, sf::Vector2i point) const;

    // Finds the sprite path for a Pokemon, including alternate forms.
    std::filesystem::path resolveSpritePath(const Pokemon& pokemon) const;

    // Returns the SFML texture for a Pokemon, loading and caching it if needed.
    sf::Texture* getSpriteTexture(const Pokemon& pokemon);
};

#endif