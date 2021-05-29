#include "pch.h"
#include "Menu.h"
#include "Stripper.h"
#include "ArgumentException.h"

Menu::Menu() 
	: _length(0), _selected(-1), _menuButton(nullptr), 
	_contents(""), _font(nullptr), _resolution(nullptr)
{	}

Menu::Menu(const Menu& old)
	: _length(old._length), _selected(old._selected), _menuButton(old._menuButton),
	_contents(old._contents), _font(old._font), _resolution(old._resolution)
{	}

Menu& Menu::operator=(const Menu& old)
{
	if (this != &old)
	{
		_length = old._length;
		_selected = old._selected;
		_menuButton = old._menuButton;
		_contents = old._contents;
		_font = old._font;
		_resolution = old._resolution;
	}
	return* this;
}

Menu& Menu::create()
{
	try {
		 *this = (*this).setResolution(sf::Vector2u(640, 480))
			.loadFont("arial.ttf")
			.loadContents("contents.txt")
			.loadButtons();
	}
	catch (Exception & exception) {
		exception.what();
		throw EXIT_FAILURE;
	}
	return *this;
}

Menu& Menu::setResolution(const sf::Vector2u& resolution = sf::Vector2u(0,0))
{
	if (resolution.x == 0 || resolution.y == 0)
	{
		throw ArgumentException()
			.setFilename("Menu.cpp")
			.setFunc("Menu Menu::setResolution(const sf::Vector2u&)")
			.setLine(15)
			.setVarName("resolution")
			.setVarType("const sf::Vector2u&")
			.setInfo("resolution should be specified and their members should be bigger than 0");
	}
	else if (resolution.x < 0 || resolution.y < 0) 
	{
		throw ArgumentException()
			.setFilename("Menu.cpp")
			.setFunc("Menu Menu::setResolution(const sf::Vector2u&)")
			.setLine(15)
			.setVarName("resolution")
			.setVarType("const sf::Vector2u&")
			.setInfo("resolution's members should be positive");
	}
	this->_resolution = const_cast<sf::Vector2u*>(&resolution);
	return *this;
}

Menu& Menu::loadFont(const std::string& filename = "")
{
	if (filename == "") 
	{
		throw ArgumentException()
			.setFilename("Menu.cpp")
			.setFunc("Menu Menu::loadFont(const std::string&)")
			.setLine(41)
			.setVarName("filename")
			.setVarType("const std::string&")
			.setInfo("filename should be specified");
	}

	_font = new sf::Font();

	if (!_font->loadFromFile(filename))
	{
		throw new Exception("File Exception");
	}
	return *this;
}

Menu& Menu::loadContents(const std::string& filename = "")
{
	std::fstream file;
	file.open(filename);

	std::string buffor[2] = { "", "" };
	int i = 0;
	while (std::getline(file, buffor[i]))
	{
		i++;
	}

	std::string contents = buffor[0];
	int length = std::stoi(buffor[1]);

	file.close();

	*this = (*this).setContents(contents, length);
	
	return *this;
}

Menu& Menu::setContents(const std::string& contents = "", const int& length = 0)
{
	if (contents == "")
	{
		throw ArgumentException()
			.setFilename("Menu.cpp")
			.setFunc("Menu Menu::setContents(const std::string&, const int&)")
			.setLine(61)
			.setVarName("contents")
			.setVarType("const std::string&")
			.setInfo("contents should be specified and not empty");
	}
	if (length <= 0)
	{
		throw ArgumentException()
			.setFilename("Menu.cpp")
			.setFunc("Menu Menu::setContents(const std::string&, const int&)")
			.setLine(61)
			.setVarName("length")
			.setVarType("const int&")
			.setInfo("length should be specified and positive");
	}

	this->_contents = contents;
	this->_length = length;

	return *this;
}

Menu& Menu::loadButtons()
{
	unsigned int width = _resolution->x;
	unsigned int height = _resolution->y;
	std::string separator = ":";
	Stripper stripper(_contents, separator);

	this->_menuButton = new MenuButton[_length];

	for (int i = 0; i < _length; i++)
	{
		std::string temp = stripper.strip();
		_menuButton[i] = _menuButton[i].setFont(*_font)
			.setActiveColor(sf::Color::Red)
			.setInactiveColor(sf::Color::White)
			.setString(temp)
			.setPosition(new sf::Vector2f((float) width / 2, 
			(float) height / ((float) _length + 1) * (i + 1)))
			.loadText(false);
	}
	return *this;
}

void Menu::draw(sf::RenderWindow& window) const
{
	for (int i = 0; i < _length; i++) 
	{
		_menuButton[i].draw(window);
	}
}

void Menu::move(const bool& direction)
{
	if (_selected == -1) {
		_selected = 0;
		_menuButton[_selected].reloadText(true);
		return;
	}
	if (direction == true) 
	{
		if (_selected > 0) 
		{
			_menuButton[_selected].reloadText(false);
			_selected -= 1;
			_menuButton[_selected].reloadText(true);
		}
		else 
		{
			_menuButton[_selected].reloadText(false);
			_selected = _length - 1;
			_menuButton[_selected].reloadText(true);
		}
	}
	else
	{
		if (_selected < _length - 1) 
		{
			_menuButton[_selected].reloadText(false);
			_selected += 1;
			_menuButton[_selected].reloadText(true);
		}
		else 
		{
			_menuButton[_selected].reloadText(false);
			_selected = 0;
			_menuButton[_selected].reloadText(true);
		}
	}
}

int Menu::getSelected() const
{
	return _selected;
}

Menu::~Menu()
{
	/*delete[] _menuButton;
	_menuButton = nullptr;
	delete _font;
	_font = nullptr;
	delete _contents;
	_contents = nullptr;
	delete _resolution;
	_resolution = nullptr;*/
}