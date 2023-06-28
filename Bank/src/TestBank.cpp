// This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <openssl/evp.h>
#include <conio.h>
#include "UserService.h"
#include "UserSession.h"
#include "di.hpp"

using namespace std;

int main()
{
    const auto injector = boost::di::make_injector
    (
        boost::di::bind<BaseDatabase<User>>.to<UserDatabase>().in(boost::di::singleton),
        boost::di::bind<UserSession>.to<UserSession>().in(boost::di::singleton),
        boost::di::bind<BaseRepository<User>>.to<UserRepository>(),
        boost::di::bind<UserService>.to<UserService>()
    );

    UserService userService = injector.create<UserService>();
    UserSession userSession;

    int role;
    string nationalcode, password = "";
    cout << "Welcome to our bank!\n\n";

    while (true)
    {
        cout << "Choose a login panel\n\n" << "1: Admin\n2: Employee\n3: Customer\n4: Exit\n";

        while (true)
        {
            cout << "->";
            cin >> role;
            cout << "\n";
            if (role == 1 || role == 2 || role == 3)
                break;
            else if (role == 4)
            {
                cout << "Thank you for choosing our bank!\n";
                return 0;
            }
            else
                cerr << "Invalid input!\n";
        }

        bool is_loggedin = false;

        while (!is_loggedin)
        {
            cout << "Enter national code and password.\n->";
            cin >> nationalcode;
            UserService::PasswordManipulator(password);
            cout << "\n";

            try
            {
                userSession = userService.login(nationalcode, password, role, &is_loggedin);
            }

            catch (int error)
            {
                if (error == 0)
                { 
                    cout << "User not found!\n\n";
                    system("cls");
                }
                else if (error == 1)
                {
                    cout << "Wrong password or national code!\n\n";
                    system("cls");
                }
            }
        }

        int Admin_choice = 0, Employee_choice = 0, Customer_choice = 0;

        while (is_loggedin)
        {
            switch (role)
            {
                case 1:
                {
                    cout << "Choose a task\n\n1: Add a employee\n2: Add a customer\n"
                        << "3: Show employees list\n4: Show customers list\n"
                        << "5: Show all accounts\n6: Show a customer's accounts\n"
                        << "7: Show an account's transactions\n"
                        << "8: Show a customer's loans\n9: Logout\n->";
                    cin >> Admin_choice;
                    cout << "\n\n";
                    break;
                }

                case 2:
                {
                    cout << "Choose a task\n\n1: Add a cutomer\n"
                        << "2: Show customers list\n3: Show all accounts\n"
                        << "4: Show a customer's accounts\n5: New transaction\n"
                        << "6: Check applicatins for opening an account\n7: Check applications for loans\n"
                        << "8: Logout\n->";
                    cin >> Employee_choice;
                    cout << "\n\n";
                    break;
                }

                case 3:
                {
                    cout << "Choose a task\n\n1: Show accounts\n2: New transaction\n"
                        << "3: Show accounts transactions\n"
                        << "4: Request to open a new account\n5: close an existing account\n"
                        << "6: Make a loan request\n7: Logout\n->";
                    cin >> Customer_choice;
                    cout << "\n\n";
                    break;
                }
            }

            switch (Admin_choice)
            {
                case 1:
                {
                    try
                    {
                        userService.AddUser(Employee);
                    }
                    catch (int error)
                    {
                        if (error == 0)
                            cerr << "Invalid birthdate; You must be over 18 to register in our bank\n";
                    }
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 2:
                {
                    try
                    {
                        userService.AddUser(Customer);
                    }
                    catch (int error)
                    {
                        if (error == 0)
                            cerr << "Invalid birthdate; You must be over 18 to register in our bank\n";
                    }
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 3:
                {
                    userService.ShowEmployees();
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 4:
                {
                    userService.ShowCustomers();
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 5:
                {
                    userService.ShowAllAccounts(Active);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 6:
                {
                    int userId;
                    cout << "Enter user Id\n->";
                    cin >> userId;
                    cout << "\n";
                    userService.ShowAccounts(userId);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 7:
                {
                    int accountId;
                    cout << "Enter account Id\n->";
                    cin >> accountId;
                    cout << "\n";
                    userService.ShowTransactions(userSession, accountId);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 8:
                {
                    int userId;
                    cout << "Enter user Id\n->";
                    cin >> userId;
                    cout << "\n";
                    userService.ShowLoans(userId);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 9:
                {
                    userService.logout(&is_loggedin);
                    system("cls");
                    cout << "Logged out successfully!\n\n\n";
                    break;
                }
            }

            switch (Employee_choice)
            {
                case 1:
                {
                    try
                    {
                        userService.AddUser(Customer);
                    }
                    catch (int error)
                    {
                        if (error == 0)
                            cerr << "Invalid birthdate; You must be over 18 to register in our bank\n";
                    }
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 2:
                {
                    userService.ShowCustomers();
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 3:
                {
                    userService.ShowAllAccounts(Active);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 4:
                {
                    int userId;
                    cout << "Enter user Id\n->";
                    cin >> userId;
                    cout << "\n";
                    userService.ShowAccounts(userId);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 5:
                {
                    userService.NewTransaction(userSession);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 6:
                {
                    userService.ChangeAccountStatus();
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 7:
                {
                    userService.ChangeLoanStatus();
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 8:
                {
                    userService.logout(&is_loggedin);
                    system("cls");
                    cout << "Logged out successfully!\n\n\n";
                    break;
                }
            }
            
            switch (Customer_choice)
            {
                case 1:
                {
                    userService.ShowAccounts(userSession.getId());
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 2:
                {
                    userService.NewTransaction(userSession);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 3:
                {
                    int accountId;
                    userService.ShowAccounts(userSession.getId());
                    cout << "\nEnter the account id\n->";
                    cin >> accountId;
                    cout << "\n\n";
                    userService.ShowTransactions(userSession, accountId);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }
                
                case 4:
                {
                    userService.NewAccount(userSession.getId());
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 5:
                {
                    userService.CloseAccount(userSession.getId());
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }
                
                case 6:
                {
                    int accountId;
                    userService.ShowAccounts(userSession.getId());
                    cout << "\nEnter the account id that you want to get a loan on\n->";
                    cin >> accountId;
                    cout << "\n\n";
                    userService.NewLoan(accountId);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 7:
                {
                    userService.logout(&is_loggedin);
                    system("cls");
                    cout << "Logged out successfully!\n\n\n";
                    break;
                }
            }
        }
    }
}
