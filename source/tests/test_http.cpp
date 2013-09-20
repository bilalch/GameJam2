#include "test_http.h"

HttpTest::HttpTest(){
	name = "";
	age = 0;
	grade = 0;
	active = true;
	ID = 0;
	prepareHttp();
	prepareModel();
}

HttpTest::~HttpTest(){

}

void HttpTest::httpMeta(){
	bindJsonAttribute("name", name);
	bindJsonAttribute("age", age);
	bindJsonAttribute("grade", grade);
	bindJsonAttribute("active", active);
	bindJsonAttribute("id", ID);
	setMetaName("test_https");
	setMetaListKey("test_https");
	setMetaSaveURL("/test_save.php");
	setMetaUpdateURL("/test_update.php");
	setMetaListURL("/test_array.php");
	setMetaUpdateKey("id");
	setBaseURL("http://localhost:81/test");
}

void HttpTest::receivedHTTPResponse(){
	cout<<endl<<getResponseBody()<<endl;
}

void HttpTest::modelMeta(){
	bindModelAttribute("name", name);
	bindModelAttribute("age", age);
	bindModelAttribute("grade", grade);
	bindModelAttribute("active", active);
	bindModelAttribute("id", ID);
	setModelMetaKey("id");
	setModelMetaTableName("test");
}