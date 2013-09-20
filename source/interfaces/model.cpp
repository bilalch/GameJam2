#include "model.h"
#include "model_factory.h"

Model::Model(){
	connection = ConnectionManager::getConnection();
	database = connection->getDatabase();
	deleteStmt = connection->getDeleteStmt();
	addStmt = connection->getAddStmt();
	loadStmt = connection->getLoadStmt();
	updateStmt = connection->getUpdateStmt();
	metaKey = "";
	metaTableName = "";
};

Model::~Model(){ 

};

void Model::load(AeDynArray<Model *> &dynArray, string where){
	string sql = "SELECT ";
	string columns = "";

	for(hash_map<string, ModelNode>::iterator it = modelAttributes.begin(); it != modelAttributes.end(); it++){
		if(columns != "") columns.append(", ");
		columns.append(it->first);
	}

	sql.append(columns);
	sql.append(" FROM ");
	sql.append(metaTableName);
	sql.append(" WHERE ");
	sql.append(where);

	if(sqlite3_prepare_v2(database, sql.c_str(), -1, &loadStmt, NULL) != SQLITE_OK){
		//error
	}

	while(SQLITE_DONE != sqlite3_step(loadStmt)) {
		int i = 0;
		for(hash_map<string, ModelNode>::iterator it = modelAttributes.begin(); it != modelAttributes.end(); it++){
			if(modelAttributes[metaKey].type == "int") *modelAttributes[metaKey].intVal = sqlite3_column_int(loadStmt, i);
			else if(modelAttributes[metaKey].type == "string") *modelAttributes[metaKey].stringVal = (const char *)sqlite3_column_text(loadStmt, i);
			else if(modelAttributes[metaKey].type == "double") *modelAttributes[metaKey].doubleVal = sqlite3_column_double(loadStmt, i);
			else if(modelAttributes[metaKey].type == "int64") *modelAttributes[metaKey].int64Val = sqlite3_column_int64(loadStmt, i);
			else if(modelAttributes[metaKey].type == "bool"){ 
				if(sqlite3_column_int(loadStmt, i) >= 1) *modelAttributes[metaKey].boolVal = true;
				else *modelAttributes[metaKey].boolVal = false;
			}
			i++;
		}
	}

	sqlite3_finalize(loadStmt);
};
	
void Model::loadID() {
	string sql = "SELECT ";
	string columns = "";

	for(hash_map<string, ModelNode>::iterator it = modelAttributes.begin(); it != modelAttributes.end(); it++){
		if(columns != "") columns.append(", ");
		columns.append(it->first);
	}

	sql.append(columns);
	sql.append(" FROM ");
	sql.append(metaTableName);
	sql.append(" WHERE ");
	sql.append(metaKey);
	sql.append(" = ?");

	if(sqlite3_prepare_v2(database, sql.c_str(), -1, &loadStmt, NULL) != SQLITE_OK){
		//error
	}

	if(modelAttributes[metaKey].type == "int") sqlite3_bind_int(loadStmt, 1, *modelAttributes[metaKey].intVal);
	else if(modelAttributes[metaKey].type == "string") sqlite3_bind_text(loadStmt, 1, (const char *)(*modelAttributes[metaKey].stringVal).c_str(), -1, SQLITE_TRANSIENT);
	else if(modelAttributes[metaKey].type == "double") sqlite3_bind_double(loadStmt, 1, *modelAttributes[metaKey].doubleVal);
	else if(modelAttributes[metaKey].type == "int64") sqlite3_bind_int64(loadStmt, 1, *modelAttributes[metaKey].int64Val);
	else if(modelAttributes[metaKey].type == "bool"){ 
		if(modelAttributes[metaKey].boolVal) sqlite3_bind_int(loadStmt, 1, 1);
		else sqlite3_bind_int(loadStmt, 1, 0);
	}

	if(SQLITE_DONE != sqlite3_step(loadStmt)) {
		int i = 0;
		for(hash_map<string, ModelNode>::iterator it = modelAttributes.begin(); it != modelAttributes.end(); it++){
			if(modelAttributes[it->first].type == "int") *modelAttributes[it->first].intVal = sqlite3_column_int(loadStmt, i);
			else if(modelAttributes[it->first].type == "string") *modelAttributes[it->first].stringVal = (char *)sqlite3_column_text(loadStmt, i);
			else if(modelAttributes[it->first].type == "double") *modelAttributes[it->first].doubleVal = sqlite3_column_double(loadStmt, i);
			else if(modelAttributes[it->first].type == "int64") *modelAttributes[it->first].int64Val = sqlite3_column_int64(loadStmt, i);
			else if(modelAttributes[it->first].type == "bool"){ 
				if(sqlite3_column_int(loadStmt, i) >= 1) *modelAttributes[it->first].boolVal = true;
				else *modelAttributes[it->first].boolVal = false;
			}else if(modelAttributes[it->first].type == "model"){
				Model *tmpModel;
				if(!modelAttributes[it->first].model){
					if(modelAttributes[it->first].table == "") tmpModel = MODEL_FACTORY->createModelObject(it->first);
					else tmpModel = MODEL_FACTORY->createModelObject(modelAttributes[it->first].table);
					modelAttributes[it->first].model = tmpModel;
				}else{
					tmpModel = modelAttributes[it->first].model;
				}

				hash_map<string, ModelNode>attr = tmpModel->getModelAttributes();
				if(attr[tmpModel->getMetaKey()].type == "int") *attr[tmpModel->getMetaKey()].intVal = sqlite3_column_int(loadStmt, i);
				else if(attr[tmpModel->getMetaKey()].type == "string") *attr[tmpModel->getMetaKey()].stringVal = (char *)sqlite3_column_text(loadStmt, i);
				else if(attr[tmpModel->getMetaKey()].type == "double") *attr[tmpModel->getMetaKey()].doubleVal = sqlite3_column_double(loadStmt, i);
				else if(attr[tmpModel->getMetaKey()].type == "int64") *attr[tmpModel->getMetaKey()].int64Val = sqlite3_column_int64(loadStmt, i);
				else if(attr[tmpModel->getMetaKey()].type == "bool"){ 
					if(sqlite3_column_int(loadStmt, i)) *attr[tmpModel->getMetaKey()].boolVal = true;
					else *attr[tmpModel->getMetaKey()].boolVal = false;
				}

				if(tmpModel->primaryKeyExits()) tmpModel->loadID();
			}
			i++;
		}
	}

	sqlite3_finalize(loadStmt);
};
	
void Model::save(){
	if(primaryKeyExits()) update();
	else insert();
};

void Model::insert() {
	string sql = "INSERT INTO ";
	sql.append(metaTableName);
	sql.append(" ( ");
	string columns = "";
	string values = "";

	for(hash_map<string, ModelNode>::iterator it = modelAttributes.begin(); it != modelAttributes.end(); it++){
		if(it->first == metaKey) continue;
		if(columns != "") columns.append(", ");
		columns.append(it->first);
		if(values != "") values.append(", ");
		values.append("?");
	}

	sql.append(columns);
	sql.append(" ) VALUES ( ");
	sql.append(values);
	sql.append(" ) ");

	if(sqlite3_prepare_v2(database, sql.c_str(), -1, &addStmt, NULL) != SQLITE_OK){
		//error
		cout<<"error";
		cout<<endl<<sqlite3_prepare_v2(database, sql.c_str(), -1, &addStmt, NULL)<<endl;
	}

	int i = 1;
	for(hash_map<string, ModelNode>::iterator it = modelAttributes.begin(); it != modelAttributes.end(); it++){
		if(it->first == metaKey) continue;
		if(modelAttributes[it->first].type == "int") sqlite3_bind_int(addStmt, i, *modelAttributes[it->first].intVal);
		else if(modelAttributes[it->first].type == "string") sqlite3_bind_text(addStmt, i, (const char*)(*modelAttributes[it->first].stringVal).c_str(), -1, SQLITE_TRANSIENT);
		else if(modelAttributes[it->first].type == "double") sqlite3_bind_double(addStmt, i, *modelAttributes[it->first].doubleVal);
		else if(modelAttributes[it->first].type == "int64") sqlite3_bind_int64(addStmt, i, *modelAttributes[it->first].int64Val);
		else if(modelAttributes[it->first].type == "bool"){ 
			if(*modelAttributes[it->first].boolVal) sqlite3_bind_int(addStmt, i, 1);
			else sqlite3_bind_int(addStmt, i, 0);
		}else if(modelAttributes[it->first].type == "model"){
			if(modelAttributes[it->first].model){
				Model *tmpModel = modelAttributes[it->first].model;
				hash_map<string, ModelNode> attr = tmpModel->getModelAttributes();
				
				if(attr[tmpModel->getMetaKey()].type == "int") sqlite3_bind_int(addStmt, i, *attr[tmpModel->getMetaKey()].intVal);
				else if(attr[tmpModel->getMetaKey()].type == "string") sqlite3_bind_text(addStmt, i, (const char *)(*attr[tmpModel->getMetaKey()].stringVal).c_str(), -1, SQLITE_TRANSIENT);
				else if(attr[tmpModel->getMetaKey()].type == "double") sqlite3_bind_double(addStmt, i, *attr[tmpModel->getMetaKey()].doubleVal);
				else if(attr[tmpModel->getMetaKey()].type == "int64") sqlite3_bind_int64(addStmt, i, *attr[tmpModel->getMetaKey()].int64Val);
				else if(attr[tmpModel->getMetaKey()].type == "bool"){ 
					if(attr[tmpModel->getMetaKey()].boolVal) sqlite3_bind_int(addStmt, i, 1);
					else sqlite3_bind_int(addStmt, i, 0);
				}
			}
		}
		i++;
	}

	cout<<endl<<sqlite3_sql(addStmt)<<endl;

	if(SQLITE_DONE != sqlite3_step(addStmt)){
	
	}else{
		if(modelAttributes[metaKey].type == "int") *modelAttributes[metaKey].intVal = sqlite3_last_insert_rowid(database);
		else if(modelAttributes[metaKey].type == "string") *modelAttributes[metaKey].stringVal = (char *)sqlite3_last_insert_rowid(database);
		else if(modelAttributes[metaKey].type == "double") *modelAttributes[metaKey].doubleVal = sqlite3_last_insert_rowid(database);
		else if(modelAttributes[metaKey].type == "int64") *modelAttributes[metaKey].int64Val = sqlite3_last_insert_rowid(database);
		else if(modelAttributes[metaKey].type == "bool"){ 
			if(sqlite3_last_insert_rowid(database)) *modelAttributes[metaKey].boolVal = true;
			else *modelAttributes[metaKey].intVal = false;
		}
	}

	sqlite3_finalize(addStmt);
};

void Model::update() {
	string sql = "INSERT OR REPLACE INTO ";
	sql.append(metaTableName);
	sql.append(" ( ");
	string columns = "";
	string values = "";

	for(hash_map<string, ModelNode>::iterator it = modelAttributes.begin(); it != modelAttributes.end(); it++){
		if(columns != "") columns.append(", ");
		columns.append(it->first);
		if(values != "") values.append(", ");
		values.append("?");
	}

	sql.append(columns);
	sql.append(" ) VALUES ( ");
	sql.append(values);
	sql.append(" ) ");

	if(sqlite3_prepare_v2(database, sql.c_str(), -1, &updateStmt, NULL) != SQLITE_OK){
		//error
	}

	int i = 1;
	for(hash_map<string, ModelNode>::iterator it = modelAttributes.begin(); it != modelAttributes.end(); it++){
		if(modelAttributes[it->first].type == "int") sqlite3_bind_int(updateStmt, i, *modelAttributes[it->first].intVal);
		else if(modelAttributes[it->first].type == "string") sqlite3_bind_text(updateStmt, i, (const char *)(*modelAttributes[it->first].stringVal).c_str(), -1, SQLITE_TRANSIENT);
		else if(modelAttributes[it->first].type == "double") sqlite3_bind_double(updateStmt, i, *modelAttributes[it->first].doubleVal);
		else if(modelAttributes[it->first].type == "int64") sqlite3_bind_int64(updateStmt, i, *modelAttributes[it->first].int64Val);
		else if(modelAttributes[it->first].type == "bool"){ 
			if(*modelAttributes[it->first].boolVal) sqlite3_bind_int(updateStmt, i, 1);
			else sqlite3_bind_int(updateStmt, i, 0);
		}else if(modelAttributes[it->first].type == "model"){
			if(modelAttributes[it->first].model){
				Model *tmpModel = modelAttributes[it->first].model;
				hash_map<string, ModelNode> attr = tmpModel->getModelAttributes();
				
				if(attr[tmpModel->getMetaKey()].type == "int") {
					sqlite3_bind_int(updateStmt, i, *attr[tmpModel->getMetaKey()].intVal);
					cout<<endl<<*attr[tmpModel->getMetaKey()].intVal<<endl;
					cout<<endl<<tmpModel->getMetaKey()<<endl;
				}
				else if(attr[tmpModel->getMetaKey()].type == "string") sqlite3_bind_text(updateStmt, i, (const char *)(*attr[tmpModel->getMetaKey()].stringVal).c_str(), -1, SQLITE_TRANSIENT);
				else if(attr[tmpModel->getMetaKey()].type == "double") sqlite3_bind_double(updateStmt, i, *attr[tmpModel->getMetaKey()].doubleVal);
				else if(attr[tmpModel->getMetaKey()].type == "int64") sqlite3_bind_int64(updateStmt, i, *attr[tmpModel->getMetaKey()].int64Val);
				else if(attr[tmpModel->getMetaKey()].type == "bool"){ 
					if(attr[tmpModel->getMetaKey()].boolVal) sqlite3_bind_int(updateStmt, i, 1);
					else sqlite3_bind_int(updateStmt, i, 0);
				}
			}
		}
		i++;
	}

	cout<<endl<<sqlite3_sql(updateStmt)<<endl;

	if(SQLITE_DONE != sqlite3_step(updateStmt)){
	
	}else{
		if(!primaryKeyExits()){
			if(modelAttributes[metaKey].type == "int") *modelAttributes[metaKey].intVal = sqlite3_last_insert_rowid(database);
			else if(modelAttributes[metaKey].type == "string") *modelAttributes[metaKey].stringVal = sqlite3_last_insert_rowid(database);
			else if(modelAttributes[metaKey].type == "double") *modelAttributes[metaKey].doubleVal = sqlite3_last_insert_rowid(database);
			else if(modelAttributes[metaKey].type == "int64") *modelAttributes[metaKey].int64Val = sqlite3_last_insert_rowid(database);
			else if(modelAttributes[metaKey].type == "bool"){ 
				if(sqlite3_last_insert_rowid(database)) *modelAttributes[metaKey].boolVal = true;
				else *modelAttributes[metaKey].intVal = false;
			}
		}
	}

	sqlite3_finalize(updateStmt);
}

void Model::remove(){
	string sql = "DELETE FROM ";
	sql.append(metaTableName);
	sql.append(" WHERE ");
	sql.append(metaKey);
	sql.append(" = ?");

	if(sqlite3_prepare_v2(database, sql.c_str(), -1, &deleteStmt, NULL) != SQLITE_OK){
		//error
	}

	if(modelAttributes[metaKey].type == "int") sqlite3_bind_int(deleteStmt, 1, *modelAttributes[metaKey].intVal);
	else if(modelAttributes[metaKey].type == "string") sqlite3_bind_text(deleteStmt, 1, (const char *)(*modelAttributes[metaKey].stringVal).c_str(), -1, SQLITE_TRANSIENT);
	else if(modelAttributes[metaKey].type == "double") sqlite3_bind_double(deleteStmt, 1, *modelAttributes[metaKey].doubleVal);
	else if(modelAttributes[metaKey].type == "int64") sqlite3_bind_int64(deleteStmt, 1, *modelAttributes[metaKey].int64Val);
	else if(modelAttributes[metaKey].type == "bool"){ 
		if(modelAttributes[metaKey].boolVal) sqlite3_bind_int(deleteStmt, 1, 1);
		else sqlite3_bind_int(deleteStmt, 1, 0);
	}

	if(SQLITE_DONE != sqlite3_step(deleteStmt)){
		//error
	}

	sqlite3_finalize(deleteStmt);
}

void Model::refresh(){
	if(primaryKeyExits())
		loadID();
}

void Model::bindModelAttribute(string _key, int &val) {
	ModelNode node;
	node.intVal = &val;
	node.type = "int";
	modelAttributes[_key] = node;
}

void Model::bindModelAttribute(string _key, double &val) {
	ModelNode node;
	node.doubleVal = &val;
	node.type = "double";
	modelAttributes[_key] = node;
}

void Model::bindModelAttribute(string _key, string &val) {
	ModelNode node;
	node.stringVal = &val;
	node.type = "string";
	modelAttributes[_key] = node;
}

void Model::bindModelAttribute(string _key, int64 &val) {
	ModelNode node;
	node.int64Val = &val;
	node.type = "int64";
	modelAttributes[_key] = node;
}

void Model::bindModelAttribute(string _key, bool &val) {
	ModelNode node;
	node.boolVal = &val;
	node.type = "bool";
	modelAttributes[_key] = node;
}

void Model::bindModelAttribute(string _key, Model *val) {
	ModelNode node;
	node.model = val;
	node.type = "model";
	node.table = "";
	modelAttributes[_key] = node;
}

void Model::bindModelAttribute(string _key, Model *val, string _table) {
	ModelNode node;
	node.model = val;
	node.type = "model";
	node.table = _table;
	modelAttributes[_key] = node;
}

void Model::setModelMetaKey(string _key){
	metaKey = _key;
}

void Model::setModelMetaTableName(string _table){
	metaTableName = _table;
}

void Model::prepareModel(){
	modelMeta();
}

bool Model::primaryKeyExits(){
	if(modelAttributes[metaKey].type == "int"){
		if(*modelAttributes[metaKey].intVal) return true;
		else return false;
	}else if(modelAttributes[metaKey].type == "int64"){
		if(*modelAttributes[metaKey].int64Val) return true;
		else return false;
	}else if(modelAttributes[metaKey].type == "string"){
		if(*modelAttributes[metaKey].stringVal == "") return false;
		else return true;
	}
}