#include "gtest/gtest.h"
#include "rshellbase.hpp"
#include <vector>
#include <iostream>
using namespace std;

TEST(RshellBaseTest, DisintegrateTest_ExeArgu) {
	vector<Connector*> con;
	vector<Command*> com;
	vector<ExeArgu*> ea;
	string input = "ls #- a; echo hello && mkdir test || echo \"hello && goodbye\"; git status";
	//getline(cin, input);
	Rshellbase *base = new Rshellbase(input);
	base->Disintegrate(ea, con, com);
	ASSERT_EQ(con.size(), 5);
	ASSERT_EQ(com.size(), 5);
	ASSERT_EQ(ea.size(), 5);
	EXPECT_EQ(ea.at(0)->getExe(), "ls");
	EXPECT_EQ(ea.at(0)->getArgu(), "");
	EXPECT_EQ(ea.at(1)->getExe(), "echo");
	EXPECT_EQ(ea.at(1)->getArgu(), "hello");
	EXPECT_EQ(ea.at(2)->getExe(), "mkdir");
	EXPECT_EQ(ea.at(2)->getArgu(), "test");
	EXPECT_EQ(ea.at(3)->getExe(), "echo");
	EXPECT_EQ(ea.at(3)->getArgu(), "hello && goodbye");
	EXPECT_EQ(ea.at(4)->getExe(), "git");
	EXPECT_EQ(ea.at(4)->getArgu(), "status");
}

TEST(RshellBaseTest, DisintegrateTest_Connector) {
	vector<Connector*> con;
	vector<Command*> com;
	vector<ExeArgu*> ea;
	string input = "ls #- a; echo hello && mkdir test || echo \"hello && goodbye\"; git status";
	//getline(cin, input);
	Rshellbase *base = new Rshellbase(input);
	base->Disintegrate(ea, con, com);
	ASSERT_EQ(con.size(), 5);
	ASSERT_EQ(com.size(), 5);
	ASSERT_EQ(ea.size(), 5);
	EXPECT_EQ(con.at(0)->GetSign(), ';');
	EXPECT_EQ(con.at(1)->GetSign(), '&');
	EXPECT_EQ(con.at(2)->GetSign(), '|');
	EXPECT_EQ(con.at(3)->GetSign(), ';');
	EXPECT_EQ(con.at(4)->GetSign(), '.');
}

TEST(ConnectorTest, GetSignTest) {
	vector<Connector*> con;
	vector<Command*> com;
	vector<ExeArgu*> ea;
	string input = "ls #- a; echo hello && mkdir test || echo \"hello && goodbye\"; git status";
	//getline(cin, input);
	Rshellbase *base = new Rshellbase(input);
	base->Disintegrate(ea, con, com);
	ASSERT_EQ(con.size(), 5);
	ASSERT_EQ(com.size(), 5);
	ASSERT_EQ(ea.size(), 5);
	EXPECT_EQ(con.at(0)->GetSign(), ';');
	EXPECT_EQ(con.at(1)->GetSign(), '&');
	EXPECT_EQ(con.at(2)->GetSign(), '|');
	EXPECT_EQ(con.at(3)->GetSign(), ';');
	EXPECT_EQ(con.at(4)->GetSign(), '.');
}

TEST(ConnectorTest, OperateTest) {
	vector<Connector*> con;
	vector<Command*> com;
	vector<ExeArgu*> ea;
	string input = "ls #- a; echo hello && mkdir test || echo \"hello && goodbye\"; git status";
	//getline(cin, input);
	Rshellbase *base = new Rshellbase(input);
	base->Disintegrate(ea, con, com);
	ASSERT_EQ(con.size(), 5);
	ASSERT_EQ(com.size(), 5);
	ASSERT_EQ(ea.size(), 5);
	EXPECT_EQ(con.at(0)->Operate(true), true);
	EXPECT_EQ(con.at(1)->Operate(true), true);
	EXPECT_EQ(con.at(1)->Operate(false), false);
	EXPECT_EQ(con.at(2)->Operate(true), false);
	EXPECT_EQ(con.at(2)->Operate(false), true);
	EXPECT_EQ(con.at(3)->Operate(true), true);
	EXPECT_EQ(con.at(4)->Operate(true), false);
	EXPECT_EQ(con.at(4)->Operate(false), false);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
