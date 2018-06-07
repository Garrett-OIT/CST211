/*
 Author: Garrett Fechter
 Date Created: 6/2/2018
 Date Modified: 6/5/2018 - added arc iterator
*/
#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <queue>
#include <iterator>
#include "Vertex.h"
#include "Exception.h"
#include <string>
using std::string;

using std::list;

/*
class Graph
 functions:
	Graph();
		ctor. empty graph
	~Graph();
		dtor, makes graph empty
	void InsertVertex(VData data); 
		insert a vertex with data
	void DeleteVertex(VData data); 
		delete vertex that matches data
	void InsertArc(VData from, VData to, EData edge, float weight);
		insert arc into from, destination pointer to to
		also insert arc from to to from (undirected)
	void DeleteArc(VData from, VData to, EData edge);
		removes an arc
	void DepthFirst(void(*Visit) (VData));
		performs a depth first iteration over the graph
	void BreadthFirst(void(*Visit) (VData));
		performs a breadth first iteration over the graph
	bool isEmpty();
		whether or not the graph is empty
	int operator[] (VData find);
		returns index (using depth first approach) of an element, -1 if not found
*/
template <typename EData, typename VData>
class Graph
{
public:
	friend void roadDijkstra(Graph<string, string> &roads, string from, string to);
	Graph();
	void InsertVertex(VData data); //insert a vertex with data
	void DeleteVertex(VData data); //delete vertex that matches data
	void InsertArc(VData from, VData to, EData edge, float weight);//insert arc into from, destination pointer to to
		//also insert acr from to to from (undirected)
	void DeleteArc(VData from, VData to, EData edge);
	void DepthFirst(void(*Visit) (VData));
	void BreadthFirst(void(*Visit) (VData));
	bool isEmpty();
	int operator[] (VData find);
	~Graph();
	/*
		Class: Iter - an iterator for a vertex's edges
			friend void roadDijkstra(Graph<string, string> &roads, string from, string to);
				roadDijkstra can access members
			Arc<EData, VData> GetCurrent();
				Gets the current arc
			Iter(const Graph<EData, VData> &graph, VData data);
				ctor that specifies the graph and node you're interested in
			void MoveNext();
				moves to next arc
			~Iter();
				dtor
			void Reset(VData data);
				resets the iterator to the beggining of data's arc
			bool isDone();
				whether or not the iterator has reached all arcs
	*/
	class Iter
	{
	public:
		friend void roadDijkstra(Graph<string, string> &roads, string from, string to);
		Arc<EData, VData> GetCurrent();
		Iter(const Graph<EData, VData> &graph, VData data);
		void MoveNext();
		~Iter();
		void Reset(VData data);
		bool isDone();
	protected:
		int m_index;//the index of walking through a vertex's arcs
		const Graph<EData, VData> * m_graph;//the graph that the iterator works on
		Vertex<EData, VData> * m_vertex;//the vertex inside graph currently being iterated over
	};
private:
	int m_count; //# of vertices
	list<Vertex<EData, VData> *> m_vertices;//list of vertices
};

template<typename EData, typename VData>
inline Graph<EData, VData>::Graph() : m_count(0), m_vertices()
{ }

template<typename EData, typename VData>
inline void Graph<EData, VData>::InsertVertex(VData data)
{
	Vertex<EData, VData> *vert = new Vertex<EData, VData>(data);
	m_count++;
	m_vertices.push_front(vert);
}

template<typename EData, typename VData>
inline void Graph<EData, VData>::DeleteVertex(VData data)
{
	bool found = false;
	auto iter = m_vertices.begin();
	for (iter = m_vertices.begin(); !found && iter != m_vertices.end();)
	{
		if ((*iter)->m_data == data)
			found = true;
		else
			iter++;
	}
	if (found)
	{
		if ((*iter)->m_indegree != 0 && (*iter)->m_outdegree != 0)
			throw Exception("Can't delete a vertex with arcs still attached\n");
		delete (*iter);
		m_vertices.remove(*iter);
		m_count--;
	}
	else
		throw Exception("Did not find that vertex\n");
}

template<typename EData, typename VData>
inline void Graph<EData, VData>::InsertArc(VData from, VData to, EData edge, float weight)
{
	bool found = false;
	Vertex<EData, VData> *fromVp = nullptr;
	Vertex<EData, VData> *toVp = nullptr;
	auto fromIter = m_vertices.begin();
	for (fromIter = m_vertices.begin(); !found && fromIter != m_vertices.end(); fromIter++)
	{
		if ((*fromIter)->m_data == from)
		{
			found = true;
			fromVp = *fromIter;
		}
	}

	auto toIter = m_vertices.begin();
	found = false;
	for (toIter = m_vertices.begin(); !found && toIter != m_vertices.end(); toIter++)
	{
		if ((*toIter)->m_data == to)
		{
			found = true;
			toVp = *toIter;
		}
	}
	if (toVp == nullptr || fromVp == nullptr)
		throw Exception("Couldn't find to or from vertex\n");
	Arc<EData, VData> toArc(toVp, edge, weight);
	fromVp->m_edges.push_front(toArc);
	fromVp->m_indegree++;
	fromVp->m_outdegree++;
	Arc<EData, VData> fromArc(fromVp, edge, weight);
	toVp->m_edges.push_front(fromArc);
	toVp->m_indegree++;
	toVp->m_outdegree++;
}

template<typename EData, typename VData>
inline void Graph<EData, VData>::DeleteArc(VData from, VData to, EData edge)
{
	bool found = false;
	Vertex<EData, VData> *fromVp = nullptr;
	Vertex<EData, VData> *toVp = nullptr;
	auto fromIter = m_vertices.begin();
	for (fromIter = m_vertices.begin(); !found && fromIter != m_vertices.end(); fromIter++)
	{
		if ((*fromIter)->m_data == from)
		{
			found = true;
			fromVp = *fromIter;
		}
	}
	auto toIter = m_vertices.begin();
	found = false;
	for (toIter = m_vertices.begin(); !found && toIter != m_vertices.end(); toIter++)
	{
		if ((*toIter)->m_data == to)
		{
			found = true;
			toVp = *toIter;
		}
	}
	if (toVp == nullptr || fromVp == nullptr)
		throw Exception("Couldn't find to or from vertex\n");

	//we now have from and to vertex pointers
	//now look for specified edge
	found = false;
	auto fromVpIter = fromVp->m_edges.begin();
	Arc<EData, VData> fromArc;
	for (; !found && fromVpIter != fromVp->m_edges.end();)
	{
		if ((*fromVpIter).m_data == edge && (*fromVpIter).m_destination == toVp)
		{
			fromArc = *fromVpIter;
			found = true;
			fromVp->m_edges.remove(fromArc);
			fromVp->m_indegree--;
			fromVp->m_outdegree--;
		}
		else
			fromVpIter++;
	}
	if (!found)
		throw Exception("Did not find that edge in specified vertex\n");

	auto toVpIter = toVp->m_edges.begin();
	found = false;
	Arc<EData, VData> toArc;
	for (; !found && toVpIter != toVp->m_edges.end();)
	{
		if ((*toVpIter).m_data == edge && (*toVpIter).m_destination == fromVp)
		{
			toArc = *toVpIter;
			found = true;
			toVp->m_edges.remove(toArc);
			toVpIter = toVp->m_edges.end();
			toVp->m_indegree--;
			toVp->m_outdegree--;
		}
		else
			toVpIter++;
	}
	if (!found)
		throw Exception("Did not find that edge in specified vertex\n");

}

template<typename EData, typename VData>
inline void Graph<EData, VData>::DepthFirst(void(*Visit)(VData))
{
	std::queue<bool> procs;
	if (!m_vertices.empty())
	{
		//reset processed flags
		auto vertIter = m_vertices.begin();
		for (; vertIter != m_vertices.end(); vertIter++)
		{
			procs.push((*vertIter)->m_processed);
			(*vertIter)->m_processed = false;
		}

		list<Vertex<EData, VData> *> verts;
		verts.push_front(m_vertices.front());
		Vertex<EData, VData> * current = nullptr;
		while (!verts.empty())
		{
			current = verts.front();
			verts.pop_front();
			if (current->m_processed == false)
				Visit(current->m_data);
			current->m_processed = true;
			for (auto eIter = current->m_edges.begin(); eIter != current->m_edges.end(); eIter++)
			{
				if ((*eIter).m_destination->m_processed == false)
					verts.push_front((*eIter).m_destination);
			}
		}
	}
	auto vertIter = m_vertices.begin();
	for (; vertIter != m_vertices.end(); vertIter++) 
	{
		(*vertIter)->m_processed = procs.front();
		procs.pop();
	}
}

template<typename EData, typename VData>
inline int Graph<EData, VData>::operator[](VData find)
{
	std::queue<bool> procs;
	int index = 0;
	int location = -1;
	bool found = false;
	if (!m_vertices.empty())
	{
		//reset processed flags
		auto vertIter = m_vertices.begin();
		for (; vertIter != m_vertices.end(); vertIter++)
		{
			procs.push((*vertIter)->m_processed);
			(*vertIter)->m_processed = false;
		}

		list<Vertex<EData, VData> *> verts;
		verts.push_front(m_vertices.front());
		Vertex<EData, VData> * current = nullptr;
		while (!verts.empty())
		{
			current = verts.front();
			verts.pop_front();
			if (current->m_processed == false) 
			{
				if (current->m_data == find) 
				{
					found = true;
					location = index;
				}
				if (!found)
					index++;
			}
			current->m_processed = true;
			for (auto eIter = current->m_edges.begin(); eIter != current->m_edges.end(); eIter++)
			{
				if ((*eIter).m_destination->m_processed == false)
					verts.push_front((*eIter).m_destination);
			}
		}
	}
	auto vertIter = m_vertices.begin();
	for (; vertIter != m_vertices.end(); vertIter++) 
	{
		(*vertIter)->m_processed = procs.front();
		procs.pop();
	}
	return location;
}

template<typename EData, typename VData>
inline void Graph<EData, VData>::BreadthFirst(void(*Visit)(VData))
{
	if (!m_vertices.empty())
	{
		//reset processed flags
		auto vertIter = m_vertices.begin();
		for (; vertIter != m_vertices.end(); vertIter++)
			(*vertIter)->m_processed = false;

		list<Vertex<EData, VData> *> verts;
		verts.push_back(m_vertices.front());
		Vertex<EData, VData> * current = nullptr;
		while (!verts.empty())
		{
			current = verts.front();
			verts.pop_front();
			if (current->m_processed == false)
				Visit(current->m_data);
			current->m_processed = true;
			for (auto eIter = current->m_edges.begin(); eIter != current->m_edges.end(); eIter++)
			{
				if ((*eIter).m_destination->m_processed == false)
					verts.push_back((*eIter).m_destination);
			}
		}
	}
}

template<typename EData, typename VData>
inline bool Graph<EData, VData>::isEmpty()
{
	return m_vertices.empty();
}


template<typename EData, typename VData>
inline Graph<EData, VData>::~Graph()
{
	while (!m_vertices.empty())
	{
		delete m_vertices.front();
		m_vertices.pop_front();
	}
	m_count = 0;
}

template<typename EData, typename VData>
inline Arc<EData, VData> Graph<EData, VData>::Iter::GetCurrent()
{
	Arc<EData, VData> ret;
	if (m_vertex != nullptr && m_index < m_vertex->m_edges.size())
	{
		auto eIter = m_vertex->m_edges.begin();
		std::advance(eIter, m_index);
		ret = *eIter;
	}
	return ret;
}

template<typename EData, typename VData>
inline Graph<EData, VData>::Iter::Iter(const Graph<EData, VData>& graph, VData data) : m_index(0), m_graph(&graph), m_vertex(nullptr)
{
	std::queue<bool> procs;
	if (m_graph != nullptr)
	{
		int found = -1;
		if (!m_graph->m_vertices.empty())
		{
			//reset processed flags
			auto vertIter = m_graph->m_vertices.begin();
			for (; vertIter != m_graph->m_vertices.end(); vertIter++)
			{
				procs.push((*vertIter)->m_processed);
				(*vertIter)->m_processed = false;
			}
			list<Vertex<EData, VData> *> verts;
			verts.push_front(m_graph->m_vertices.front());
			Vertex<EData, VData> * current = nullptr;
			int index = 0;
			while (!verts.empty() && found == -1)
			{
				current = verts.front();
				verts.pop_front();
				if (current->m_processed == false)
				{
					if (data == current->m_data)
					{
						m_vertex = current;
						found = 0;
					}
				}
				index++;
				current->m_processed = true;
				for (auto eIter = current->m_edges.begin(); found == -1 && eIter != current->m_edges.end(); eIter++)
				{
					if ((*eIter).m_destination->m_processed == false)
						verts.push_front((*eIter).m_destination);
				}
			}
		}
	}
	auto vertIter = m_graph->m_vertices.begin();
	for (; vertIter != m_graph->m_vertices.end(); vertIter++) 
	{
		(*vertIter)->m_processed = procs.front();
		procs.pop();
	}
}

template<typename EData, typename VData>
inline void Graph<EData, VData>::Iter::MoveNext()
{
	m_index++;
}

template<typename EData, typename VData>
inline Graph<EData, VData>::Iter::~Iter()
{
	m_index = 0;
	m_graph = nullptr;
	m_vertex = nullptr;
}

template<typename EData, typename VData>
inline void Graph<EData, VData>::Iter::Reset(VData data)
{
	std::queue<bool> procs;
	if (m_graph != nullptr)
	{
		int found = -1;
		if (!m_graph->m_vertices.empty())
		{
			//reset processed flags
			auto vertIter = m_graph->m_vertices.begin();
			for (; vertIter != m_graph->m_vertices.end(); vertIter++)
			{
				procs.push((*vertIter)->m_processed);
				(*vertIter)->m_processed = false;
			}

			list<Vertex<EData, VData> *> verts;
			verts.push_front(m_graph->m_vertices.front());
			Vertex<EData, VData> * current = nullptr;
			int index = 0;
			while (!verts.empty() && found == -1)
			{
				current = verts.front();
				verts.pop_front();
				if (current->m_processed == false)
				{
					if (data == current->m_data)
					{
						m_vertex = current;
						found = 0;
					}
				}
				index++;
				current->m_processed = true;
				for (auto eIter = current->m_edges.begin(); found == -1 && eIter != current->m_edges.end(); eIter++)
				{
					if ((*eIter).m_destination->m_processed == false)
						verts.push_front((*eIter).m_destination);
				}
			}
		}
	}
	auto vertIter = m_vertices.begin();
	for (; vertIter != m_vertices.end(); vertIter++) 
	{
		(*vertIter)->m_processed = procs.front();
		procs.pop();
	}
}

template<typename EData, typename VData>
inline bool Graph<EData, VData>::Iter::isDone()
{
	bool done = false;
	if (m_vertex != nullptr)
	{
		if (m_index >= m_vertex->m_outdegree)
			done = true;
	}
	else
		throw Exception("iterator is null\n");
	return done;
}

#endif
