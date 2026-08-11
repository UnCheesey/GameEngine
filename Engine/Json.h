#pragma once

#include <rapidjson/document.h>
#include <string>

#include "Vector2.h"
#include "Vector3.h"

#define JSON_READ(value, data) json::Read(value, #data, data)

namespace json {
	bool Load(const std::string& filename, rapidjson::Document& document);

	// read json data
	bool Read(const rapidjson::Value& value, const std::string& name, int& data);
	bool Read(const rapidjson::Value& value, const std::string& name, float& data);
	bool Read(const rapidjson::Value& value, const std::string& name, bool& data);
	bool Read(const rapidjson::Value& value, const std::string& name, std::string& data);

	bool Read(const rapidjson::Value& value, const std::string& name, nu::Vector2& data);
	bool Read(const rapidjson::Value& value, const std::string& name, nu::Vector3& data);
}