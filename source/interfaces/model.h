/*
 *  model.h
 *  ArmyCitiesSQLite
 *
 *  Created by frt on 9/29/11.
 *  Copyright 2011 Fiverivers Technologies. All rights reserved.
 *
 */
/*************************************************************************
 ** This header file defines interface for Database operations.
 ** Each DB model class should implement this interface
 */

#ifndef MODEL_INTERFACE
#define MODEL_INTERFACE

#include "ConnectionManager.h"
#include "sqlite3.h"
#include "dynamicArray.h"
#include <string>
#include <iostream>
#include <hash_map>

using namespace std;

class Model;

struct ModelNode{
	string type;
	int *intVal;
	double *doubleVal;
	string *stringVal;
	int64 *int64Val;
	bool *boolVal;
	Model *model;
	string table;
};

class Model {
public:
	Model();
	virtual ~Model();

	virtual void load(AeDynArray<Model *> &dynArray, string where = "1");
	virtual void loadID();
	virtual void save();
	virtual void insert();
	virtual void update();
	virtual void remove();
	virtual void refresh();
	virtual hash_map<string, ModelNode> getModelAttributes() { return modelAttributes; };
	virtual void modelMeta() = 0;
	virtual string getMetaTableName() { return metaTableName; };
	virtual string getMetaKey() { return metaKey; };
	virtual ModelNode getModelAttributeForKey(string _key) { return modelAttributes[_key]; };
	virtual bool primaryKeyExits();

protected:
	ConnectionManager *connection;
	sqlite3 *database;
	sqlite3_stmt *deleteStmt;
	sqlite3_stmt *addStmt;
	sqlite3_stmt *loadStmt;
	sqlite3_stmt *updateStmt;

	virtual void bindModelAttribute(string _key, int &val);
	virtual void bindModelAttribute(string _key, double &val);
	virtual void bindModelAttribute(string _key, string &val);
	virtual void bindModelAttribute(string _key, int64 &val);
	virtual void bindModelAttribute(string _key, bool &val);
	virtual void bindModelAttribute(string _key, Model *val);
	virtual void bindModelAttribute(string _key, Model *val, string _table);
	virtual void setModelMetaKey(string _key);
	virtual void setModelMetaTableName(string _table);
	void prepareModel();

private:
	string metaKey;
	string metaTableName;
	hash_map<string, ModelNode> modelAttributes;
};

#endif