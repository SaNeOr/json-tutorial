#ifndef LEPTJSON_H__
#define LEPTJSON_H__


enum class lept_type { LNULL, FALSE, TRUE, NUMBER, STRING, ARRAY, OBJECT }; //JSON_ALL_TYPES


struct lept_value
{
	union {
		struct { char *s; size_t len; };
		double n;//json number
	};
	lept_type type;

};


enum
{
	LEPT_PARSE_OK = 0,				//parse ok
	LEPT_PARSE_EXECPT_VALUE,		//若一个 JSON 只含有空白
	LEPT_PARSE_INVALID_VALUE,			//既不是空白 也不是含有其它字符
	LEPT_PARSE_ROOT_NOT_SINGULAR,	// 若一个值之后，在空白之后还有其他字符
	LEPT_PARSE_NUMBER_TOO_BIG,	//数字太大了
	LEPT_PARSE_MISS_QUOTATION_MARK, //引号问题
};

// is json right? 
int lept_parse(lept_value &v, const char *json);


//parse lept_value is what lept_type
lept_type lept_get_type(const lept_value &v);

double lept_get_number(const lept_value &v);

//获得lept.string
char *lept_get_string(const lept_value &v);

//获得lept.string_length
int lept_get_string_length(const lept_value &v);




#include<cstring>
#include<cassert>

void lept_set_string(lept_value &v, const char* s, size_t len);

void lept_free(lept_value &v);

#define lept_init(v) do{ v.type = lept_type::LNULL; }while(0)


#endif // !LEPTJSON_H__
