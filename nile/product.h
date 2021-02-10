#ifndef PRODUCT_H
#define PRODUCT_H

#include <QWidget>
#include <QMessageBox>
#include "productdata.h"

namespace Ui {
	class Product;
}

class Product : public QWidget
{
		Q_OBJECT

	signals:
		void sendPurchase(int, QString);

	public:
		explicit Product(QWidget *parent = nullptr);
		~Product();
		void setData(const productData& product);

	private slots:
		void on_buyPB_clicked();

	private:
		Ui::Product *ui;
		//Id para saber que producto se compro
		QString productId;
};

#endif // PRODUCT_H
