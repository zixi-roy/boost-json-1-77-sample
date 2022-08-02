#pragma once
#include <string>
#include <boost/json.hpp>
#include <vector>
#include <map>

class simple {
public:
	simple(std::string const& n, int v);

	std::string another_name;
	int			another_value;

	bool operator==(const simple& o) const;

};

class complex {
public:
	complex(std::string const& name, 
		std::vector<simple> const& vals,
		std::map<int, int> const & more_vals);


	bool operator==(const complex& o) const;

	std::string complex_name;
	std::vector<simple>  vector_values;
	std::map<int, int> map_values;
};

template<class T> static void extract(boost::json::object const& obj, T& t, boost::json::string_view key, boost::json::error_code& ec)
{
	auto temp = obj.at(key, ec);
	if (!ec) {
		t = boost::json::value_to<T>(temp);
	}
}

/// <summary>
/// //
/// </summary>
/// <param name=""></param>
/// <param name="v"></param>
/// <param name="wrap"></param>
void tag_invoke(boost::json::value_from_tag, boost::json::value& v, simple const& wrap);
simple tag_invoke(boost::json::value_to_tag<simple>, boost::json::value const& v);

/// <summary>
/// 
/// </summary>
/// <returns></returns>
/// 

std::string get_simple_json();
simple get_simple_obj();



void tag_invoke(boost::json::value_from_tag, boost::json::value& v, complex const& wrap);
complex tag_invoke(boost::json::value_to_tag<complex>, boost::json::value const& v);


std::string get_complex_json();
complex get_complex_obj();
