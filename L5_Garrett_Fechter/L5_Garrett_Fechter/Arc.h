/*
 Author: Garrett Fechter
 Date Created: 6/2/2018
 Date Modified:
*/
#ifndef ARC_H
#define ARC_H
template<typename EData, typename VData>
class Vertex;

template<typename EData, typename VData>
class Graph;

#include <string>
using std::string;

template <typename EData, typename VData>
class Arc
{
public:
	friend void roadDijkstra(Graph<string, string> &roads, string from, string to);
	Arc();
	Arc(Vertex<EData, VData> * vert, EData data, float weight);
	Arc(const Arc & copy);
	Arc<EData, VData> & operator = (const Arc & rhs);
	bool operator == (const Arc & rhs) const;
	~Arc();
private:
	template<typename, typename> friend class Graph;
	Vertex<EData, VData> * m_destination;
	EData m_data;
	float m_weight;
};

template<typename EData, typename VData>
inline Arc<EData, VData>::Arc() : m_destination(nullptr), m_data(), m_weight(0)
{ }

template<typename EData, typename VData>
inline Arc<EData, VData>::Arc(Vertex<EData, VData>* vert, EData data, float weight) : m_destination(vert), m_weight(weight), m_data(data)
{ }

template<typename EData, typename VData>
inline Arc<EData, VData>::Arc(const Arc & copy) : m_destination(copy.m_destination), m_data(copy.m_data), m_weight(copy.m_weight)
{
}

template<typename EData, typename VData>
inline Arc<EData, VData> & Arc<EData, VData>::operator=(const Arc & rhs)
{
	m_destination = rhs.m_destination;
	m_data = rhs.m_data;
	m_weight = rhs.m_weight;
	return *this;
}

template<typename EData, typename VData>
inline bool Arc<EData, VData>::operator==(const Arc & rhs) const
{
	return ((m_destination == rhs.m_destination) && (m_data == rhs.m_data) && (m_weight == rhs.m_weight));
}

template<typename EData, typename VData>
inline Arc<EData, VData>::~Arc()
{
	m_destination = nullptr;
	m_weight = 0;
}
#endif