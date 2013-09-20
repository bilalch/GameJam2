/*
 *  connectionManager.h
 *  ArmyCitiesSQLite
 *
 *  Created by frt on 9/29/11.
 *  Copyright 2011 Fiverivers Technologies. All rights reserved.
 *
 */
/*************************************************************************
 ** This class is responsable for opening and closing Database connection.
 ** This class acts as a signleton so rather than creating a new object, 
 ** always get a connection through getConnection static method.
 ** This class is used by model interface meaning that every DB model class
 ** has an open connection available.
 */

#define DB_NAME "game.sqlite"

#include "sqlite3.h"

#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

class ConnectionManager {
public:
	ConnectionManager();
	~ConnectionManager();
	static ConnectionManager * getConnection();
	sqlite3 * getDatabase();
	sqlite3_stmt * getAddStmt();
	sqlite3_stmt * getDeleteStmt();
	sqlite3_stmt * getLoadStmt();
	sqlite3_stmt * getUpdateStmt();
	void close();

private:
	sqlite3 *database;
	sqlite3_stmt *deleteStmt;
	sqlite3_stmt *addStmt;
	sqlite3_stmt *loadStmt;
	sqlite3_stmt *updateStmt;
	static ConnectionManager *_connectionManager;
	bool openConnection();
};

#endif