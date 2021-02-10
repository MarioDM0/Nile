#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRegularExpression>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{        
	ui->setupUi(this);
	ui->viewsSW->setCurrentIndex(0);
	fileMenu = ui->menubar->addMenu(tr("&File"));
	openFileAction = new QAction(tr("Open file"), this);
	//Conectar envento y comportamiento
	//Connect (Quien envia, Que envia, Quien responde, COn que responde)
	connect( openFileAction, SIGNAL( triggered() ) , this, SLOT( openFile() ) );
	//connect( ui->categoriesCB , SIGNAL( currentIndexChanged() ) , this, SLOT( indexChanged() ) );
	fileMenu->addAction(openFileAction);
	ui->searchLE->setPlaceholderText("Busqueda");
	totPurchase = 0;
	band = false;
}

MainWindow::~MainWindow()
{	
	//Al cerrar el programa, guardar los datos
	band = true;
	ui->LogoutPB->click();
	saveDB();
	delete ui;
}

void MainWindow::enableLoginPB()
{
	//Sí y solo sí ambos line edit cuentan con texto, se puede pulsar el boton
	if( ui->userLE->text().length() > 0 && ui->paswordLE->text().length() > 0 ){
		ui->loginButton->setEnabled(true);
	}
	else {
		ui->loginButton->setEnabled(false);
	}
}

void MainWindow::enableCreatePB()
{
	//Sí y solo sí ambos line edit cuentan con texto, se puede pulsar el boton
	if( ui->newUserLE->text().length() > 0 && ui->newPasswordLE->text().length() > 0 && ui->emailLE->text().length() > 0 ){
		ui->createPB->setEnabled(true);
	}
	else {
		ui->createPB->setEnabled(false);
	}
}

void MainWindow::validateUser()
{
	QMessageBox message;
	size_t i;
	for ( i = 0 ; i < users.size() ; i++ ){
		if( users.at(i).getEmail() == ui->userLE->text() ){
			//Si se encuentra match con contraseñas de manera local, inicia sesión
			if( users.at(i).getPassword() == ui->paswordLE->text() ) {
				userLoged = users.at(i).getEmail();
				ui->viewsSW->setCurrentIndex(1);
				message.setText("Welcome to Nile!");
				message.exec();
				catalogue(0,0,"");
				randomProducts();
			}
			else{
				message.setText("Invalid user/password");
				message.exec();
			}
			break;
		}
	}
	//En caso que no se encuentre ya sea usuario o contraseña, avisar al usuario
	if ( i == users.size() ){
		message.setText("Invalid user/password");
		message.exec();
	}
}

void MainWindow::saveDB()
{
	QJsonDocument jsonDoc;
	QJsonObject jsonObj;

	//Utilizar un objeto guardando ambos arreglos, tanto de productos como de usuarios
	jsonObj["products"] = productsArray;
	jsonObj["users"] = usersArray;
	jsonDoc = QJsonDocument(jsonObj);

	dbFile.open(QIODevice::WriteOnly);
	dbFile.write(jsonDoc.toJson());
	dbFile.close();
}

void MainWindow::loadBD()
{    
	QJsonDocument jsonDoc;
	QJsonObject jsonObj, jsonObj2;
	QByteArray data;
	QJsonValue jsonVal;
	User u;
	productData dataP;

	dbFile.open(QIODevice::ReadOnly);
	data = dbFile.readAll();
	jsonDoc = QJsonDocument::fromJson(data);
	jsonObj = jsonDoc.object();
	usersArray = jsonObj["users"].toArray();
	productsArray =jsonObj["products"].toArray();

	dbFile.close();

	//Cargar usuarios a un arreglo local directamente
	for ( auto i = 0 ; i < usersArray.count() ;  i ++) {
		jsonVal = usersArray.at(i);
		jsonObj = jsonVal.toObject();
		u.setName(jsonObj["name"].toString());
		u.setEmail(jsonObj["email"].toString());
		u.setPassword(jsonObj["password"].toString());
		users.push_back(u);
	}

	//Cargar productos a un arreglo local directamente
	for ( auto i = 0 ; i < productsArray.count() ;  i ++) {
		jsonVal = productsArray.at(i);
		jsonObj = jsonVal.toObject();
		dataP.setImage(jsonObj["id"].toString());
		dataP.setName(jsonObj["name"].toString());
		dataP.setPrice(jsonObj["price"].toDouble());
		dataP.setSold(jsonObj["sold"].toInt());
		productsOriginal.push_back(dataP);
	}
	//Crear el grafo a partir de los datos existentes
	createGraph();
}

void MainWindow::catalogue(const int &value, const int &order, const QString &search)
{
	//Eliminar todos los items dentro del layout
	QLayoutItem *deleteItems;
	while((deleteItems = ui->productsLO->takeAt(0)) != NULL) {
		delete deleteItems->widget();
		delete deleteItems;
	}

	//Widget auxiliar para todos los mostrados e índice para acceder a ellos
	Product *newWidget;
	size_t i(0);

	//Según el criterio de orden enviado, se adaptará
	switch (order) {
		//Orden Original de los productos
		case 0:
			products = productsOriginal;
			break;
			//Orden ascendente de los productos
		case 1:
			qSort(products.begin(), products.end(),[](const productData& a, const productData& b) -> bool { return a.getPrice() < b.getPrice(); });
			break;
			//Orden descendente de los productos
		case 2:
			qSort(products.begin(), products.end(),[](const productData& a, const productData& b) -> bool { return a.getPrice() > b.getPrice(); });
			break;
	}

	char key = ' ';

	//Categorización de los productos
	switch (value) {
		//Todos los departamentos
		case 0:
			key = ' ';
			break;
			//Alimentos y bebidas
		case 1:
			key = 'A';
			break;
			//Libros
		case 2:
			key = 'L';
			break;
			//Electrónicos
		case 3:
			key = 'E';
			break;
			//Hogar y Cocina
		case 4:
			key = 'H';
			break;
			//Deporte y aire libre
		case 5:
			key = 'D';
			break;
	}

	//Si se está buscando alguna subcadena en especial
	if(search.length() > 0) {
		//Si se tiene seleccionado para todos los productos
		if(key == ' ') {
			for (int j = 0; i < products.size(); ++i) {
				//Si encuentra la subcadena, muestra solo el producto que contenga la subcadena
				if(isSubString(products.at(i).getName(), search)) {
					ui->stuffSA->setWidgetResizable(true);
					newWidget = new Product(ui->stuffSA);
					newWidget->setData(products.at(i));
					//Conexión para saber cuantos y que productos se compraron
					connect(newWidget,SIGNAL(sendPurchase(int, QString)),this,SLOT(savePurchase(int, QString)));
					ui->productsLO->addWidget(newWidget,j/4,j%4);
					j++;
				}
			}
		} else {
			//Si se busca una categoria en especial
			for (int j = 0 ; i < products.size(); ++i) {
				//Revisa que la categoria corresponda a la llave selecta
				if(products.at(i).getImage()[0] == key) {
					//Revisa que se encuentre la subcadena y se muestre dicho producto
					if(isSubString(products.at(i).getName(), search)) {
						ui->stuffSA->setWidgetResizable(true);
						newWidget = new Product(ui->stuffSA);
						newWidget->setData(products.at(i));
						//Conexión para saber cuantos y que productos se compraron
						connect(newWidget,SIGNAL(sendPurchase(int, QString)),this,SLOT(savePurchase(int, QString)));
						ui->productsLO->addWidget(newWidget,j/4,j%4);
						j++;
					}
				}
			}
		}

	} else {
		//Si no se busca ningun producto pero se tienen todos los productos en categoria
		if(key == ' ') {
			for (; i < products.size(); ++i) {
				ui->stuffSA->setWidgetResizable(true);
				newWidget = new Product(ui->stuffSA);
				newWidget->setData(products.at(i));
				//Conexión para saber cuantos y que productos se compraron
				connect(newWidget,SIGNAL(sendPurchase(int, QString)),this,SLOT(savePurchase(int, QString)));
				ui->productsLO->addWidget(newWidget,i/4,i%4);
			}
		} else {
			//Si se busca alguna categoria en especial, se compara la llave con la categoria
			for (int j = 0; i < products.size(); ++i) {
				if(products.at(i).getImage()[0] == key) {
					ui->stuffSA->setWidgetResizable(true);
					newWidget = new Product(ui->stuffSA);
					newWidget->setData(products.at(i));
					//Conexión para saber cuantos y que productos se compraron
					connect(newWidget,SIGNAL(sendPurchase(int, QString)),this,SLOT(savePurchase(int, QString)));
					ui->productsLO->addWidget(newWidget,j/4,j%4);
					j++;
				}
			}
		}

	}
}

bool MainWindow::isSubString(QString str_1, QString str_2)
{    
	string str_1Aux = str_1.toUtf8().constData();
	string str_2Aux = str_2.toUtf8().constData();

	//Convertir todo a minusculas
	str_1Aux = toLowerString(str_1Aux);
	str_2Aux  = toLowerString(str_2Aux );

	//Revisar que se encuentre dentro de la cadena requerida
	string::size_type n;
	n = str_1Aux.find(str_2Aux);

	if(n == string::npos) {
		return false;
	} else {
		return true;
	}
}

string MainWindow::toLowerString(string &value)
{
	//Convertir una cadena a minusculas
	unsigned int i;
	for(i = 0; i < value.length(); i++) {
		value[i] = tolower(value[i]);
	}
	return  value;
}

void MainWindow::createGraph()
{
	//Para recorrer los usuarios
	for ( size_t i(0) ; i < usersArray.size() ; i++ ) {
		//Tomar usuario por usuario para revisar todas sus compras
		QJsonObject userAux = usersArray.at(i).toObject();
		QJsonArray userPurchase = userAux["purchase"].toArray();
		if( !userPurchase.isEmpty() ) {
			//Recorrer todos las compras del usuario
			for( size_t j(0) ; j < userPurchase.size(); j++){
				//Obtener los objetos y las claves del arreglo (id's)
				QJsonObject onePurchase = userPurchase.at(j).toObject();
				QString auxKey = onePurchase.keys().first();
				QJsonArray tempPurchase = onePurchase[auxKey].toArray();
				//Si en la sesión dada se hicieron al menos dos compras
				if(tempPurchase.size() > 1) {
					//Recorrer cada objeto con respecto a los otros
					for( size_t k(0) ; k < tempPurchase.size(); k++){
						//Almacenar el pimer objeto con sus relaciones
						QJsonObject baseObject = tempPurchase.at(k).toObject();
						//Recorrer a todos los productos sin tener en cuenta los anteriores
						for( size_t h( k + 1 ) ; h < tempPurchase.size(); h++){
							QJsonObject relatedObject = tempPurchase.at(h).toObject();
							//Se revisa si ya hay una arista con dicho producto
							if(myGraph.isEdge(baseObject["id"].toString().toStdString(),relatedObject["id"].toString().toStdString())){
								//En caso de ser así, se toma el valor existente y se incrementa en uno el valor total
								myGraph.createEdge(baseObject["id"].toString().toStdString(),relatedObject["id"].toString().toStdString(), myGraph.getCost(baseObject["id"].toString().toStdString(),relatedObject["id"].toString().toStdString() ) + 1 );
							}
							else {
								//Si no existía dicha relación, se crea, con índice de creación en uno
								myGraph.createEdge(baseObject["id"].toString().toStdString(),relatedObject["id"].toString().toStdString(), 1 );
							}
						}
					}
				}
			}
		}

	}
	//Mostrar el grafo resultante
	myGraph.printData();
}

vector<User> MainWindow::getUsers() const
{
	return users;
}

void MainWindow::setUsers(const vector<User> &value)
{
	users = value;
}

void MainWindow::on_userLE_textChanged(const QString &arg1)
{
	Q_UNUSED(arg1)
	enableLoginPB();
}

void MainWindow::on_paswordLE_textChanged(const QString &arg1)
{
	Q_UNUSED(arg1)
	enableLoginPB();
}

void MainWindow::on_newUserLE_textChanged(const QString &arg1)
{
	Q_UNUSED(arg1)
	enableCreatePB();
}

void MainWindow::on_emailLE_textChanged(const QString &arg1)
{
	Q_UNUSED(arg1)
	enableCreatePB();
}

void MainWindow::on_newPasswordLE_textChanged(const QString &arg1)
{
	Q_UNUSED(arg1)
	enableCreatePB();
}

void MainWindow::on_createPB_clicked()
{
	QMessageBox message;
	QJsonObject jsonObj;

	//Solo correos preestablecidos
	//QRegularExpression vEmail("[^\\s][A-Za-z]{1}[A-Za-z0-9\\._]{0,29}@(nile|hotmail|gmail|outlook|live)(.com|.com.mx|.udg.mx)");
	QRegularExpression vEmail("[^\\s][A-Za-z]{1}[A-Za-z0-9\\._]{0,29}@[A-Za-z]{2,8}.[A-Za-z]{2,4}.*[A-Za-z]*");
	QRegularExpressionMatch match = vEmail.match( ui->emailLE->text() );

	//Si se encuentra coincidencia entre formato de correo y line edit
	if ( !match.hasMatch() ) {
		message.setText("The email format is not valid");
		message.exec();
		return;
	}

	//Comprobar que no exista el mismo correo
	size_t i;
	for ( i = 0 ; i < users.size() ; i++ ) {
		if (users.at(i).getEmail() == ui->emailLE->text() ) {
			message.setText("The email already exist");
			message.exec();
			return;
		}
	}

	//Establecer usuario
	User u;
	u.setName(ui->newUserLE->text());
	u.setEmail(ui->emailLE->text());
	u.setPassword(ui->newPasswordLE->text());

	//Guardar el usuario completo en un vector
	users.push_back(u);

	//Guardar el usuario en el arreglo de Json
	jsonObj["name"] = u.getName();
	jsonObj["email"] = u.getEmail();
	jsonObj["password"] = u.getPassword();
	usersArray.append(jsonObj);

	//Avisar al usuario que se creo el usuario
	message.setText("New user created!");
	message.exec();

	//Limpiar campos de escritura
	ui->newUserLE->clear();
	ui->emailLE->clear();
	ui->newPasswordLE->clear();
}

void MainWindow::on_loginButton_clicked()
{
	//Expresion regular para correos
	QRegularExpression vEmail("[^\\s][A-Za-z]{1}[A-Za-z0-9\\._]{0,29}@[A-Za-z]{2,8}.[A-Za-z]{2,4}.*[A-Za-z]*");
	QMessageBox message;
	QRegularExpressionMatch match = vEmail.match( ui->userLE->text() );

	//Si encuentra coincidencia entre line edit y expresión regular
	if ( match.hasMatch() ) {
		validateUser();
	}
	//Avisa si no es valido el formato de line edit respecto a expresión regular
	else {
		message.setText("The email format is not valid");
		message.exec();
	}

	//Limpiar campos de texto
	ui->userLE->clear();
	ui->paswordLE->clear();
}

void MainWindow::openFile()
{
	QString fileName;

	//Abrir cuadro de dialogo para archivo
	fileName = QFileDialog::getOpenFileName(this, "Nile DataBase", "./", "JSON files (*.json)");
	//Si el formato de archivo tiene como nombre valido
	if( fileName.length() > 0 ) {
		dbFile.setFileName(fileName);
		//Cargar base de datos
		loadBD();
		ui->loginFrame->setEnabled(true);
	}
}

void MainWindow::savePurchase(int ammount, QString Id)
{
	//Para guardar el producto
	QJsonObject jsonObj;
	size_t i(0);
	//Se revisa dentro de todos los productos
	for(; i < products.size(); i++){
		//Si los productos almacenados se encuentran dentro de la lista, añadirlos
		if(products.at(i).getImage() == Id){
			//Aumentar la cantidad de vendidos de tal producto
			products.at(i).setSold(products.at(i).getSold() + ammount);
			totPurchase += ammount;
			jsonObj["id"] = products.at(i).getImage();
			jsonObj["name"] = products.at(i).getName();
			jsonObj["price"] = products.at(i).getPrice();
			jsonObj["sold"] = products.at(i).getSold();
			products.at(i).getSold();
			//Modificar eliminando e insertando el mismo producto para no perder su esencia
			productsArray.removeAt(i);
			productsArray.insert(i, jsonObj);
		}
	}

	//Buscar si ya se compró el producto anteriormente
	bool isInPurchase = false;
	i = 0;
	for ( ; i < purchase.size() ; i++ ){
		if(purchase.at(i) == Id){
			isInPurchase = true;
		}
	}
	//Si no se ha comprado, añadirlo, sino, si lo añade
	if ( !isInPurchase ){
		purchase.push_back(Id);
	}

	recomendedProducts(Id.toStdString());
}

void MainWindow::on_categoriesCB_currentIndexChanged(int index)
{        
	//Cada que se cambie el indice del combo box, mandar a llamar de nuevo la función para categorizar
	catalogue(index,ui->orderFCB->currentIndex(),ui->searchLE->text());
}

void MainWindow::on_searchLE_textChanged(const QString &arg1)
{
	//Cada que se cambie el texto del lineEdit, mandar a llamar de nuevo la función para categorizar
	catalogue(ui->categoriesCB->currentIndex(),ui->orderFCB->currentIndex(),arg1);
}

void MainWindow::on_orderFCB_currentIndexChanged(int index)
{
	//Cada que se cambie el indice del combo box, mandar a llamar de nuevo la función para categorizar
	catalogue(ui->categoriesCB->currentIndex(),index,ui->searchLE->text());
}

void MainWindow::on_LogoutPB_clicked()
{	
	//Al cerrar sesión
	QMessageBox msgBox;
	//Preguntar si se desea cerrar sesión
	msgBox.setText(tr("¿Estas seguro de cerrar sesion?"));
	QAbstractButton* pButtonYes = msgBox.addButton(tr("¡SI!"), QMessageBox::YesRole);
	msgBox.addButton(tr("¡NO!"), QMessageBox::NoRole);

	//Cuando haya sesión iniciada, compras existentes y se quiera cerrar el programa por completo
	if( ui->viewsSW->currentIndex() == 1 and !band )
		msgBox.exec();
	//Solo cuando se este cerrando el sistema por completo
	else {
		//Revisar si hay productos en el carrito
		if(purchase.size() > 0) {
			size_t i(0);
			for(; i < users.size(); i++){
				//Buscar el usuario que esta logeado
				if(users.at(i).getEmail() == userLoged) {
					//Guardar al usuario para modificarlo
					QJsonObject user = usersArray.at(i).toObject();
					QJsonArray oldPurchase = user["purchase"].toArray();

					QJsonArray newPurchase;
					QJsonObject datePurchase;
					QJsonObject savedPurchase;

					//Guardar todos los id de producto comprados (sin cantidades)
					for(int j(0); j < purchase.size(); j++) {
						savedPurchase.insert("id", QJsonValue::fromVariant(purchase.at(j)));
						newPurchase.push_back(savedPurchase);
					}

					//Tomar la fecha actual e insertarla
					QString actualDateTime = QDateTime::currentDateTime().toString("dd/MM/yy HH:mm:ss");
					datePurchase.insert(actualDateTime, newPurchase);
					oldPurchase.push_back(datePurchase);

					//Insertar las compras de dicho usuario
					user.insert("purchase", oldPurchase);

					//Eliminar el antiguo usuario y añadir las modificaciones
					usersArray.removeAt(i);
					usersArray.insert(i, user);
				}
			}
			//Guardar la base de datos
			saveDB();
		}
	}

	//Si se desea salir
	if (msgBox.clickedButton() == pButtonYes) {
		//Regresar a la interfaz de inicio de sesión
		ui->viewsSW->setCurrentIndex(0);
		//Revisar que si hay productos en el carrito, se deben guardar
		if(purchase.size() > 0) {
			size_t i(0);
			for(; i < users.size(); i++){
				//Buscar el usuario que esta logeado
				if(users.at(i).getEmail() == userLoged) {
					//Guardar al usuario para modificarlo
					QJsonObject user = usersArray.at(i).toObject();
					QJsonArray oldPurchase = user["purchase"].toArray();

					QJsonArray newPurchase;
					QJsonObject datePurchase;
					QJsonObject savedPurchase;

					//Guardar todos los id de producto comprados (sin cantidades)
					for(int j(0); j < purchase.size(); j++) {
						savedPurchase.insert("id", QJsonValue::fromVariant(purchase.at(j)));
						newPurchase.push_back(savedPurchase);
					}

					//Tomar la fecha actual e insertarla
					QString actualDateTime = QDateTime::currentDateTime().toString("dd/MM/yy HH:mm:ss");
					datePurchase.insert(actualDateTime, newPurchase);
					oldPurchase.push_back(datePurchase);

					//Insertar las compras de dicho usuario
					user.insert("purchase", oldPurchase);

					//Eliminar el antiguo usuario y añadir las modificaciones
					usersArray.removeAt(i);
					usersArray.insert(i, user);
				}
			}
			//Guardar la base de datos
			saveDB();
			if( purchase.size() > 1 ){
				//Recorrer cada objeto con respecto a los otros
				for( size_t k(0) ; k < purchase.size(); k++){
					//Almacenar el pimer objeto con sus relaciones
					string baseObject = purchase.at(k).toStdString();
					//Recorrer a todos los productos sin tener en cuenta los anteriores
					for( size_t h( k + 1 ) ; h < purchase.size(); h++){
						string relatedObject = purchase.at(h).toStdString();
						//Se revisa si ya hay una arista con dicho producto
						if(myGraph.isEdge(baseObject,relatedObject)){
							//En caso de ser así, se toma el valor existente y se incrementa en uno el valor total
							myGraph.createEdge(baseObject,relatedObject, myGraph.getCost(baseObject,relatedObject ) + 1 );
						}
						else {
							//Si no existía dicha relación, se crea, con índice de creación en uno
							myGraph.createEdge(baseObject,relatedObject, 1 );
						}
					}
				}
				myGraph.printData();
			}
		}

		//Eliminar todos los productos del carrito para la proxima sesion
		while (purchase.size() > 0){
			purchase.erase(purchase.begin());
		}
		totPurchase = 0;
	}
}

void MainWindow::on_carPB_clicked()
{
	QMessageBox message;

	//Si hay compras realizadas, decirle al ususario cuantos tipos de producto se han comprado
	if(purchase.size() > 0) {
		message.setText("Has comprado: " + QString::number(totPurchase) + ( totPurchase > 1 ? " productos" : " producto"));
	}
	//Decirle al usuario que no se compró nada
	else {
		message.setText("No se han comprado productos en esta sesión");
	}
	message.exec();
}

void MainWindow::recomendedProducts(const string &product)
{
	//Eliminar todos los productos anteriormente escritos en layout
	QLayoutItem *deleteItems;
	while((deleteItems = ui->productsLO_2->takeAt(0)) != NULL) {
		delete deleteItems->widget();
		delete deleteItems;
	}

	QList<Vertex> list = myGraph.orderPriority(myGraph.getNeighbors(product));
	vector<productData> myProducts = productsOriginal;

	//Eliminar los productos que se encuentren en el carrito
	//Recorrer productos a recomendar
	for ( int i = 0 ; i < list.size() ; i++ ){
		//Recorrer carrito
		for( size_t j = 0 ; j < purchase.size() ; j++ ){
			//Si se encuentra en el carrito, no se recomendará
			if ( list.at(i).getProduct() == purchase.at(j).toStdString() ){
				list.removeAt(i);
				i = -1;
				break;
			}
		}
	}

	//Establecer conexiones de productos
	Product *newWidget;
	//Recorrer hasta el tamaño del arreglo o hasta que sean cinco objetos
	for ( int j = 0 ; j < list.size() ; ++j ){
		for ( size_t i = 0 ; i < products.size() ; ++i ) {
			if ( list.at(j).getProduct() == products.at(i).getImage().toStdString() ){
				if ( j > 4 ) {
					return;
				}
				ui->stuffSA_2->setWidgetResizable(true);
				newWidget = new Product(ui->stuffSA_2);
				newWidget->setData(products.at(i));
				//Conexión para saber cuantos y que productos se compraron
				connect(newWidget,SIGNAL(sendPurchase(int, QString)),this,SLOT(savePurchase(int, QString)));
				ui->productsLO_2->addWidget(newWidget,j/1,j%1);
			}
		}
	}

}

void MainWindow::randomProducts()
{
	//Eliminar todos los productos anteriormente escritos en layout
	QLayoutItem *deleteItems;
	while((deleteItems = ui->productsLO_2->takeAt(0)) != NULL) {
		delete deleteItems->widget();
		delete deleteItems;
	}

	int arr[5];
	int num;
	srand(time(NULL));

	products = productsOriginal;

	for ( int i = 0 ; i < 5 ; i++ ){
		num = rand() % 50;
		if(arr[i] == num ){
			i = -1;
		}
		else {
			arr[i] = num;
		}
	}

	Product *newWidget;
	for (size_t i = 0; i < 5 ; ++i ) {		
		ui->stuffSA_2->setWidgetResizable(true);
		newWidget = new Product(ui->stuffSA_2);
		newWidget->setData(products.at(arr[i]));
		//Conexión para saber cuantos y que productos se compraron
		connect(newWidget,SIGNAL(sendPurchase(int, QString)),this,SLOT(savePurchase(int, QString)));
		ui->productsLO_2->addWidget(newWidget,i/1,i%1);
	}
}
