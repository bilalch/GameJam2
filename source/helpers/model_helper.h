/*
 *  model_helper.h
 *  ArmyCitiesSQLite
 *
 *  Created by frt on 9/29/11.
 *  Copyright 2011 Fiverivers Technologies. All rights reserved.
 *
 */
/*************************************************************************
 ** This header file defines a helper singleton class which derives from model interface.
 */

#ifndef MODEL_HELPER_INTERFACE
#define MODEL_HELPER_INTERFACE

#include "model.h"
#include <string>
#include <iostream>

using namespace std;

#define MODEL_HELPER	ModelHelper::getModelHelper()

class ModelHelper : public Model {
public:
	~ModelHelper();
	static ModelHelper * getModelHelper();
	static void destroyModelHelper();
	void fetch_list(string _modelMetaKey, AeDynArray<Model *> &_array, string _whereConditions = "1");

private:
	static ModelHelper *_modelHelper;

	ModelHelper();
	void load(AeDynArray<Model *> &dynArray, string where = "1") { Model::load(dynArray, where); };
	void loadID() { Model::loadID(); };
	void save() { Model::save(); };
	void insert() { Model::insert(); };
	void update() { Model::update(); };
	void remove() { Model::remove(); };
	void refresh() { Model::refresh(); };
	void modelMeta() {};
};

#endif