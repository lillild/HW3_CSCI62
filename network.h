#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>
#include <queue>


class Network{
//a vector of User ponter 
std::vector<User*> users_;


//we need a dfault contructor
//User* getUser(int id)
//void addUser(User*)
//int addConnection(string s1, string s2)
//int deleteConnection(string s1, string s2)
//int getId(string name)
//int numUsers()
public:
	//Defalt constructor 
	//pre:
	//post: create default values for each
	Network();

	//Destructor 
	~Network();

	//pre: takes in an ID
	//post: returns a pointer to the corresponding User
	//		if user not found return nullptr
	User* getUser(int id);

		//pre: takes a string into the [firstname][lastname]
	//post:return the id for that user
	//	   return -1 if no user exists
	int getId(std::string name);

	//pre: takes in a pinter to a new User object
	//post: adds the User to Network database
	void addUser(User*);

	//pre: takes two strings [firstname] [lastname] 
	//post: add a connection (addfriend in user??)if it doesnt exist
	//      return -1 if either user is invalid
	//      and 0 otherwise(else)
	int addConnection(std::string s1, std::string s2);

	//pre: takes two strings [firstname] [lastname]
	//post:delete the friend connection if it exists.
	//	   Return -1 if either user is invalid 
	//	   and 0 otherwise(else)
	int deleteConnection(std::string s1, std::string s2);

	//pre:
	//post:returns the number of Users in the Network
	int numUsers();


    //File I/O

    //pre: readin a file 
    //post:initialized all the liness into user and network
    void readUsers(const char* filename); 



    //pre: provided network
    //post:export a file
    void writeUsers(const char* filename);



//HW2
    //pre: take in from(which is the friend to start BFS) and to
    //post: return the shortest path to to (the ending friend )
    std::vector<int> shortestPath(int from, int to);
 


	//pre: take in from, to, and distance
    //post: if a user exist with the exact distance from from, returns the shortest path to that user 
    //		and sets to to the user’s ID. If no such user exists, returns an empty vector and sets 
    //		to to -1.
    std::vector<int> distanceUser(int from, int& to, int distance);


    //pre: take in a who, user id must be valid in network
    //post:Returns a list of friend suggestions for the user with the given ID who, 
    //		and sets score to the highest number of mutual friends found. 
	std::vector<int> suggestFriends(int who, int& score);



	//DFS functions 
	//pre: cur is a user ID, vector called group, visited
	//post: recursion helper
	void dfsHelper(int cur, std::vector<int>& group, std::vector<bool>& visited);


	// Entry point for DFS, calls disHelper to actually perform the search
	//pre: startuser is a user ID, group, visited
	//post: fill group with all users connecter to 'startUser' mark visited 
	void dfs(int startUser, std::vector<int>& group, std::vector<bool>& visited);


	//pre:
	//post:Returns a vector of vectors,  each inner vector who all have paths to one another 
	//		but have no edges to all other uses.
	std::vector<std::vector<int> >groups();


/*
+addPost(ownerId:int, message:string, likes:int,
         isIncoming:bool, authorName:string, isPublic:bool): void
+getPostsString(ownerId:int, howMany:int, showOnlyPublic:bool): string
*/


	// Pre: check ownerId 
	// Post: Adds a post to the specific user's messages
    void addPost(int ownerId, const std::string& message, int likes, bool isIncoming, const std::string& authorName, bool isPublic);




	// Pre: check ownerId 
	// Post: Returns a  string of posts for the specific user
    std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic) const;


    //Pre:
    //Post: Reads posts from a file
    int readPosts(const char* fname);

    //Pre:
    //Post: Comparison function 
    static bool comparePosts(const Post* a, const Post* b);

    //Pre:
    //Post: Writes posts to a file
    int writePosts(const char* fname) const;


    const std::vector<User*>& GETUSER_GETTER() const;

    };



#endif
