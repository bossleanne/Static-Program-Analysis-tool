## This is a basic instruction on how to compile and run AutoTester of SPA programs for `MacOS users` only.

#### Prerequisite
* Xcode and gcc need to be install.
* Download the file under home folder

#### Compile:
Open Clion, click `open project`, select SPA, choose the right `cmakeList`, the choose build to build the whole project.

#### How to run:
##### After build, open a new terminal, go to the folder path: 
cd $HOME/Main/Code/cmake-build-debug/src/autotester 

##### run the following command line in your terminal:
```
./autotester <source file full path> <query file full path> <~/Main/Code/tests/Iter1_output.xml>
```

##### View result:
A file named Iter1_output.xml will show the total pass of the testcase.