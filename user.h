#ifndef USER_H
#define USER_H
#include <string>
#include <set>
#include<cassert>
#include "post.h"

class User {
//id
//name_
//year_
//zip_
//friend_

	// Internal Variables
	int id_;
	std::string name_;
	int year_;
	int zip_;
	std::set<int> friends_;
	std::vector<Post*> messages_;  //HW3




//we need default contructor
// 		  primary contructor
//accessors for id, name, year, zip, friend 
//add Friend void 
//delete Friend void
public:
	//Default contructor
	//pre:
	//post:create default values for each
	User();

	//Primary contructor
	//pre: 
	//post: create default values for each 
 	User(int id_, std::string name_, int year_, int zip_, std::set<int>friends_);

 	// Destructor
 	~User();




/* 
Example for Getters
  vector<int> getVec () { return vec; };
  vector<int> & getVecRef () { return vec; };
*/

 	//Getter for ID
 	//pre:
 	//post: return the user's id
 	int getId()const;


 	//Getter for NAME
 	//pre: 
 	//post: return the user's name
 	const std::string& getName()const;


	//Getter for YEAR
 	//pre: 
 	//post: return the user's year
 	int getYear()const;


 	//Getter for ZIP
 	//pre: 
 	//post: return the user's zip
 	int getZip()const;


 	//Getter for FRIEND
 	//pre: 
 	//post: return the user's friend (set)
 	std::set<int>& getFriends();                //cant be const or cant pass test_user_get_friend_reference (test_subprocess.TestDiff)



 	//pre: prompt the user to enter the id which is valid
 	//post: check the set if it already includes this id,
 	//		if so do nothing. If not add the id into the 
 	//      set
 	void addFriend(int id);


 	//pre: prompt the user to enter the id which is valid
 	//post: check the set if it already includes this id,
 	//		if NOT do nothing. If so delete the id from the 
 	//      set
 	void deleteFriend(int id);



/*
+addPost(Post*):void
+getPosts(): vector<Post*>
+getPostsString(howMany:int, showOnlyPublic:bool):string
*/

	
  // Pre: assert the pointer
  // Post: Adds the post to messages_
  void addPost(Post* post);



  // Pre: 
  // Post: Returns the messages_ vector of Post pointers.
  std::vector<Post*> getPosts() const;



  // Pre: howMany >= 0, assert showOnlyPublic
  // Post: Returns a string of posts formatted per requirements
  std::string getPostsString(int howMany, bool showOnlyPublic) const;

};



#endif