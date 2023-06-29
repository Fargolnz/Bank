// This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <openssl/evp.h>
#include <conio.h>
#include "../Header/UserService.h"
#include "../Header/UserSession.h"
#include "../Additional Sources/di.hpp"

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
            password = "";
            cout << "Enter national code and password (enter 0 to go back to login panel).\n->";
            cin >> nationalcode;
            if (nationalcode == "0")
            {
                system("cls");
                break;
            }
            cout << "->";
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
                    cout << "Press any key to continue!\n\n";
                    _getch();
                    system("cls");
                }
                else if (error == 1)
                {
                    cout << "Wrong password or national code!\n\n";
                    cout << "Press any key to continue!\n\n";
                    _getch();
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
                    cout << "Choose a task\n\n1: Add an employee\n2: Add a customer\n"
                        << "3: Delete an employee\n4: Delete a customer\n"
                        << "5: Show employees list\n6: Show customers list\n"
                        << "7: Show all accounts\n8: Show all loans\n"
                        << "9: Show a customer's accounts\n"
                        << "10: Show an account's transactions\n"
                        << "11: Show a customer's loans\n12: Logout\n->";
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
                        << "3: Show balance \n4: Show accounts transactions\n5: Show an account's loan\n"
                        << "6: Request to open a new account\n7: Close an existing account\n"
                        << "8: Make a loan request\n9: Deposit cash into an account\n"
                        << "10: Change password\n11: Change phone number\n12: Logout\n->";
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
                            cerr << "Invalid birthdate; You must be over 18 to register in our bank!\n";
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
                            cerr << "Invalid birthdate; You must be over 18 to register in our bank!\n";
                    }
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 3:
                {
                    userService.DeleteUser(Employee);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 4:
                {
                    userService.DeleteUser(Customer);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 5:
                {
                    userService.ShowEmployees();
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 6:
                {
                    userService.ShowCustomers();
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 7:
                {
                    userService.ShowAllAccounts(Active);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }
                case 8:
                {
                    userService.ShowAllLoans(Accepted);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 9:
                {
                    int userId;
                    cout << "Enter the user Id that you want to see its accounts\n->";
                    cin >> userId;
                    cout << "\n";
                    userService.ShowAccounts(userId);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 10:
                {
                    int accountId;
                    cout << "Enter the account Id that you want to see its transactions\n->";
                    cin >> accountId;
                    cout << "\n";
                    userService.ShowTransactions(userSession, accountId);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 11:
                {
                    int userId;
                    cout << "Enter the user Id that you want to see its loans\n->";
                    cin >> userId;
                    cout << "\n";
                    userService.ShowLoans(userId);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 12:
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
                            cerr << "Invalid birthdate; You must be over 18 to register in our bank!\n";
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
                    cout << "Enter the user Id that you want to see its accounts\n->";
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
                    cout << "\nEnter the account id that you want to see its balance\n->";
                    cin >> accountId;
                    cout << "\n";
                    userService.CheckBalance(accountId);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;

                }

                case 4:
                {
                    int accountId;
                    userService.ShowAccounts(userSession.getId());
                    cout << "\nEnter the account id that you want to see its transactions\n->";
                    cin >> accountId;
                    cout << "\n\n";
                    userService.ShowTransactions(userSession, accountId);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 5:
                {
                    int accountId;
                    userService.ShowAccounts(userSession.getId());
                    cout << "\nEnter the account id that you want to see its loans\n->";
                    cin >> accountId;
                    cout << "\n\n";
                    userService.ShowLoans(accountId);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 6:
                {
                    userService.NewAccount(userSession.getId());
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 7:
                {
                    userService.CloseAccount(userSession.getId());
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }
                
                case 8:
                {
                    int accountId;
                    userService.ShowAccounts(userSession.getId());
                    cout << "\nEnter the account id that you want to get a loan on (You can only get a loan on active accounts!)\n->";
                    cin >> accountId;
                    cout << "\n\n";
                    userService.NewLoan(accountId);
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }

                case 9:
                {
                    userService.Deposit(userSession.getId());
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }
                case 10:
                {
                    userService.ChangeUserPassword(userSession.getId());
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                }
                case 11:
                {
                    userService.ChangePhone(userSession.getId());
                    cout << endl << "Press any key to continue!\n";
                    _getch();
                    system("cls");
                    break;
                    
                }
                case 12:
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
