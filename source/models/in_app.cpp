#include "in_app.h"

InAppModel::InAppModel(){
	ID = 0;
	name = "";
	packageID = "";
	type = 0;
	value = 0;
	price = 0;
	prepareHttp();
	prepareModel();
}

InAppModel::~InAppModel(){

}

void InAppModel::httpMeta(){
	bindJsonAttribute("id", ID);
	bindJsonAttribute("name", name);
	bindJsonAttribute("price", price);
	bindJsonAttribute("value", value);
	bindJsonAttribute("type", type);
	bindJsonAttribute("package_id", packageID);
	setMetaName("in_app");
	setMetaListKey("");
	setMetaSaveURL("");
	setMetaUpdateURL("");
	setMetaListURL("?task=get_all_packages");
	setMetaUpdateKey("");
	setBaseURL("http://www.pepper.pk/retrorun/m_controller/m_controller.php");
}

void InAppModel::modelMeta(){
	bindModelAttribute("id", ID);
	bindModelAttribute("name", name);
	bindModelAttribute("price", price);
	bindModelAttribute("value", value);
	bindModelAttribute("type", type);
	bindModelAttribute("package_id", packageID);
	setModelMetaKey("id");
	setModelMetaTableName("in_app");
}

void InAppModel::receivedHTTPResponse(){

}