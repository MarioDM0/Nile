#include "productdata.h"

productData::productData()
{

}

QString productData::getImage() const
{
	return image;
}

void productData::setImage(const QString &value)
{
	image = value;
}

QString productData::getName() const
{
	return name;
}

void productData::setName(const QString &value)
{
	name = value;
}

double productData::getPrice() const
{
	return price;
}

void productData::setPrice(const double &value)
{
	price = value;
}

int productData::getSold() const
{
	return sold;
}

void productData::setSold(const int &value)
{
	sold = value;
}
