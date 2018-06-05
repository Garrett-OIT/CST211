/*
 Author: Garrett Fechter
 Lab 5 - Dijkstra's algorithm implementation
 Date Created: 6/5/2018
 Date Modified:
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Graph.h"
#include <string>
#include <sstream>
#include <list>

using std::string;
using std::istringstream;
using std::cout;
using std::stoi;
using std::list;

list<string> nodes;
void Append(string data);

int main()
{
	Graph<string, string> roads;
	std::ifstream fin;
	fin.open("lab05.txt");;
	if (fin.is_open())
	{
		string line;
		string startNode;
		string endNode;
		string path;
		string mileage;
		float miles;
		bool success = true;
		while (success && std::getline(fin, line))
		{
			istringstream parse(line);
			std::getline(parse, startNode, ','); //token is now start node
			std::getline(parse, endNode, ','); //token is now end node
			std::getline(parse, path, ','); //token is now path
			std::getline(parse, mileage, ','); //token is now weight
			if (startNode.empty() || endNode.empty() || path.empty() || mileage.empty())
				success = false;
			else
			{
				miles = stoi(mileage);
				if (roads[startNode] == -1)
					roads.InsertVertex(startNode);
				if (roads[endNode] == -1)
					roads.InsertVertex(endNode);
				roads.InsertArc(startNode, endNode, path, miles);
			}
		}
		if (!success)
			cout << "Invalid file contents. Exiting.\n";
		else 
		{
			nodes.clear();
			roads.DepthFirst(Append);
			Graph<string, string>::Iter iter(roads, "Klamath Falls");
			while (!iter.isDone()) 
			{
				Arc<string, string> demoArc = iter.GetCurrent();
				iter.MoveNext();
			}
			//process
		}
	}
	else
		cout << "Error opening file. Exiting.\n";
}

void Append(string data) 
{
	nodes.push_back(data);
}