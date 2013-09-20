/*
 *  http_helper.h
 *  ArmyCitiesSQLite
 *
 *  Created by frt on 9/29/11.
 *  Copyright 2011 Fiverivers Technologies. All rights reserved.
 *
 */
/*************************************************************************
 ** This header file defines a helper singleton class which derives from http interface.
 */

#ifndef HTTP_HELPER_INTERFACE
#define HTTP_HELPER_INTERFACE

#include "http.h"
#include <string>
#include <iostream>

using namespace std;

#define HTTP_HELPER	HttpHelper::getHttpHelper()

class HttpHelper : public Http {
public:
	~HttpHelper();
	static HttpHelper * getHttpHelper();
	static void destroyHttpHelper();
	void send_http_request(string _url, string _body, bool _get, bool _sync);
	void fetch_remote_list(string _listKey, AeDynArray<JsonParser *> &_array, string _queryString = "", bool _sync = true);
	void httpMeta();

private:
	static HttpHelper *_httpHelper;
	HttpHelper();

	void sendHTTPRequest() { Http::sendHTTPRequest(); }
	void receivedHTTPError(int error);
	void receivedHTTPResponse();
	string getBaseURL() { return getBaseURL(); };
	void setBaseURL(string _url) {};
	void remoteHTTPSave(bool _sync = true) {};
	void remoteHTTPUpdate(bool _sync = true) {};
};

#endif