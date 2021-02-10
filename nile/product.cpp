#include "product.h"
#include "ui_product.h"

Product::Product(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Product)
{
	ui->setupUi(this);	
}

Product::~Product()
{
	delete ui;
}

void Product::setData(const productData& product)
{    
	//Cargar imagen desde carpeta
	QPixmap aux("C:/Users/Mario/Desktop/Nile/nile/Img/" + product.getImage() );
	//Re-escalar imagen
	aux = aux.scaled(200,200,Qt::AspectRatioMode::KeepAspectRatio);
	//Establecer imagen
	ui->Image->setPixmap(aux);
	productId = product.getImage();
	//Dar tamaño y formato de texto a label
	ui->Name->resize(200,200);
	ui->Name->setWordWrap(true);
	ui->Name->setText(product.getName());
	//Dar tamaño y formato de texto a label
	ui->Price->resize(200,200);
	ui->Price->setWordWrap(true);
	ui->Price->setText(QString::number(product.getPrice()));
}

void Product::on_buyPB_clicked()
{    
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Warning);
	msgBox.setText(tr("¿Estas seguro de continuar con la compra?"));
	//Avisar al ususario que se estan comprando n articulos de x producto
	msgBox.setInformativeText("Comprando " + QString::number(ui->ammountSB->value()) + (ui->ammountSB->value() > 1 ? " productos" : " producto") + " por: $" + QString::number( ui->Price->text().toDouble() * ui->ammountSB->value() ) );
	QAbstractButton* pButtonYes = msgBox.addButton(tr("¡SI!"), QMessageBox::YesRole);
	msgBox.addButton(tr("¡NO!"), QMessageBox::NoRole);

	msgBox.exec();

	//Regresar la cantidad a 1
	ui->ammountSB->setValue(1);

	//En caso de que se presione que se siga comprando
	if (msgBox.clickedButton()==pButtonYes) {
		//Emitir señal de conexion entre distintos diseños para decir cuantos productos y que producto se ha comprado
		emit sendPurchase(ui->ammountSB->value(), productId);
	}

}
