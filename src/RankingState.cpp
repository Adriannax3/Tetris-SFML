#include "RankingState.h"
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <ranges>

RankingState::RankingState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color(39, 60, 84));
	downloadResults();
    initButtons();
    this->running = false;
    blocks.resize(24, 0);
    for (int i = 0; i < blocks.size(); i++) {
        blocks[i] = i % 7;
    }
    
    if (!texture.loadFromFile("./assets/star.png"))
    {
        std::cerr << "Failed to load texture" << std::endl;
    }
    this->sprite.setTexture(texture);
    this->sprite.setPosition(sf::Vector2f(360, 165));
}

RankingState::~RankingState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != buttons.end(); ++it) {
        delete it->second;
    }

    this->stopAnimation();
}

bool compareByScore(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second;
}

void RankingState::downloadResults()
{
	std::filesystem::path path("./results.txt"); 
    std::ifstream file(path);

    std::vector<std::pair<std::string, int>> temp;

    if (std::filesystem::exists(path)) {
        if (file.is_open()) {
            std::string nick;
            int value;
            while (file >> nick >> value) {
                temp.emplace_back(nick, value);
            }

            file.close();

            std::ranges::sort(temp, compareByScore);
            auto view = temp | std::views::take(10);

            for (const auto el : view) {
                results.emplace_back(el);
            }

        }
        else {
            std::cerr << "pliku " << path << " nie udalo sie otworzyc" << std::endl;
        }
    }
    else {
        std::cerr << "plik " << path << " nie istnieje" << std::endl;
    }
}

void RankingState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);
    renderRanking();
    renderButtons(target);
    drawBlocks(target);
    target->draw(this->sprite);

    if (!this->running) {
        this->running = true;
        animation = std::jthread(&RankingState::updateBlocks, this);
    }
}

void RankingState::renderRanking()
{
    sf::Text text;
    sf::Font font;
    
    if (!font.loadFromFile("./FONT/VT323-Regular.ttf"))
    {
        std::cerr << "nie udalo sie zaladowac czcionki - RankingState" << std::endl;
    }
    renderHeader(font);

    const int positionX = this->window->getSize().x / 2.f - 180;
    int positionY = 150;

    text.setFont(font);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::White);

    int Y = 0;
    int counter = 0;
    for(const auto el : results) {
        std::string v = std::to_string(el.second);
        std::string pos = std::to_string(counter+1);
        text.setString(pos+". "+el.first + " " + v);
        text.setPosition(sf::Vector2f(positionX, positionY + Y));
        this->window->draw(text);
        Y += 50;
        counter++;
    }
}

void RankingState::renderHeader(sf::Font font)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(140);
    text.setFillColor(sf::Color::White);


    const int positionX = this->window->getSize().x / 2.f - 200;
    const int positionY = 0;
    text.setPosition(sf::Vector2f(positionX, positionY));
    text.setString("RANKING");
    this->window->draw(text);
}

void RankingState::initButtons()
{
    this->buttons["BACK"] = new Button(50, 680, 250, 100, &this->font, "BACK",
        sf::Color(154, 202, 209), sf::Color(112, 170, 178), sf::Color(173, 216, 230), 40);

    this->buttons["EXIT"] = new Button(900, 680, 250, 100, &this->font, "EXIT",
        sf::Color(154, 202, 209), sf::Color(112, 170, 178), sf::Color(173, 216, 230), 40);
}

void RankingState::renderButtons(sf::RenderTarget* target)
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != buttons.end(); ++it) {
        it->second->render(target);
    }
}

void RankingState::updateButtons()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != buttons.end(); ++it) {
        it->second->update(this->mousePosition);
    }

    if (this->buttons["BACK"]->isPressed()) {
        this->isEnd = true;
        this->states->pop();
        this->states->push(new MainMenuState(this->window, this->states));
    }

    if (this->buttons["EXIT"]->isPressed()) {
        this->isEnd = true;
    }
}

void RankingState::update(const float& dt)
{
    this->updateMousePosition();
    this->checkForEnd();
    this->updateButtons();
    
}

void RankingState::drawBlocks(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    const int posX1 = 0;
    const int posX2 = 1160;
    const int cell_size = 40;
    sf::RectangleShape cell;
    cell.setSize(sf::Vector2f(cell_size-1, cell_size-1));
    for (int i = 0; i < blocks.size(); i++) {
        switch (blocks[i]) {
        case 0:
            cell.setFillColor(sf::Color(0, 153, 94));
            break;
        case 1:
            cell.setFillColor(sf::Color(63, 89, 119));
            break;
        case 2:
            cell.setFillColor(sf::Color(255, 197, 103));
            break;
        case 3:
            cell.setFillColor(sf::Color(5, 140, 215));
            break;
        case 4:
            cell.setFillColor(sf::Color(251, 125, 168));
            break;
        case 5:
            cell.setFillColor(sf::Color(253, 90, 70));
            break;
        case 6:
            cell.setFillColor(sf::Color(85, 44, 183));
            break;
        default:
            break;
        }
        cell.setPosition(posX1, i * cell_size);
        target->draw(cell);
        cell.setPosition(posX2, i * cell_size);
        target->draw(cell);
    }
}

void RankingState::updateBlocks()
{
    while (!this->isEnd) {
        for (int i = 0; i < this->blocks.size(); i++) {
            this->blocks[i] = this->blocks[i] - 1;
            if (this->blocks[i] == -1) this->blocks[i] = 6;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }
    
}

void RankingState::stopAnimation()
{
    if (this->running)
    {
        this->running = false;

        if (animation.joinable()) {
            animation.join();
        }
    }
}
