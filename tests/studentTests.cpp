// Copyright (c) 2024 Nathan Greenfield. All rights reserved
#include "catch.hpp"
#include "SMCDoubleList.hpp"

// Helper function declarations (don't change this)
extern bool CheckTextFilesSame(const std::string& fileNameA,
	const std::string& fileNameB);

// Your tests -- only add sections
TEST_CASE("Student tests", "[student]") 
{
	// Complete tests are worth 1 point for each test

	SECTION("Default constructor, size, and destructor")
	{
		smcList<int> testList;
		REQUIRE(testList.size()==0);
	}

	SECTION("Push_front, front, back")
	{
		//push values and test that theyre in the right spot
		smcList<int> testList;
		testList.push_front(1);
		testList.push_front(2);
		REQUIRE(testList.front() == 2);
		REQUIRE(testList.back() == 1);
	}

	SECTION("Push_front, front, back, pop_front")
	{
		//push values and test that theyre in the right spot after removing one
		smcList<int> testList;
		testList.push_front(1);
		testList.push_front(2);
		testList.push_front(3);
		testList.pop_front();
		REQUIRE(testList.front() == 2);
		REQUIRE(testList.back() == 1);
	}

	SECTION("Push_back, front, back")
	{
		//push values (from behind) and test that they're in the right spot
		smcList<int> testList;
		testList.push_back(1);
		testList.push_back(2);
		REQUIRE(testList.front() == 1);
		REQUIRE(testList.back() == 2);
	}

	SECTION("Push_back, front, back, pop_back")
	{	
		//push values (from behind) and test that they're in the right spot
		smcList<int> testList;
		testList.push_back(1);
		testList.push_back(2);
		testList.push_back(3);
		//test toString and reverse formatting and reading
		REQUIRE(testList.toString() == "{1,2,3}");
		REQUIRE(testList.toReverseString() == "{3,2,1}");
		testList.pop_back();
		REQUIRE(testList.front() == 1);
		REQUIRE(testList.back() == 2);
	}

	SECTION("Push_back, clear")
	{
		//clear and test that the string is empty
		smcList<int> testList;
		testList.push_back(1);
		testList.push_back(2);
		testList.push_back(3);
		testList.clear();
		REQUIRE(testList.toString() == "{}");
		REQUIRE(testList.size() == 0);
	}

	SECTION("Push_back, front, back, pop_back, copy constructor")
	{
		//make a list and copy it and test the copy
		smcList<int> testList;
		testList.push_back(1);
		testList.push_back(2);
		testList.push_back(3);
		testList.pop_back();
		smcList<int> listCopy = testList;
		REQUIRE(listCopy.front() == 1);
		REQUIRE(listCopy.back() == 2);
	}

	SECTION("Push_back, front, back, pop_back, assignment")
	{
		//make a list and assign it and test the assigment
		smcList<int> testList;
		testList.push_back(1);
		testList.push_back(2);
		testList.push_back(3);
		testList.pop_back();
		smcList<int> listCopy(testList);
		REQUIRE(listCopy.front() == 1);
		REQUIRE(listCopy.back() == 2);
	}

	SECTION("Back, front, pop_front, pop_back, exceptions")
	{
		smcList<int> testList;
		std::string error;
		try{
			testList.front();
		}
		catch(std::exception &e){
			error = e.what();
		}
		REQUIRE(error == "list is empty!");
		
		error.clear();
		try{
			testList.back();
		}
		catch(std::exception &e){
			error = e.what();
		}
		REQUIRE(error == "list is empty!");

		error.clear();
		try{
			testList.pop_back();
		}
		catch(std::exception &e){
			error = e.what();
		}
		REQUIRE(error == "list is empty!");

		error.clear();
		try{
			testList.pop_front();
		}
		catch(std::exception &e){
			error = e.what();
		}
		REQUIRE(error == "list is empty!");
	}

	SECTION("Push_front, front, back, begin, iterator dereference, copy constructor")
	{
		/*smcList<int> testList;
		testList.push_back(1);
		testList.push_back(2);
		testList.push_back(3);
		smcList<int>::Iterator front(testList.begin());
		smcList<int>::Iterator back(testList.end());
		REQUIRE(*back == 3);
		REQUIRE(*front == 1);*/
	}

	SECTION("List: begin, end; Iterator: dereference, assignment, comparison")
	{
		/*smcList<int> testList;
		testList.push_back(1);
		testList.push_back(2);
		testList.push_back(3);
		smcList<int>::Iterator front = testList.begin();
		smcList<int>::Iterator back = testList.end();
		REQUIRE(*back == 3);
		REQUIRE(*front == 1);*/
	}

	SECTION("List: begin, end; Iterator: dereference, increment")
	{
		// TODO: Tests go here
		REQUIRE(true);
	}

	SECTION("List: begin, end; Iterator: dereference, increment, decrement")
	{
		// TODO: Tests go here
		REQUIRE(true);
	}

	SECTION("List: insert with iterator at begin, middle, and one away from end")
	{
		/*smcList<int> testList;
		smcList<int>::Iterator i = testList.begin();
		testList.push_back(2);
		testList.push_back(3);
		testList.push_back(4);
		testList.insert(i, 0);
		testList.insert(++i, 1);
		i = testList.end();
		testList.insert(i, 5);

		REQUIRE(testList.toString() == "{1,2,3,4,5}");*/
	}

	SECTION("List: erase with iterator at begin, middle, and one away from end")
	{
		// TODO: Tests go here
		REQUIRE(true);
	}
}

TEST_CASE("Student movie", "[student]")
{
	SECTION("Bad constructor")
	{
		// TODO: Tests go here
		REQUIRE(true);
	}

	SECTION("Creating scene 2")
	{
		// TODO: Tests go here
		REQUIRE(true);
	}

	SECTION("Checking frames, scene 2")
	{
		// TODO: Tests go here
		REQUIRE(true);
	}
}


