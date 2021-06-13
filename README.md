# File-Management-System
C++ File Management System using Priority Queue and Hashing.

## Code Description
### Priority Queue
We created a priority queue to maintain the list of users who want to access a file for reading or writing. Template-based Priority Queue is implemented as Max heap using dynamic
array.
Each node in the queue maintain the following information
1. Key (to maintains Priority)
2. Information that includes:
    * Id of the user
    * Operation type (read or write)

Following functions for priority Queue class are provided:

* BuildQueue: Takes in an unsorted array and convert in to a priority queue
* ExtractMax: Remove and return the maximum element
* FindMax: Return the maximum value in O(1) time
* FindMin: Return the minimum value in O(1) time
* Insert: Insert a value with given priority
* size
* empty

### Hash Table
Generic template-based Hash Table is used to maintain a repository of the files. The hash table uses chaining to
resolve collision. I have used STL (standard template library) linked list for chaining. 

Hast table uses file id as hashing index.
Each node in the linked list will have a pointer to a priority queue of the users who wants to access the file, we will call it waiting
queue. If a user requests an access to a file. We will check the file’s waiting priority queue. If queue is empty the user will be granted
access otherwise, he will be inserted in the particular file’s waiting queue with given priority.


Provide the following functionality
1. Insert a file in the hash table using a hash function based on file id
2. Request File Access
    * Get User Id and File Id as input
    * Get priority as input
        1. user can either give a number for priority or
        2. specify priority is high or low
        3. If priority is high, then you will assign the user a number(priority) that is maximum in the given
        file’s waiting queue. (use FindMax function in the priority queue)
        4. If priority is low, then you will assign the user a number(priority) that is minimum value in the
        given file’s current waiting queue. (use FindMin function in the priority queue)

    * Insert a user with given id in the file’s waiting queue with given priority. If waiting queue is empty and no user is
    currently accessing the file, give the user immediate access to the file.
    * If file does not exist print error message
3. Release File
* If a user no longer needs to access a file, provide access to the next user with highest priority.
    1. If the next highest priority user in waiting queue wants a write access, then he got exclusive access to the
    file.
    2. However, if the next user with highest priority wants a read access then we grant access to all the top
    priority users in the queue that want read access till we find a user with write access.
        * For example: if there are 5 users in the waiting queue with following priorities and access requests
        
              1. UserID 14, read access, priority = 10
              2. UserID 55, read access, priority = 7
              3. UserID 10, read access, priority = 7
              4. UserID 12, write access, priority = 6
              5. UserID 1, read access, priority = 5
              
        * We will grant read access to top 3 users. We will remove first three users from waiting priority
        queue, grant them access to the file and keep track of their IDs.

4. Print the Hash table:

    * Print the list of the files in Hash table along with the user’s ids who are currently accessing the file and the next user
    to get the access.
          * Output should be as follows:
          
              * H1 → File 5001 ... Access granted to User 1, read
              Next User 23, write
              Waiting 10 users
              * H2 → File 5012 ... Access granted to User 12, write
              Next User 2, write
              Waiting 1 user
              * H2 → File 5051 ... Access granted to User 1, User 2, read
              Next User 3, write
              Waiting 3 users
              * H3 → File 5111 ... Access granted to none
              Next none
              Waiting none
              

5. Load the data regarding files and users from the given input file
      * Input File Format
          1. File Id is a number between 5000-99999
          2. User Id is an integer in a range 0-10000
          3. Priority is an integer in a range 0-100
          4. File Access is a character R or W
    * Sample:
          File ID, User ID, Priority, Access (read or write)
          
          7551, 10, 3, R
          
          25551, 3, 10, W
          
          32451, 4, 7, R
          

6. Provide a menu with following options:
* Print Hash table with file information
* Load data
* Insert a file
* Delete a file

      1. Delete the file only if no one is currently accessing it
* Request an access to a file by a user

      1. Get user id, file id and access type (read or write) and perform the desire operation
* Release the file by a user

      1. Get user id and file id and perform the desire operation

## Execution
Clone the project, open it in Visual Studio and run the file. For loading data from file the syntax is given above for file.
