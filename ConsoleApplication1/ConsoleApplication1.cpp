// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>

#include "common.h"

bool string_to_obj(std::string& const json_str, boost::json::value& out) {
	boost::json::stream_parser parser;
	boost::json::error_code ec;
	parser.write(json_str, ec);
	if (ec) {
		return false;
	}
	else {
		parser.finish(ec);
		if (ec)
			return false;

		out = parser.release();
		
		return true;
	}
	return false;
}

void simple_test() {
	std::string common_json = get_simple_json();
	simple s = get_simple_obj();
	boost::json::value v_from = boost::json::value_from(s);
	std::string s_string = boost::json::serialize(v_from);

	if (s_string.compare(common_json) != 0) {
		std::cout << "Failed \n " << common_json << "\n" << s_string << "\n";
	} else {
		std::cout << "String same \n===============\n" << s_string << "\n==============\n";
	}

	boost::json::value v;
	if (string_to_obj(common_json, v)) {
		simple parsed = boost::json::value_to<simple>(v);
		if (parsed == s) {
			std::cout << "simple objs ==\n";
		} else {
			std::cout << "simple objs !=\n";
		}
	} else {
		std::cout << "Failed to parse json object from " << common_json << "\n";
	}
}

void complex_test() {
	std::string common_json = get_complex_json();
	complex c = get_complex_obj();
	std::string s_string = boost::json::serialize(boost::json::value_from(c));

	if (s_string.compare(common_json) != 0) {
		std::cout << "Failed \n " << common_json << "\n" << s_string << "\n";
	} else {
		std::cout << "String same \n===============\n" << s_string << "\n==============\n";
	}

	boost::json::value v;
	if (string_to_obj(common_json, v)) {
		complex parsed = boost::json::value_to<complex>(v);
		if (parsed == c) {
			std::cout << "complex objs ==\n";
		} else {
			std::cout << "complex objs !=\n";
		}
	} else {
		std::cout << "Failed to parse json object from " << common_json << "\n";
	}
}
int main()
{
	simple_test();
	complex_test();
	return -1;
}

