#include <iostream>
#include <vector>
using namespace std;

// CLASS FOR REGISTERED USERS
class userClass
{
private:
    string password;
public:
    string username;
public:
    void setUsername(string uniqueUsername) // Sets username to user's input
    {
        username = uniqueUsername;
    }
    string getUsername() // Returns username to function
    {
        return username;
    }
    void setPassword(string uniquePassword) // Sets password to user's input
    {
        password = uniquePassword;
    }
    string getPassword() // Returns password to function
    {
        return password;
    }
    bool compareUsernames(string uniqueUsername) // Sends comparison bool to usernameExists funct.
    {
        return (uniqueUsername == username);
    }
};

// GLOBAL VARIABLES
string commonPass1 = "password", commonPass2 = "123456789", commonPass3 = "password123"; // Three common passwords to prohibit users from
int userNumber = 0; // Tracks how many users are currently registered

// FUNCTION PROTOTYPES
string createPassword();
bool usernameExists(string uniqueUsername, vector<userClass> &registeredUsers, int *matchedUserPtr);
void createAccount(vector<userClass> &registeredUsers, int *matchedUserPtr);
void whenLoggedIn(vector<userClass> &registeredUsers, string uniqueUsername, int *matchedUserPtr);
void loginAccount(vector<userClass> &registeredUsers, int *matchedUserPtr);


// ++++++++++++++++
// MAIN FUNCTION
// ++++++++++++++++
int main() {
// Initialize variables and vector of objects
    vector<userClass> registeredUsers;
    string menuChoice;
    int matchedUser;
// While loops runs the program until user tells it to stop
    bool runProgram = true;
    while (runProgram)
    {
        try {
            cout << "\n--------------------------------\nHello! Please select an option:\n--------------------------------\n1. Create an account\n2. Log in\n3. Quit\n--------------------------------\n";
            cin >> menuChoice;
            if (menuChoice == "1") // 1. Create an account
            {
                createAccount(registeredUsers, &matchedUser);
            }
            else if(menuChoice == "2") // 2. Log in to an account
            {
                loginAccount(registeredUsers, &matchedUser);
            }
            else if (menuChoice == "3") // 3. Close program
            {
                cout << "Goodbye!";
                runProgram = false;
            }
            else if (menuChoice == "ADMIN") // 4. View users in system (not shown to users)
            {
                cout << "\n------------------------\n         USERS\n------------------------\n";
                for (int i=0; i<registeredUsers.size(); i++) {
                    cout << registeredUsers[i].getUsername() << endl;
                }
            } else {
                throw (menuChoice);
            } // Error thrown if user does not choose 1, 2, 3, or ADMIN
        }
        catch (...) {
            cout << "Error reading input. Try again.\n";
        } // Exception for data type error in menu screen
    }
    // Clear memory
    return 0;
}


// ++++++++++++++++++++++++++++++++++
// FUNCTION TO SET A NEW PASSWORD
// ++++++++++++++++++++++++++++++++++
string createPassword()
{
    bool goodPassword = false;
    string enterPassword, confirmPassword;
    while (!goodPassword)
    {
        cout << "Enter your desired password: ";
        cin >> enterPassword;
        if (enterPassword == commonPass1 || enterPassword == commonPass2 || enterPassword == commonPass3)
        {
            cout << "Your password is too easy to guess. Please select a different one.\n";
        }
        else
        {
            cout << "Please confirm your password: ";
            cin >> confirmPassword;
            if (enterPassword == confirmPassword)
            {
                cout << "Your password has been set.\n";
                goodPassword = true;
            }
            else
            {
                cout << "Passwords did not match, please try again.\n";
            }
        }
    }
    return enterPassword;
    enterPassword = "x";
    confirmPassword = "x";
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION TO CHECK IF A USERNAME IS ALREADY REGISTERED IN THE SYSTEM
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool usernameExists(string uniqueUsername, vector<userClass> &registeredUsers, int *matchedUserPtr)
{
    bool doesExist = false;
    bool compareResult;
    for (int i = 0; i < registeredUsers.size(); i++)
    {
        compareResult = registeredUsers[i].compareUsernames(uniqueUsername);
        if (compareResult)
        {
            doesExist = true;
            *matchedUserPtr = i;
        }
    }
    return doesExist;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION TO REGISTER A NEW USER & ADD THEM TO THE CLASS
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void createAccount(vector<userClass> &registeredUsers, int *matchedUserPtr)
{
    userClass user;
    string inputUsername, inputPassword;
// Create username
    bool goodUsername = false;
    while (!goodUsername)
    {
        cout << "Enter your desired username: ";
        cin >> inputUsername;
        bool doesUserExist = usernameExists(inputUsername, registeredUsers, &*matchedUserPtr);
        if (doesUserExist)
        {
            cout << "Username already exists.\n";
        } else {
            user.setUsername(inputUsername);
            goodUsername = true;
        }
    }
// Create password by calling setPassword() function
    inputPassword = createPassword();
    user.setPassword(inputPassword);
// Create a new object of userClass with chosen username/password
    registeredUsers.push_back(user);
    userNumber = userNumber + 1;
    inputPassword = 'x'; // Clears password from staying memory for a long time
    cout << "\nAccount successfully created! Welcome, " << inputUsername << "!\n";
    whenLoggedIn(registeredUsers, inputUsername, &*matchedUserPtr);
}


//+++++++++++++++++++++++++++++++++++
// INTERFACE WHEN USER IS LOGGED IN
//+++++++++++++++++++++++++++++++++++
void whenLoggedIn(vector<userClass> &registeredUsers, string uniqueUsername, int *matchedUserPtr)
{
    int matchedUser = *matchedUserPtr;
    bool loggedin = true;
    string menuChoice, inputPassword;
    while (loggedin)
    {
        try {
            cout << "\n--------------------------------\n1. Change password\n2. Log out\n--------------------------------\n";
            cin >> menuChoice;
            if (menuChoice == "1") // 1. Change password
            {
                cout << "Confirm your old password: ";
                cin >> inputPassword;
                    if (registeredUsers[matchedUser].getPassword() == inputPassword)
                    {
                        cout << "Password accepted.\n";
                        string newPassword = createPassword();
                        registeredUsers[matchedUser].setPassword(newPassword);
                        cout << "Your password has been changed.\n";
                        inputPassword = 'x'; // Remove password from public memory
                    }
                    cout << "Incorrect password.\n";
            }
            else if (menuChoice == "2") // 3. Log out, return to main menu
            {
                cout << "Logging out...";
                loggedin = false;
            } else {
                throw (menuChoice);
            } // Error thrown if user does not choose 1 or 2
        }
        catch (...) {
            cout << "Error reading input. Try again.\n";
        } // Exception for data type error in menu screen
    }
}


//++++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION TO LOG IN TO AN EXISTING ACCOUNT
//++++++++++++++++++++++++++++++++++++++++++++++
void loginAccount(vector<userClass> &registeredUsers, int *matchedUserPtr)
{
    int matchedUser = *matchedUserPtr;
    bool goodLogin = false;
    while (!goodLogin)
    {
        string inputUsername, inputPassword;
        cout << "Enter your username: ";
        cin >> inputUsername;
        if (inputUsername == "EXIT") // Exit to main menu if the user enters "EXIT"
        {
            goodLogin = true;
        } else {
            bool doesUserExist = usernameExists(inputUsername, registeredUsers, &*matchedUserPtr);
            // If username exists, the user is prompted to log into that account
            if (doesUserExist)
            {
                bool goodPassword = false;
                while (!goodPassword)
                {
                    cout << "Enter your password: ";
                    cin >> inputPassword;
                    if (registeredUsers[matchedUser].getPassword() == inputPassword)
                    {
                        cout << "Password accepted.\n";
                        inputPassword = 'x'; // Remove password from public memory
                        goodLogin = true;
                        goodPassword = true;
                        cout << "\nWelcome back, " << inputUsername << "!\n";
                        whenLoggedIn(registeredUsers, inputUsername, &*matchedUserPtr);
                    }
                    else if (inputPassword == "FORGOT")
                    {
                        string forgotPassword = createPassword();
                        registeredUsers[matchedUser].setPassword(forgotPassword);
                    }
                    else {
                        cout << "Invalid password. Try again or type \"FORGOT\"\n";
                    }
                }
            } else { // If username DOES NOT exist
                cout << "Username not found. Type \"EXIT\" to exit\n";
            }
        }
    }
}
