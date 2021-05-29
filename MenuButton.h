#pragma once

class MenuButton
{
public:
	MenuButton();
	~MenuButton();
	void draw(sf::RenderWindow& window);
	MenuButton& setFont(const sf::Font& font);
	MenuButton& setActiveColor(const sf::Color& color);
	MenuButton& setInactiveColor(const sf::Color& color);
	MenuButton& setPosition(sf::Vector2f* position);
	MenuButton& setString(std::string content);
	MenuButton& setCallback(void(&callback)());
	MenuButton& loadText(bool active);
	void reloadText(bool active);
private:
	sf::Font _font;
	std::string _content;
	sf::Color _activeColor;
	sf::Color _inactiveColor;
	sf::Text* _text;
	sf::Vector2f _position;
	void (*_callback)();
};