#pragma once
#include <exception>
#include <string>

class BaseException : public std::exception
{
public:
    virtual const char* what() const override {
		return "Exception!";
	};
};


class BookException : public BaseException
{
private:
	std::string m_error;

public:
	BookException(std::string error) {
		m_error = "Book exception caught: " + error;
	}
	const char* what()const override  { return m_error.c_str(); }
};


class AdminException: public BaseException
{
private:
	std::string m_error;

public:
	AdminException(std::string error) {
        m_error = "Admin exception caught: " + error;
	}
	const char* what() const override { return m_error.c_str(); }
};


class UserException: public BaseException
{
private:
	std::string m_error;

public:
	UserException(std::string error) {
        m_error = "User exception caught: " + error;
	}
	const char* what() const override { return m_error.c_str(); }
};

class FileException: public BaseException
{
private:
	std::string m_error;
	std::string m_file_name;

public:
    FileException(std::string error, std::string file): m_file_name(file) {
		m_error = "File exception caught : " + error + "The file used is: " + m_file_name + "\n\n";
    }
    const char* what() const override {return m_error.c_str(); }
};
