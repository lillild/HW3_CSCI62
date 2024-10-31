#include "network.h"
#include "user.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

void menu(){ 
	std::cout<< "\nHi, Dear user! Here is the selection menu:\n"<<std::endl;
	std::cout<< "\n1. Adding a user \n"<<std::endl;
	std::cout<< "\n2. Add a friend connection\n"<<std::endl;
	std::cout<< "\n3. Delete a friend connection\n"<<std::endl;
	std::cout<< "\n4. Write to file\n"<<std::endl;
    std::cout<< "\n5: View recent posts for a user\n"<<std::endl;
	std::cout<< "\nPlease make your selection by typing in the selection number:\n"<<std::endl;
}

// ./test 1
//
// argv -> ["./test", "user.txt"]
//              0      1  
//
// argc -> 2 (size of argv)

int main (int argc, char *argv[]) {
    
    if(argc != 3){
        std::cerr << "ERROR - Usage: " << argv[0] << "<Number>" << std::endl;
        return EXIT_FAILURE;
    }


    bool keepRunning = true;
    Network network;


    // Read users from the file passed as an argument
    network.readUsers(argv[1]);
    network.readPosts(argv[2]);


    // Debugging: Check how many users were loaded
    std::cout << "Number of users loaded: " << network.numUsers() << std::endl;



    do{

        menu();
        int user_input;
        if(!(std::cin >> user_input)){
            std::cerr << "ERROR: Invalid Value" << std::endl;
            return EXIT_FAILURE;
        }

        if(user_input==1){    
            std::string firstName;
            std::string lastName;
            std::string name;
            int year;
            int zip;
            std::cout << "Enter firstname, lastname, birth year, and zip code: ";
            std::cin >> firstName >> lastName >> year >> zip;
            name = firstName + " " + lastName;

            // Add new user to the network
            User* newUser = new User(network.numUsers(), name, year, zip, std::set<int>{});
            network.addUser(newUser);
            std::cout << "User " << name << " added." << std::endl;
        }

		//add friend connection
        else if(user_input==2){ 
            std::string firstUser;
            std::string secondUser;
            std::string firstName1;
            std::string lastName1;
            std::string firstName2;
            std::string lastName2;

            std::cout << "Enter first user (fistname and last name): ";
            std::cin >> firstName1 >> lastName1;
            std::cout << "Enter second user (fistname and last name): ";
            std::cin >> firstName2 >> lastName2;
            firstUser = firstName1 + " " + lastName1;
            secondUser = firstName2 + " " + lastName2;

            int result = network.addConnection(firstUser, secondUser);
            if (result == 0) {
                std::cout << "Connection added between " 
                    << firstUser << " and " << secondUser << std::endl;
            }
        }
        //delete a friend connection
        else if (user_input==3){ 
                std::string firstUser;
                std::string secondUser;
                std::string firstName1;
                std::string lastName1;
                std::string firstName2;
                std::string lastName2;

                std::cout << "Enter first user (fistname and last name): ";
                std::cin >> firstName1 >> lastName1;
                std::cout << "Enter second user (fistname and last name): ";
                std::cin >> firstName2 >> lastName2;
                firstUser = firstName1 + " " + lastName1;
                secondUser = firstName2 + " " + lastName2;

                int result = network.deleteConnection(firstUser, secondUser);
            if (result == 0) {
                std::cout << "Connection deleted between " 
                    << firstUser << " and " << secondUser << "." << std::endl;
            }
        }

        else if (user_input==4){ 
            std::string outFilename;
            std::cout << "Enter filename to write data to: ";
            std::cin >> outFilename;

            network.writeUsers(outFilename.c_str());
            std::cout << "Network data written to " << outFilename 
                << " with " << network.numUsers() << " users." << std::endl;

        }


        else if (user_input == 5) {
            std::cout << "Enter query in format: <First Name> <Last Name> <Number of posts>: ";
            std::cin.ignore();  // Clear any remaining newline
            std::string fullName; 
            std::getline(std::cin, fullName);

            std::istringstream StrmIn(fullName);
            std::string firstName, lastName;
            int numPosts;
            StrmIn >> firstName >> lastName >> numPosts;

            std::string inputFullName = firstName + " " + lastName;

            // Manually search for the user by full name
            int userId = -1;
            for (const User* user : network.GETUSER_GETTER()) {
                if (user->getName() == inputFullName) {  // Use getName() which returns the full name
                    userId = user->getId();
                    break;
                }
            }

            if (userId == -1) {
                std::cerr << "User not found\n";
            } else {
                std::string recentPosts = network.getPostsString(userId, numPosts, false);  // `false` to show all posts
                if (recentPosts.empty()) {
                    std::cout << "No posts found for this user.\n";
                } else {
                    std::cout << "Recent posts for " << inputFullName << ":\n";
                    std::cout << recentPosts << "\n";
                }
            }
        }
    }while(keepRunning);

    return EXIT_SUCCESS;

}
