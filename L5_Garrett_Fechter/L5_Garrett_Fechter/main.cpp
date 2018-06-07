/*
 Author: Garrett Fechter
 Lab 5 - Dijkstra's algorithm implementation
 Date Created: 6/5/2018
 Date Modified:
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <list>
#include <vector>

#include "Graph.h"

using std::vector;
vector<string> nodes;
using std::string;
using std::istringstream;
using std::cout;
using std::stoi;
using std::list;
using std::cin;
using std::getline;

void Append(string data);

/*
 Function: main
 Purpose: Handle some input and output from files and console, create graph, do some mapping
 Entry: Reads from lab05.txt which has lines with information about graph
	format is: startnode,endnode,pathdata,mileage
 Exit: Outputs to console
*/
int main()
{
	Graph<string, string> roads; //our graph of roads
	std::ifstream fin; //file input
	fin.open("lab05.txt");;
	if (fin.is_open())
	{
		string line;//reading a line from the 
		string startNode;//the starting ndoe
		string endNode;//the ending noe
		string path;//the path data
		string mileage;//the miles the path is
		float miles;//converted miles
		bool success = true;//whether or not a record was in the right format
		int numElem = 0;//# of records read
		while (success && getline(fin, line))
		{
			istringstream parse(line);
			getline(parse, startNode, ','); //token is now start node
			getline(parse, endNode, ','); //token is now end node
			getline(parse, path, ','); //token is now path
			getline(parse, mileage, ','); //token is now weight
			if (startNode.empty() || endNode.empty() || path.empty() || mileage.empty())
				success = false;
			else
			{
				miles = stoi(mileage);
				if (roads[startNode] == -1)
				{
					roads.InsertVertex(startNode);
					numElem++;
				}
				if (roads[endNode] == -1)
				{
					numElem++;
					roads.InsertVertex(endNode);
				}
				roads.InsertArc(startNode, endNode, path, miles);
			}
		}
		if (!success)
			cout << "Invalid file contents. Exiting.\n";
		else
		{
			nodes.clear();
			roads.DepthFirst(Append);
			//process
			cout << "Where are you traveling from? (type 'exit' to exit): ";
			string from;//origination
			string to;//where they're going
			getline(cin, from);
			bool exit = false;
			if (from == "exit")
				exit = true;
			while (!exit && roads[from] == -1 ) 
			{
				cout << "Not a valid entry. Where are you traveling from?: ";
				getline(cin, from);
				if (from == "exit")
					exit = true;
			}
			if (!exit) 
			{
				cout << "Where are you going?: ";
				getline(cin, to);
				if (to == "exit")
					exit = true;
				while (!exit && roads[to] == -1 ) 
				{
					cout << "Not a valid entry. Where are you going?: ";
					getline(cin, to);
					if (to == "exit")
						exit = true;
				}
				if (!exit)
					roadDijkstra(roads, from, to);
			}
		}
		cout << "Press enter to exit...\n";
		getchar();
	}
	else
		cout << "Error opening file. Exiting.\n";
}

/*
 Function: Append
 Purpose: Provide a function for DepthFirst to create a vector of the vertex datas
 Entry: -
 Exit: Appends data to nodes
*/
void Append(string data)
{
	nodes.push_back(data);
}

/*
 Function: roadDijkstra
 Purpose: Find the shortest path from a vertex w/data from to to
 Entry: roads is a graph, from and to are strings
 Exit: Some output to console about path details
*/
void roadDijkstra(Graph<string, string> &roads, string from, string to)
{
	//nodes is the array of vertex datas
	//distance array
	vector<int> distance(36);//the distance vector used in algorithm
	for (size_t i = 0; i < nodes.size(); i++)
		distance[i] = -1;
	//predecessor array
	vector<int> pred(36);//the predecessor algorithm used in Dijkstras
	for (size_t i = 0; i < nodes.size(); i++)
		pred[i] = -1;
	//reset processed flags
	auto vertIter = roads.m_vertices.begin();
	for (; vertIter != roads.m_vertices.end(); vertIter++)
		(*vertIter)->m_processed = false;
	int current = roads[from];//the VData we're working with
	if (nodes.size() > 0)
		distance[current] = 0;
	bool next = true;
	for (size_t i = roads[from]; next;)
	{
		current = i;
		Graph<string, string>::Iter iter(roads, nodes[i]);//iterate through arcs
		while (next && !iter.isDone())
		{
			int indexOfDestination = roads[iter.GetCurrent().m_destination->m_data];//index of the destination
			int dist = distance[indexOfDestination];//distance of destination
			//if dist(arc destination) == -1 or (current dist + weight < dist(arc destination)
			if (!iter.GetCurrent().m_destination->m_processed && (dist == -1 || ((distance[current] + iter.GetCurrent().m_weight) < dist)))
			{
				//update dist of destination
				distance[indexOfDestination] = distance[current] + iter.GetCurrent().m_weight;
				//update predecessor
				pred[indexOfDestination] = current;
			}
			iter.MoveNext();
		}
		iter.m_vertex->m_processed = true;
		//select next node, smallest num not processed or -1
		next = false;
		int min = -2;
		for (int j = 0; !next && j < nodes.size(); j++) 
		{
			Graph<string, string>::Iter checkProc(roads, nodes[j]);//check if arcs are processed 
			if (checkProc.m_vertex->m_processed == false) 
			{
				if ((distance[j] > -1) && ((min == -2) || (distance[j] < min)))
					min = j;
			}
		}
		if (min != -2)
		{
			i = min;
			next = true;
		}
	}
	//output stuff
	cout << "From: " << from << "\n";
	cout << "To: " << to << "\n";
	cout << "Distance: " << distance[roads[to]] << " miles\n";
	float time = 0;//estimated travel time
	int pathing = roads[to];//used to walk through predecessor array
	//follow path, add up time
	cout << "Path: \n";
	list<string> paths;//saves path strings (walking backwards)
	while (pathing != roads[from]) 
	{
		Graph<string, string>::Iter checkPath(roads, nodes[pathing]);//iterate through paths
		//find path that leads to nodes[pred[pathing]]
		while (checkPath.GetCurrent().m_destination->m_data != nodes[pred[pathing]])
			checkPath.MoveNext();
		paths.push_back("Take " + checkPath.GetCurrent().m_data + " from " + checkPath.GetCurrent().m_destination->m_data
			+ " to " + checkPath.m_vertex->m_data + ": " + std::to_string((int) checkPath.GetCurrent().m_weight) + " miles\n");
		//if path = 'I-5' else 
		if (checkPath.GetCurrent().m_data == "I-5")
			time += checkPath.GetCurrent().m_weight / 65.0;
		else
			time += checkPath.GetCurrent().m_weight / 55.0;
		pathing = pred[pathing];
	}
	while (!paths.empty()) 
	{
		cout << paths.back();
		paths.pop_back();
	}
	cout << "Estimated time: " << time << " hours\n";
}

