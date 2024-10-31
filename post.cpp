#include "post.h"



//Post Class
	// Default constructor
 	//pre:
 	//post:create default values for each
    Post::Post(): messageId_(0), ownerId_(0), message_(""), likes_(0){}

    // Parameterized constructor
    //pre:
 	//post:create default values for each
    Post::Post(int messageId, int ownerId, const std::string& message, int likes){
    	messageId_ = messageId;
	    ownerId_ = ownerId;        
	    message_ = message;        
	    likes_ = likes;

    }

   
    //pre: 
 	//post: return a string ”[message_] Liked by [likes_] people.”
 	//		 where [message_] and [likes_] are replaced by their respective values.
    std::string Post::toString() const {
    return message_ + " Liked by " + std::to_string(likes_) + " people.";
	}




    //Getters
	/*
	Example for Getters
	  vector<int> getVec () { return vec; };
	  vector<int> & getVecRef () { return vec; };
	*/


    //pre:
 	//post:returns the messageId_
    int Post::getMessageId() const{
    	return messageId_;
    }

    //pre:
 	//post:returns the ownerId_
    int Post::getOwnerId() const {
    	return ownerId_;
    }

    //pre:
 	//post:returns the message_
    std::string Post::getMessage() const{
    	return message_;
    }

    //pre:
 	//post:returns the likes_
    int Post::getLikes() const{
    	return likes_;
    }

    //pre:
 	//post: return "" 
    std::string Post::getAuthor() const{   //virtual can only be specified inside the class def
    	return "";
    }

    //pre:
 	//post: return true 
     bool Post::getIsPublic() const{
    	return true;  
    }















//incomingPost Class
	// Default constructor
	//pre:
 	//post:create default values for each
    IncomingPost::IncomingPost(): Post(), author_(""), isPublic_(true) {}

    // Parameterized constructor
    //pre:
 	//post:create default values for each
	IncomingPost::IncomingPost(int messageId, int ownerId, const std::string& message, int likes, bool isPublic, const std::string& author)
    : Post(messageId, ownerId, message, likes), author_(author), isPublic_(isPublic) {}
   


    //toString() should return a string ”[author_] wrote[private]: [toString]” where [author_] 
    //is the value of author_, [toString] is the value obtained by calling the Post toString
    //method, and [private] is the empty string if isPublic_ is true, and ” (private)” 
    //if isPublic_ is false.

    //pre:
 	//post:override the parent to return ”[author_] wrote[private]: [toString]”
    std::string IncomingPost::toString() const{
    	std::string private_post_or_not;
    	if (isPublic_) {
        	private_post_or_not = "";  // Leave empty if public
    	} 
	    else {
	        private_post_or_not = " (private)";  // Set to "(private)" if not public
	    }

	    return author_ + " wrote" + private_post_or_not + ": " + Post::toString();  //call parent function to change ot string
    }


	//getters
    //pre:
 	//post:returns author
    std::string IncomingPost::getAuthor() const{
    	return author_;
    }

    //pre:
 	//post:return whether if public
    bool IncomingPost::getIsPublic() const{
    	return isPublic_;
    }




