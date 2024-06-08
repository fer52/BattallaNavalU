// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <iostream>
#include <string>
#include <curl/curl.h>

/**
 * 
 */
class JUEGOBN_API ConnectDB
{
public:
	ConnectDB();
	~ConnectDB();

    // Function to insert data into a table (Firebase Realtime Database)
    bool insert(const std::string& table, const std::string& json_data) {
        std::string url = database_url + "/" + table + ".json?auth=" + auth_token;
        return performRequest(url, json_data, "POST");
    }

    // Function to select data from a table (Firebase Realtime Database)
    std::string select(const std::string& table) {
        std::string url = database_url + "/" + table + ".json?auth=" + auth_token;
        return performRequest(url, "", "GET");
    }


private:
    std::string database_url;
    std::string auth_token;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    bool performRequest(const std::string& url, const std::string& data, const std::string& request_type) {
        CURL* curl;
        CURLcode res;
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            if (request_type == "POST") {
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
            }

            std::string response_string;
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                curl_easy_cleanup(curl);
                curl_global_cleanup();
                return false;
            }

            std::cout << "Response: " << response_string << std::endl;

            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
        return true;
    }

    std::string performRequest(const std::string& url, const std::string& data, const std::string& request_type) {
        CURL* curl;
        CURLcode res;
        std::string response_string;

        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            if (request_type == "POST") {
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
            }

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                response_string = "";
            }

            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
        return response_string;
    }

};
