/*
 *  json_factory.h
 *  ArmyCitiesSQLite
 *
 *  Created by frt on 9/29/11.
 *  Copyright 2011 Fiverivers Technologies. All rights reserved.
 *
 */
/*************************************************************************
 ** This header file defines an abstract factory for creating objects which implement json interface
 */

#ifndef JSON_FACTORY_H
#define JSON_FACTORY_H

#include <string>
#include "dynamicArray.h"

using namespace std;

class JsonParser;

#define JSON_FACTORY	JsonFactory::getJsonFactory()

class JsonFactory {
public:
	~JsonFactory();
	static JsonFactory * getJsonFactory();
	static void destroyJsonFactory();
	JsonParser * createJsonObject(string _type);
private:
	static JsonFactory *_jsonFactory;
	JsonFactory();
};

#endif