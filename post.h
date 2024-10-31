#ifndef POST_H
#define POST_H
#include <string>

/*
+ Post()
+ Post(messageId: int, ownerId: int, message: string, likes: int)
+ toString(): string
+ getMessageId(): int
+ getOwnerId(): int
+ getMessage(): string
+ getLikes(): int
+ getAuthor(): string
+ getIsPublic(): bool
- messageId_: int 
- ownerId_: int
- message_: string
- likes_: int
*/

class Post{
	int messageId_;
	int ownerId_;
	std::string message_;
	int likes_;

public:
 	// Default constructor
 	//pre:
 	//post:create default values for each
    Post();

    // Parameterized constructor
    //pre:
 	//post:create default values for each
    Post(int messageId, int ownerId, const std::string& message, int likes);

   
    //pre: 
 	//post: return a string ”[message_] Liked by [likes_] people.”
 	//		 where [message_] and [likes_] are replaced by their respective values.
    virtual std::string toString() const;  //now can override



    //Getters
	/*
	Example for Getters
	  vector<int> getVec () { return vec; };
	  vector<int> & getVecRef () { return vec; };
	*/


    //pre:
 	//post:returns the messageId_
    int getMessageId() const;

    //pre:
 	//post:returns the ownerId_
    int getOwnerId() const;

    //pre:
 	//post:returns the message_
    std::string getMessage() const;

    //pre:
 	//post:returns the likes_
    int getLikes() const;

    //pre:
 	//post: return "" as default, getter for the author 
    virtual std::string getAuthor() const;

    //pre:
 	//post: return true as default, check if post is pubic 
    virtual bool getIsPublic() const;
};









/*IncomingPost
+ IncomingPost()
+ IncomingPost(messageId: int, ownerId: int, message: string,
               likes: int, isPublic: bool, author: string)
+ toString(): string
+ getAuthor(): string
+ getIsPublic(): bool
- author_: string
- isPublic_: bool
*/

class IncomingPost:public Post{
	std::string author_;
	bool isPublic_;

public:
	// Default constructor
	//pre:
 	//post:create default values for each
    IncomingPost();

    // Parameterized constructor
    //pre:
 	//post:create default values for each
    IncomingPost(int messageId, int ownerId, const std::string& message, int likes, bool isPublic, const std::string& author);


    //toString() should return a string ”[author_] wrote[private]: [toString]” where [author_] 
    //is the value of author_, [toString] is the value obtained by calling the Post toString
    //method, and [private] is the empty string if isPublic_ is true, and ” (private)” 
    //if isPublic_ is false.

    //pre:
 	//post:override the parent to return ”[author_] wrote[private]: [toString]”
    std::string toString() const;


	//getters
    //pre:
 	//post:returns author
    std::string getAuthor() const;

    //pre:
 	//post:return whether if public
    bool getIsPublic() const;

};

#endif

