/*
 *  connectionManager.cpp
 *  ArmyCitiesSQLite
 *
 *  Created by frt on 9/29/11.
 *  Copyright 2011 Fiverivers Technologies. All rights reserved.
 *
 */

#include "connectionManager.h"
#include <iostream.h>

ConnectionManager * ConnectionManager::_connectionManager = 0;

#pragma mark -
#pragma mark Constructor

ConnectionManager::ConnectionManager(){
	database = 0;
	deleteStmt = 0;
	addStmt = 0;
	loadStmt = 0;
	updateStmt = 0;
}

#pragma mark -
#pragma mark Destructor

ConnectionManager::~ConnectionManager(){
	_connectionManager = NULL;
}

#pragma mark -
#pragma mark Getters

ConnectionManager * ConnectionManager::getConnection(){
	if(!_connectionManager){
		_connectionManager = new ConnectionManager();
		_connectionManager->openConnection();
	}
	
	return _connectionManager;
}

sqlite3 * ConnectionManager::getDatabase(){
	return database;
}

sqlite3_stmt * ConnectionManager::getAddStmt(){
	return addStmt;
}

sqlite3_stmt * ConnectionManager::getDeleteStmt(){
	return deleteStmt;
}

sqlite3_stmt * ConnectionManager::getLoadStmt(){
	return loadStmt;
}

sqlite3_stmt * ConnectionManager::getUpdateStmt(){
	return updateStmt;
}

#pragma mark -
#pragma mark Open connection

bool ConnectionManager::openConnection(){
	
	if (sqlite3_open(DB_NAME, &database) == SQLITE_OK) {
		sqlite3_exec(database, "PRAGMA JOURNAL_MODE=OFF;", NULL, NULL, NULL);
		return true;
	}
	
	return false;
}

#pragma mark -
#pragma mark Close connection

void ConnectionManager::close(){
	sqlite3_close(database);
	if(_connectionManager)
		delete _connectionManager;
	_connectionManager = NULL;
}