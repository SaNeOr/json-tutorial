#include<iostream>
#include<cstdio>
#include<cstring>



#include"leptjson.h"


static int main_ret = 0; 
static int test_count = 0;
static int test_pass = 0;
#define EXPECT_EQ_BASE(equality,expect, actual, format)\
	do{\
		test_count++;\
		if(equality)\
			test_pass++; \
		else{\
			fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
			main_ret = 1;\
		}\
	}while(0)


#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")


#define TEST_ERROR(error, json)\
	do {\
		lept_value v; \
		EXPECT_EQ_INT(error, lept_parse(v, json)); \
		EXPECT_EQ_INT(lept_type::LNULL, lept_get_type(v)); \
	}while(0)


#define TEST_NUMBER(expect, json)\
	do{\
		lept_value v;\
		EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(v,json));\
		EXPECT_EQ_INT(lept_type::NUMBER, lept_get_type(v));\
		EXPECT_EQ_INT(expect, lept_get_number(v));\
	}while(0)


static void test_parse_null()
{
	lept_value v;
	//v.type = lept_type::TRUE;
	EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(v, "  null  "));//EQ lept_parse if success
	EXPECT_EQ_INT(lept_type::LNULL, lept_get_type(v));	//EQ the v.type if == LNULL
}

static void test_parse_true()
{
	lept_value v;
	
	EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(v, " true  "));
	EXPECT_EQ_INT(lept_type::TRUE, lept_get_type(v));


}

static void test_parse_false()
{
	lept_value v;
	EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(v, "  false  "));
	EXPECT_EQ_INT(lept_type::FALSE, lept_get_type(v));

}

static void test_parse_except_value()
{
	TEST_ERROR(LEPT_PARSE_EXECPT_VALUE, "");
}


static void test_parse_invalid_value()
{
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "tr");

	/*invalid number*/

	/* invalid number */
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "+0");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "+1");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, ".123"); /* at least one digit before '.' */
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "1.");   /* at least one digit after '.' */

#if 1
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "INF");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "inf");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "NAN");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "nan");
#endif

	TEST_ERROR(LEPT_PARSE_NUMBER_TOO_BIG, "1e309");
}

static void test_parse_root_not_singular()
{
	TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "true s");
#if 0
	/* invalid number */
	TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "0123"); /* after zero should be '.' or nothing */
	TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "0x0");
	TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "0x123");
#endif

}
static void test_parse_number_too_big() {
#if 0
	TEST_ERROR(LEPT_PARSE_NUMBER_TOO_BIG, "1e309");
	TEST_ERROR(LEPT_PARSE_NUMBER_TOO_BIG, "-1e309");
#endif
}


static void test_parse_number() {
	TEST_NUMBER(0.0, "0");
	TEST_NUMBER(0.0, "-0");
	TEST_NUMBER(0.0, "-0.0");
	TEST_NUMBER(1.0, "1");
	TEST_NUMBER(-1.0, "-1");
	TEST_NUMBER(1.5, "1.5");
	TEST_NUMBER(-1.5, "-1.5");
	TEST_NUMBER(3.1416, "3.1416");
	TEST_NUMBER(1E10, "1E10");
	TEST_NUMBER(1e10, "1e10");
	TEST_NUMBER(1E+10, "1E+10");
	TEST_NUMBER(1E-10, "1E-10");
	TEST_NUMBER(-1E10, "-1E10");
	TEST_NUMBER(-1e10, "-1e10");
	TEST_NUMBER(-1E+10, "-1E+10");
	TEST_NUMBER(-1E-10, "-1E-10");
	TEST_NUMBER(1.234E+10, "1.234E+10");
	TEST_NUMBER(1.234E-10, "1.234E-10");
	TEST_NUMBER(0.0, "1e-10000"); /* must underflow */


	
}


static void test_parse()
{
	test_parse_null();
	test_parse_true();
	test_parse_false();

	test_parse_except_value();
	test_parse_invalid_value();
	test_parse_root_not_singular();

	test_parse_number();
}



#define EXPECT_EQ_STRING(expect,actual, alength)\
	EXPECT_EQ_BASE(sizeof(expect)-1 == alength && memcmp(expect, actual, alength)== 0, expect,actual, "%s" )

static void test_access_string()
{
	lept_value v;
	lept_init(v);
	lept_set_string(v, "", 0);
	EXPECT_EQ_STRING("", lept_get_string(v), lept_get_string_length(v)); 

	lept_set_string(v, "P&S", 3);
	EXPECT_EQ_STRING("P&G", lept_get_string(v), lept_get_string_length(v));
	lept_free(v);
}


int main()
{
	test_parse();
	printf("%d/%d  (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
	return main_ret;

}
