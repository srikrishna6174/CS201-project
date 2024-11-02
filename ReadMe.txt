Workspace used for writing the code:- Visual Studio Code

External Libraries/Tools required to Run the code:- 
1.Make Command
2.Gnuplot

How to install Make Command:-
1.Open this website(https://scoop.sh/)
2.Run the following code in Windows Powershell to install scoop
	Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
	Invoke-RestMethod -Uri https://get.scoop.sh | Invoke-Expression
3.Run the following code to install make command(if there is any error in the code below mentioned please search make in the website provided above)
	scoop bucket add main
	scoop install main/make
4.Run the following code to install gcc compiler(if there is any error in the code below mentioned please search gcc in the website provided above)
	scoop bucket add main
	scoop install main/gcc

How to install Gnuplot:-
1.Open this website(https://sourceforge.net/projects/gnuplot/files/gnuplot/)
2.Download the files mentioned in the website
3.Install the file(while installing make sure to add the path to directory)

Download all the files to a single directory
How to run code:-
1.Open the directory in the compiler(VSCode/Git Bash)
2.Compile the Code - make
3.Run the Code - ./main

What to Input?
A text file(Project.txt) containing a standard dataset is provided, you can also manually enter the data after calling the Insertion(I) function.
We have given two modes of Insertion - Manual(M) and Automatic(A)
Note:- Make sure you call the Traversal(T) function before you call the Predict(P) and Graph(G) functions

What to expect to see as a result?
Search(S) Function- When given a date(MM/DD/YYYY) as an input, the search function returns stock that day if it is present in the splay tree.
Traversal(T) Function- This functions prints all the nodes in the splay tree ascending datewise order with price and volume of each day.
Predict(P) Function - This function returns the expected price when an input of a date is given along with Mean Square Error of the Linear Regression Model based on the given data.
Graph(G) Function - This function gives the image of a plot of the data in the splay tree (Price or Volume).
















	