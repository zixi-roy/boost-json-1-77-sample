#include "common.h"
#include <algorithm>
#include <sstream>

complex::complex(std::string const& name,
	std::vector<simple> const& vals,
	std::map<int, int> const& more_vals) :
	complex_name(name),
	vector_values(vals),
	map_values(more_vals) {}

bool complex::operator==(const complex& o) const {
	bool r = complex_name.compare(o.complex_name) == 0;
	if (r)  r = std::equal(o.vector_values.begin(), o.vector_values.end(), vector_values.begin());
	if (r) r = std::equal(map_values.begin(), map_values.end(), o.map_values.begin());
	return r;
}


void tag_invoke(boost::json::value_from_tag, boost::json::value& v, complex const& wrap) {
	v = {
			{ "name_complex"  , wrap.complex_name},
			{ "vector_values" , wrap.vector_values},
			{ "map_values", wrap.map_values}
	};
}
complex tag_invoke(boost::json::value_to_tag<complex>, boost::json::value const& v) {
	std::vector<simple> vec;
	std::map<int, int> ma;

	boost::json::error_code ec;
	std::string str;
	extract(v.as_object(), str, std::string("name_complex"), ec);
	if (ec) {
		return complex("ERROR-1", vec, ma);
	}
	extract(v.as_object(), vec, std::string("vector_values"), ec);
	if (ec) {
		return complex("ERROR-2", vec, ma);
	}
	extract(v.as_object(), ma, std::string("map_values"), ec);
	if (ec) {
		return complex("ERROR-3", vec, ma);
	}

	return complex(str, vec, ma);
}


std::string get_complex_json() {
	return "{\"name_complex\":\"ACOMPLEX\",\"vector_values\":[{\"name_key\":\"name_1\",\"value_key\":0},{\"name_key\":\"name_2\",\"value_key\":10},{\"name_key\":\"name_3\",\"value_key\":20},{\"name_key\":\"name_4\",\"value_key\":30},{\"name_key\":\"name_5\",\"value_key\":40}],\"map_values\":[[5,0],[6,777],[7,1554],[8,2331],[9,3108]]}";
}
complex get_complex_obj() {
	std::vector<simple> vec;
	std::map<int, int> ma;
	for (int i = 0; i < 5; ++i) {
		std::ostringstream ss;
		ss << "name_" << i + 1;
		simple s(ss.str(), i * 10);
		vec.push_back(s);
		ma.insert(std::make_pair(i + 5, i * 777));
	}
	 return complex ("ACOMPLEX", vec, ma);
}
