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
}

static void test_parse_root_not_singular()
{
	TEST_ERROR(LEPT_PARSE_ROOT_NOT_SINGULAR, "true s");
}




static void test_parse()
{
	test_parse_null();
	test_parse_true();
	test_parse_false();

	test_parse_except_value();
	test_parse_invalid_value();
	test_parse_root_not_singular();
}

int main()
{
	test_parse();
	printf("%d/%d  (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
	return main_ret;

}
