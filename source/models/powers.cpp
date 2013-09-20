#include "powers.h"

PowersModel::PowersModel(){
	ID = 0;
	typeName = "";
	levelNumber = 0;
	type = 0;
	value = 0;
	price = 0;
	prepareHttp();
	prepareModel();
}

PowersModel::~PowersModel(){

}

void PowersModel::httpMeta(){
	bindJsonAttribute("id", ID);
	bindJsonAttribute("type_name", typeName);
	bindJsonAttribute("price", price);
	bindJsonAttribute("value", value);
	bindJsonAttribute("type", type);
	bindJsonAttribute("level_number", levelNumber);
	setMetaName("powers");
	setMetaListKey("");
	setMetaSaveURL("");
	setMetaUpdateURL("");
	setMetaListURL("?task=get_all_powers");
	setMetaUpdateKey("");
	setBaseURL("http://www.pepper.pk/retrorun/m_controller/m_controller.php");
}

void PowersModel::modelMeta(){
	bindModelAttribute("id", ID);
	bindModelAttribute("type_name", typeName);
	bindModelAttribute("price", price);
	bindModelAttribute("value", value);
	bindModelAttribute("type", type);
	bindModelAttribute("level_number", levelNumber);
	setModelMetaKey("id");
	setModelMetaTableName("powers");
}

void PowersModel::receivedHTTPResponse(){

}

PowersModel * PowersModel::clone(){
	PowersModel *newModel = new PowersModel();
	newModel->ID = ID;
	newModel->type = type;
	newModel->typeName = typeName;
	newModel->levelNumber = levelNumber;
	newModel->price = price;
	newModel->value = value;
	return newModel;
}

void PowersModel::copy(PowersModel *_power){
	ID = _power->ID;
	type = _power->type;
	typeName = _power->typeName;
	levelNumber = _power->levelNumber;
	price = _power->price;
	value = _power->value;
}