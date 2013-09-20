#include "json_factory.h"
#include "..\tests\test_http.h"
#include "..\models\in_app.h"
#include "..\models\powers.h"

JsonFactory * JsonFactory::_jsonFactory = NULL;

JsonFactory::JsonFactory(){

}

JsonFactory::~JsonFactory(){

}

JsonFactory * JsonFactory::getJsonFactory(){
	if(!_jsonFactory)
		_jsonFactory = new JsonFactory();

	return _jsonFactory;
}

void JsonFactory::destroyJsonFactory(){
	if(_jsonFactory)
		delete _jsonFactory;

	_jsonFactory = NULL;
}

JsonParser * JsonFactory::createJsonObject(string _type){
	if(_type == "test_https"){
		return new HttpTest();
	}else if(_type == "in_app"){
		return new InAppModel();
	}else if(_type == "powers"){
		return new PowersModel();
	}
}