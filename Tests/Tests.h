#pragma once
#include "BookDatabase.h"
#include "UserController.h"
#include "AdministratorController.h"
#include <assert.h>

void testGetters(Book book)
{
	assert(book.getTitle() == "Test1"); 
	assert(book.getAuthor() == "a");
	assert(book.getGenre() == "science fiction (sf)");
	assert(book.getDescription() == "bla");
	assert(book.getPublicationYear() == 1900);
	assert(book.getCover() == "https://");
}

void testSetters(Book book )
{
	book.setTitle("Test1");
	book.setAuthor( "a");
	book.setGenre("science fiction (sf)");
	book.setDescription( "bla");
	book.setPublicationYear(1900);
	book.setCover("https://");

	assert(book.getTitle() == "Test1");
	assert(book.getAuthor() == "a");
	assert(book.getGenre() == "science fiction (sf)");
	assert(book.getDescription() == "bla");
	assert(book.getPublicationYear() == 1900);
	assert(book.getCover() == "https://");               

	bool exceptionThrown = false;
	try
	{
		book.setGenre("dsfdsdhjfasdghf");
	}
	catch (...)
	{
		exceptionThrown = true;
	}
	assert(exceptionThrown);

	bool exceptionThrown1 = false;
	try
	{
		book.setPublicationYear(-2323.565);
	}
	catch (...)
	{
		exceptionThrown1 = true;
	}
	assert(exceptionThrown1);
}

void testOperatorEqual(Book book)
{
	Book book1{ "Test1", "a   ", "sf", "bla", 1900, "https://" }, book2{ "Test2", "b   ", "sf", "blabla", 2000, "https://///" };

	assert(book == book1);
	assert(!(book == book2));
}

void TestBook()
{
	Book book{ "Test1", "a   ", "sf", "bla", 1900, "https://" }, book2{ "Test2", "b   ", "sf", "blabla", 2000, "https://///" };

	testGetters(book);
	testSetters(book2);
	testOperatorEqual(book);
};
////////////////////////////////////////////////////////////////////

void testAdd(BookDatabase &database)
{
	assert(database.addBook("Test1", "a", "sf", "bla", 1900, "https://") == true);
	assert(database.addBook("Test2", "b", "realistic fiction", "bla", 2020, "https://") == true);
	assert(database.addBook("Test3", "c", "sf", "bla", 1800, "https://") == true);
	assert(database.addBook("Test1", "a", "sf", "bla", 1900, "https://") == false);
}

void testDelete(BookDatabase database)
{
    Book b1={"Test1", "a", "sf", "bla", 1900, "https://"};
    assert(database.deleteBook("Test1", "a") == b1);
    bool exceptionThrown1 = false;
    try
    {
        database.deleteBook("Test1", "a");
    }
    catch (...)
    {
        exceptionThrown1 = true;
    }
    assert(exceptionThrown1);
}

void testUpdate(BookDatabase database)
{
	assert(database.updateBook("Test1", "a", "self", "blabla", 21113, "https:///////") == true);
	assert(database.updateBook("Test399", "ds", "self", "blabla", 2000, "https:////") == false);
}

void testReturnDatabase(BookDatabase database)
{
	Book b1{ "Test1", "a", "sf", "bla", 1900, "https://" }, b2{ "Test2", "b", "realistic fiction", "bla", 2020, "https://" };
	assert(database.returnDatabase()[0] == b1);
	assert(database.returnDatabase()[1] == b2);
	assert(!(database.returnDatabase()[2] == b2));
}

void TestBookDatabase()
{
	BookDatabase database;

	testAdd(database);
	testDelete(database);
	testUpdate(database);
	testReturnDatabase(database);
};
////////////////////////////////////////////////////////////////////

void testAdd(AdministratorController& admin)
{
	assert(admin.addAdmin("Test1", "a", "sf", "bla", 1900, "https://") == "Book added to the database!\n");
	assert(admin.addAdmin("Test1", "a", "sf", "bla", 1900, "https://") == "Add operation failed, duplicate book!\n");
}

void testDelete(AdministratorController admin)
{
	assert(admin.deleteAdmin("Test1", "dasd") == "Delete operation failed, inexistent book!\n");
	assert(admin.deleteAdmin("Test1", "a") == "Book deleted from the database!\n");
	bool exceptionThrown=false;
	try
	{
		admin.deleteAdmin("Test1", "a");
	}
	catch (...)
	{
		exceptionThrown = true;
	}
	assert(exceptionThrown);
}

void testUpdate(AdministratorController admin)
{
	assert(admin.updateAdmin("Test1", "a", "self", "blabla", 21113, "https:///////") == "Book updated successfully!\n");
	assert(admin.updateAdmin("Test399", "ds", "self", "blabla", 2000, "https:////") == "Update operation failed, inexistent book!\n");
}

void testReturnDatabase(AdministratorController admin)
{
	Book b1{ "Test1", "a", "sf", "bla", 1900, "https://" }, b2{ "Test2", "b", "realistic fiction", "bla", 2020, "https://" };
	assert(admin.returnAdminDatabase()[0] == b1);
	assert(!(admin.returnAdminDatabase()[0] == b2));
}

void TestAdministratorController()
{
	AdministratorController admin;

	testAdd(admin);
	testDelete(admin);
	testUpdate(admin);
	testReturnDatabase(admin);
};
//////////////////////////////////////////////////////////////////////

void testDelete(UserController user)
{
	bool exceptionThrown = false;
	try
	{
		user.deleteUser("Test1", "a");
	}
	catch (...)
	{
		exceptionThrown = true;
	}
	assert(exceptionThrown);
}

void TestUserController()
{
	AdministratorController admin;
	admin.addAdmin("Test1", "a", "sf", "bla", 1900, "https://");
	admin.addAdmin("Test2", "b", "realistic fiction", "bla", 2020, "https://");
	admin.addAdmin("Test3", "c", "sf", "bla", 1800, "https://");
    std::vector<Book> database = admin.returnAdminDatabase();
    UserController user{ database };

	testDelete(user);
};

void runAllTests()
{
	TestBook();
	TestBookDatabase();
	TestAdministratorController();
	TestUserController();
}


