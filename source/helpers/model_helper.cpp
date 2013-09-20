#include "model_helper.h"
#include "model_factory.h"

ModelHelper * ModelHelper::_modelHelper = NULL;

ModelHelper::ModelHelper(){
	prepareModel();
}

ModelHelper::~ModelHelper(){

}

ModelHelper * ModelHelper::getModelHelper(){
	if(!_modelHelper)
		_modelHelper = new ModelHelper();

	return _modelHelper;
}

void ModelHelper::destroyModelHelper(){
	if(_modelHelper)
		delete _modelHelper;

	_modelHelper = NULL;
}

void ModelHelper::fetch_list(string _modelMetaKey, AeDynArray<Model *> &_array, string _whereConditions){
	Model *model = MODEL_FACTORY->createModelObject(_modelMetaKey);

	string sql = "SELECT ";
	string columns = "";
	hash_map<string, ModelNode> attr = model->getModelAttributes();

	for(hash_map<string, ModelNode>::iterator it = attr.begin(); it != attr.end(); it++){
		if(columns != "") columns.append(", ");
		columns.append(it->first);
	}

	sql.append(columns);
	sql.append(" FROM ");
	sql.append(model->getMetaTableName());
	sql.append(" WHERE ");
	sql.append(_whereConditions);

	if(sqlite3_prepare_v2(database, sql.c_str(), -1, &loadStmt, NULL) != SQLITE_OK){
		//error
		cout<<endl<<sqlite3_prepare_v2(database, sql.c_str(), -1, &loadStmt, NULL)<<endl;
	}

	while(SQLITE_DONE != sqlite3_step(loadStmt)) {
		Model *newModel = MODEL_FACTORY->createModelObject(_modelMetaKey);
		hash_map<string, ModelNode> attr = newModel->getModelAttributes();
		int i = 0;
		for(hash_map<string, ModelNode>::iterator it = attr.begin(); it != attr.end(); it++){
			if(attr[it->first].type == "int") *attr[it->first].intVal = sqlite3_column_int(loadStmt, i);
			else if(attr[it->first].type == "string") *attr[it->first].stringVal = (const char *)sqlite3_column_text(loadStmt, i);
			else if(attr[it->first].type == "double") *attr[it->first].doubleVal = sqlite3_column_double(loadStmt, i);
			else if(attr[it->first].type == "int64") *attr[it->first].int64Val = sqlite3_column_int64(loadStmt, i);
			else if(attr[it->first].type == "bool"){ 
				if(sqlite3_column_int(loadStmt, i) >= 1) *attr[it->first].boolVal = true;
				else *attr[it->first].boolVal = false;
			}else if(attr[it->first].type == "model"){
				Model *tmpModel;
				if(!attr[it->first].model){
					if(attr[it->first].table == "") tmpModel = MODEL_FACTORY->createModelObject(it->first);
					else tmpModel = MODEL_FACTORY->createModelObject(attr[it->first].table);
					attr[it->first].model = tmpModel;
				}else{
					tmpModel = attr[it->first].model;
				}

				hash_map<string, ModelNode>attr1 = tmpModel->getModelAttributes();
				if(attr1[tmpModel->getMetaKey()].type == "int") *attr1[tmpModel->getMetaKey()].intVal = sqlite3_column_int(loadStmt, i);
				else if(attr1[tmpModel->getMetaKey()].type == "string") *attr1[tmpModel->getMetaKey()].stringVal = (char *)sqlite3_column_text(loadStmt, i);
				else if(attr1[tmpModel->getMetaKey()].type == "double") *attr1[tmpModel->getMetaKey()].doubleVal = sqlite3_column_double(loadStmt, i);
				else if(attr1[tmpModel->getMetaKey()].type == "int64") *attr1[tmpModel->getMetaKey()].int64Val = sqlite3_column_int64(loadStmt, i);
				else if(attr1[tmpModel->getMetaKey()].type == "bool"){ 
					if(sqlite3_column_int(loadStmt, i)) *attr1[tmpModel->getMetaKey()].boolVal = true;
					else *attr1[tmpModel->getMetaKey()].boolVal = false;
				}

				if(tmpModel->primaryKeyExits()) tmpModel->loadID();
			}
			i++;
		}
		_array.Add(newModel);
	}

	sqlite3_finalize(loadStmt);
}