#include "http_helper.h"

int32 GlobalResponseReceived(void* caller, Http* data);

HttpHelper * HttpHelper::_httpHelper = NULL;

HttpHelper::HttpHelper(){
	prepareHttp();
}

HttpHelper::~HttpHelper(){

}

HttpHelper * HttpHelper::getHttpHelper(){
	if(!_httpHelper)
		_httpHelper = new HttpHelper();

	return _httpHelper;
}

void HttpHelper::destroyHttpHelper(){
	if(_httpHelper)
		delete _httpHelper;

	_httpHelper = NULL;
}

void HttpHelper::send_http_request(string _url, string _body, bool _get, bool _sync){
	setStatus(SENDING);
	CIwGameHttpRequest* Request = new CIwGameHttpRequest();
	if(!_get) Request->setPOST();
	else Request->setGET();
	Request->setBody(_body.c_str());
	Request->setURI(_url.c_str());
	Request->SetHeader("User-Agent", IW_GAME_HTTP_MANAGER->getUserAgent().c_str());
	Request->SetHeader("Content-Type", "application/x-www-form-urlencoded");
	Request->SetHeader("Content-Length", CIwGameString(Request->getBody().GetLength()).c_str());

	Request->setContentAvailableCallback((CIwGameCallback)&GlobalResponseReceived, (void*)this);
	IW_GAME_HTTP_MANAGER->AddRequest(Request);
	IW_GAME_HTTP_MANAGER->Update();

	if(_sync){
		while(getStatus() == SENDING){
			s3eDeviceYield(30);
			IW_GAME_HTTP_MANAGER->Update();
		}
	}
}

void HttpHelper::fetch_remote_list(string _listKey, AeDynArray<JsonParser *> &_array, string _queryString, bool _sync){
	Http *httpObj = (Http *)JSON_FACTORY->createJsonObject(_listKey);
	string url = httpObj->getBaseURL();
	url.append(httpObj->getMetaListURL());
	delete httpObj;
	setRequestURL(url);
	string body = _queryString;
	setRequestBody(body);
	setGET();
	if(_sync) setSynchronous();
	else setASynchronous();
	sendHTTPRequest();
	JsonParser::json_decode(_array, _listKey, getResponseBody());
}

void HttpHelper::receivedHTTPError(int error){

}

void HttpHelper::receivedHTTPResponse(){
	cout<<endl<<getResponseBody()<<endl;
}

void HttpHelper::httpMeta(){

}