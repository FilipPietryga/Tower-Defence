#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include "Vec2i.h"

namespace pf
{

	using HeuristicFunction = std::function<unsigned int(const sf::Vector2i&, const sf::Vector2i&, int)>; //alias funkcji o pewnych argumentach

	struct Node //no³d, czyli pojedynczy wierzcho³ek
	{
	public:

		Node() : pos(0, 0), parent(0, 0), f(0), g(0), h(0) {}; //tak "inicjujemy niezainicjowanego" no³da
		Node(const sf::Vector2i& pos, unsigned int f) : pos(pos), parent(0, 0), f(f), g(0), h(0) {} //a tak tylko z niektorymi
		Node(const sf::Vector2i& pos, const sf::Vector2i& parent, unsigned int f, unsigned int g, unsigned int h) :
			pos(pos), parent(parent), f(f), g(g), h(h) {} //tak inicjujemy ze wszystkimi zmiennymi

		sf::Vector2i pos; //pozycja no³da
		sf::Vector2i parent; //poprzedni no³d ??
		unsigned int f; //wartosc f
		unsigned int g; //wartosc g
		unsigned int h; //wartosc h
	};

	inline bool operator< (const Node& a, const Node& b) { return a.f < b.f; }; //porownywanie no³dów w ³atwiejszy sposob

	class AStar //funkcjonalnosc agwiazdki
	{
	public:
		AStar(); //konstruktor

		std::vector<sf::Vector2i> findPath(sf::Vector2i& start, sf::Vector2i& target, HeuristicFunction heuristic, int weight = 1); //funkcja wytyczania sciezki
		void loadMap(const std::string& filename); //funkcja ladowania mapy
		void setDiagonalMovement(bool enable); //funkcja przelaczania ruchu na skos
		void setDimentions(sf::Vector2i dimentions);
		void setGridToEmpty();
		void setGridToRandom();

	private:
		std::vector<sf::Vector2i> buildPath(); //funkcja tworzenia sciezki ??
		bool isValid(const sf::Vector2i& pos) const; //funkcja sprawdzania czy koordynat jest mozliwy
		bool isBlocked(int index) const; //funkcja sprawdzania czy koordynat jest zablokowany
		int convertTo1D(sf::Vector2i pos); //funkcja rzutujaca koordynaty na model jednowymiarowy

		int m_weight; //waga
		int m_size; //rozmiar ??
		unsigned int m_nrOfDirections; //ilosc kierunkow
		sf::Vector2i m_dimentions; //wymiary??
		sf::Vector2i m_startPos; //pozycja startowa
		sf::Vector2i m_targetPos; //pozycja docelowa
		std::priority_queue<Node> m_openList; //lista No³dów ktore mozemy jeszcze odwiedzic
		std::vector<bool> m_closedList; //no³dy ktorych nie mozemy odwiedzac
		std::vector<Node> m_cameFrom; //oznaczenie z ktorego nolda poruszalismy sie do ktorego
		std::vector<int> m_grid; //wektor siatki
		std::vector<sf::Vector2i> m_directions; //wektor kierunkow?
		HeuristicFunction m_heuristic; //funkcja heurystyczna sluzaca do obliczania h
	};

	namespace heuristic //mozliwe funkcje heurystyczne
	{
		unsigned int manhattan(const sf::Vector2i& v1, const sf::Vector2i& v2, int weight); //funkcja manhattan
		unsigned int euclidean(const sf::Vector2i& v1, const sf::Vector2i& v2, int weight); //funkcja eukleidesowa
	}

}