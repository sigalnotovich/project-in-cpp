#include "testMacros.h"
#include "../Group.h"
#include "../exceptions.h"

using namespace mtm;

bool GroupTest() {
	ASSERT_EXCEPTION(Group("", 1, 1), GroupInvalidArgs);
	Group alpha("Alpha", "Beta", 6, 10, 40, 50, 80);
	Group alpha_same("Alpha", "Beta", 6, 10, 40, 50, 80);
	Group alpha_long_name("Alpha_long_name", "Beta", 6, 10, 40, 50, 80);
	Group alpha_more_adults("Alpha", "Beta", 6, 15, 40, 50, 80);
	ASSERT_EXCEPTION(Group("Alpha", "Beta", -1, 10, 40, 50, 80), GroupInvalidArgs);
	Group alpha2("Alpha", 3, 10);
	Group alpha3(alpha);
	ASSERT_TRUE(alpha.getName() == "Alpha");
	ASSERT_TRUE(alpha2.getName() == "Alpha");
	ASSERT_TRUE(alpha.getSize() == 16);
	ASSERT_TRUE(alpha2.getClan() == "");
	ASSERT_TRUE(alpha.getClan() == "Beta");
	ASSERT_NO_EXCEPTION(alpha.changeClan("Lambda"));
	ASSERT_TRUE(alpha.getClan() == "Lambda");
	ASSERT_TRUE(alpha < alpha_long_name);
	ASSERT_TRUE(alpha < alpha_more_adults);
	ASSERT_FALSE(alpha_long_name < alpha);
	ASSERT_FALSE(alpha > alpha_long_name);
	ASSERT_FALSE(alpha_same > alpha_long_name);

	return true;
}

bool GroupConstractorTest() {
	ASSERT_EXCEPTION(Group("", "Beta", 6, 10, 40, 50, 80), GroupInvalidArgs);
	ASSERT_EXCEPTION(Group("Alpha", "Beta", -1, 10, 40, 50, 80), GroupInvalidArgs);
	ASSERT_EXCEPTION(Group("Alpha", "Beta", 6, -1, 40, 50, 80), GroupInvalidArgs);
	ASSERT_EXCEPTION(Group("Alpha", "Beta", 6, 10, -1, 50, 80), GroupInvalidArgs);
	ASSERT_EXCEPTION(Group("Alpha", "Beta", 6, 10, 40, -1, 80), GroupInvalidArgs);
	ASSERT_EXCEPTION(Group("Alpha", "Beta", 6, 10, 40, 50, 110), GroupInvalidArgs);
	ASSERT_EXCEPTION(Group("Alpha", "Beta", 6, 10, 40, 50, -1), GroupInvalidArgs);
	ASSERT_EXCEPTION(Group("Alpha", "Beta", 0, 0, 40, 50, 80), GroupInvalidArgs);
	ASSERT_NO_EXCEPTION(Group("Alpha", "Beta", 6, 10, 40, 50, 80));

	ASSERT_EXCEPTION(Group("", 1, 1), GroupInvalidArgs);
	ASSERT_EXCEPTION(Group("gamma", -1, 1), GroupInvalidArgs);
	ASSERT_EXCEPTION(Group("gamma", 1, -1), GroupInvalidArgs);
	ASSERT_EXCEPTION(Group("gamma", 0, 0), GroupInvalidArgs);
	ASSERT_NO_EXCEPTION(Group("gamma", 1, 1));

	return true;
}

bool checkGetFunction() { //getName getSize getClan
	Group alpha("Alpha", "Beta", 6, 10, 40, 50, 80);
	ASSERT_TRUE(alpha.getName() == "Alpha");
	ASSERT_TRUE(alpha.getClan() == "Beta");
	ASSERT_TRUE(alpha.getSize() == 16);

	Group gamma("gamma", 1, 1);
	ASSERT_TRUE(gamma.getName() == "gamma");
	ASSERT_TRUE(gamma.getClan() == "");
	ASSERT_TRUE(gamma.getSize() == 2);

	return true;
}

bool changeClanTest() {
	Group alpha("Alpha", "Beta", 6, 10, 40, 50, 80);
	alpha.changeClan("new_clane");
	ASSERT_TRUE(alpha.getClan() == "new_clane");
	//checked morale manualy //morale is 72;

	Group lamda("Alpha", "Beta", 6, 10, 40, 50, 80);
	lamda.changeClan("Beta");
	ASSERT_TRUE(lamda.getClan() == "Beta");
	//checked morale manualy //morale is 80;

	Group gamma("gamma", 1, 1);
	gamma.changeClan("Beta");
	ASSERT_TRUE(gamma.getClan() == "Beta");
	//checked morale manualy //morale is 77;

	return true;
}

bool operatorSmallerThentest() {
	Group alpha("Alpha", "Beta", 6, 10, 40, 50, 80);
	Group alpha_same_name("Alpha", "Beta", 6, 10, 40, 50, 80); //same name same power; 
	Group alpha_diffrent_name("Alpha_diff", "Beta", 6, 10, 40, 50, 80);//diff name same power;
	Group alpha_diff_power("Alpha", "Beta", 6, 16, 40, 50, 80); //same name diff power; 
	ASSERT_FALSE(alpha < alpha_same_name); //same name same power;
	ASSERT_FALSE(alpha_same_name < alpha); //same name same power;
	ASSERT_TRUE(alpha < alpha_diffrent_name);//diff name same power;
	ASSERT_FALSE(alpha_diffrent_name < alpha);//diff name same power;
	ASSERT_TRUE(alpha < alpha_diff_power);//same name diff power;
	ASSERT_FALSE(alpha_diff_power < alpha);//same name diff power;
	return true;
}

/**
* Compare two groups. according to power, and name.
* @param rhs
* @return true, if power(this) > power(rhs), or if they're equal and
*  this group's name is not smaller (lexicographic) than rhs's name.
*  false otherwise.
*/

/* Power: ((10 * number_of_adults + 3 * number_of_children) *
* (10 * number_of_tools + number_of_food)*morale) / 100 (floor)*/

bool operatorBiggerThenTest() {
	Group alpha("Alpha", "Beta", 6, 10, 40, 50, 80);
	Group alpha_same_name("Alpha", "Beta", 6, 10, 40, 50, 80); //same name same power; 
	Group alpha_diffrent_name("Alpha_diff", "Beta", 6, 10, 40, 50, 80);//diff name same power;
	Group alpha_diff_power("Alpha", "Beta", 6, 16, 40, 50, 80); //same name diff power; 
	ASSERT_FALSE(alpha > alpha_same_name);
	ASSERT_FALSE(alpha > alpha_diff_power);
	ASSERT_TRUE(alpha_diff_power > alpha);
	ASSERT_TRUE(alpha_diffrent_name > alpha);
	ASSERT_FALSE(alpha > alpha_diffrent_name);
	return true;
}


/**
* Compare two groups. according to power, and name.
* @param rhs
* @return true, if power(this) < power(rhs), or if they're equal and
*  this group's name is not bigger (lexicographic) than rhs's name.
*  false otherwise.
*/
bool operatorSmallerThenOrEqualtest() {
	Group alpha("Alpha", "Beta", 6, 10, 40, 50, 80);
	Group alpha_same_name("Alpha", "Beta", 6, 10, 40, 50, 80); //same name same power; 
	Group alpha_diffrent_name("Alpha_diff", "Beta", 6, 10, 40, 50, 80);//diff name same power;
	Group alpha_diff_power("Alpha", "Beta", 6, 16, 40, 50, 80); //same name diff power; 
	ASSERT_TRUE(alpha <= alpha_same_name);
	ASSERT_TRUE(alpha <= alpha_diffrent_name);
	ASSERT_FALSE(alpha_diffrent_name <= alpha);
	ASSERT_TRUE(alpha <= alpha_diff_power);
	ASSERT_FALSE(alpha_diff_power <= alpha);
	return true;
}

/**
* Compare two groups. according to power, and name.
* @param rhs
* @return true, if power(this) > power(rhs), or if they're equal and
*  this group's name is not smaller (lexicographic) than rhs's name.
*  false otherwise.
*/
bool operatorBiggerThenOrEqualtest() {
	Group alpha("Alpha", "Beta", 6, 10, 40, 50, 80);
	Group alpha_same_name("Alpha", "Beta", 6, 10, 40, 50, 80); //same name same power; 
	Group alpha_diffrent_name("Alpha_diff", "Beta", 6, 10, 40, 50, 80);//diff name same power;
	Group alpha_diff_power("Alpha", "Beta", 6, 16, 40, 50, 80); //same name diff power; 
	ASSERT_TRUE(alpha_diff_power >= alpha);
	ASSERT_FALSE(alpha >= alpha_diff_power);
	ASSERT_TRUE(alpha >= alpha_same_name);
	ASSERT_TRUE(alpha_same_name >= alpha);
	ASSERT_TRUE(alpha_diffrent_name >= alpha);
	ASSERT_FALSE(alpha >= alpha_diffrent_name);
	return true;
}


/**
* Compare two groups. according to power, and name.
* @param rhs
* @return true, if power(this) == power(rhs), and this group's name is
* equal to rhs's name.
* false otherwise.
*/
bool operatorEqualTest() {
	Group alpha("Alpha", "Beta", 6, 10, 40, 50, 80);
	Group alpha_same_name("Alpha", "Beta", 6, 10, 40, 50, 80); //same name same power; 
	Group alpha_diffrent_name("Alpha_diff", "Beta", 6, 10, 40, 50, 80);//diff name same power;
	Group alpha_diff_power("Alpha", "Beta", 6, 16, 40, 50, 80); //same name diff power;
	ASSERT_TRUE(alpha == alpha_same_name);
	ASSERT_TRUE(alpha_same_name == alpha);
	ASSERT_FALSE(alpha == alpha_diffrent_name);
	ASSERT_FALSE(alpha_diffrent_name == alpha);
	ASSERT_FALSE(alpha == alpha_diff_power);
	ASSERT_FALSE(alpha_diff_power == alpha);

	return true;
}



bool uniteTetsBed() {
	Group alpha("Alpha", "Beta", 6, 10, 40, 50, 80);
	Group alpha2("Alpha", "Beta", 6, 10, 40, 50, 80);
	ASSERT_TRUE(alpha.unite(alpha2, 100)); //two groups are the same
	Group gamma("gamma", 1, 1);
	Group gamma2("gamma", 1, 1);
	ASSERT_FALSE(gamma.unite(gamma2, 6));////two groups are the same
										 //difrent groups same clan
	Group lamda("lamda", "Beta", 4, 5, 70, 60, 90);
	Group lamda2("lamda2", "Beta1", 6, 10, 40, 50, 80);
	ASSERT_FALSE(lamda.unite(lamda2, 100)); //two groups are -not- in the same clan
	Group delta("lamda", "Beta", 4, 5, 70, 60, 90);
	Group delta2("lamda", "Beta", 6, 10, 40, 50, 60);
	ASSERT_FALSE(delta.unite(delta, 100)); //one group has morale less then 70
	Group delta3("lamda", "Beta", 40, 50, 70, 60, 90);
	Group delta4("lamda", "Beta", 60, 10, 40, 50, 60);
	ASSERT_FALSE(delta3.unite(delta4, 100)); //groups have more peaple then 100
	return true;
}


bool uniteTetsGood() {
	Group alpha("Alpha", "Beta", 5, 10, 40, 50, 80);
	Group alpha2("Alpha2", "Beta", 5, 15, 40, 50, 80);
	ASSERT_TRUE(alpha.unite(alpha2, 100));
	ASSERT_TRUE(alpha.getName() == "Alpha2");
	ASSERT_TRUE(alpha.getClan() == "Beta");
	ASSERT_TRUE(alpha.getSize() == 35);
	ASSERT_TRUE(alpha2.getClan() == "");
	ASSERT_TRUE(alpha2.getName() == "");
	ASSERT_TRUE(alpha2.getSize() == 0);

	return true;
}

bool divideGroupTest() {
	Group alpha("Alpha", "Beta", 6, 11, 40, 50, 80);
	ASSERT_EXCEPTION(alpha.divide(""), GroupInvalidArgs);
	Group alpha2("Alpha", "Beta", 1, 1, 40, 50, 80);
	ASSERT_EXCEPTION(alpha2.divide("hey"), GroupCantDivide);
	Group new_group = alpha.divide("new_group");
	ASSERT_TRUE(alpha.getName() == "Alpha");
	ASSERT_TRUE(alpha.getClan() == "Beta");
	ASSERT_TRUE(alpha.getSize() == 9);
	ASSERT_TRUE(new_group.getClan() == "Beta");
	ASSERT_TRUE(new_group.getName() == "new_group");
	ASSERT_TRUE(new_group.getSize() == 8);

	return true;
}

bool testFight() {
	Group alpha("Alpha", "Beta", 6, 11, 40, 50, 80);
	Group alpha2("Alpha", "Beta2", 6, 11, 40, 50, 80);
	//ASSERT_TRUE(alpha.fight(alpha2)== DRAW);
	Group alpha3("Alpha3", "Beta", 6, 11, 40, 50, 80);
	ASSERT_EXCEPTION(alpha.fight(alpha), GroupCantFightWithItself);
	ASSERT_TRUE(alpha3.fight(alpha) == WON);
	ASSERT_TRUE(alpha.fight(alpha3) == LOST);
	return true;
}

bool printTest() {
	Group alpha("Alpha", "", 6, 11, 40, 50, 80);
	std::ostringstream os;
	os << alpha;

	return true;
}
int main() {
	RUN_TEST(GroupTest);
	RUN_TEST(GroupConstractorTest);
	RUN_TEST(checkGetFunction);
	RUN_TEST(changeClanTest);
	RUN_TEST(operatorSmallerThentest);
	RUN_TEST(operatorBiggerThenTest);
	RUN_TEST(operatorSmallerThenOrEqualtest);
	RUN_TEST(operatorBiggerThenOrEqualtest);
	RUN_TEST(operatorEqualTest);
	RUN_TEST(uniteTetsBed);
	RUN_TEST(uniteTetsGood);
	RUN_TEST(divideGroupTest);
	RUN_TEST(testFight);
	RUN_TEST(printTest);
	return 0;
}