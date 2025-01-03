#include "Game.h"

Game::Game()
{
	this->window = new sf::RenderWindow(sf::VideoMode(width, height), "T E T R I S");
    this->window->setView(sf::View(sf::FloatRect(0, 0, width, height)));
    this->window->setFramerateLimit(60);
    auto image = sf::Image{};
    if (!image.loadFromFile("./assets/tetrisIcon.png"))
    {
        std::cerr << "Nie uda³o siê wczytaæ pliku 'tetrisIcon.png'." << std::endl;
    }

    this->window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    this->initStates();

}

Game::~Game()
{
    delete this->window;

    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }

}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->Event))
    {
        if (this->Event.type == sf::Event::Closed) {
            this->window->close();
        }
    }
}

void Game::render()
{
    this->window->clear();

    if (!this->states.empty()) {
        this->states.top()->render(this->window);
    }

    this->window->display();
}

void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty()) {
        this->states.top()->update(this->dt);
        if (this->states.top()->getEnd()) {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else {
        this->window->close();
    }
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}

void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->states));
}
