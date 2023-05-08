#EtudGate
[github link](https://github.com/imranboutadghart/students-manipulation-project.git)

EtudGate is a command-line interface (CLI) program designed for storing and managing a database of student information. Written in C programming language, EtudGate uses dynamic memory allocation to reduce memory usage, and it stores data in files located in the DATA folder. Files are named according to user preferences, making it easy to manage multiple classes.
Getting Started

To run EtudGate, open a terminal and navigate to the directory where the program is located. Then, enter the command ./build/etudgate , or you can just click on the etudgate.exe if you're on windows

if any troubles were to be encountered, user may needs to use the make command to recompile the program.

Upon launching EtudGate, the program will prompt you to run it in full-screen mode. After you accept, the EtudGate logo and a brief description of its functionalities will appear. You will then be asked to proceed, answering "O" or "o" for yes, and "N" or "n" for no. If you answer with "O" or "o", the program will begin.

The first thing you need to do is type in the file name. The program will detect whether the file already has data in it or not.

###    If the file has no data:
        The program will prompt you to input new student information, which it will then add to the file.
###        The program will then move on to the main menu.
    If the file already has students in it:
        The program will display the main menu.

##Main Menu

The main menu contains six options, with the last option allowing you to exit the program.

###    ->Add a new student: This option prompts you to input the following information in order:
        *Personal name
        *Family name
        *Year of subscription (written in the format "dd mm yy" or "dd mm yyyy")
        *Section (input a number corresponding to the list of sections)
        *Level of formation (input a number corresponding to the formation level)
        *Whether the student is repeating a year or not (answered by "O" or "N")
        *Group number
        *Whether you want to give the student marks or not (the maximum number of marks that can be given is six)
        Each student is given a random ID number that starts with the year of subscription.
        The program will then ask whether you want to input more students or not and repeat the process.

###    ->Modify a student's data: This option prompts you to select a student by their corresponding blue number on the left of their name. You can then change any of the following information:
        *Personal name
        *Family name
        *Year of subscription
        *Section
        *Level of formation
        *Group number
        *Marks (if you chose to modify them, the program will ask whether you want to add or change a mark).
        *You can also choose to cancel the modification.

###    ->Delete a student: This option prompts you to select a student by their corresponding blue number on the left of their name.

###    ->Search for a student: This option allows you to search for a student by personal or family name, ID number, or subscription year.

###    ->Customize the order of student information: This option allows you to customize the order in which student information is displayed, and filter the results based on section, formation level, whether the student is repeating a year, or group number. The default ordering is by insertion date.

###    ->Exit the program: This option allows you to exit the program.

##Contributing

Contributions to EtudGate are welcome and can take many forms, such as reporting bugs, providing feedback, updating information from the readme, etc...
every contribution would be very helpful, but if it was a critical contribution you may end up being added to the credits part

##Credits:
    Credits are to be given to all those who contributed to EtudGate in any form, but above all else, the programmers who contributed the most to EtudGate are:
        ***youssef ait boudderoub***
        ***imran boutadghart***
    speciall thanks to our professor ***Rachida Hannane***
