#ifndef VERTEX_H
#define VERTEX_H
#include <list>
#include "Arc.h"

using std::list;

template <typename EData, typename VData>
class Arc;

template <typename EData, typename VData>
class Vertex
{
public:
	Vertex();
	Vertex(const Vertex & copy);
	Vertex(VData data);
	Vertex<EData, VData> & operator = (const Vertex & rhs);
	~Vertex();
private:
	template <typename, typename> friend class Graph;
	bool m_processed;
	int m_indegree;
	int m_outdegree;
	VData m_data;
	list<Arc<EData, VData>> m_edges;
};

#endif

template<typename EData, typename VData>
inline Vertex<EData, VData>::Vertex() : m_processed(false), m_indegree(0), m_outdegree(0), m_data(), m_edges()
{ }

template<typename EData, typename VData>
inline Vertex<EData, VData>::Vertex(const Vertex & copy) : m_processed(copy.m_processed), 
	m_indegree(copy.m_indegree), m_outdegree(copy.m_outdegree), m_data(copy.m_data), m_edges(copy.m_edges)
{ }

template<typename EData, typename VData>
inline Vertex<EData, VData>::Vertex(VData data) : m_processed(false), 
	m_indegree(0), m_outdegree(0), m_data(data), m_edges()
{ }

template<typename EData, typename VData>
inline Vertex<EData, VData> & Vertex<EData, VData>::operator=(const Vertex & rhs)
{
	m_processed = rhs.m_processed;
	m_indegree = rhs.m_indegree;
	m_outdegree = rhs.m_outdegree;
	m_data = rhs.m_data;
	m_edges = rhs.m_edges;
	return *this;
}

template<typename EData, typename VData>
inline Vertex<EData, VData>::~Vertex()
{
	m_processed = false;
	m_indegree = 0;
	m_outdegree = 0;
	m_edges.clear();
}
