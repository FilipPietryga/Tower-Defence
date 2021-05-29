#include "pch.h"
#include "MenuButton.h"

MenuButton::MenuButton()
{
	_text = nullptr;
	_callback = nullptr;
}

MenuButton& MenuButton::setActiveColor(const sf::Color& color)
{
	this->_activeColor = color;
	return *this;
}

MenuButton& MenuButton::setInactiveColor(const sf::Color& color)
{
	this->_inactiveColor = color;
	return *this;
}

MenuButton& MenuButton::setFont(const sf::Font& font)
{
	this->_font = font;
	return *this;
}

MenuButton& MenuButton::setPosition(sf::Vector2f* position)
{
	this->_position = *position;
	return *this;
}

MenuButton& MenuButton::setString(std::string content)
{
	this->_content = content;
	return *this;
}

MenuButton& MenuButton::setCallback(void(&callback)())
{
	this->_callback = &callback;
	return *this;
}

MenuButton& MenuButton::loadText(bool active)
{
	this->_text = new sf::Text;
	_text->setFont(_font);
	_text->setString(_content);
	if (active) {
		_text->setFillColor(_activeColor);
	}
	else {
		_text->setFillColor(_inactiveColor);
	}
	_text->setPosition(_position);
	return *this;
}

void MenuButton::reloadText(bool active)
{
	if (active) {
		_text->setFillColor(_activeColor);
	}
	else {
		_text->setFillColor(_inactiveColor);
	}
}

void MenuButton::draw(sf::RenderWindow& window)
{
	window.draw(*(this->_text));
}

MenuButton::~MenuButton()
{
	/*delete _text;
	_text = nullptr;
	delete _activeColor;
	_activeColor = nullptr;
	delete _inactiveColor;
	_inactiveColor = nullptr;
	delete _font;
	_font = nullptr;
	_callback = nullptr;*/
}