#ifndef leptjson_h__
#define leptjson_h__

//namespace lept_json {
    enum class lept_type{
        LNULL,
        FALSE,TRUE,
        NUMBER,
        STRING,
        ARRAY,
        OBJECT
    };
//using namespace lept_json;
enum{
    LEPT_PARSE_OK,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR
};

struct lept_value{
    lept_type type;
    
};

int lept_parse(lept_value &v, const char* json);
lept_type lept_get_type(const lept_value& v);

#endif /* leptjson_h__ */
