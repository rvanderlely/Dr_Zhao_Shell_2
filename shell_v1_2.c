/********************************************************
*	File name:	shell_v1-2.c
*	Author:		C. Zhao
*	Date:		Sept 2, 2020
*	Class:		CS3513
*	Purpose:	Execute a command
***************************************************** */

#include <stdio.h> //for printf() and scanf()
#include <string.h>//strlen(), strcpy(), strcmp()
#include <unistd.h>//execl()
#include <stdlib.h>//exit()
#define SIZE 80
int main()
//No longer just do one path. Now we get as uch infomarion as we can. We make a 2d array to hold the paths/. 

{

	char Globalcmd[SIZE];         //store cmd from kb
	int pathcounter = 0;	            //Counter for the 2D array 
	int commandcounter =0;
	char *p;                 //points to path fetched from system
	char *paths[SIZE];      //this is a 2D array. Pointer array. 
	char *temp;             //store one path temp
	p = getenv("PATH");     //get enviorment then path// so after this p will point to the path string and one of them will be bin
    //PATH simply returns all directories, seperated by a : that executible can be stored in. 
    //For example, PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Library/Apple/usr/bin
	printf("\nPath info is %s\n", p);//
	                        //print path information
	temp = strtok(p, ":");  //use a string token to take first token then set counter = to 0. 
	

//Then go through it compy what in temp into path[i]. You are filing up the array with strings????? AHHHH
//Then print it to see what it is
	while(temp)//parsing path into 2_d array
	{
		paths[pathcounter] = temp;//store temp to paths
		printf("\n The temp string is %s\n", temp);
		pathcounter++;				//keep increasing through the paths
		temp = strtok(NULL, ":");	// : is the deliminator that you are specifiying. In this case it is a colon. 
	}
	
	for(;;) //service loop until the user quits
	{
		printf("\nRachel's Shell %s >>> ", getenv("HOME"));
		//get envi “HOME” is your name and post and attaches to it
		//scanf("%s", Globalcmd); //read data in this case you only read one with scanf
		fgets(Globalcmd,80,stdin);
		printf("\n Cmd is: %s", Globalcmd);//print it 
		printf("\t length of Global COMMAND ISis %d\n", strlen(Globalcmd));
	//The & operator is not required in the case of String capture. 
	//The scanf() automatically appends the null character('\0') to the end of the string so 

        //If at any time the user types exit, then exit the  program.
        //THIS IS in the infinite for loop so will work at any time. 
		if(strcmp(Globalcmd, "exit\n") == 0)
		{
			printf("\n Goodbye \n");
			exit(0);
		}

		//why we need a for loop? TO GO THROUGH ALL PATHS
		//The I is the number of paths

		if(fork() == 0)
		{
			//if a child process has been made fork will ==0 child process
			//?THIS SI WHERE YOU NEED TO DO THE WORK
			//You need to add to local var 
			//one to store cmd and one to store the arguments That are seprated by a space. 
			//This prog must run with or without an argument such as -l
			

		// 	//My work
		// 	char *Localcmd[SIZE];         //Make a 2D array to hold the commands (points to the cstrings)
		// 	char *tempcmd; 					//Make a temp cstring
		// 	tempcmd = strtok(Globalcmd, " ");// " " is the deliminator that you are specifiying. In this case it is a colon. 
		// 	printf("Adding commands to 2D array");
		// 		while(tempcmd)//parsing path into 2_d array
		// 		{
		// 			Localcmd[commandcounter] = tempcmd;//store temp to paths
		// 			printf("\n The fist command is %s\n", tempcmd);
		// 			commandcounter++;	//keep increasing through the path
		// 			tempcmd = strtok(NULL, " ");// : is the deliminator that you are specifiying. In this case it is a colon. 
		// 		}

		// 		//Okay now Localcmd holds pointers to all the char commands
		// 		//Idk if each command has null after though

		// 			//get all the commands out of the 2D array called Localcmd into one string
		// 			char realCommand[SIZE];					//Will hold the real command
		// 			int i;
		// 			for(i = 0; i < commandcounter; i++)
		// 			//go through all paths and see if that command is in there
		// 			{
		// 				strcat(realCommand, Localcmd[i]);		//Copy the kth array in the 2D array to this new 1D array
		// 				strcat(realCommand, " ");				//Put a / after each path added 
		// 			}
		// 			printf("THE REAL COMMAND IS %s\n",realCommand);
		// 			printf("\t length of REAL COMMAND ISis %d\n", strlen(realCommand));



		// //End my work



			//load the task to it
				
					int k;
					for(k = 0; k < pathcounter; k++)
					//go through all paths and see if that command is in there
					{
						char path[SIZE]; 			//Make a new 1D array of size 80	
						strcpy(path, paths[k]);		//Copy the kth array in the 2D array to this new 1D array
						strcat(path, "/");			//Put a / after each path added 
						strcat(path, Globalcmd);	//add the command that the user typed to the path
						printf("!!!!!!The path about to be executed is %s\n",path);
						execl(path, Globalcmd, 0);
					}
					printf("\nCmd NOT FOUND\n");
					exit(1);//terminate child process
				}
				else
					wait(0);//wait for child process term
				
	}//end of the infiirnte for loop


exit(0);
} //end of main
	


//This is still not dealing with args just yet. This is what we have to do on our way 
//we use fgets to read then the rest same
//if you like you can use just one save and append null char at the end of your string you may fo tht 
//but most times you are okay without doing this because fgets is going to do that for you. That’s why you use fgets instead of gets. 

//This is the second version. It is parsing the path variable and researching all paths. The first program only searched the bin directory. Other than that they are exactly the same thing. 
