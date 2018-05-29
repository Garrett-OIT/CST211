#ifndef ARC_H
#define ARC_H

template<typename EData, typename VData>
class Vertex;

template <typename EData, typename VData>
class Arc 
{
public:
	Arc();
	Arc(Vertex<EData, VData> * vert, EData data, int weight);
	Arc(const Arc & copy);
	Arc<EData, VData> & operator = (const Arc & rhs);
	~Arc();
private:
	template<typename, typename> friend class Graph;
	Vertex<EData, VData> * m_destination;
	EData m_data;
	int m_weight;
};

template<typename EData, typename VData>
inline Arc<EData, VData>::Arc() : m_destination(nullptr), m_data(), m_weight(0)
{ }

template<typename EData, typename VData>
inline Arc<EData, VData>::Arc(Vertex<EData, VData>* vert, EData data, int weight) : m_destination(vert), m_weight(weight), m_data(data)
{ }

template<typename EData, typename VData>
inline Arc<EData, VData>::Arc(const Arc & copy) : m_destination(copy.m_destination), m_data(copy.m_data), m_weight(copy.m_weight)
{
}

template<typename EData, typename VData>
inline Arc<EData, VData> & Arc<EData, VData>::operator=(const Arc & rhs)
{
	m_destination = rhs.m_desination;
	m_data = rhs.m_data;
	m_weight = rhs.weight;
	return *this;
}

template<typename EData, typename VData>
inline Arc<EData, VData>::~Arc()
{
	m_destination = nullptr;
	m_weight = 0;
}

#endif