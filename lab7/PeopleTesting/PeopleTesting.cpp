#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "headers.h"

TEST_CASE("СPupil testing")
{
	SECTION("CPupil Valid Creation and Access")
	{
		CPupil pupil("John", "Smith", "Michael", "London", "School No5", "7A");
		CHECK(pupil.GetFirstName() == "John");
		CHECK(pupil.GetSecondName() == "Smith");
		CHECK(pupil.GetPatronymic() == "Michael");
		CHECK(pupil.GetAdress() == "London");
		CHECK(pupil.GetSchool() == "School No5");
		CHECK(pupil.GetGrade() == "7A");
	}
	SECTION("CPupil Empty Fields")
	{
		CHECK_THROWS_AS(CPupil("", "Smith", "Michael", "London", "School No5", "7c"),
			std::invalid_argument);
		CHECK_THROWS_AS(CPupil("John", "Smith", "Michael", "London", "", "7c"),
			std::invalid_argument);
		CHECK_THROWS_AS(CPupil("John", "Smith", "Michael", "London", "School No5", ""),
			std::invalid_argument);
	}
	SECTION("CPupil Whitespace Fields")
	{
		CHECK_THROWS_AS(CPupil(" ", "Smith", "Michael", "London", "School No5", "7c"),
			std::invalid_argument);
		CHECK_THROWS_AS(CPupil("John", "Smith", "Michael", "London", "   ", "7c"),
			std::invalid_argument);
		CHECK_THROWS_AS(CPupil("John", "Smith", "Michael", "London", "School No5", "\t\n"),
			std::invalid_argument);
	}
	//с помощью интерфейса обращаться к объекту
	SECTION("CPupil Invalid Class Format")
	{
		CHECK_THROWS_AS(CPupil("John", "Smith", "Michael", "London", "School No5", "abc"),
			std::invalid_argument);
		CHECK_THROWS_AS(CPupil("John", "Smith", "Michael", "London", "School No5", "7"),
			std::invalid_argument);
		CHECK_THROWS_AS(CPupil("John", "Smith", "Michael", "London", "School No5", "c7"),
			std::invalid_argument);
	}

	SECTION("CPupil Long School Name")
	{
		std::string longSchool(101, 'a');
		CHECK_THROWS_AS(CPupil("John", "Smith", "Michael", "London", longSchool, "7c"),
			std::invalid_argument);
	}
}

TEST_CASE("Teacher testing")
{
	SECTION("CTeacher Valid Creation and Access")
	{
		CTeacher teacher("Mary", "Johnson", "Ann", "Manchester", "Mathematics");

		CHECK(teacher.GetFirstName() == "Mary");
		CHECK(teacher.GetSecondName() == "Johnson");
		CHECK(teacher.GetPatronymic() == "Ann");
		CHECK(teacher.GetAdress() == "Manchester");
		CHECK(teacher.GetSubject() == "Mathematics");
	}

	SECTION("CTeacher Empty Subject")
	{
		CHECK_THROWS_AS(CTeacher("Mary", "Johnson", "Ann", "Manchester", ""),
			std::invalid_argument);
	}

	SECTION("CTeacher Invalid Subject")
	{
		CHECK_THROWS_AS(CTeacher("Mary", "Johnson", "Ann", "Manchester", "Math123"),
			std::invalid_argument);
	}

	SECTION("CTeacher Long Subject")
	{
		std::string longSubject(51, 'a');
		CHECK_THROWS_AS(CTeacher("Mary", "Johnson", "Ann", "Manchester", longSubject),
			std::invalid_argument);
	}
}

TEST_CASE("Worker testing")
{
	SECTION("CWorker Valid Creation and Access")
	{
		CWorker worker("James", "Brown", "William", "Birmingham", "Electrician");

		CHECK(worker.GetFirstName() == "James");
		CHECK(worker.GetSecondName() == "Brown");
		CHECK(worker.GetPatronymic() == "William");
		CHECK(worker.GetAdress() == "Birmingham");
		CHECK(worker.GetSpecialization() == "Electrician");
	}

	SECTION("CWorker Empty Specialty")
	{
		CHECK_THROWS_AS(CWorker("James", "Brown", "William", "Birmingham", ""),
			std::invalid_argument);
	}

	SECTION("CWorker Invalid Specialty")
	{
		CHECK_THROWS_AS(CWorker("James", "Brown", "William", "Birmingham", "Electrician123"),
			std::invalid_argument);
	}

	SECTION("CWorker Long Specialty")
	{
		std::string longSpecialty(51, 'a');
		CHECK_THROWS_AS(CWorker("James", "Brown", "William", "Birmingham", longSpecialty),
			std::invalid_argument);
	}
}

TEST_CASE("Student testing")
{

	SECTION("CStudent Valid Creation and Access") 
	{
		CStudent student("Peter", "Davis", "Thomas", "Oxford", "Oxford University", "123456");

		CHECK(student.GetFirstName() == "Peter");
		CHECK(student.GetSecondName() == "Davis");
		CHECK(student.GetPatronymic() == "Thomas");
		CHECK(student.GetAdress() == "Oxford");
		CHECK(student.GetUniversity() == "Oxford University");
		CHECK(student.GetStudentId() == "123456");
	}

	SECTION("CStudent Empty University") 
	{
		CHECK_THROWS_AS(CStudent("Peter", "Davis", "Thomas", "Oxford", "", "123456"), 
			std::invalid_argument);
	}

	SECTION("CStudent Invalid Student ID") 
	{
		CHECK_THROWS_AS(CStudent("Peter", 
			"Davis", 
			"Thomas", 
			"Oxford", 
			"Oxford University", 
			"123"), 
			std::invalid_argument);

		CHECK_THROWS_AS(CStudent("Peter", 
			"Davis", 
			"Thomas", 
			"Oxford", 
			"Oxford University", 
			"12345678901"), 
			std::invalid_argument);
	}

	SECTION("CStudent Long University") 
	{
		std::string longUniversity(101, 'a');
		CHECK_THROWS_AS(CStudent("Peter", 
			"Davis", 
			"Thomas", 
			"Oxford", 
			longUniversity, 
			"123456"), 
			std::invalid_argument);
	}
}

TEST_CASE("AdvancedStudent testing")
{

	SECTION("CAdvancedStudent Valid Creation and Access") 
	{
		CAdvancedStudent advStudent("Anna", 
			"Wilson", 
			"Elizabeth", 
			"Cambridge", 
			"Cambridge University", 
			"67890", 
			"Quantum Physics");

		CHECK(advStudent.GetFirstName() == "Anna");
		CHECK(advStudent.GetSecondName() == "Wilson");
		CHECK(advStudent.GetPatronymic() == "Elizabeth");
		CHECK(advStudent.GetAdress() == "Cambridge");
		CHECK(advStudent.GetUniversity() == "Cambridge University");
		CHECK(advStudent.GetStudentId() == "67890");
		CHECK(advStudent.GetDissertationTopic() == "Quantum Physics");
	}

	SECTION("CAdvancedStudent Empty Dissertation Topic") 
	{
		CHECK_THROWS_AS(CAdvancedStudent("Anna", 
			"Wilson", 
			"Elizabeth", 
			"Cambridge", 
			"Cambridge University", 
			"67890", 
			""), 
			std::invalid_argument);
	}

	SECTION("CAdvancedStudent Long Dissertation Topic") 
	{
		std::string longTopic(201, 'a');
		CHECK_THROWS_AS(CAdvancedStudent("Anna", 
			"Wilson", 
			"Elizabeth", 
			"Cambridge", 
			"Cambridge University", 
			"67890", 
			longTopic), 
			std::invalid_argument);
	}
}
