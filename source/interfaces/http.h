/*
 *  http.h
 *  ArmyCitiesSQLite
 *
 *  Created by frt on 9/29/11.
 *  Copyright 2011 Fiverivers Technologies. All rights reserved.
 *
 */
/*************************************************************************
 ** This header file defines interface for http operations.
 ** Each remote class should implement this interface
 */

#ifndef HTTP_INTERFACE
#define HTTP_INTERFACE

#include <string>
#include <iostream>
#include "IwGameHttp.h"
#include "json_parser.h"

using namespace std;

enum RequestStatus{
	SENDING,
	COMPLETE,
};

class Http : public JsonParser {
public:
	Http(){
		baseURL = "";
		type = 1;
		sync = false;
		metaName = "";
		metaListKey = "";
	};

	virtual ~Http(){
		
	};

	virtual string getMetaListURL() { return metaListUrl; }
	virtual RequestStatus getStatus() { return status; }
	virtual void setStatus(RequestStatus _status) { status = _status; }
	virtual bool getPOST() { return type == 1; }
	virtual bool getGET() { return type == 2; }
	virtual void setPOST() { type = 1; }
	virtual void setGET() { type = 2; }
	virtual bool getSynchronous() { return sync; }
	virtual bool getASynchronous() { return sync; }
	virtual void setSynchronous() { sync = true; }
	virtual void setASynchronous() { sync = false; }
	virtual string getBaseURL() { return baseURL; }
	virtual void setBaseURL(string _url) { baseURL = _url; }
	virtual void setRequestURL(string URL) { requestURL = URL; }
	virtual string getRequestURL() { return requestURL; }
	virtual void setRequestBody(string _body) { requestBody = _body; }
	virtual string getRequestBody() { return requestBody; }
	virtual string getResponseBody() { return responseBody; }
	virtual void setResponseBody(string _response) { responseBody = _response; }
	virtual void sendHTTPRequest();

	virtual void remoteHTTPSave(bool _sync = true){
		string body = metaName;
		body.append("=");
		body.append(jsonEncode());

		string url = getBaseURL();
		url.append(getMetaSaveURL());

		setRequestBody(body);
		setRequestURL(url);
		setPOST();
		if(_sync) setSynchronous();
		else setASynchronous();
		sendHTTPRequest();
	}

	virtual void remoteHTTPUpdate(bool _sync = true) {
		string body = metaUpdateKey;
		body.append("=");
		body.append((string)getJsonAttributeForKey(metaUpdateKey));
		setRequestBody(body);
		cout<<endl<<body<<endl;
		string url = getBaseURL();
		url.append(getMetaUpdateURL());

		setRequestURL(url);
		setGET();
		if(_sync) setSynchronous();
		else setASynchronous();
		sendHTTPRequest();
		jsonDecode(getResponseBody());
	}

	virtual string getMetaListKey() { return metaListKey; }

	//callbacks
	virtual void receivedHTTPResponse() = 0;
	virtual void receivedHTTPError(int error) { /*error received*/ };

protected:
	virtual void prepareHttp() { httpMeta(); setJsonMetaName(metaName); }
	virtual string getMetaName() { return metaName; }
	virtual void setMetaName(string _name) { metaName = _name; }
	virtual void setMetaListKey(string _key) { metaListKey = _key; }
	virtual void setMetaListURL(string _url) { metaListUrl = _url; }
	virtual string getMetaSaveURL() { return metaSaveUrl; }
	virtual void setMetaSaveURL(string _url) { metaSaveUrl = _url; }
	virtual string getMetaUpdateURL() { return metaUpdateUrl; }
	virtual void setMetaUpdateURL(string _url) { metaUpdateUrl = _url; }
	virtual string getMetaUpdateKey() { return metaUpdateKey; }
	virtual void setMetaUpdateKey(string _key) { metaUpdateKey = _key; }
	virtual void httpMeta() = 0;

private:
	string requestURL;
	string requestBody;
	string responseBody;
	string baseURL;
	RequestStatus status;
	int type;
	bool sync;
	string metaName;
	string metaSaveUrl;
	string metaUpdateUrl;
	string metaListUrl;
	string metaUpdateKey;
	string metaListKey;
};

#endif