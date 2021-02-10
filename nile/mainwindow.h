#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "product.h"
#include "graph.h"
#include "vertex.h"
#include <vector>
#include <QMenu>
#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPicture>
#include <QDateTime>
#include <stdlib.h>
#include <time.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();

		vector<User> getUsers() const;
		void setUsers(const vector<User> &value);

	private slots:
		void on_userLE_textChanged(const QString &arg1);

		void on_paswordLE_textChanged(const QString &arg1);

		void on_newUserLE_textChanged(const QString &arg1);

		void on_emailLE_textChanged(const QString &arg1);

		void on_newPasswordLE_textChanged(const QString &arg1);

		void on_createPB_clicked();

		void on_loginButton_clicked();

		void openFile();

		void savePurchase(int, QString);

		void on_categoriesCB_currentIndexChanged(int index);

		void on_searchLE_textChanged(const QString &arg1);

		void on_orderFCB_currentIndexChanged(int index);

		void on_LogoutPB_clicked();

		void on_carPB_clicked();

	private:
		Ui::MainWindow *ui;

		//Grafo
		Graph<string> myGraph;
		//Salir y guardar
		bool band;
		//Usuarios registrados
		vector<User> users;
		//Lectura y escritura de datos
		QJsonArray usersArray;
		QAction *openFileAction;
		QMenu *fileMenu;
		QFile dbFile;
		QJsonArray productsArray;
		//Productos y auxiliar para mostrar el orden que se requiera
		vector<productData> products;
		vector<productData> productsOriginal;
		//Registro de productos comprados en sesión
		vector<QString> purchase;
		//Conocer quién tiene sesión iniciada
		QString userLoged;
		//Total de productos comprados en la sesion
		int totPurchase;

		//Método para productos recomendados
		void recomendedProducts(const string &product );
		void randomProducts();
		//Método para crear el grafo
		void createGraph();
		//Validaciones de usuario y botones
		void enableLoginPB();
		void enableCreatePB();
		void validateUser();
		//Cargar y guardar base de datos (json)
		void saveDB();
		void loadBD();
		//Función para mostar todo
		void catalogue(const int &value, const int &order, const QString &search);
		//Validaciones
		bool isSubString(QString str_1, QString str_2);
		string toLowerString(string &value);

};
#endif // MAINWINDOW_H
