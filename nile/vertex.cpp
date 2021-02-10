#include "vertex.h"

Vertex::Vertex()
{

}

string Vertex::getProduct() const
{
	return product;
}

void Vertex::setProduct(const string &value)
{
	product = value;
}

int Vertex::getPriority() const
{
	return priority;
}

void Vertex::setPriority(int value)
{
	priority = value;
}
