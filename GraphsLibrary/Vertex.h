#pragma once
#include <unordered_map>

template<typename T>
class Vertex
{
private:
	T data;
	std::unordered_map<Vertex<T>*, int> hash;
public:
	Vertex(T data_);

	void SetConnection(Vertex<T>* other)
};

template<typename T>
inline Vertex<T>::Vertex(T data_) : data(data_){}


