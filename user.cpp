#include "user.h"

//Default contructor
//pre:none
//post:create default values for each
User::User() : id_(0), name_("unknown"), year_(0000),
				zip_(00000), friends_(std::set<int>()) {}

//Primary contructor
//pre: none
//post: create default for each 
User::User(int id, std::string name, int year, 
	 int zip, std::set<int>friends){
	id_ 	= id;
	name_ 	= name;
	year_   = year;
	zip_    = zip;
	friends_= friends;
}

User::~User() { }

/* 
Example for Getters
  vector<int> getVec () { return vec; };
  vector<int> & getVecRef () { return vec; };
*/

//Getter for ID
//pre:
//post: return the user's id
int User::getId()const {return id_;};



//Getter for NAME
//pre: 
//post: return the user's name
const std::string& User::getName()const{return name_;}



//Getter for YEAR
//pre: 
//post: return the user's year
int User::getYear()const {return year_;}



//Getter for ZIP
//pre: 
//post: return the user's zip
int User::getZip()const {return zip_;}



//Getter for FRIEND
//pre: 
//post: return the user's friend (set)
std::set<int>& User::getFriends() {return friends_;}         //cant be const or cant pass test_user_get_friend_reference (test_subprocess.TestDiff)




//pre: prompt the user to enter the id which is valid
//post: check the set if it already includes this id,
//		if so do nothing. If not add the id into the 
//      set
void User::addFriend(int id){
	if (friends_.find (id) == friends_.end()){
		friends_.insert(id);
	}
}
	


//pre: prompt the user to enter the id which is valid
//post: check the set if it already includes this id,
//		if NOT do nothing. If so delete the id from the 
//      set
void User::deleteFriend(int id){
	if (friends_.find (id) != friends_.end()){
		friends_.erase(id);
	}
}




// Pre: assert the pointer
// Post: Adds the post to messages_
void User::addPost(Post* post){
	assert(post != nullptr); 
	messages_.push_back(post);
}



// Pre: 
// Post: Returns the messages_ vector of Post pointers.
std::vector<Post*> User::getPosts() const{
	return messages_;
}



// Pre: howMany >= 0
// Post: Returns a string of posts formatted per requirements
std::string User::getPostsString(int howMany, bool showOnlyPublic) const{
	assert(howMany >= 0);
	std::string result; //for return 
  int count = 0; 

  // Loop through messages
    for (int i = messages_.size() - 1; i >= 0 && count < howMany; --i) {  //recent post first
        Post* post = messages_[i]; // Access the post directly

        // Check privacy
        if (showOnlyPublic && !post->getIsPublic()) {
            continue; // Skip 
        }

        // Append the post's string representation to result
        result += post->toString();
        count++;

        // Add two newlines after each post
        if (count < howMany && i > 0) {
            result += "\n\n"; 
        }
    }

    return result; // Return the accumulated string
}













 		