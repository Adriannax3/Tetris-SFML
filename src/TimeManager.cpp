#include "TimeManager.h"

void TimeManager::start()
{
	if (!this->running) {
		this->running = true;
		timer = std::jthread(&TimeManager::update, this);
	}
}

void TimeManager::update()
{
	time = 0;
	while (running)
	{
		time++;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void TimeManager::draw(sf::RenderWindow* window)
{
	int seconds = 0;
	int minutes = 0;
	std::string sec;
	std::string min;

	if (time < 10) {
		sec = std::to_string(this->time);
		sec = "0" + sec;
		min = "00";
	}
	else if (time > 9 && time < 60) {
		sec = std::to_string(this->time);
		min = "00";
	}
	else if (time >= 60) {
		minutes = time / 60;
		seconds = time % 60;

		if (minutes < 10) {
			min = std::to_string(minutes);
			min = "0" + min;
		}
		else {
			min = std::to_string(minutes);
		}

		if (seconds < 10) {
			sec = std::to_string(seconds);
			sec = "0" + sec;
		}
		else {
			sec = std::to_string(seconds);
		}
	}

	this->text.setCharacterSize(50);
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setPosition(sf::Vector2f(840, 80));
	this->text.setString(min+":"+sec);
	window->draw(text);
}

void TimeManager::stop()
{
	if (this->running)
	{
		this->running = false;

		if (timer.joinable()) {
			timer.join();
		}
	}
}

std::string TimeManager::getTime()
{
	int seconds = 0;
	int minutes = 0;
	std::string sec;
	std::string min;
	std::string string_time;

	if (time < 10) {
		sec = std::to_string(this->time);
		sec = "0" + sec;
		min = "00";
	}
	else if (time > 9 && time < 60) {
		sec = std::to_string(this->time);
		min = "00";
	}
	else if (time >= 60) {
		minutes = time / 60;
		seconds = time % 60;

		if (minutes < 10) {
			min = std::to_string(minutes);
			min = "0" + min;
		}
		else {
			min = std::to_string(minutes);
		}

		if (seconds < 10) {
			sec = std::to_string(seconds);
			sec = "0" + sec;
		}
		else {
			sec = std::to_string(seconds);
		}
	}

	string_time = min + ":" + sec;

	return string_time;
}
