// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectDB.h"

ConnectDB::ConnectDB(const std::string& database_url, const std::string& auth_token): database_url(database_url), auth_token(auth_token) {}

ConnectDB::~ConnectDB()
{
}
