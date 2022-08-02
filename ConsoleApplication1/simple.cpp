#include "common.h"

std::string get_simple_json() {
	return "{\"name_key\":\"my_name\",\"value_key\":42}";
}

simple get_simple_obj() {
	return simple("my_name", 42);
}


simple::simple(std::string const& n, int v) : another_name(n), another_value(v) {}
bool simple::operator==(const simple& o) const {
	return another_name.compare(o.another_name) == 0 &&
		another_value == o.another_value;
}




void tag_invoke(boost::json::value_from_tag, boost::json::value& v, simple const& wrap) {

	v = { 
			{ "name_key"  , wrap.another_name},
			{ "value_key" , wrap.another_value } 
	};
}

simple tag_invoke(boost::json::value_to_tag<simple> dummy, boost::json::value const& v) {
	
	boost::json::error_code ec;
	std::string str;
	int i;
	extract(v.as_object(), str, std::string("name_key"), ec);
	if (ec) {
		return simple("ERROR", -1);
	}
	extract(v.as_object(), i  , std::string("value_key"), ec);
	if (ec) {
		return simple("ERROR", -2);
	}
	return simple(str, i);
}