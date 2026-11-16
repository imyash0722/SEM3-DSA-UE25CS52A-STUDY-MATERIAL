Steps to find running median
let 
left - max heap (which keeps first half of inserted elements) 
right - min heap (which keeps second half of inserted elements)

for every insertion 
   a.  if left is null (intial condition when both the trees is empty by default insert in left) - insert new node in left
   b.  if left is not null and new key to be inserted is less than or equal to left root then insert into left heap else insert in right heap
   c.  after insertion check size of both trees and perform following according to condition
	- if size(left) > size(right)+1 then delete root from left and insert into right
	- if size(right) > size(left) then delete root from right and insert into left
   d. print both the trees
   e. find median 
	- if size(left) == size(right) then median = root(left)+root(right)/2
          else
             median = root(left)