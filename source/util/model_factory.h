/*
 *  model_factory.h
 *  ArmyCitiesSQLite
 *
 *  Created by frt on 9/29/11.
 *  Copyright 2011 Fiverivers Technologies. All rights reserved.
 *
 */
/*************************************************************************
 ** This header file defines a factory for creating objects which implement model interface
 */

#ifndef MODEL_FACTORY_H
#define MODEL_FACTORY_H

#include <string>
#include "dynamicArray.h"

using namespace std;

class Model;

#define MODEL_FACTORY	ModelFactory::getModelFactory()

class ModelFactory {
public:
	~ModelFactory();
	static ModelFactory * getModelFactory();
	static void destroyModelFactory();
	Model * createModelObject(string _type);
private:
	static ModelFactory *_modelFactory;
	ModelFactory();
};

#endif