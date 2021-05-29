#include "pch.h"
#include "AStar.h"

#include "AStar.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <random>

namespace pf
{
	//konstruktor AStara
	AStar::AStar() :
		m_weight(1), //waga
		m_dimentions(0, 0), //wymimary??
		m_startPos(0, 0), //poczatkowa pozycja
		m_targetPos(0, 0), //koncowa pozycja
		m_size(0), //rozmiar mapy
		m_nrOfDirections(4) //ilosc dostepnych kierunkow
	{
		m_directions = { {-1, 0}, {1, 0}, {0, 1}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} }; //zawartosc kierunkow
	}

	//funkcja odnajduj¹ca œcie¿kê na podstawie pocz¹tkowego no³da, koñcowego no³da, funkcji heurystycznej mierz¹cej odleg³oœæ od
	//ostatniego no³da i wagê
	std::vector<sf::Vector2i> AStar::findPath(sf::Vector2i& start, sf::Vector2i& end, HeuristicFunction heuristic, int weight)
	{
		m_startPos = start; //poczatkowy wêze³
		m_targetPos = end; //koñwocy wêze³
		m_weight = weight; //waga wêz³a
		m_heuristic = std::bind(heuristic, start, end, weight); //funkcja heurystyczna "zespolona" z argumentami
		m_size = m_dimentions.x * m_dimentions.y;
		m_cameFrom.resize(m_size); //wektor wêz³ów po których przeszed³ obiekt, wyzeruj
		m_closedList.resize(m_size, false); //weŸ listê zamkniêt¹ i zmieñ jej rozmiar na 0

		m_cameFrom[convertTo1D(m_startPos)].parent = m_startPos; //ustaw rodzica pierwszego obiektu na pozycje startow¹
		m_openList.push(Node(m_startPos, 0)); //dodaj obiekt wêz³a na pocz¹tek otwartej listy

		unsigned int fNew, gNew, hNew; //zmienne przechowuj¹ce zmienne chwilowe dla f, g i h
		sf::Vector2i currentPos; //pozycja obecnego no³da (z niej liczony jest indeks dla wektorów)

		while (!m_openList.empty()) //dopoki otwarta lista nie zostanie oprozniona
		{
			currentPos = m_openList.top().pos; //pobierz pozycje z gory otwartej listy

			if (currentPos == m_targetPos) //sprawdz czy obecnie badana pozycja jest ta ostatnia
			{
				break; //jezeli tak, to wyjdz z petli
			}

			m_openList.pop(); //pozbadz sie ostatniego elementu z otwartej listy
			m_closedList[convertTo1D(currentPos)] = true; //ustaw ze odpowiedni wêze³ jest juz zajety

			for (unsigned int i = 0; i < m_nrOfDirections; i++) //dla kazdego kierunku
			{
				const auto neighbourPos = currentPos + m_directions[i]; //pobierz "potencjalny nastepny wêze³"
				const auto neighbourIndex = convertTo1D(neighbourPos); //pobierz indeks tego potencjalnego wêz³a

				//sprawdz czy potencjalny wêze³ mieœci siê na mapie, nie nalezy do zablokowanych no³dów oraz czy nie zostal zapisany jako zamkniety
				if (!isValid(neighbourPos) || isBlocked(neighbourIndex) || m_closedList[neighbourIndex] == true)
				{
					//przejdz do nastepnego kierunku
					continue;
				}

				gNew = m_cameFrom[convertTo1D(currentPos)].g + 1; //oblicz g, dodajac 1 do g potencjalnego poprzedniego wêz³a
				hNew = m_heuristic(neighbourPos, m_targetPos, m_weight); //oblicz h wykorzystujac funkcje heurystyki
				fNew = gNew + hNew; //oblicz f

				//jezeli f jest rowne 0 i jezeli nowe f jest mniejsze niz to nalezace do zapisanego w f ktore odwiedzilismy
				if (m_cameFrom[neighbourIndex].f == 0 || fNew < m_cameFrom[neighbourIndex].f)
				{
					m_openList.push(Node(neighbourPos, fNew)); //dodaj node o pozycji do otwartej listy powiazana z f
					m_cameFrom[neighbourIndex] = { neighbourPos, currentPos, fNew, gNew, hNew }; //zapisz informacje odnosnie noda ktory obecnie badamy
				}
			}
		}
		return buildPath(); //zwroc wynik funkcji buildPath
	}

	void AStar::setGridToEmpty()
	{
		int width = m_dimentions.x;
		int height = m_dimentions.y;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				m_grid.push_back(1);
			}
		}
	}

	void AStar::setGridToRandom()
	{
		int width = m_dimentions.x;
		int height = m_dimentions.y;

		std::random_device rd;  
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<> distrib(0, 9);

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				m_grid.push_back(distrib(gen) == 0 ? 0 : 1);
			}
		}
	}

	void AStar::setDimentions(sf::Vector2i dimentions)
	{
		m_dimentions = dimentions;
	}

	std::vector<sf::Vector2i> AStar::buildPath()
	{
		std::vector<sf::Vector2i> path; //sciezka
		sf::Vector2i currentPos = m_targetPos; //oblicz pozycje poczawszy od ostatniego no³da
		int currentIndex = convertTo1D(currentPos); //indeks tablicy jednowymiarowej z obecnej pozycji

		//dopoki istnieje rodzic obecnie badanego no³da i nie doszlismy do poczatkowego elementu listy
		while (!(m_cameFrom[currentIndex].parent == currentPos))
		{
			path.push_back(currentPos); //dodaj obecnie badanego no³da do sciezki
			currentPos = m_cameFrom[currentIndex].parent; //pobiez rodzica i sprawdz wszystko dla niego
			currentIndex = convertTo1D(currentPos); //przeksztalc pozycje na indeks
		}
		path.push_back(currentPos);

		std::reverse(path.begin(), path.end()); //odwroc sciezke tak zeby zaczynala sie od poczatku, a nie od konca

		return path; //zwroc obliczona sciezke
	}

	void AStar::loadMap(const std::string& filename) //zaladuj mapke z pliku
	{
		std::ifstream file(filename); //otworz plik

		if (file.is_open()) //jezeli plik jest otwarty
		{
			std::string line; 
			while (std::getline(file, line)) //pobierz koleja linie do stringa
			{
				if (line.find('w') != std::string::npos) //przy znalezieniu znaku "w:" pobiez nastepna wartosc szerokosci ekranu
				{
					line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char c) { return (c == 'w' || c == ':') ? true : false; }), line.end());
					m_dimentions.x = std::stoi(line);
				}
				else if (line.find('h') != std::string::npos) //przy znalezieniu znaku "h:" pobiez nastepna wartosc dlugosci ekranu
				{
					line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char c) { return (c == 'h' || c == ':') ? true : false; }), line.end());
					m_dimentions.y = std::stoi(line);
				}
				else
				{
					line.erase(std::remove(line.begin(), line.end(), ','), line.end());

					for (const auto& c : line)
					{
						m_grid.push_back(c - 48);
					}
				}
			}
			m_size = m_dimentions.x * m_dimentions.y;
			file.close();
		}
	}

	void AStar::setDiagonalMovement(bool enable)
	{
		m_nrOfDirections = (enable) ? 8 : 4;
	}

	bool AStar::isValid(const sf::Vector2i& pos) const
	{
		return (pos.x >= 0) && (pos.x < m_dimentions.x) && (pos.y >= 0) && (pos.y < m_dimentions.y);
	}

	bool AStar::isBlocked(int index) const
	{
		return (m_grid[index] == 0);
	}

	int AStar::convertTo1D(sf::Vector2i pos)
	{
		return (pos.y * m_dimentions.x) + pos.x;
	}

	unsigned int heuristic::manhattan(const sf::Vector2i& v1, const sf::Vector2i& v2, int weight)
	{
		const auto delta = sf::Vector2i(abs(v1.x - v2.x), abs(v1.y - v2.y));
		return static_cast<unsigned int>(weight * (delta.x + delta.y));
	}

	unsigned int heuristic::euclidean(const sf::Vector2i& v1, const sf::Vector2i& v2, int weight)
	{
		const auto delta = sf::Vector2i(abs(v1.x - v2.x), abs(v1.y - v2.y));
		return static_cast<unsigned int>(weight * sqrt((delta.x * delta.x) + (delta.y * delta.y)));
	}
}