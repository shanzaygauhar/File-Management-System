# File-Management-System
C++ File Management System using Priority Queue and Hashing.

## Code Description
We created a priority queue to maintain the list of users who want to access a file for reading or writing. Template-based Priority Queue is implemented as Max heap using dynamic
array.
Each node in the queue maintain the following information
1. Key (to maintains Priority)
2. Information
* Id of the user
* Operation type (read or write)

Following functions for priority Queue class are provided:

• BuildQueue: Takes in an unsorted array and convert in to a priority queue
• ExtractMax: Remove and return the maximum element
• FindMax: Return the maximum value in O(1) time
• FindMin: Return the minimum value in O(1) time
• Insert: Insert a value with given priority
• size
• empty

