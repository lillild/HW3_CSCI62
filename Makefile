COMP = g++

FLAGS = -Wall -std=c++11		#flags

# Object files
OBJS = user.o network.o social_network.o post.o		

# Target to create the executable
social_network: $(OBJS)
	$(COMP) $(FLAGS) $(OBJS) -o social_network

# Compile each .cpp file into .o files
user.o: user.cpp user.h
	$(COMP) $(FLAGS) -c user.cpp

network.o: network.cpp network.h user.h
	$(COMP) $(FLAGS) -c network.cpp

social_network.o: social_network.cpp network.h user.h
	$(COMP) $(FLAGS) -c social_network.cpp

post.o: post.cpp post.h					
	$(COMP) $(FLAGS) -c post.cpp

# Clean up
clean:
	rm -f *.o social_network
