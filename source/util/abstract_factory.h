/*
 *  abstract_factory.h
 *  ArmyCitiesSQLite
 *
 *  Created by frt on 9/29/11.
 *  Copyright 2011 Fiverivers Technologies. All rights reserved.
 *
 */
/*************************************************************************
 ** This header file defines an abstract factory for creating objects
 ** Each factory class should implement this interface
 */

#ifndef ABSTRACT_FACTORY
#define ABSTRACT_FACTORY

#include <string>

using namespace std;

class AbstractFactory {
public:
	virtual string jsonEncode(){
		Json::Value root;
		Json::Value *cur;
		cur = &root;
		Json::Reader reader;

		for(hash_map<string, JsonNode>::iterator it = jsonAttributes.begin(); it != jsonAttributes.end(); it++){
			if(it->second.type == "int") 
				(*cur)[it->first] = *it->second.intVal;
			else if(it->second.type == "double") 
				(*cur)[it->first] = *it->second.doubleVal;
			else if(it->second.type == "string") 
				(*cur)[it->first] = *it->second.stringVal;
			else if(it->second.type == "int64"){
				stringstream ss;
				ss<<*it->second.int64Val;
				(*cur)[it->first] = ss.str();
			}else if(it->second.type == "bool") 
				(*cur)[it->first] = *it->second.boolVal;
			else if(it->second.type == "array"){
				for(int i = 0; i < it->second.jsonArray->GetSize(); i++){
					(*cur)[it->first][i] = it->second.jsonArray->GetIndex(i)->jsonEncode();
				}
			}
		}

		Json::StyledWriter writer;
		string encodedString = writer.write( root );

		return encodedString;
	}

	virtual void jsonDecode(string _encodedStrong){
		Json::Value root;
		Json::Reader reader;
		bool parsingSuccessful = reader.parse( _encodedStrong, root );

		for(hash_map<string, JsonNode>::iterator it = jsonAttributes.begin(); it != jsonAttributes.end(); it++){
			if(it->second.type == "int") *it->second.intVal = root.get(it->first, 0).asInt();
			else if(it->second.type == "string")*it->second.stringVal = root.get(it->first, "").asString();
			else if(it->second.type == "double") *it->second.doubleVal = root.get(it->first, 0).asDouble();
			else if(it->second.type == "int64") *it->second.int64Val = root.get(it->first, 0).asInt64();
			else if(it->second.type == "bool") *it->second.boolVal = root.get(it->first, 0).asBool();
			else if(it->second.type == "array"){
				for(int i = 0; i < root[it->first].size(); i++){
					(*it->second.jsonArray)[i] =;
					(*it->second.jsonArray)[i]->jsonDecode(root[it->first][i]);
				}
			}
		}
	}

	virtual void jsonDecode(Json::Value node){

		
	}

protected:
	virtual void decodeTraversing(Json::Value node){
		for(hash_map<string, JsonNode>::iterator it = jsonAttributes.begin(); it != jsonAttributes.end(); it++){
			if(it->second.type == "int") *it->second.intVal = node.get(it->first, 0).asInt();
			else if(it->second.type == "string")*it->second.stringVal = node.get(it->first, "").asString();
			else if(it->second.type == "double") *it->second.doubleVal = node.get(it->first, 0).asDouble();
			else if(it->second.type == "int64") *it->second.int64Val = node.get(it->first, 0).asInt64();
			else if(it->second.type == "bool") *it->second.boolVal = node.get(it->first, 0).asBool();
			else if(it->second.type == "array"){
				(*cur)[it->first][i] = it->second.jsonArray->GetIndex(i)->jsonEncode();
			}
		}
	}

	virtual void bindJsonAttribute(string _key, int &val) {
		JsonNode node;
		node.intVal = &val;
		node.type = "int";
		jsonAttributes[_key] = node;
	}

	virtual void bindJsonAttribute(string _key, double &val) {
		JsonNode node;
		node.doubleVal = &val;
		node.type = "double";
		jsonAttributes[_key] = node;
	}

	virtual void bindJsonAttribute(string _key, string &val) {
		JsonNode node;
		node.stringVal = &val;
		node.type = "string";
		jsonAttributes[_key] = node;
	}

	virtual void bindJsonAttribute(string _key, int64 &val) {
		JsonNode node;
		node.int64Val = &val;
		node.type = "int64";
		jsonAttributes[_key] = node;
	}

	virtual void bindJsonAttribute(string _key, bool &val) {
		JsonNode node;
		node.boolVal = &val;
		node.type = "bool";
		jsonAttributes[_key] = node;
	}

	virtual void bindJsonArray(string _key, AeDynArray<JsonParser *> *_jsonArray) {
		JsonNode node;
		node.jsonArray = _jsonArray;
		node.type = "array";
		jsonAttributes[_key] = node;
	}

	virtual JsonNode getJsonAttributeForKey(string _key){
		return jsonAttributes[_key];
	}

private:
	hash_map<string, JsonNode> jsonAttributes;
	meta
};

#endif