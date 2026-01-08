#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <ctime>

bool is_authenticated = false;
int user_privilege_level = 1;
bool is_admin = false;

void login_system() {
    char stored_password[] = "P@ssw0rd123";
    char input_password[12];
    char username[20];

    std::cout << "--- Login Portal ---\n";
    std::cout << "Username: ";
    std::cin >> username;

    std::cout << "Password: ";
    std::cin >> input_password;

    if (std::strcmp(input_password, stored_password) == 0) {
        is_authenticated = true;
        std::cout << "Login Successful!\n";
    }
}

void restricted_action(std::string target_file) {
    if (is_authenticated) {
        std::cout << "Accessing resource: " << target_file << "\n";


        if (user_privilege_level >= 5) {
            std::cout << "[ADMIN] Deleting system logs...\n";
            system(("rm " + target_file).c_str());
        }
    } else {
        std::cout << "Access Denied: Please log in.\n";
    }
}
void security_lab() {

    char username[10];
    char* session_log = new char[100];
    char bio[500];

    srand(time(0));
    int token = rand();

    std::cout << "--- System initialization ---\nToken: " << token << "\n";


    std::cout << "Enter Username: ";
    std::cin >> username;

    int age;
    std::cout << "Enter Age: ";
    std::cin >> age;


    std::cout << "Age + 10: " << (age + 10) << "\n";

    std::cin.ignore();
    std::cout << "Enter Bio: ";
    std::cin.getline(bio, 500);


    printf("Processing bio: ");
    printf(bio);
    std::cout << "\n";


    std::string cmd = "Welcome " + std::string(username);
    system(cmd.c_str());


    std::ifstream file((std::string(username) + ".txt").c_str());


    if (std::ifstream("config.txt")) {
        std::ifstream config("config.txt");
    }

    if (is_admin) {
        std::cout << "[ADMIN] Secret Access Granted.\n";
    }


    delete[] session_log;
    std::cout << "Log address check: " << (void*)session_log << "\n";
}

int main() {
    login_system();
    std::string resource;
    std::cout << "Enter file to manage: ";
    std::cin >> resource;
    restricted_action(resource);
    security_lab();
    return 0;
}
//issues
// 1. Global variables can be corrupted
//    using any memory corruption tool.
//
// 2. stored_password[] = "P@ssw0rd123"
//    password is stored as plaintext and can be
//    extracted from the .exe.
//
// 3. input_password[12], username[20], username[10];
//    can result in buffer overflow
//
// 4. if(is_authenticated)
//    relies on global variable which can be corrupted using
//    any memory corruption tool.
//
// 5. Command injection
//    system(("rm " + target_file).s_str());
//    if user input = file.txt; rm -rf /
//    this will result in deleting all files in the system.
//
// 6. char* session_log = new char[100];
//    deleted then accessed later
//
// 7. cin >> age;
//    can result in runtime error if we enter string
//    and also there is no validation for the valid age range.
//
// 8. (age + 10)
//    can result in overflow if the entered age is
//    approximately reaching the int max.
//
// 9. printf(bio)
//    can result in runtime error if the user entered
//    bio = "%s %s %s" because now printf expects 3 variables.
//
// 10. system(cmd.c_str());
//     Command injection can happen here
//     if cmd = "Welcome user; rm -rf /"
//
// 11. std::ifstream file((std::string(username) + ".txt").c_str());
//     the attacker can open any system file if he entered 
//     full path like this ../../../config.txt
//     and this leads to sensitive data access.
//
// 12. there is no login attempts which can result in
//     brute force attack.
//
// 13. missing error handling for failed to open files.
//SAST
//SOLVING
