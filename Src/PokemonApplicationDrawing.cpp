#include "PokemonApplication.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <filesystem>
namespace {
constexpr unsigned int windowWidth = 1280;
constexpr unsigned int windowHeight = 800;
constexpr float headerHeight = 100.0f;
constexpr std::size_t visibleRows = 12;
constexpr std::size_t partySize = 6;

const sf::Color backgroundColor(226, 240, 239);
const sf::Color headerColor(210, 62, 70);
const sf::Color panelColor(255, 252, 239);
const sf::Color selectedColor(255, 237, 172);
const sf::Color outlineColor(69, 91, 111);
const sf::Color primaryTextColor(38, 53, 76);
const sf::Color secondaryTextColor(101, 119, 137);
const sf::Color accentColor(42, 151, 160);
const sf::Color actionColor(242, 174, 61);
const sf::Color shadowColor(42, 67, 83, 55);

std::filesystem::path findResource(const std::string& relativePath) {
    const std::array<std::filesystem::path, 3> candidates = {
        std::filesystem::current_path() / relativePath,
        std::filesystem::current_path() / ".." / relativePath,
        std::filesystem::current_path() / ".." / ".." / relativePath
    };

    for (const auto& candidate : candidates) {
        if (std::filesystem::exists(candidate)) {
            return candidate;
        }
    }
    return {};
}

sf::Color typeColor(const std::string& type) {
    if (type == "Fire") return sf::Color(207, 91, 65);
    if (type == "Water") return sf::Color(73, 132, 180);
    if (type == "Grass") return sf::Color(84, 145, 92);
    if (type == "Electric") return sf::Color(199, 158, 61);
    if (type == "Psychic") return sf::Color(177, 91, 124);
    if (type == "Ice") return sf::Color(92, 164, 164);
    if (type == "Poison") return sf::Color(139, 91, 159);
    if (type == "Ground" || type == "Rock") return sf::Color(151, 116, 74);
    if (type == "Flying") return sf::Color(104, 133, 171);
    if (type == "Bug") return sf::Color(130, 145, 65);
    if (type == "Ghost") return sf::Color(98, 94, 145);
    if (type == "Dragon") return sf::Color(105, 91, 183);
    if (type == "Steel") return sf::Color(113, 130, 146);
    if (type == "Fairy") return sf::Color(193, 119, 151);
    if (type == "Fighting") return sf::Color(174, 91, 65);
    if (type == "Dark") return sf::Color(93, 82, 76);
    return sf::Color(111, 126, 103);
}

void drawCard(sf::RenderWindow& window, sf::FloatRect bounds, sf::Color fill,
              sf::Color outline = outlineColor) {
    sf::RectangleShape shadow(bounds.size);
    shadow.setPosition({bounds.position.x + 4.0f, bounds.position.y + 5.0f});
    shadow.setFillColor(shadowColor);
    window.draw(shadow);

    sf::RectangleShape card(bounds.size);
    card.setPosition(bounds.position);
    card.setFillColor(fill);
    card.setOutlineThickness(2.0f);
    card.setOutlineColor(outline);
    window.draw(card);
}

void drawPokemonLogo(sf::RenderWindow& window, sf::Vector2f position) {
    const sf::Color lineColor(115, 48, 62);

    sf::CircleShape outerCircle(21.0f);
    outerCircle.setPosition(position);
    outerCircle.setFillColor(sf::Color(255, 255, 255));
    outerCircle.setOutlineThickness(3.0f);
    outerCircle.setOutlineColor(lineColor);
    window.draw(outerCircle);

    sf::RectangleShape divider({40.0f, 5.0f});
    divider.setPosition({position.x + 1.0f, position.y + 19.0f});
    divider.setFillColor(lineColor);
    window.draw(divider);

    sf::CircleShape centerCircle(7.0f);
    centerCircle.setPosition({position.x + 14.0f, position.y + 15.0f});
    centerCircle.setFillColor(sf::Color(255, 255, 255));
    centerCircle.setOutlineThickness(3.0f);
    centerCircle.setOutlineColor(lineColor);
    window.draw(centerCircle);
}

void drawBattleArena(sf::RenderWindow& window) {
    sf::RectangleShape sky({566.0f, 346.0f});
    sky.setPosition({357.0f, 185.0f});
    sky.setFillColor(sf::Color(203, 233, 235));
    window.draw(sky);

    sf::RectangleShape ground({566.0f, 151.0f});
    ground.setPosition({357.0f, 380.0f});
    ground.setFillColor(sf::Color(185, 221, 176));
    window.draw(ground);

    sf::CircleShape hill(90.0f);
    hill.setScale({2.9f, 0.72f});
    hill.setPosition({379.0f, 338.0f});
    hill.setFillColor(sf::Color(154, 207, 173));
    window.draw(hill);

    sf::CircleShape sun(34.0f);
    sun.setPosition({832.0f, 210.0f});
    sun.setFillColor(sf::Color(255, 220, 133));
    window.draw(sun);

    sf::CircleShape playerPlatform(93.0f);
    playerPlatform.setScale({1.9f, 0.34f});
    playerPlatform.setPosition({378.0f, 390.0f});
    playerPlatform.setFillColor(sf::Color(226, 239, 183));
    playerPlatform.setOutlineThickness(3.0f);
    playerPlatform.setOutlineColor(sf::Color(118, 170, 128));
    window.draw(playerPlatform);

    sf::CircleShape opponentPlatform(80.0f);
    opponentPlatform.setScale({1.65f, 0.3f});
    opponentPlatform.setPosition({667.0f, 331.0f});
    opponentPlatform.setFillColor(sf::Color(226, 239, 183));
    opponentPlatform.setOutlineThickness(3.0f);
    opponentPlatform.setOutlineColor(sf::Color(118, 170, 128));
    window.draw(opponentPlatform);
}
}

bool PokemonApplication::contains(sf::FloatRect bounds, sf::Vector2i point) const {
    return point.x >= bounds.position.x && point.x <= bounds.position.x + bounds.size.x &&
           point.y >= bounds.position.y && point.y <= bounds.position.y + bounds.size.y;
}

std::filesystem::path PokemonApplication::resolveSpritePath(const Pokemon& pokemon) const {
    std::size_t formIndex = 0;
    bool foundPokemon = false;
    for (const Pokemon& entry : pokedex.getPokemonList()) {
        if (entry.getId() != pokemon.getId()) continue;
        if (entry.getName() == pokemon.getName()) {
            foundPokemon = true;
            break;
        }
        ++formIndex;
    }

    if (foundPokemon && formIndex > 0) {
        std::string formSuffix = std::to_string(formIndex);
        if (formIndex < 10) formSuffix.insert(formSuffix.begin(), '0');
        const std::filesystem::path formSprite = findResource(
            "ressources/pokemon/" + std::to_string(pokemon.getId()) + "." + formSuffix + ".png");
        if (!formSprite.empty()) return formSprite;
    }

    return findResource("ressources/pokemon/" + std::to_string(pokemon.getId()) + ".png");
}

sf::Texture* PokemonApplication::getSpriteTexture(const Pokemon& pokemon) {
    const std::filesystem::path path = resolveSpritePath(pokemon);
    if (path.empty()) return nullptr;

    const std::string cacheKey = path.string();
    auto texture = spriteCache.find(cacheKey);
    if (texture == spriteCache.end()) {
        texture = spriteCache.emplace(cacheKey, sf::Texture{}).first;
        if (!texture->second.loadFromFile(path)) {
            spriteCache.erase(texture);
            return nullptr;
        }
        texture->second.setSmooth(false);
    }
    return &texture->second;
}

void PokemonApplication::drawText(const std::string& value, sf::Vector2f position,
                                  unsigned int size, sf::Color color) {
    sf::Text text(font, sf::String::fromUtf8(value.begin(), value.end()), size);
    text.setFillColor(color);
    text.setPosition(position);
    window.draw(text);
}

void PokemonApplication::drawPanel(sf::FloatRect bounds, sf::Color color, sf::Color outline) {
    sf::RectangleShape panel(bounds.size);
    panel.setPosition(bounds.position);
    panel.setFillColor(color);
    if (outline != sf::Color::Transparent) {
        panel.setOutlineThickness(2.0f);
        panel.setOutlineColor(outline);
    }
    window.draw(panel);
}

void PokemonApplication::drawButton(sf::FloatRect bounds, const std::string& label, bool emphasized) {
    const bool hovered = contains(bounds, mousePosition);
    const sf::Color fill = emphasized ? actionColor : panelColor;
    const sf::Color hoverFill(
        static_cast<std::uint8_t>(std::min(255, static_cast<int>(fill.r) + 12)),
        static_cast<std::uint8_t>(std::min(255, static_cast<int>(fill.g) + 12)),
        static_cast<std::uint8_t>(std::min(255, static_cast<int>(fill.b) + 12)));
    drawCard(window, bounds, hovered ? hoverFill : fill,
             emphasized ? sf::Color(158, 105, 35) : outlineColor);
    sf::Text text(font, sf::String::fromUtf8(label.begin(), label.end()), 17);
    const sf::FloatRect textBounds = text.getLocalBounds();
    text.setFillColor(primaryTextColor);    text.setPosition({bounds.position.x + (bounds.size.x - textBounds.size.x) / 2.0f - textBounds.position.x,
                      bounds.position.y + (bounds.size.y - textBounds.size.y) / 2.0f - textBounds.position.y});
    window.draw(text);
}

void PokemonApplication::drawPokemonSprite(const Pokemon& pokemon, sf::FloatRect bounds) {
    sf::Texture* texture = getSpriteTexture(pokemon);
    if (texture == nullptr) {
        drawPanel(bounds, panelColor, outlineColor);
        drawText("#" + std::to_string(pokemon.getId()), {bounds.position.x + 24.0f, bounds.position.y + bounds.size.y / 2.0f}, 22, secondaryTextColor);
        return;
    }

    sf::Sprite sprite(*texture);
    const sf::Vector2u textureSize = texture->getSize();
    const float scale = std::min(bounds.size.x / static_cast<float>(textureSize.x),
                                 bounds.size.y / static_cast<float>(textureSize.y));
    sprite.setScale({scale, scale});
    sprite.setPosition({bounds.position.x + (bounds.size.x - textureSize.x * scale) / 2.0f,
                        bounds.position.y + (bounds.size.y - textureSize.y * scale) / 2.0f});
    window.draw(sprite);
}

void PokemonApplication::drawPokemonDetails(const Pokemon& pokemon, sf::Vector2f position) {
    drawText(pokemon.getName(), position, 32, primaryTextColor);
    drawText("N° " + std::to_string(pokemon.getId()) + "  |  Generation " + std::to_string(pokemon.getGeneration()),
             {position.x, position.y + 44.0f}, 16, secondaryTextColor);

    const std::array<std::string, 2> types = {pokemon.getType1(), pokemon.getType2()};
    float typeX = position.x;
    for (const std::string& type : types) {
        if (type.empty()) continue;
        drawCard(window, {{typeX, position.y + 82.0f}, {120.0f, 34.0f}}, typeColor(type),
                 sf::Color(255, 255, 255));
        drawText(type, {typeX + 12.0f, position.y + 88.0f}, 16, primaryTextColor);
        typeX += 132.0f;
    }

    const std::array<std::pair<std::string, double>, 6> stats = {{
        {"HP", pokemon.getHitPoint()}, {"Attack", pokemon.getAttack()},
        {"Defense", pokemon.getDefense()}, {"Sp. Atk", pokemon.getSpecialAttack()},
        {"Sp. Def", pokemon.getSpecialDefense()}, {"Speed", pokemon.getSpeed()}
    }};
    for (std::size_t index = 0; index < stats.size(); ++index) {
        const float columnX = position.x + static_cast<float>(index % 2) * 195.0f;
        const float rowY = position.y + 148.0f + static_cast<float>(index / 2) * 46.0f;
        drawPanel({{columnX - 8.0f, rowY - 5.0f}, {176.0f, 36.0f}},
                  index % 2 == 0 ? sf::Color(238, 247, 245) : sf::Color(247, 247, 237));
        drawText(stats[index].first, {columnX, rowY}, 15, secondaryTextColor);
        drawText(std::to_string(static_cast<int>(stats[index].second)), {columnX + 125.0f, rowY - 2.0f}, 18, primaryTextColor);
    }
}

void PokemonApplication::draw() {
    window.clear(backgroundColor);
    if (currentView == View::StarterSelection) {
        drawStarterSelection();
    } else {
        drawHeader();
        switch (currentView) {
            case View::Pokedex: drawPokedex(); break;
            case View::Team: drawTeam(); break;
            case View::Storage: drawStorage(); break;
            case View::Battle: drawBattle(); break;
            case View::StarterSelection: break;
        }
        if (!statusMessage.empty()) {
            drawText(statusMessage, {34.0f, 766.0f}, 15, accentColor);
        }
    }
    window.display();
}

void PokemonApplication::drawStarterSelection() {
    drawPanel({{0.0f, 0.0f}, {static_cast<float>(windowWidth), 106.0f}}, headerColor);
    drawPanel({{0.0f, 101.0f}, {static_cast<float>(windowWidth), 5.0f}}, sf::Color(168, 44, 57));
    drawPokemonLogo(window, {30.0f, 20.0f});
    drawText("POKEMON", {83.0f, 29.0f}, 22, sf::Color(255, 255, 255));
    drawCard(window, {{70.0f, 124.0f}, {1140.0f, 78.0f}}, panelColor);
    drawText("Choose your team", {94.0f, 133.0f}, 31, primaryTextColor);
    drawText("Pick " + std::to_string(draftRound + 1) + " / 10  -  Choose a Pokemon from the three options",
             {96.0f, 171.0f}, 16, secondaryTextColor);

    constexpr float cardStartX = 75.0f;
    constexpr float cardWidth = 350.0f;
    constexpr float cardGap = 40.0f;
    for (std::size_t index = 0; index < draftChoices.size(); ++index) {
        const Pokemon& pokemon = draftChoices[index];
        const float x = cardStartX + static_cast<float>(index) * (cardWidth + cardGap);
        const sf::FloatRect card({x, 240.0f}, {cardWidth, 430.0f});
        const bool hovered = contains(card, mousePosition);
        drawCard(window, card, hovered ? selectedColor : panelColor,
                 hovered ? sf::Color(216, 153, 50) : outlineColor);
        drawPanel({{x + 12.0f, 252.0f}, {326.0f, 240.0f}},
                  sf::Color(223, 242, 241));
        drawPokemonSprite(pokemon, {{x + 45.0f, 270.0f}, {260.0f, 220.0f}});
        drawText("#" + std::to_string(pokemon.getId()), {x + 24.0f, 505.0f}, 14, secondaryTextColor);
        drawText(pokemon.getName(), {x + 24.0f, 526.0f}, 25, primaryTextColor);
        const bool hasSecondaryType = !pokemon.getType2().empty();
        const float typeBadgeWidth = 142.0f;
        const float firstTypeX = hasSecondaryType ? x + 24.0f : x + 104.0f;
        drawPanel({{firstTypeX, 566.0f}, {typeBadgeWidth, 26.0f}}, typeColor(pokemon.getType1()));
        drawText(pokemon.getType1(), {firstTypeX + 8.0f, 568.0f}, 15, sf::Color(255, 255, 255));
        if (hasSecondaryType) {
            const float secondTypeX = x + 184.0f;
            drawPanel({{secondTypeX, 566.0f}, {typeBadgeWidth, 26.0f}},
                      typeColor(pokemon.getType2()));
            drawText(pokemon.getType2(), {secondTypeX + 8.0f, 568.0f}, 15, sf::Color(255, 255, 255));
        }
        drawButton({{x + 24.0f, 600.0f}, {302.0f, 48.0f}}, "CHOOSE THIS POKEMON", hovered);
    }

    drawCard(window, {{70.0f, 690.0f}, {1140.0f, 62.0f}}, panelColor);
    drawText("Team in preparation", {94.0f, 700.0f}, 16, secondaryTextColor);
    drawText(std::to_string(storage.getPokemonList().size()) + " / 10 Pokemon chosen",
             {94.0f, 723.0f}, 17, accentColor);
    drawText("Click a Pokemon card to choose it", {760.0f, 714.0f}, 15, secondaryTextColor);
}

void PokemonApplication::drawHeader() {
    drawPanel({{0.0f, 0.0f}, {static_cast<float>(windowWidth), headerHeight}}, headerColor);
    drawPanel({{0.0f, 94.0f}, {static_cast<float>(windowWidth), 6.0f}}, sf::Color(168, 44, 57));
    drawPokemonLogo(window, {25.0f, 24.0f});
    drawText("POKEMON", {76.0f, 24.0f}, 21, sf::Color(255, 255, 255));
    drawText("ADVENTURE", {78.0f, 51.0f}, 12, sf::Color(255, 220, 196));
    drawText("PC  " + std::to_string(storage.getPokemonList().size()) + " Pokemon",
             {270.0f, 40.0f}, 15, sf::Color(255, 255, 255));

    const std::array<std::string, 4> labels = {"Pokedex", "Team", "PC", "Battle"};
    const std::array<View, 4> views = {View::Pokedex, View::Team, View::Storage, View::Battle};
    const std::array<float, 4> positions = {590.0f, 715.0f, 830.0f, 930.0f};
    for (std::size_t index = 0; index < labels.size(); ++index) {
        const bool active = currentView == views[index];
        drawButton({{positions[index], 26.0f}, {112.0f, 48.0f}}, labels[index], active);
    }
}

void PokemonApplication::drawPokedex() {
    const auto& pokemonList = pokedex.getPokemonList();
    drawCard(window, {{28.0f, 130.0f}, {365.0f, 610.0f}}, panelColor);
    drawText("POKEDEX NATIONAL", {48.0f, 143.0f}, 16, primaryTextColor);
    drawText(std::to_string(pokemonList.size()) + " species", {48.0f, 165.0f}, 13, secondaryTextColor);
    for (std::size_t row = 0; row < visibleRows && dexOffset + row < pokemonList.size(); ++row) {
        const std::size_t index = dexOffset + row;
        const float y = 180.0f + static_cast<float>(row) * 45.0f;
        const bool selected = index == dexSelection;
        if (selected) drawCard(window, {{39.0f, y}, {342.0f, 40.0f}}, selectedColor,
                               sf::Color(216, 153, 50));
        const Pokemon& pokemon = pokemonList[index];
        drawText("#" + std::to_string(pokemon.getId()), {51.0f, y + 8.0f}, 13, accentColor);
        drawText(pokemon.getName(), {104.0f, y + 7.0f}, 15, selected ? primaryTextColor : secondaryTextColor);
    }

    if (pokemonList.empty()) return;
    drawCard(window, {{414.0f, 130.0f}, {838.0f, 610.0f}}, panelColor);
    const Pokemon& selectedPokemon = pokemonList.at(dexSelection);
    drawPanel({{440.0f, 190.0f}, {310.0f, 390.0f}}, sf::Color(223, 242, 241));
    drawPokemonSprite(selectedPokemon, {{450.0f, 214.0f}, {290.0f, 330.0f}});
    drawPokemonDetails(selectedPokemon, {785.0f, 170.0f});
    drawText("Use the mouse wheel to browse the Pokedex", {50.0f, 716.0f}, 14, secondaryTextColor);
}

void PokemonApplication::drawTeam() {
    const auto& pokemonList = battleTeam.empty() ? team.getPokemonList() : battleTeam;
    drawCard(window, {{28.0f, 120.0f}, {1224.0f, 36.0f}}, panelColor);
    drawText("MY TEAM", {49.0f, 124.0f}, 19, primaryTextColor);
    drawText(std::to_string(pokemonList.size()) + " / 6", {1110.0f, 126.0f}, 17, accentColor);
    for (std::size_t index = 0; index < 6; ++index) {
        const float x = 35.0f + static_cast<float>(index % 2) * 410.0f;
        const float y = 160.0f + static_cast<float>(index / 2) * 190.0f;
        const sf::FloatRect card({x, y}, {390.0f, 165.0f});
        const bool occupied = index < pokemonList.size();
        drawCard(window, card, occupied && index == teamSelection ? selectedColor : panelColor,
                 occupied && index == teamSelection ? sf::Color(216, 153, 50) : outlineColor);
        if (occupied) {
            const Pokemon& pokemon = pokemonList[index];
            drawPanel({{x + 9.0f, y + 9.0f}, {132.0f, 145.0f}}, sf::Color(223, 242, 241));
            drawPokemonSprite(pokemon, {{x + 12.0f, y + 12.0f}, {128.0f, 136.0f}});
            drawText(pokemon.getName(), {x + 150.0f, y + 24.0f}, 20, primaryTextColor);
            drawText(pokemon.getType1() + (pokemon.getType2().empty() ? "" : " / " + pokemon.getType2()),
                     {x + 150.0f, y + 59.0f}, 15, secondaryTextColor);
            drawText("HP " + std::to_string(static_cast<int>(pokemon.getHitPoint())) +
                     "     ATK " + std::to_string(static_cast<int>(pokemon.getAttack())),
                     {x + 150.0f, y + 96.0f}, 14, accentColor);
        } else {
            drawText("Free slot", {x + 28.0f, y + 62.0f}, 18, secondaryTextColor);
        }
    }
    if (battleTeam.empty()) {
        drawText("Click a member to return it to the PC.", {35.0f, 718.0f}, 14, secondaryTextColor);
        drawButton({{720.0f, 715.0f}, {500.0f, 44.0f}},
                   pokemonList.size() == partySize ? "CONFIRM TEAM AND FIGHT" : "CHOOSE 6 POKEMON FROM THE PC",
                   pokemonList.size() == partySize);
    } else {
        drawText("Team locked for this battle.", {35.0f, 760.0f}, 14, secondaryTextColor);
    }
}

void PokemonApplication::drawStorage() {
    const auto& pokemonList = storage.getPokemonList();
    drawCard(window, {{28.0f, 130.0f}, {365.0f, 610.0f}}, panelColor);
    drawText("PC BOX", {48.0f, 143.0f}, 16, primaryTextColor);
    drawText(std::to_string(pokemonList.size()) + " stored Pokemon", {48.0f, 165.0f}, 13, secondaryTextColor);
    for (std::size_t row = 0; row < visibleRows && storageOffset + row < pokemonList.size(); ++row) {
        const std::size_t index = storageOffset + row;
        const float y = 180.0f + static_cast<float>(row) * 45.0f;
        const bool selected = index == storageSelection;
        if (selected) drawCard(window, {{39.0f, y}, {342.0f, 40.0f}}, selectedColor,
                               sf::Color(216, 153, 50));
        const Pokemon& pokemon = pokemonList[index];
        drawText("#" + std::to_string(pokemon.getId()), {51.0f, y + 8.0f}, 13, accentColor);
        drawText(pokemon.getName(), {104.0f, y + 7.0f}, 15, selected ? primaryTextColor : secondaryTextColor);
    }

    if (pokemonList.empty()) return;
    const Pokemon& selectedPokemon = pokemonList.at(storageSelection);
    drawCard(window, {{414.0f, 130.0f}, {838.0f, 610.0f}}, panelColor);
    drawPanel({{440.0f, 190.0f}, {310.0f, 390.0f}}, sf::Color(223, 242, 241));
    drawPokemonSprite(selectedPokemon, {{450.0f, 214.0f}, {290.0f, 330.0f}});
    drawPokemonDetails(selectedPokemon, {785.0f, 170.0f});
    drawButton({{785.0f, 660.0f}, {330.0f, 52.0f}},
               team.getPokemonList().size() < partySize ? "ADD TO TEAM" : "TEAM COMPLETE",
               team.getPokemonList().size() < partySize);
    drawText("Use the mouse wheel to browse, then click Add to Team", {50.0f, 716.0f}, 14, secondaryTextColor);
}

void PokemonApplication::drawBattle() {
    drawCard(window, {{28.0f, 116.0f}, {1224.0f, 48.0f}}, panelColor);
    drawText("BATTLE", {48.0f, 126.0f}, 18, primaryTextColor);
    drawText("Opponent " + std::to_string(std::min(opponentSelection + 1, opponentTeam.size())) + " / 6",
             {1030.0f, 128.0f}, 15, accentColor);
    drawCard(window, {{24.0f, 174.0f}, {306.0f, 481.0f}}, panelColor);
    drawCard(window, {{346.0f, 174.0f}, {588.0f, 481.0f}}, panelColor);
    drawCard(window, {{958.0f, 174.0f}, {298.0f, 481.0f}}, panelColor);

    drawBattleArena(window);

    drawText("YOUR TEAM", {42.0f, 165.0f}, 15, accentColor);
    for (std::size_t index = 0; index < battleTeam.size(); ++index) {
        const Pokemon& pokemon = battleTeam[index];
        const float y = 194.0f + static_cast<float>(index) * 74.0f;
        const bool active = index == teamSelection;
        drawPanel({{34.0f, y}, {286.0f, 68.0f}}, active ? selectedColor : panelColor,
                  active ? sf::Color(216, 153, 50) : outlineColor);
        drawPokemonSprite(pokemon, {{39.0f, y + 4.0f}, {72.0f, 58.0f}});
        drawText(std::to_string(index + 1) + ". " + pokemon.getName(), {117.0f, y + 8.0f}, 14, primaryTextColor);
        const double maxHitPoints = std::max(1.0, pokedex.findPokemonByName(pokemon.getName()).getHitPoint());
        const float hpRatio = static_cast<float>(pokemon.getHitPoint() / maxHitPoints);
        drawPanel({{117.0f, y + 35.0f}, {170.0f, 8.0f}}, sf::Color(72, 79, 66));
        drawPanel({{117.0f, y + 35.0f}, {170.0f * hpRatio, 8.0f}},
                  pokemon.getHitPoint() > 0.0 ? accentColor : actionColor);
        drawText("HP " + std::to_string(static_cast<int>(pokemon.getHitPoint())),
                 {117.0f, y + 47.0f}, 12, secondaryTextColor);
    }

    if (!battleTeam.empty()) {
        const Pokemon& player = battleTeam.at(teamSelection);
        drawPokemonSprite(player, {{409.0f, 240.0f}, {230.0f, 220.0f}});
        drawCard(window, {{376.0f, 193.0f}, {250.0f, 60.0f}}, panelColor);
        drawText(player.getName(), {390.0f, 199.0f}, 17, primaryTextColor);
        drawText("N° " + std::to_string(player.getId()) + "  " +
                 player.getType1() + (player.getType2().empty() ? "" : " / " + player.getType2()),
                 {390.0f, 225.0f}, 12, secondaryTextColor);
    }

    if (opponentSelection < opponentTeam.size()) {
        const Pokemon& enemy = opponentTeam.at(opponentSelection);
        drawPokemonSprite(enemy, {{690.0f, 214.0f}, {190.0f, 180.0f}});
        drawCard(window, {{666.0f, 428.0f}, {244.0f, 60.0f}}, panelColor);
        drawText(enemy.getName(), {680.0f, 434.0f}, 17, primaryTextColor);
        drawText("N° " + std::to_string(enemy.getId()) + "  " +
                 enemy.getType1() + (enemy.getType2().empty() ? "" : " / " + enemy.getType2()),
                 {680.0f, 460.0f}, 12, secondaryTextColor);
    }

    drawText("ENEMY TEAM", {976.0f, 165.0f}, 15, accentColor);
    for (std::size_t index = 0; index < opponentTeam.size(); ++index) {
        const Pokemon& pokemon = opponentTeam[index];
        const float y = 194.0f + static_cast<float>(index) * 74.0f;
        const bool active = index == opponentSelection;
        const bool rewardSelected = battleWon && !rewardClaimed && index == rewardSelection;
        drawPanel({{968.0f, y}, {278.0f, 68.0f}},
                  active || rewardSelected ? selectedColor : panelColor,
                  active || rewardSelected ? sf::Color(216, 153, 50) : outlineColor);
        drawPokemonSprite(pokemon, {{973.0f, y + 4.0f}, {72.0f, 58.0f}});
        drawText(pokemon.getName(), {1051.0f, y + 8.0f}, 14, primaryTextColor);
        const double maxHitPoints = std::max(1.0, pokedex.findPokemonByName(pokemon.getName()).getHitPoint());
        const float hpRatio = static_cast<float>(pokemon.getHitPoint() / maxHitPoints);
        drawPanel({{1051.0f, y + 35.0f}, {170.0f, 8.0f}}, sf::Color(72, 79, 66));
        drawPanel({{1051.0f, y + 35.0f}, {170.0f * hpRatio, 8.0f}},
                  pokemon.getHitPoint() > 0.0 ? accentColor : actionColor);
        drawText("HP " + std::to_string(static_cast<int>(pokemon.getHitPoint())),
                 {1051.0f, y + 47.0f}, 12, secondaryTextColor);
    }

    for (std::size_t index = 0; index < lastRound.size() && index < 2; ++index) {
        const AttackResult& attack = lastRound[index];
        const std::string result = attack.hasNoEffect ? "no effect" :
            std::to_string(static_cast<int>(attack.damage)) + " damage (x" + std::to_string(attack.typeEffectiveness) + ")";
        drawText(attack.attackerName + " : " + result,
                 {375.0f, 545.0f + static_cast<float>(index) * 25.0f}, 13,
                 attack.hasNoEffect ? secondaryTextColor : primaryTextColor);
    }

    const std::string battleAction = battleWon && !rewardClaimed
        ? "CLAIM AT PC"
        : (battleFinished ? "BATTLE OVER" : "FIGHT");
    const std::string opponentAction = battleWon && !rewardClaimed
        ? "CLAIM YOUR POKEMON FIRST"
        : "NEW ENEMY TEAM";
    drawButton({{590.0f, 666.0f}, {300.0f, 60.0f}}, battleAction, true);
    drawButton({{920.0f, 666.0f}, {300.0f, 60.0f}}, opponentAction);
    if (battleWon && !rewardClaimed) {
        drawText("Click an enemy Pokemon, then click Claim at PC.",
                 {28.0f, 738.0f}, 14, accentColor);
    } else {
        drawText("Click a teammate to switch, then click Fight.",
                 {28.0f, 738.0f}, 14, secondaryTextColor);
    }
}