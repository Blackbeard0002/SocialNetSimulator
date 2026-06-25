# SocialNet Simulator

This is a C++ project for COL106: Data Structures that simulates the backend of a simple social network. It allows users to be added, friendships to be created, and posts to be managed, all from a command-line interface.

The project is built using a multi-file C++ structure to cleanly separate logic for the main application, the graph data structure, and the AVL tree data structure.

# Core Data Structures

This project implements core data structures from scratch as required by the assignment.

* Graph (for Friendships): An undirected graph is used to manage friendships. The graph is implemented using a std::map<int, std::vector<int>>.

* * The int key is a user's unique ID.

* * The std::vector<int> is the adjacency list (the user's list of friends). 

* AVL Tree (for Posts): A self-balancing AVL Tree is implemented from scratch to store and retrieve user posts.

* * Posts are sorted chronologically by using a static long long as an auto-incrementing timestamp, which serves as the key for each node in the tree.

* Hash Map (for User Mapping): A std::map<std::string, int> is used to map case-insensitive usernames to their unique integer IDs used in the graph.

# How to Compile

A shell script `compile.sh` is provided to build the project. It requires `g++` and compiles with C++17, `-Wall`, `-Wextra`, and `-g`.

1. Open your terminal in the project's root directory.

2. If needed, make the script executable (you only need to do this once):

```bash
chmod +x compile.sh
```

3. Build the program:

```bash
./compile.sh
```

This compiles `main.cpp`, `SocialNet.cpp`, `Graph.cpp`, and `AVLTree.cpp` into an executable named `socialnet` in the project root.

# How to Run

After successful compilation, you can run the program from the same terminal.

1. Execute the compiled program:

./socialnet

(Note: On Windows, you may need to use .\socialnet.exe)

2. The simulator will start and display:

SocialNet Simulator started. Enter commands (or EXIT to quit).

3. You can now type commands directly into the terminal.

4. To stop the program, type EXIT and press Enter.

# Command Reference

The program accepts the following commands from stdin. Input arguments are separated by spaces.

# ADD_USER

Adds a new user to the network. Usernames are case-insensitive.

* Format: ADD_USER <username>

* Arguments:

* * <username>: A single string without spaces (e.g., Alice, Bob_123).

* Example:
ADD_USER Alice

# ADD_FRIEND

Establishes a bidirectional friendship between two existing users.

* Format: ADD_FRIEND <username1> <username2>

* Arguments:

* * <username1>: The username of the first user.

* * <username2>: The username of the second user.

* Example:
ADD_FRIEND Alice Bob

# LIST_FRIENDS

Prints an alphabetically sorted list of the specified user's friends.

* Format: LIST_FRIENDS <username>

* Arguments:

* * <username>: The user whose friends you want to list.

* Example:
LIST_FRIENDS Alice

# SUGGEST_FRIENDS

Recommends up to N new friends who are "friends of a friend."

* Format: SUGGEST_FRIENDS <username> <N>

* Arguments:

* * <username>: The user to get suggestions for.

* * <N>: An integer for the maximum number of suggestions to show.

* Example:
SUGGEST_FRIENDS Alice 3

# DEGREES_OF_SEPARATION

Calculates the shortest path (number of friendship links) between two users.

* Format: DEGREES_OF_SEPARATION <username1> <username2>

* Arguments:

* * <username1>: The username of the starting user.

* * <username2>: The username of the ending user.

* Example:
DEGREES_OF_SEPARATION Alice Charlie

# ADD_POST

Adds a new post for the user. The post content MUST be enclosed in double-quotes.

* Format: ADD_POST <username> "<post_content>"

* Arguments:

* * <username>: The user who is posting.

* * "<post_content>": The content of the post, enclosed in double-quotes.

* Example:
ADD_POST Alice "This is my first post!"

# OUTPUT_POSTS 

Outputs the most recent N posts for the user in reverse chronological order.

* Format: OUTPUT_POSTS <username> <N>

* Arguments:

* * <username>: The user whose posts you want to see.

* * <N>: An integer for the number of posts to show.

* If N is a positive number (e.g., 5), it shows the N most recent posts.

* If N is -1, it shows ALL posts from the user.

* Example (Last 3 posts):
OUTPUT_POSTS Alice 3

* Example (All posts):
OUTPUT_POSTS Alice -1

# EXIT 

Shuts down the simulator and returns you to the terminal.

* Format: EXIT

* Example:
EXIT