#include "http.h"

int32 GlobalResponseReceived(void* caller, Http* data){
	CIwGameHttpRequest* request = (CIwGameHttpRequest*)caller;
	
	int error = request->getError();

	if(error != 0){
		IW_GAME_HTTP_MANAGER->RemoveRequest(request);
		data->receivedHTTPError(error);
		return 0;
	}

    if (request->getProcessed())                                    // Check to see if our request was processed by the http manager
    {
        IW_GAME_HTTP_MANAGER->RemoveRequest(request);                // Remove request from http manager queue

		CIwGameString cIResponse = request->getContent();
		char *ptr = cIResponse.GetCharPtr();
		int length = request->getContentLength();
		if(length < strlen(ptr)){
			ptr[length] = '\0';
		}
		
		data->setResponseBody(ptr);
		data->setStatus(COMPLETE);
		data->receivedHTTPResponse();
	}else{
		data->receivedHTTPError(-101);
	}

	return 0;
}

void Http::sendHTTPRequest(){
	status = SENDING;
	CIwGameHttpRequest* Request = new CIwGameHttpRequest();
	if(type == 1) Request->setPOST();
	else Request->setGET();
	Request->setBody(requestBody.c_str());
	Request->setURI(requestURL.c_str());
	Request->SetHeader("User-Agent", IW_GAME_HTTP_MANAGER->getUserAgent().c_str());
	Request->SetHeader("Content-Type", "application/x-www-form-urlencoded");
	Request->SetHeader("Content-Length", CIwGameString(Request->getBody().GetLength()).c_str());

	Request->setContentAvailableCallback((CIwGameCallback)&GlobalResponseReceived, (void*)this);
	IW_GAME_HTTP_MANAGER->AddRequest(Request);
	IW_GAME_HTTP_MANAGER->Update();

	if(sync){
		while(status == SENDING){
			s3eDeviceYield(30);
			IW_GAME_HTTP_MANAGER->Update();
		}
	}
}