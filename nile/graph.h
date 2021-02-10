#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <map>
#include <stdexcept>
#include <QList>
#include "vertex.h"

using namespace std;

template<typename T>
class Graph
{
	public:
		//Al momento de crear la clase, se establece si es dirigido o no lo es.
		Graph(bool d = false)
		{
			directed = d;
		}

		bool isEdge(const T& origin, const T& destiny);
		void createEdge(const T& origin, const T& destiny, int cost);
		void printData();
		int getCost(const T& origin, const T& destiny);
		map<T, int>& getNeighbors(const T& origin);
		QList<Vertex> orderPriority(map<T, int>& origin);

	private:
		map<T, map<T, int>> graph;
		bool directed;
};
#endif // GRAPH_H

template<typename T>
bool Graph<T>::isEdge(const T &origin, const T &destiny)
{
	//Si se encuentra en la lista devolvemos verdadero, caso contrario, falso.
	if (graph.find(origin) != graph.end())
	{
		if (graph[origin].find(destiny) != graph[origin].end())
		{
			return true;
		}
		return false;
	}
	return false;
}

template<typename T>
void Graph<T>::createEdge(const T& origin, const T& destiny, int cost)
{
	map<T, int> destinies;

	//Si es dirigido, se agrega automaticamente al diccionario de manera que solo se ingresa el valor del costo
	if (directed)
	{
		if (graph.find(origin) != graph.end())
		{
			destinies = graph[origin];
		}
		destinies[destiny] = cost;

		graph[origin] = destinies;
	}
	//Si no es dirigido los pasos para añadir los costos, deben funcionar bidireccionalmente
	else
	{
		map<T, int> o_d;
		map<T, int> d_o;
		if (graph.find(origin) != graph.end())
		{
			o_d = graph[origin];
		}
		o_d[destiny] = cost;
		if (graph.find(destiny) != graph.end())
		{
			d_o = graph[destiny];
		}
		d_o[origin] = cost;

		graph[origin] = o_d;
		graph[destiny] = d_o;
	}
}

template<typename T>
void Graph<T>::printData()
{
	typename map<T, map<T, int>>::const_iterator it;

	it = graph.begin();

	//Solo es recorrer todo el mapa mostrando las conexiones con los nodos
	while(it != graph.end())
	{
		typename map<T, int>::const_iterator itDest;
		itDest = graph[it->first].begin();
		while(itDest != graph[it->first].end())
		{
			cout << "(" << it->first <<  "," << itDest->first << "," << itDest->second << ")" << endl;
			++itDest;
		}
		++it;
		cout << endl;
	}
}

template<typename T>
int Graph<T>::getCost(const T& origin, const T& destiny)
{
	//Si no existe el arista, se expresa mediante una excepción.
	if (!isEdge(origin, destiny))
	{
		throw invalid_argument("The edge does not exist");
	}
	return graph[origin][destiny];
}

template<typename T>
map<T, int> &Graph<T>::getNeighbors(const T &origin)
{
	if (graph.find(origin) == graph.end())
		throw runtime_error("The origin doesn't exist");
	return graph[origin];
}

template<typename T>
QList<Vertex> Graph<T>::orderPriority(map<T, int> &origin)
{
	QList<Vertex> auxList;
	Vertex myVertex;
	typename map<T, int>::const_iterator it;
	it = origin.begin();
	while(it!= origin.end())
	{
		myVertex.setProduct(it->first);
		myVertex.setPriority(it->second);
		auxList.append(myVertex);
		++it;
	}
	qSort(auxList.begin(), auxList.end(),[](const Vertex& a, const Vertex& b) -> bool { return a.getPriority() > b.getPriority(); });

	cout << "Ordenados por peso" << endl;
	for( int i = 0 ; i < auxList.size() ; i++ ){
		cout << auxList.at(i).getProduct() << " : " << auxList.at(i).getPriority() << endl;
	}

	return auxList;
}
