To find the running median given mean and max heaps.

1. understand the concept of callback.
To make the data in a function flexible, we use parameters which stand for data 
- are variables.
To make the operation in a function flexible, we use parameters which are 
pointers to functions.
You have come across them in pthread_create function in OS.
You have come across such functions in Python in map, filter, reduce, ...

Develop functions to mimic map, filter and reduce in 'C' 

2. Given a heap, make this a minheap or a maxheap based on a callback used 
to specify the way of comparison.

3. Find the running median of given sequence of data. 
Algorithm:
Data structures:
- Max-Heap (left_half): Stores the smaller half of the numbers. 
The root gives the largest element of this lower half.
- Min-Heap (right_half): Stores the larger half of the numbers. 
The root gives the smallest element of this upper half.

procedure:

Step-by-Step Algorithm for Each Incoming Number x

1. Insert:
	• If left_half is empty or x <= root(left_half), 
		push x into left_half.
	• Otherwise, push x into right_half.
2. Balance:
	• If the size of left_half exceeds right_half by more than 1
	  pop the root from left_half and push it into right_half.
	• If the size of right_half exceeds left_half, 
	  pop the root from right_half and push it into left_half.
	  
3. Query Median:
	• If total elements N is even: The median is the average of the 
		two root elements: 
	• If total elements N is odd: The median is the root of the heap 
	  that has the extra element.