#include "errors.h"
#include "parsing.h"
#include "datagram.h"

#include <UnitTest++/UnitTest++.h>
#include <memory>
#include <iostream>
#include <stdexcept>

using namespace std;


TEST(tokenize) {
    vector<string> tokens = tokenize("   de@f.com  \"ghi j-k \"w == \"z\"");
    vector<string> tokens_check = {"de@f.com", "ghi j-k ", "w", "==", "z"};
    CHECK_EQUAL(tokens_check.size(),tokens.size());
    for (size_t i = 0; i<tokens_check.size(); ++i) {
        CHECK_EQUAL(tokens_check[i],tokens[i]);
    }

    tokens = tokenize("hel\"l\"o world \"\"\"eecs   211\"");
    tokens_check = {"hel", "l", "o", "world", "", "eecs   211"};
    CHECK_EQUAL(tokens_check.size(),tokens.size());
    for (size_t i = 0; i<tokens_check.size(); ++i) {
        CHECK_EQUAL(tokens_check[i],tokens[i]);
    }

    tokens = tokenize("\"abc\\\"\"def\"");
    tokens_check = {"abc\\", "def"};
    CHECK_EQUAL(tokens_check.size(),tokens.size());
    for (size_t i = 0; i<tokens_check.size(); ++i) {
        CHECK_EQUAL(tokens_check[i],tokens[i]);
    }

    //check empty string
    tokens = tokenize("   ");
    tokens_check = {""};
    CHECK_EQUAL(tokens_check.size(),tokens.size());
    for (size_t i = 0; i<tokens_check.size(); ++i) {
        CHECK_EQUAL(tokens_check[i],tokens[i]);
    }

    //check to make sure spaces are kept when quote-enclosed
    tokens = tokenize("\"   \"");
    tokens_check = {"   "};
    CHECK_EQUAL(tokens_check.size(),tokens.size());
    for (size_t i = 0; i<tokens_check.size(); ++i) {
        CHECK_EQUAL(tokens_check[i],tokens[i]);
    }

    //check to make sure single tokens work
    tokens = tokenize("brownfox");
    tokens_check = {"brownfox"};
    CHECK_EQUAL(tokens_check.size(),tokens.size());
    for (size_t i = 0; i<tokens_check.size(); ++i) {
        CHECK_EQUAL(tokens_check[i],tokens[i]);
    }

    tokens = tokenize("  brownfox");
    tokens_check = {"brownfox"};
    CHECK_EQUAL(tokens_check.size(),tokens.size());
    for (size_t i = 0; i<tokens_check.size(); ++i) {
        CHECK_EQUAL(tokens_check[i],tokens[i]);
    }

    //make sure strings separated only by strings work
    tokens = tokenize("brown fox");
    tokens_check = {"brown","fox"};
    CHECK_EQUAL(tokens_check.size(),tokens.size());
    for (size_t i = 0; i<tokens_check.size(); ++i) {
        CHECK_EQUAL(tokens_check[i],tokens[i]);
    }

    //make sure strings separated only by quotes work
    tokens = tokenize("\"brown\"\"fox\"");
    tokens_check = {"brown","fox"};
    CHECK_EQUAL(tokens_check.size(),tokens.size());
    for (size_t i = 0; i<tokens_check.size(); ++i) {
        CHECK_EQUAL(tokens_check[i],tokens[i]);
    }

    //make sure spaces work in quotes again
    tokens = tokenize("\"    brown  \"\"   fox \"");
    tokens_check = {"    brown  ","   fox "};
    CHECK_EQUAL(tokens_check.size(),tokens.size());
    for (size_t i = 0; i<tokens_check.size(); ++i) {
        CHECK_EQUAL(tokens_check[i],tokens[i]);
    }

    //make sure multiple empty strings separated by quotes are tokenized
    tokens = tokenize("\"\"\"\"");
    tokens_check = {"",""};
    CHECK_EQUAL(tokens_check.size(),tokens.size());
    for (size_t i = 0; i<tokens_check.size(); ++i) {
        CHECK_EQUAL(tokens_check[i],tokens[i]);
    }

    //check new line works
    tokens = tokenize("t\na\"blah  \"   test\"\"");
    tokens_check = {"t\na","blah  ","test",""};
    CHECK_EQUAL(tokens_check.size(),tokens.size());
    for (size_t i = 0; i<tokens_check.size(); ++i) {
        CHECK_EQUAL(tokens_check[i],tokens[i]);
    }

    CHECK_THROW(tokenize("\"\"\""),runtime_error);
    CHECK_THROW(tokenize("\""),runtime_error);
    CHECK_THROW(tokenize("hel\"l\"o world \"\"\"eecs   211"),runtime_error);


}

TEST(INTPARSE) {
    CHECK_EQUAL(500,parse_int("500"));
    CHECK_EQUAL(456435,parse_int("00456435"));
    CHECK_EQUAL(1,parse_int("001"));
    CHECK_EQUAL(5350,parse_int("0000005350"));
    CHECK_EQUAL(0,parse_int("0000000"));
    CHECK_EQUAL(0,parse_int("0"));
    CHECK_EQUAL(3,parse_int("3"));

    CHECK_THROW(parse_int("a"),runtime_error);
    CHECK_THROW(parse_int("1.0"),runtime_error);
    CHECK_THROW(parse_int(""),runtime_error);
    CHECK_THROW(parse_int("-"),runtime_error);
    CHECK_THROW(parse_int("-10"),runtime_error);
    CHECK_THROW(parse_int("0.\n"),runtime_error);
}

TEST(PARSEIP) {
    IP_address IP_actual = parse_IP("255.255.255.0");
    IP_address IP_expected = {255,255,255,0};
    CHECK_EQUAL(IP_expected.size(),IP_actual.size());
    for (size_t i = 0; i < IP_expected.size(); ++i) {
        CHECK_EQUAL(IP_expected[i],IP_actual[i]);
    }

    IP_actual = parse_IP("0.254.0.196");
    IP_expected = {0,254,0,196};
    for (size_t i = 0; i < IP_expected.size(); ++i) {
        CHECK_EQUAL(IP_expected[i],IP_actual[i]);
    }

    IP_actual = parse_IP("0.0.0.50");
    IP_expected = {0,0,0,50};
    for (size_t i = 0; i < IP_expected.size(); ++i) {
        CHECK_EQUAL(IP_expected[i],IP_actual[i]);
    }

    IP_actual = parse_IP("0.0.0.0");
    IP_expected = {0,0,0,0};
    for (size_t i = 0; i < IP_expected.size(); ++i) {
        CHECK_EQUAL(IP_expected[i],IP_actual[i]);
    }

    IP_actual = parse_IP("1.1.1.1");
    IP_expected = {1,1,1,1};
    for (size_t i = 0; i < IP_expected.size(); ++i) {
        CHECK_EQUAL(IP_expected[i],IP_actual[i]);
    }

    IP_actual = parse_IP("20.21.22.23");
    IP_expected = {20,21,22,23};
    for (size_t i = 0; i < IP_expected.size(); ++i) {
        CHECK_EQUAL(IP_expected[i],IP_actual[i]);
    }

    IP_actual = parse_IP("254.254.254.254");
    IP_expected = {254,254,254,254};
    for (size_t i = 0; i < IP_expected.size(); ++i) {
        CHECK_EQUAL(IP_expected[i],IP_actual[i]);
    }

    CHECK_THROW(parse_IP("0.0.0.50.5"), err_code);
    CHECK_THROW(parse_IP("0.0.0.f"),err_code);
    CHECK_THROW(parse_IP("@.0.0.0"),err_code);
    CHECK_THROW(parse_IP("0.0.0."),err_code);
    CHECK_THROW(parse_IP("0.0.0.0."),err_code);
    CHECK_THROW(parse_IP("05.0.0.0"),err_code);
    CHECK_THROW(parse_IP("0.0.0.256"),err_code);
    CHECK_THROW(parse_IP("500.0.0.0"),err_code);
    CHECK_THROW(parse_IP("..."),err_code);
    CHECK_THROW(parse_IP("...."),err_code);
    CHECK_THROW(parse_IP(""),err_code);
    CHECK_THROW(parse_IP("0 .0.0.0"),err_code);
    CHECK_THROW(parse_IP("0.0.0.\n"),err_code);
}