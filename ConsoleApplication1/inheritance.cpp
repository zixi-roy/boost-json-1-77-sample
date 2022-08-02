#include "inheritance.h"

void tag_invoke(boost::json::value_from_tag, boost::json::value& v, TheForeFather const& wrap)
{
	v = {
		{"member", wrap.m_member}
	};
}


TheForeFather tag_invoke(boost::json::value_to_tag<TheForeFather>, boost::json::value const& v)
{	//	Might throw, don't care, not the issue.
	return TheForeFather(boost::json::value_to<char>(v.as_object().at("member")));	
}

void tag_invoke(boost::json::value_from_tag dummy, boost::json::value& v, TheNextFather const& wrap)
{
	tag_invoke(dummy, v, (TheForeFather const&)wrap);
	v.as_object()["prodigy"] = wrap.m_prodigy;
}

TheNextFather tag_invoke(boost::json::value_to_tag<TheNextFather>, boost::json::value const& v) 
{//	Might throw, don't care, not the issue.
	return TheNextFather(boost::json::value_to<TheForeFather>(v), boost::json::value_to<unsigned char>(v.as_object().at("prodigy")));
}


