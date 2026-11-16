Problem statement :
Input :
You are given the interface and implementation of 
ordered list of integers
Output :
Modified the above programs to represent a polynomial in one 
variable
steps :
1. read and review the code of ordered list. 
2. we shall represent each term in the polynomial as having
	coefficient and exponent. 
	create header file called term.h and 
	implementation file called term.c 
	provide and support the following interfaces.
	set_term(term_t *ptr_term, coeff, expo);
	disp_term(term_t* ptr_term);
	
	In a polynomial, for ease of processing, terms are stored 
	in the decreasing order of exponent.
	Provide a function to compare two terms based on the exponents.
	int compare_exponents(term_t* left, term_t* right);
	This should return 0 if both the exponents are same,
	a negative value if the exponent of the left term is lesser,
	otherwise a positive value.
	
3. Modify the order list implementation to make a list of terms 
   in the decreasing order of exponent. You may assume that no 
   two terms will have the same exponent. Inputs may not be in the 
   same order.
   
4. Write a client program to create a polynomial and display it.

