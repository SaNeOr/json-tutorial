#ifndef LEPTJSON_H__
#define LEPTJSON_H__


enum class lept_type { LNULL, FALSE, TRUE, NUMBER, STRING, ARRAY, OBJECT }; //JSON_ALL_TYPES


struct lept_value
{
	lept_type type;
};

enum
{
	LEPT_PARSE_OK = 0,
	LEPT_PARSE_EXECPT_VALUE,		//若一个 JSON 只含有空白
	LEPT_PARSE_INVALID_VALUE,			//既不是空白 也不是含有其它字符
	LEPT_PARSE_ROOT_NOT_SINGULAR	// 若一个值之后，在空白之后还有其他字符
};


int lept_parse(lept_value &v, const char *json); // equlity a json if ok
lept_type lept_get_type(const lept_value& v); //parse lept_value is what lept_type



#endif // !LEPTJSON_H__
