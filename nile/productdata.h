#ifndef PRODUCTDATA_H
#define PRODUCTDATA_H

#include <QString>
class productData
{
	public:
		productData();


		QString getImage() const;
		void setImage(const QString &value);

		QString getName() const;
		void setName(const QString &value);

		double getPrice() const;
		void setPrice(const double &value);

		int getSold() const;		
		void setSold(const int &value);

	private:
		//Datos del producto
		QString image;
		QString name;
		double price;
		int sold;
};

#endif // PRODUCTDATA_H
