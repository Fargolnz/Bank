#include <iomanip>
#include <ctime>
#include <stdexcept>
#include <conio.h>
#include "../Header/UserService.h"

using namespace std;


UserService::UserService(UserRepository& userRepository, AccountRepository& accountRepository, TransactionRepository& transactionRepository, LoanRepository& loanRepository) : 
    userRepository(userRepository), accountRepository(accountRepository), loanRepository(loanRepository), transactionRepository (transactionRepository)
{
    userRepository.init();
    accountRepository.init();
    transactionRepository.init();
    loanRepository.init();
}

UserSession UserService::login(string nationalCode, string password, int role, bool* is_loggedin)
{
	User* user = userRepository.getByNationalCode(nationalCode);

	if (user == nullptr)
	{
        throw 0;
	}

	StringHasher hasher;
	string dbPassword = user->getPassword();	// User password
	bool correctPassword = hasher.verify(password, dbPassword);		// Verify password

	if (correctPassword && role == user->getRole())
	{
        system("cls");
        cout << "Login was succssesful!\n\nWelcome " << user->getName() << "!\n\n";
		*is_loggedin = true;
		UserSession User_Session(user->getId(), user->getRole());
		return User_Session;
	}
    else
    {
        throw 1;
    }
}

void UserService::logout(bool* is_loggedin)
{
    *is_loggedin = false;
}

void UserService::PasswordManipulator(string& password)
{
    char ch;
    while ((ch = _getch()) != '\r')  // Loop until Enter key is pressed
    { 
        if (ch == '\b') // Handle backspace
        {  
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";  // Erase the last character from the console
            }
        }
        else {
            password += ch;
            std::cout << "*";
        }
    }
    std::cout << std::endl;
}

void UserService::unixToDatetime(time_t unix)
{
    char str[26];
    ctime_s(str, sizeof str, &unix);
    printf("%s", str);
}

void UserService::AddUser(RoleEnum calledRole)
{
    string nationalCode;
	string name;
	string phone;
	string password;
	string stringBirthDate;
	time_t joinDate = time(nullptr);
	GenderEnum gender;
	RoleEnum role;

    cout << "Enter the national code: ";
    cin >> nationalCode;
    cin.ignore();

    cout << "Enter the name: ";
    getline(cin, name);

    cout << "Enter the phone number: ";
    cin >> phone;
    cin.ignore();

    cout << "Enter the password: ";
    UserService::PasswordManipulator(password);
    StringHasher hasher;
    password = hasher.hash(password);

    cout << "Enter the birthdate in the format dd/mm/yyyy: ";
    getline(cin, stringBirthDate);
    tm time_struct = {};
    istringstream ss(stringBirthDate);
    ss >> get_time(&time_struct, "%d/%m/%Y");
    time_t birthDate;
    cout << '\b';

    if (time(nullptr) - mktime(&time_struct) >= 567981000)
    {
        birthDate = mktime(&time_struct);
    }
    else
    {
        throw 0;
    }

    cout << "Enter the gender:\n1: Male\n2: Female\n->";
    int stringGender;
    cin >> stringGender;

    switch (stringGender)
    {
        case 1: {gender = Male; break; }
        case 2: {gender = Female; break; }
        default: {cerr << "Invalid Input!!\nGender set to Male by default\n"; gender = Male; break; }
    }

    User user(nationalCode, name, phone, password, birthDate, joinDate, gender, role = calledRole);
    userRepository.add(user);
    userRepository.save();
    userRepository.reloadEntities();

    switch (calledRole)
    {
        case 2: {cout << "Employee"; break; }
        case 3: {cout << "Customer"; break; }
    }
    cout << " added successfully!\n\n\n";
    cout << "Create an account for your ";
    switch (calledRole)
    {
        case 2: {cout << "employee:\n\n"; break; }
        case 3: {cout << "customer:\n\n"; break; }
    }
    this->NewAccount(user.getId());
}

void UserService::NewAccount(int userId)
{
    double balance;
    int intType;
    AccountTypeEnum type;
    AccountStatusEnum status;

    cout << "Enter the balance: ";
    cin >> balance;
    cin.ignore();


    cout << "Enter the account type:\n1: Current\n2: LongTerm\n3: ShortTerm\n->";
    cin >> intType;
    cin.ignore();

    switch (intType)
    {
        case 1: {type = Current; break; }
        case 2: {type = LongTerm; break; }
        case 3: {type = ShortTerm; break; }
    }

    Account account(userId, balance, type, status = Pending, time(nullptr));
    accountRepository.add(account);
    accountRepository.save();
   accountRepository.reloadEntities();

    cout << "Account request sent successfully!\n";
}

void UserService::NewTransaction(UserSession userSession)
{
    if (userSession.getRole() == RoleEnum::Employee)
    {
        int senderAccountId, receiverAccountId;
        this->ShowAllAccounts(Active);
        cout << "\nChoose the sender account id\n->";
        cin >> senderAccountId;
        cout << "\n";
        cout << "Choose the receiver account id\n->";
        cin >> receiverAccountId;
        cout << "\n";

        if (accountRepository.SearchAccountId(senderAccountId) &&
            accountRepository.SearchAccountId(receiverAccountId) &&
            accountRepository.CheckStatus(senderAccountId) &&
            accountRepository.CheckStatus(receiverAccountId))
        {
            double amount;
            cout << "Please enter the amount of money\n->";
            cin >> amount;
            cout << "\n";

            if (accountRepository.CheckAmount(senderAccountId, amount))
            {
                string password;
                cout << "Enter password\n->";
                UserService::PasswordManipulator(password);
                cout << "\n";
                Account* account = accountRepository.getById(senderAccountId);
                User* user = userRepository.getById(account->getUserId());
                StringHasher hasher;
                string dbPassword = user->getPassword();	// User password
                bool correctPassword = hasher.verify(password, dbPassword);		// Verify password

                if (correctPassword)
                {
                    accountRepository.Withdraw(senderAccountId, amount);
                    accountRepository.Deposit(receiverAccountId, amount);
                    Transaction transaction(senderAccountId, receiverAccountId, amount, time(nullptr));
                    transactionRepository.add(transaction);
                    transactionRepository.save();
                    transactionRepository.reloadEntities();
                    cout << "Transaction was successful!\n";
                }
                else
                    cerr << "Wrong password!\n";
            }
            else
                cerr << "Insufficient balance:(\n";
        }
        else
            cerr << "Invalid account id!\n";
    }

    else
    {
        int senderAccountId, receiverAccountId;
        this->ShowAccounts(userSession.getId());
        cout << "\nChoose the sender account id (You can only transfer from your active accounts!)\n->";
        cin >> senderAccountId;
        cout << "\n";
        cout << "Enter the receiver account id\n->";
        cin >> receiverAccountId;
        cout << "\n";

        if (accountRepository.SearchAccountId(senderAccountId) &&
            accountRepository.SearchAccountId(receiverAccountId) &&
            accountRepository.CheckStatus(senderAccountId) &&
            accountRepository.CheckStatus(receiverAccountId))
        {
            double amount;
            cout << "Please enter the amount of money\n->";
            cin >> amount;
            cout << "\n";

            if (accountRepository.CheckAmount(senderAccountId, amount))
            {
                string password;
                cout << "Enter password\n->";
                UserService::PasswordManipulator(password);
                cout << "\n";
                Account* account = accountRepository.getById(senderAccountId);
                User* user = userRepository.getById(account->getUserId());
                StringHasher hasher;
                string dbPassword = user->getPassword();	// User password
                bool correctPassword = hasher.verify(password, dbPassword);		// Verify password

                if (correctPassword)
                {
                    accountRepository.Withdraw(senderAccountId, amount);
                    accountRepository.Deposit(receiverAccountId, amount);
                    Transaction transaction(senderAccountId, receiverAccountId, amount, time(nullptr));
                    transactionRepository.add(transaction);
                    transactionRepository.save();
                    transactionRepository.reloadEntities();
                    cout << "Transaction was successful!\n";
                }
                else
                    cerr << "Wrong password!\n";
            }
            else
                cerr << "Insufficient balance:(\n";
        }
        else
            cerr << "Invalid account id!\n";
    }
}

void UserService::NewLoan(int accountId)
{
    Account* account = accountRepository.getById(accountId);

    if (account->getStatus() == Active)
    {
        double totalAmount;
        double leftAmount;
        double rate;
        LoanStatusEnum status;

        cout << "Enter the amount of loan: ";
        cin >> totalAmount;
        cin.ignore();

        cout << "Enter the rate of loan: ";
        cin >> rate;
        cin.ignore();

        leftAmount = ((rate / 100) * totalAmount) + totalAmount;

        Loan loan(accountId, totalAmount, leftAmount, rate, status = Awaitence, time(nullptr));
        accountRepository.Deposit(accountId, totalAmount);

        loanRepository.add(loan);
        loanRepository.save();
        loanRepository.reloadEntities();

        cout << "Loan request sent successfully!\n";
    }
    else
        cerr << "Invalid account id!\n";
}

void UserService::ShowEmployees()
{
    cout << left << "Employees List:\n\n" << setw(16) << "Employee Id" << setw(18) << "National Code" << setw(15) << "Name"
        << setw(15) << "Phone" << setw(10) << "Gender" << setw(15) << "Join Date" << endl << endl;

    for (auto employee : userRepository.getAll())
    {
        if (employee->getRole() == RoleEnum::Employee)
        {
            cout << left << setw(16) << employee->getId() << setw(18) << employee->getNationalCode()
                << setw(15) << employee->getName() << setw(15) << employee->getPhone();

            switch (employee->getGender())
            {
                case 1:
                {
                    cout << left << setw(10) << "Male";
                    break;
                }

                case 2:
                {
                    cout << left << setw(10) << "Female";
                    break;
                }
            }

            cout << left << setw(15);
            unixToDatetime(employee->getJoinDate());
        }
    }
}

void UserService::ShowCustomers()
{
    cout << left << "Customers List:\n\n" << setw(16) << "Customer Id" << setw(18) << "National Code" << setw(10) << "Name"
        << setw(15) << "Phone" << setw(10) << "Gender" << setw(15) << "Join Date" << endl << endl;

    for (auto customer : userRepository.getAll())
    {
        if (customer->getRole() == RoleEnum::Customer)
        {
            cout << left << setw(16) << customer->getId() << setw(18) << customer->getNationalCode()
                << setw(10) << customer->getName() << setw(15) << customer->getPhone();

            switch (customer->getGender())
            {
                case 1:
                {
                    cout << left << setw(10) << "Male";
                    break;
                }

                case 2:
                {
                    cout << left << setw(10) << "Female";
                    break;
                }
            }

            cout << left << setw(15);
            unixToDatetime(customer->getJoinDate());
        }
    }
}

bool UserService::ShowAllAccounts(AccountStatusEnum status)
{
    bool found = false;
    cout << left << "All accounts list:\n\n" << setw(15) << "Account Id" << setw(10) << "User Id" << setw(10) << "Balance"
        << setw(15) << "Account Type" << setw(18) << "Account Status" << setw(15) << "Create Date" << endl << endl;

    if (status == Active)
    {
        for (auto account : accountRepository.getAll())
        {
            if (account->getStatus() == Active)
            {
                found = true;
                cout << left << setw(15) << account->getId() << setw(10) << account->getUserId()
                    << setw(10) << account->getBalance();

                switch (account->getType())
                {
                    case 1:
                    {
                        cout << left << setw(15) << "Current";
                        break;
                    }

                    case 2:
                    {
                        cout << left << setw(15) << "Long Term";
                        break;
                    }

                    case 3:
                    {
                        cout << left << setw(15) << "Short Term";
                        break;
                    }
                }

                switch (account->getStatus())
                {
                    case 1:
                    {
                        cout << left << setw(18) << "Active";
                        break;
                    }

                    case 2:
                    {
                        cout << left << setw(18) << "Pending";
                        break;
                    }

                    case 3:
                    {
                        cout << left << setw(18) << "Deactive";
                        break;
                    }
                }

                cout << left << setw(15);
                unixToDatetime(account->getCreateDate());
            }
        }
    }

    else if (status == Pending)
    {
        for (auto account : accountRepository.getAll())
        {
            if (account->getStatus() == Pending)
            {
                found = true;
                cout << left << setw(15) << account->getId() << setw(10) << account->getUserId()
                    << setw(10) << account->getBalance();

                switch (account->getType())
                {
                    case 1:
                    {
                        cout << left << setw(15) << "Current";
                        break;
                    }
                    case 2:
                    {
                        cout << left << setw(15) << "Long Term";
                        break;
                    }
                    case 3:
                    {
                        cout << left << setw(15) << "Short Term";
                        break;
                    }
                }

                switch (account->getStatus())
                {
                    case 1:
                    {
                        cout << left << setw(18) << "Active";
                        break;
                    }
                    case 2:
                    {
                        cout << left << setw(18) << "Pending";
                        break;
                    }
                    case 3:
                    {
                        cout << left << setw(18) << "Deactive";
                        break;
                    }
                }

                cout << left << setw(15);
                unixToDatetime(account->getCreateDate());
            }
        }
    }
    return found;
}

void UserService::ShowAccounts(int userId)
{
    cout << left << "Accounts list:\n\n" << setw(15) << "Account Id" << setw(10) << "User Id" << setw(10) << "Balance"
        << setw(15) << "Account Type" << setw(18) << "Account Status" << setw(15) << "Create Date" << endl << endl;

    for (auto account : accountRepository.getAll())
    {
        if (account->getUserId() == userId && (account->getStatus() == Active || account->getStatus() == Pending))
        {
            cout << left << setw(15) << account->getId() << setw(10) << account->getUserId()
                << setw(10) << account->getBalance();

            switch (account->getType())
            {
                case 1:
                {
                    cout << left << setw(15) << "Current";
                    break;
                }

                case 2:
                {
                    cout << left << setw(15) << "Long Term";
                    break;
                }

                case 3:
                {
                    cout << left << setw(15) << "Short Term";
                    break;
                }
            }

            switch (account->getStatus())
            {
                case 1:
                {
                    cout << left << setw(18) << "Active";
                    break;
                }

                case 2:
                {
                    cout << left << setw(18) << "Pending";
                    break;
                }
            }

            cout << left << setw(15);
            unixToDatetime(account->getCreateDate());
        }
    }
}

void UserService::ShowTransactions(UserSession userSession, int accountId)
{
    if (userSession.getRole() == Admin)
    {
        cout << left << "Transactions list:\n\n" << setw(20) << "Sender Account Id" << setw(23) << "Receiver Account Id"
            << setw(10) << "Amount" << setw(15) << "Date" << endl << endl;

        for (auto transaction : transactionRepository.getAll())
        {
            if (transaction->getSenderAccountId() == accountId)
            {
                cout << left << setw(20) << transaction->getSenderAccountId()
                    << setw(23) << transaction->getReceiverAccountId() << "-" << setw(10) << transaction->getAmount()
                    << setw(15);
                unixToDatetime(transaction->getDate());
            }

            else if (transaction->getReceiverAccountId() == accountId)
            {
                cout << left << setw(20) << transaction->getSenderAccountId()
                    << setw(23) << transaction->getReceiverAccountId() << "+" << setw(10) << transaction->getAmount()
                    << setw(15);
                unixToDatetime(transaction->getDate());
            }
        }
        cout << "\n";
        this->CheckBalance(accountId);
    }

    else
    {
        cout << left << "Transactions list:\n\n" << setw(20) << "Sender Account Id" << setw(23) << "Receiver Account Id"
            << setw(10) << "Amount" << setw(15) << "Date" << endl << endl;

        for (auto transaction : transactionRepository.getAll())
        {
            if (transaction->getSenderAccountId() == accountId)
            {
                cout << left << setw(20) << transaction->getSenderAccountId()
                    << setw(23) << transaction->getReceiverAccountId() << "-" << setw(10) << transaction->getAmount()
                    << setw(15);
                unixToDatetime(transaction->getDate());
            }

            else if (transaction->getReceiverAccountId() == accountId)
            {
                cout << left << setw(20) << transaction->getSenderAccountId()
                    << setw(23) << transaction->getReceiverAccountId() << "+" << setw(10) << transaction->getAmount()
                    << setw(15);
                unixToDatetime(transaction->getDate());
            }
        }
        cout << "\n";
        this->CheckBalance(accountId);
    }
}

void UserService::ShowAllLoans(LoanStatusEnum status)
{
    cout << left << setw(10) << "Loan Id" << setw(15) << "Account Id" << setw(15) << "Total Amount"
        << setw(15) << "Left Amount" << setw(10) << "Rate" << setw(14) << "Status"
        << setw(15) << "Create Date" << endl << endl;

    if (status == Accepted)
    {
        for (auto loan : loanRepository.getAll())
        {
            cout << left << setw(10) << loan->getId() << setw(15) << loan->getAccountId() << setw(15)
                << loan->getTotalAmount() << setw(15) << loan->getLeftAmount() << setw(10) << loan->getRate();

            switch (loan->getStatus())
            {
                case 1: {cout << left << setw(14) << "Accepted"; break; }
                case 2: {cout << left << setw(14) << "Awaitence"; break; }
                case 3: {cout << left << setw(14) << "Declined"; break; }
            }

            cout << left << setw(15);
            unixToDatetime(loan->getCreateDate());
        }
    }

    else if (status == Awaitence)
    {
        for (auto loan : loanRepository.getAll())
        {
            if (loan->getStatus() == Awaitence)
            {
                cout << left << setw(10) << loan->getId() << setw(15) << loan->getAccountId() << setw(15)
                    << loan->getTotalAmount() << setw(15) << loan->getLeftAmount() << setw(10) << loan->getRate();
                
                switch (loan->getStatus())
                {
                    case 1: {cout << left << setw(14) << "Accepted"; break; }
                    case 2: {cout << left << setw(14) << "Awaitence"; break; }
                    case 3: {cout << left << setw(14) << "Declined"; break; }
                }
                
                cout << left << setw(15);
                unixToDatetime(loan->getCreateDate());
            }
        }
    }
}

void UserService::ShowLoans(int accountId)
{
    cout << left << setw(10) << "Loan Id" << setw(15) << "Account Id" << setw(15) << "Total Amount"
        << setw(15) << "Left Amount" << setw(10) << "Rate" << setw(14) << "Status"
        << setw(15) << "Create Date" << endl << endl;

    for (auto loan : loanRepository.getAll())
    {
        if (loan->getAccountId() == accountId)
        {
            cout << left << setw(10) << loan->getId() << setw(15) << loan->getAccountId() << setw(15)
                << loan->getTotalAmount() << setw(15) << loan->getLeftAmount() << setw(10) << loan->getRate();
            
            switch (loan->getStatus())
            {
                case 1: {cout << left << setw(14) << "Accepted"; break; }
                case 2: {cout << left << setw(14) << "Awaitence"; break; }
                case 3: {cout << left << setw(14) << "Declined"; break; }
            }

            cout << left << setw(15);
            unixToDatetime(loan->getCreateDate());
        }
    }
}

void UserService::ChangeAccountStatus()
{
    int accountId, choice;
    if (this->ShowAllAccounts(AccountStatusEnum::Pending))
    {
        cout << "\nChoose the account id to accept or decline the request.\nThen choose 1 to accept or 2 to decline\n->";
        cin >> accountId >> choice;
        Account* account = accountRepository.getById(accountId);

        if (choice == 1)
        {
            account->setStatus(Active);
            cout << "Status set to active!\n";
        }

        else if (choice == 2)
        {
            account->setStatus(Deactive);
            cout << "Status set to deactive!\n";
        }

        else
            cerr << "Invalid input!\n";

        accountRepository.save();
        accountRepository.reloadEntities();
    }
    else
        cerr << "There is no Account to check status!\n";
}

void UserService::ChangeLoanStatus()
{
    int loanId, choice;
    this->ShowAllLoans(Awaitence);
    cout << "\nChoose the loan id to accept or decline the request.\nThen choose 1 to accept or 2 to decline\n->";
    cin >> loanId >> choice;
    Loan* loan = loanRepository.getById(loanId);

    if (choice == 1)
    {
        loan->setStatus(Accepted);
        cout << "Status set to accepted!\n";
    }

    else if (choice == 2)
    {
        loan->setStatus(Declined);
        cout << "Status set to declined!\n";
    }

    else
        cerr << "Invalid input!\n";

    loanRepository.save();
    loanRepository.reloadEntities();
}

void UserService::Deposit(int userId)
{
    int accountId;
    this->ShowAccounts(userId);
    cout << "\nEnter the account id that you want to deposit cash to\n->";
    cin >> accountId;
    cout << "\n";
    Account* account = accountRepository.getById(accountId);
    if (account->getUserId() == userId)
    {
        int cash;
        cout << "Enter the cash amount you want to deposit\n->";
        cin >> cash;
        accountRepository.Deposit(accountId, cash);
        cout << "Deposit was successful!\n";
    }
    else
        cerr << "The entered accountId is not vaild!\n";
}

void UserService::CloseAccount(int userId)
{
    int accountId;
    this->ShowAccounts(userId);
    cout << "\nEnter the account id that you want to close\n->";
    cin >> accountId;
    cout << "\n";
    Account* account = accountRepository.getById(accountId);

    if (account->getUserId() == userId)
    {
        accountRepository.remove(accountId);
        accountRepository.save();
        accountRepository.reloadEntities();
        cout << "\nAccount closed successfully!\n";
    }

    else
        cerr << "Invalid account id!\n";
}

void UserService::ChangeUserPassword(int userId)
{
    string password, newPassword;
    User* user = userRepository.getById(userId);
    cout << "Enter your current password\n->";
    this->PasswordManipulator(password);

    StringHasher hasher; 
    string dbPassword = user->getPassword();	
    bool correctPassword = hasher.verify(password, dbPassword);

    if (correctPassword)
    {
        cout << "Enter new password\n->";
        this->PasswordManipulator(newPassword);
        hasher.hash(newPassword);
        user->setPassword(newPassword);
        cout << "Password changed successfully!\n";
    }
    else
        cerr << "Wrong password!\n";
}

void UserService::ChangePhone(int userId)
{
    string newPhone;
    User* user = userRepository.getById(userId);
    cout << "Enter new phone number\n->";
    cin >> newPhone;
    user->setPhone(newPhone);
    cout << "Phone number changed successfully!\n";
}

void UserService::DeleteUser(RoleEnum role)
{
    if (role == Employee)
    {
        int userId;
        this->ShowEmployees();
        cout << "\nChoose the employee id that you want to remove\n->";
        cin >> userId;
        User* user = userRepository.getById(userId);
        if (user != nullptr)
        {
            userRepository.remove(userId);
            userRepository.save();
            userRepository.reloadEntities();
            cout << "\nUser removed successfuly!\n";
        }
        else
            cerr << "Invalid user id!\n";
    }
    else if (role == Customer)
    {
        int userId;
        this->ShowCustomers();
        cout << "\nChoose the customer id that you want to remove\n->";
        cin >> userId;
        User* user = userRepository.getById(userId);

        if (user != nullptr)
        {
            userRepository.remove(userId);
            userRepository.save();
            userRepository.reloadEntities();
            cout << "\nUser removed successfuly!\n";
        }
        else
            cerr << "Invalid user id!\n";
    }
}

void UserService::CheckBalance(int accountId)
{
    Account* account = accountRepository.getById(accountId);
    if (account != nullptr)
    {
        cout << "Current balance: " << account->getBalance() << "\n";
    }
    else
        cerr << "Account id is not valid!\n";
}
