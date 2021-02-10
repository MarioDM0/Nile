#ifndef VERTEX_H
#define VERTEX_H

#include <string>
using namespace std;

class Vertex
{
	public:
		Vertex();
		string getProduct() const;
		void setProduct(const string &value);

		int getPriority() const;
		void setPriority(int value);

	private:
		string product;
		int priority;
};

#endif // VERTEX_H
