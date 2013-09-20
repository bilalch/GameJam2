/*
 *  json_parser.h
 *  ArmyCitiesSQLite
 *
 *  Created by frt on 9/29/11.
 *  Copyright 2011 Fiverivers Technologies. All rights reserved.
 *
 */
/*************************************************************************
 ** This header file defines interface for parsing operations.
 ** Each class which requires parsing should implement this interface
 */

#ifndef JSON_PARSING_INTERFACE
#define JSON_PARSING_INTERFACE

#include <string>
#include <iostream>
#include <sstream>
#include <json\json.h>
#include <hash_map>
#include "dynamicArray.h"
#include <sstream>
#include "json_factory.h"

using namespace std;

class JsonParser;

struct JsonNode{
	string type;
	int *intVal;
	double *doubleVal;
	string *stringVal;
	int64 *int64Val;
	bool *boolVal;
	AeDynArray<JsonParser *> *jsonArray;

	operator string(){
		stringstream ss;
		if(type == "int") ss << *intVal;
		else if(type == "string") ss << *stringVal;
		else if(type == "double") ss << *doubleVal;
		else if(type == "int64") ss << *int64Val;
		else if(type == "bool") ss << *boolVal;
		return ss.str();
	}

	operator int(){
		int ret;
		if(type == "int") ret = *intVal;
		else if(type == "string") ret = atoi((*stringVal).c_str());
		else if(type == "double") ret = *doubleVal;
		else if(type == "int64") ret = *int64Val;
		else if(type == "bool") ret = *boolVal;
		return ret;
	}

	operator int64(){
		int64 ret;
		if(type == "int") ret = *intVal;
		else if(type == "string") ret = atoi((*stringVal).c_str());
		else if(type == "double") ret = *doubleVal;
		else if(type == "int64") ret = *int64Val;
		else if(type == "bool") ret = *boolVal;
		return ret;
	}

	operator double(){
		double ret;
		if(type == "int") ret = *intVal;
		else if(type == "string") ret = atof((*stringVal).c_str());
		else if(type == "double") ret = *doubleVal;
		else if(type == "int64") ret = *int64Val;
		else if(type == "bool") ret = *boolVal;
		return ret;
	}

	operator bool(){
		bool ret;
		if(type == "int") ret = *intVal;
		else if(type == "string") ret = *stringVal == "true";
		else if(type == "double") ret = *doubleVal;
		else if(type == "int64") ret = *int64Val;
		else if(type == "bool") ret = *boolVal;
		return ret;
	}
};

class JsonParser {
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

		decodeTraversing(root);
	}

	virtual void jsonDecode(Json::Value node){
		decodeTraversing(node);
	}

	static void json_decode(AeDynArray<JsonParser *> &dynArray, string _key, string _jsonString){
		Json::Value root;
		Json::Reader reader;
		bool parsingSuccessful = reader.parse( _jsonString, root );
		
		//if(_key != "") root = root[_key];

		for(int i = 0; i < root.size(); i++){
			JsonParser *newParser = JSON_FACTORY->createJsonObject(_key);
			newParser->jsonDecode(root[i]);
			dynArray.Add(newParser);
		}
	}

protected:
	virtual void decodeTraversing(Json::Value node){
		for(hash_map<string, JsonNode>::iterator it = jsonAttributes.begin(); it != jsonAttributes.end(); it++){
			if(it->second.type == "int" && node.isMember(it->first)) *it->second.intVal = node.get(it->first, 0).asInt();
			else if(it->second.type == "string" && node.isMember(it->first))*it->second.stringVal = node.get(it->first, "").asString();
			else if(it->second.type == "double" && node.isMember(it->first)) *it->second.doubleVal = node.get(it->first, 0).asDouble();
			else if(it->second.type == "int64" && node.isMember(it->first)) *it->second.int64Val = node.get(it->first, 0).asInt64();
			else if(it->second.type == "bool" && node.isMember(it->first)) *it->second.boolVal = node.get(it->first, 0).asBool();
			else if(it->second.type == "array" && node.isMember(it->first)){
				for(int i = 0; i < node[it->first].size(); i++){
					JsonParser *newParser = JSON_FACTORY->createJsonObject(getJsonMetaName());
					newParser->jsonDecode(node[it->first][i]);
				}
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

	string getJsonMetaName() { return jsonMetaName; };
	void setJsonMetaName(string _name) { jsonMetaName = _name; };

private:
	hash_map<string, JsonNode> jsonAttributes;
	string jsonMetaName;
};

#endif