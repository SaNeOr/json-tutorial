#include<cassert>


#include"leptjson.h"


#define EXPECT(c, ch)  do { assert(*c.json == (ch)); c.json++; } while(0) //如果第一个字母不是'n' 说明是参数问题....直接令程序崩溃 

struct lept_context
{
	const char* json; //底层 指针
};

static void lept_parse_whitespace(lept_context &c)
{
	const char*p = c.json;
	while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
		p++;
	c.json = p;
}



static int lept_parse_null(lept_context&c, lept_value &v)
{
	EXPECT(c, 'n');
	if (c.json[0] != 'u' || c.json[1] != 'l' || c.json[2] != 'l')
		return LEPT_PARSE_INVALID_VALUE;
	c.json += 3;	//已经结束了对"null"的parse

	/*
	lept_parse_whitespace(c);	//JSON-text =  ws value ws   这里处理value后面的ws
	if (c.json[0])
		return LEPT_PARSE_ROOT_NOT_SINGULAR;
	*/

	v.type = lept_type::LNULL;
	return LEPT_PARSE_OK;
	
}

static int lept_parse_true(lept_context &c, lept_value &v)
{
	EXPECT(c, 't');
	if (c.json[0] != 'r' || c.json[1] != 'u' || c.json[2] != 'e')
		return LEPT_PARSE_INVALID_VALUE;
	c.json += 3;
	/*lept_parse_whitespace(c);
	if (c.json[0])
		return LEPT_PARSE_INVALID_VALUE;*/
	
	v.type = lept_type::TRUE;
	return LEPT_PARSE_OK;	
}

static int lept_parse_false(lept_context &c, lept_value &v)
{
	EXPECT(c, 'f');
	if (c.json[0] != 'a' || c.json[1] != 'l' || c.json[2] != 's' || c.json[3] != 'e')
		return LEPT_PARSE_INVALID_VALUE;
	c.json += 4;

	/*lept_parse_whitespace(c);
	if (c.json[0])
		return LEPT_PARSE_ROOT_NOT_SINGULAR;*/
	v.type = lept_type::FALSE;

	return LEPT_PARSE_OK;
}

static int lept_parse_value(lept_context &c, lept_value& v)
{
	switch (*(&c)->json)  // *(&c)->json 取的是jason第一个字符的内容
	{
	case'n':return lept_parse_null(c, v);
	case't':return lept_parse_true(c, v);
	case'f':return lept_parse_false(c, v);


	case'\0':return LEPT_PARSE_EXECPT_VALUE;	
	default:return LEPT_PARSE_INVALID_VALUE;
	}

}

//////////////////////////////////////////////////////////////
int  lept_parse(lept_value &v, const char *json)
{
	lept_context c;

	int ret;

	assert(&v != NULL);
	c.json = json;
	//v.type = lept_type::LNULL;
	lept_parse_whitespace(c);
	if (ret = lept_parse_value(c, v) == LEPT_PARSE_OK)
	{
		lept_parse_whitespace(c);
		if (c.json[0] != '\0')
			ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
	}
	return ret;

}

lept_type lept_get_type(const lept_value& v) {
	assert(&v != NULL);
	return v.type;
}
