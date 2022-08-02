#pragma once
#include <boost/json.hpp>

struct TheForeFather {
	char m_member;

	TheForeFather() : m_member('F'){}
	TheForeFather(char a) : m_member(a) {}
};


struct TheNextFather : public TheForeFather {
	unsigned char m_prodigy;
	TheNextFather() : TheForeFather(), m_prodigy(1) {}
	TheNextFather(const TheForeFather& a, unsigned char b) : TheForeFather(a), m_prodigy(b) {}
	TheNextFather(char a, unsigned char b) : TheForeFather(a), m_prodigy(b) {}
};

void tag_invoke(boost::json::value_from_tag, boost::json::value& v, TheForeFather const& wrap);
TheForeFather tag_invoke(boost::json::value_to_tag<TheForeFather>, boost::json::value const& v);

void tag_invoke(boost::json::value_from_tag, boost::json::value& v, TheNextFather const& wrap);
TheNextFather tag_invoke(boost::json::value_to_tag<TheNextFather>, boost::json::value const& v);


