    /******************************************************/
   /***Author: Nathaniel Nation							**/
  /*													*/
 /*******Lecture:		  Miss.  			************/
/******************************************************/

/*GROUP: PBCMS1-B
  DATE GIVEN: Week of March 04, 2008
  DATE DUE:   Week of April 07, 2008
  PROGRAM:    South Coast Serenity Inn (SSI),
              reservations and booking of guests */

#include <time.h>
#include <windows.h>
#include <stdio.h>         /******************/
#include <conio.h>         //     Creat      //
#include <stdlib.h>        //      All       //
#include <string.h>        //  Preprocessors //
#define SIZE 4             /******************/

struct room{                                                /*****************/
	int room_num;                                            //               //
   int room_type;                                           //               //
   float cost;                                              //      Creat    //
   int status;                                              //               //
   int guest_num;                                           //       And     //
}rooms;                                                     //               //
                                                            //      Define   //
struct reserve{                                             //               //
	char last_name[40];	/* String holding last name.	*/    //    Structures //
   char first_name[40];	/* String holding first name.	*/    //       and     //
 	char full_name[80];	/* String holding full name.	*/    //      There    //
   char text[128];	/* String to hold keyboard input	*/    //     Records   //
   int lenght_of_stay;                                      //               //
   char credit_card_num[20];                                //               //
   int prefered_room_type;                                  //               //
   float balance;                                           //               //
   int guest_num;                                           //               //
}guest;                                                     /*****************/


int main_menu(void);                                        /****************/
void add_room_info(FILE *reroPtr);                          //    Creat     //
void add_reservation(FILE *reguPtr, FILE *reroPtr);         //              //
void cancel_reservation(FILE *reguPtr, FILE *reroPtr);  /*  //   Function   //
void check_in_guest(void);                                  //              //
void check_out_guest(void);                                 //  Prototypes  //
void income_report(void);                    */             //              //
void report_smoke_nonsmoke(FILE *reroPtr);                  //              //
void reservation_report(FILE *reguPtr, FILE *reroPtr);                              /****************/


/* Begin to excute function main*/
int main()
{
	int select_opt;
   FILE *roPtr, *guPtr;

   if ((roPtr = fopen("room.txt","rb+")) == NULL){
   	printf("\aRoom file could not be found.\n\n"
      		 "Press any to EXIT!");
      getch();
   }
   else if ((guPtr = fopen("reserved.txt","rb+")) == NULL){
   	printf("\aReserve file could not be found.\n\n"
      		 "Press any to EXIT!");
      getch();
   }
   else {
   	while( (select_opt = main_menu()) != 'X' && (select_opt = main_menu()) != 'x'){

   		switch(select_opt){
     			case 'A':
     			case 'a':
        			add_room_info(roPtr);
           		break;

     			case 'B':
     			case 'b':
        			add_reservation(guPtr, roPtr);
        			break;

     			case 'C':
     			case 'c':
        			cancel_reservation(guPtr, roPtr);
           		break;
   /*
     			case 'D':
     			case 'd':
        			check_in_guest();
           		break;

     			case 'E':
     			case 'e':
        			check_out_guest();
           		break;

     			case 'F':
     			case 'f':
        			income_report();
           		break;
                                         */
     			case 'G':
     			case 'g':
        			report_smoke_nonsmoke(roPtr);
           		break;

     			case 'H':
     			case 'h':
        			reservation_report(guPtr, roPtr);
           		break;

        		default:
        			printf("\a\a");
     		}
   		select_opt = main_menu();
   	}
   }
   fclose(roPtr); /* ensure that when the program close, */
   fclose(guPtr); /* the files close also */
   getch();
   return 0;
}



void add_room_info(FILE *reroPtr)
{
   int roomNum, response;
   struct room rooms = {0,0,0.00,0,0}; /* default information*/
   clrscr();
   printf("\t\t\tadd_room_info\n\n\n");

	printf("Enter room number(1 - 50): ");
	scanf("%d",&roomNum);
  	while (roomNum < 1 || roomNum > 50){
     	clrscr();
     	printf("\t\t\tadd_room_info\n\n\n");
     	printf("\aWrong Input!!!\n\n");
  		printf("Enter room number(1 - 50): ");
		scanf("%d",&roomNum);
  	}
	fseek(reroPtr,(roomNum-1)*sizeof(struct room),SEEK_SET);
	fread(&rooms,sizeof(struct room),1,reroPtr);

	if (rooms.room_num != 0){
  		printf("Room information already exist...");
     	Sleep(1000);
     	rewind(reroPtr);
      return;
  	}
  	else {
		printf("Room Type (Smoking \"0\" or Non-Smoking \"1\"): ");
		scanf("%d", &rooms.room_type);

		while (rooms.room_type != 0 && rooms.room_type != 1){
			printf("\n\aWrong Input!!!\n\n");
			printf("Room Type (Smoking \"0\" or Non-Smoking \"1\"): ");
			scanf("%d", &rooms.room_type);
		}/* end while*/
		if (rooms.room_type == 0){
			rooms.cost = 4000;
			printf("Room Cost: $%.2f\n", rooms.cost);
		}/* end if*/
		else{
			rooms.cost = 3000;
			printf("Room Cost: $%.2f\n", rooms.cost);
		}/* end else*/

		printf("Status (Available \"0\", Occupied \"1\", Rerserved \"2\"): ");
		scanf("%d", &rooms.status);
		while (rooms.status != 0 && rooms.status != 1 && rooms.status != 2){
			printf("\n\aWrong Input!!!\n\n");
			printf("Status (Available \"0\", Occupied \"1\", Rerserved \"2\"): ");
			scanf("%d", &rooms.status);
		}/* end while*/

    	printf("\nStill add this room? (Y\\N)");
     	response = getch();

		if ((response == 'N') || (response == 'n')) {
  			printf("\nDisregarding Input..."); Sleep(1000); printf("Discarded!");
        	Sleep(1000);
        	rewind(reroPtr);
         return;
  		}

     	rooms.room_num = roomNum;
      rooms.guest_num = 0; /* set room guest number to zero because it' available*/

		printf("\n\nPlease wait while data is being stored!\n");
     	Sleep(1000); printf(">>>>."); Sleep(1000); printf(">>>>."); Sleep(1000); printf(">>>>."); Sleep(1000);
     	/* Write data to file*/
   	//##################################################################################################################
     	fseek(reroPtr, (rooms.room_num - 1)*sizeof(struct room), SEEK_SET);
      fwrite(&rooms, sizeof(struct room), 1, reroPtr);
     	rewind(reroPtr);
      //##################################################################################################################
  		printf("\nSaved!");
     	Sleep(1000);
  	}
}



void add_reservation(FILE *reguPtr, FILE *reroPtr)
{
   int available, response;
	struct room rooms = { 0, 0, 0.00, 0, 0}; /* default room information*/
   struct reserve guest = {"", "", "", "", 0, "", 0,0.00, 0}; /* default reserve information*/
   clrscr();
   printf("\t\t\tadd_reservation\n\n\n");

   printf("\nEnter last name: "); fflush(stdin); gets(guest.text);
   sscanf(guest.text,"%s",guest.last_name); /* NOTE: no & */

   printf("If this incorrect press \"Y\" (Any key continue)");
   response = getch();

   while (response == 'Y' || response == 'y'){
   	printf("\nEnter last name: ");
   	gets(guest.text);
   	sscanf(guest.text,"%s",guest.last_name);	/* NOTE: no & */

   	printf("If this incorrect press \"Y\" (Any key continue)");
   	response = getch();
   }

   printf("\n\nGuest Mr\\Ms %s. \nEnter first name: ",guest.last_name);
   gets(guest.text);
   sscanf(guest.text,"%s",guest.first_name);	/* NOTE: no & */
   printf("If this incorrect press \"Y\" (Any key continue)");
 	response = getch();

   while (response == 'Y' || response == 'y'){
		printf("\nGuest Mr\\Ms %s. \nEnter first name: ",guest.last_name);
   	gets(guest.text);
   	sscanf(guest.text,"%s",guest.first_name);	/* NOTE: no & */

   	printf("If this incorrect press \"Y\" (Any key continue)");
   	response = getch();
   }

   /* ------ Add the names together ------ */
   strcpy(guest.full_name,guest.first_name);	/* First copy the first	*/
   strcat(guest.full_name," ");		/* name then add a space*/
   strcat(guest.full_name,guest.last_name);	/* and last name.	*/

   /* ------ Some display using puts() ------ */

   printf("\n\n");
   printf("\t================================\n");
   printf("\t\t%s\n",guest.full_name);
   printf("\t================================");
   printf("\n");

   printf("Enter length-of-stay(Days): ");
   scanf("%d", &guest.lenght_of_stay);
   fflush(stdin);  /* flush the input stream in case of bad input */

   printf("Enter credit card number: ");
   scanf("%d", &guest.credit_card_num);
   fflush(stdin);  /* flush the input stream in case of bad input */

   printf("Please choose room type -: \n"
   		 "\t0. Smoking\n"
     		 "\t1. Non-Smoking\n"
     	 	 "Option: ");
   scanf("%d", &guest.prefered_room_type);
   fflush(stdin);  /* flush the input stream in case of bad input */

   while (guest.prefered_room_type != 0 && guest.prefered_room_type != 1){
   	printf("\n\aWrong Input!!!\n\n");
   	printf("Please choose room type -: \n"
   		    "\t0. Smoking\n"
     		    "\t1. Non-Smoking\n"
     		    "Option: ");
		scanf("%d", &guest.prefered_room_type);
      fflush(stdin);  /* flush the input stream in case of bad input */
   }

   if (guest.prefered_room_type == 0 || guest.prefered_room_type == 1){
      available = 0;
   	while ( (!feof(reroPtr)) && (available == 0) ){
      	fread(&rooms, sizeof(struct room), 1, reroPtr);
   		if ( (rooms.room_type == guest.prefered_room_type) && (rooms.status == 0) ){

     			available = 1;
            printf("\nRoom #%d was found. Do you want to reserve this room? (Y\\N)", rooms.room_num);
            response = getch();
				if ((response == 'n') || (response == 'N')) {
					available = 0; // allow user to move on & see the next room
      		}
            else{
					rooms.status = 2; /* change room status to reserved  */
					guest.balance = rooms.cost;
               printf("\nRoom %d is reserved for you Mr\\Ms %c. %s", rooms.room_num, guest.first_name[0],guest.last_name);
               srand(time(NULL));
   				guest.guest_num = rand()% 1000 + 9000;
     				printf("\nYour Guest# is: %d", guest.guest_num);
      			rooms.guest_num = guest.guest_num;

           		printf("\n\nPlease wait while data is being stored!\n");
			     	Sleep(1000); printf(">>>>."); Sleep(1000); printf(">>>>."); Sleep(1000); printf(">>>>."); Sleep(1000);

					/* update the room information */
					fseek(reroPtr, (rooms.room_num - 1)*sizeof(struct room), SEEK_SET);
               fwrite(&rooms, sizeof(struct room), 1, reroPtr);
					/* update the guest information */
					fseek(reguPtr, (guest.guest_num - 1)*sizeof(struct reserve), SEEK_SET);
					fwrite(&guest, sizeof(struct reserve), 1, reguPtr);
               printf("\nSaved!");
				}
         }
   	}
   }
  	if (available == 0){
  		printf("\nI am sorry Mr\\Ms %c. %s",guest.first_name[0],guest.last_name);
  		printf("\nThe room is not available. You're not accepted!");
  	}
   Sleep(1000);
	rewind(reroPtr);
   rewind(reguPtr);
}/* end function newRecord*/



void cancel_reservation(FILE *reguPtr, FILE *reroPtr)
{
   int roomNum, response, found;
   char	holdtext[50], holdlast_name[50];
	struct room rooms = { 0, 0, 0.00, 0, 0}; /* default room information*/
   struct reserve guest = {"", "", "", "", 0, "", 0,0.00, 0}; /* default reserve information*/
   clrscr();
   printf("\t\t\tcancel_reservation\n\n\n");

   printf("Please enter details to query!\n\n");
   printf("Enter room number: ");
   scanf("%d", &roomNum);
   fseek(reroPtr, (roomNum - 1)*sizeof(struct room), SEEK_SET);
	fread(&rooms, sizeof(struct room), 1, reroPtr);

   if(rooms.room_num == 0){
   	printf("\nRoom #%d has no Information!!!", roomNum);
      Sleep(1000);
      rewind(reroPtr);
      return;
   }
   else {
   	   printf("\nEnter last name: "); fflush(stdin); gets(holdtext);
		   sscanf(holdtext,"%s",holdlast_name); /* NOTE: no & */

   		printf("If this incorrect press \"Y\" (Any key continue)");
   		response = getch();

   		while (response == 'Y' || response == 'y'){
   			printf("\nEnter last name: ");
   			gets(holdtext);
   			sscanf(holdtext,"%s",holdlast_name);	/* NOTE: no & */

   			printf("If this incorrect press \"Y\" (Any key continue)");
   			response = getch();
   		}
         found = 0;
         rewind(reguPtr);
         while ( (!feof(reguPtr)) && (found == 0) ) {
         	fread(&guest, sizeof(struct reserve), 1, reguPtr);
            if ((guest.last_name == holdlast_name) && (guest.guest_num == rooms.guest_num)){
               found = 1;

            	printf("\n\t\t Name Found\n "
            			 "\n\t\t Last name: %s"
                      "\n\t\t First name: %s"
                      "\n\t\t Full name: %s"
            			 "\n\t\t Length of stay: %d"
                      "\n\t Credit Card Number: %s",
                      guest.last_name, guest.first_name,
                      guest.full_name, guest.lenght_of_stay, guest.credit_card_num);

               if (guest.prefered_room_type == 0)
                   printf("\n\t\tRoom type: Smoking");

               if (guest.prefered_room_type == 1)
               	printf("\n\t\tRoom type: Non-Smoking");

               printf("\n\t\t Balance: %d"
                      "\n\t\t Guest's Number: %d",
                      guest.prefered_room_type, guest.balance, guest.guest_num);
            }
         }
         getch();
   }
}



void report_smoke_nonsmoke(FILE *reroPtr)
{
	FILE *report1;  /* Create file report of available smoking and
   						non-smoking rooms for printing */
   int found;
   struct room rooms = { 0, 0, 0.00, 0, 0}; /* default room information*/
   clrscr();
   printf("\t\t\treport_smoke_nonsmoke\n\n\n");

   if( (report1 = fopen("Available Smoking and Non-smoking rooms.txt", "w") ) ==
   	NULL){
   	printf("\aRoom file could not be found.\n\n"
      		 "Press any to EXIT!");
      getch();
   }
   else {
   							/*Print to screen*/
      printf("NB: Room Type (Smoking \"0\" or Non-Smoking \"1\")\n"
      		 "    Room Status (Available \"0\", Occupied \"1\", Rerserved \"2\")\n"
             "    Room Guest Number \"0\", No guest, hence equal zero.\n\n\n");
                       /*Write to file*/
      fprintf(report1,"%s\n%s\n%s\n\n\n","NB: Room Type (Smoking \"0\" or Non-Smoking \"1\")",
      		 "    Room Status (Available \"0\", Occupied \"1\", Rerserved \"2\")",
             "    Room Guest Number \"0\", No guest, hence equal zero.");
                        /*Print to screen*/
      printf("%-12s%-2s%-10s%-2s%-10s%-2s%-12s%-2s%-17s\n",
            		"Room Number","|","Room Type","|","Room Cost","|","Room Status","|","Room Guest Number");
                        /*Write to file*/
      fprintf(report1,"%-12s%-2s%-10s%-2s%-10s%-2s%-12s%-2s%-17s\n",
            		"Room Number","|","Room Type","|","Room Cost","|","Room Status","|","Room Guest Number");
      found = 0;
      rewind(reroPtr);
   	while ( (!feof(reroPtr)) && (found == 0) ){
      	fread(&rooms, sizeof(struct room), 1, reroPtr);
         if ((rooms.room_num > 0) && (rooms.status == 0)){
                       /*Print to screen*/
         	printf("%-12d%-12s%-12s%-14s%-19s\n",rooms.room_num, rooms.room_type, rooms.cost,
   				rooms.status, rooms.guest_num);
                       /*Write to file*/
         	fprintf(report1,"%-12d%-12s%-12s%-14s%-19s\n",rooms.room_num, rooms.room_type, rooms.cost,
   				rooms.status, rooms.guest_num);
            found = 1;
         }
      }
      if(found == 0) {
   		printf("\n\n\n\aNo Rooms are Available!");
         fprintf(report1,"\n\n\n%s","No Rooms are Available!");
         Sleep(1000);
      }
      else {
      	printf("\n\nPlease wait while data is being stored to report file!\n");
			Sleep(1000); printf(">>>>."); Sleep(1000); printf(">>>>."); Sleep(1000); printf(">>>>."); Sleep(1000);
         printf("Stored!\n\nData is stored in a file called \"Available Smoking and Non-smoking rooms\"");

         printf("\nPress Any Key...Main Menu!");
         getch();
      }

   }
   fclose(report1);
}



void reservation_report(FILE *reguPtr, FILE *reroPtr)
{
	FILE *report2;  /* Create a file reservatation report for printing */
   int found;
   struct room rooms = { 0, 0, 0.00, 0, 0}; /* default room information*/
   clrscr();
   printf("\t\t\treservation_report\n\n\n");

   if( (report2 = fopen("Reservation Report.txt", "w") ) ==
   	NULL){
   	printf("\aReservation file could not be found.\n\n"
      		 "Press any to EXIT!");
      getch();
   }
   else {
   					     /*Print to screen*/
		printf("NB: Room Type (Smoking \"0\" or Non-Smoking \"1\")\n\n\n");
                       /*Write to file*/
      fprintf(report2,"%s\n%s\n%s\n\n\n","NB: Room Type (Smoking \"0\" or Non-Smoking \"1\")\n\n\n");
   							/*Print to screen*/
      printf("%-12s%-2s%-9s%-2s%-5s\n","Room Number","|","Room Type","|","Guest");
                        /*Write to file*/
      fprintf(report2,"%-12s%-2s%-9s%-2s%-5s\n","Room Number","|","Room Type","|","Guest");
      found = 0;
      rewind(reroPtr);
      rewind(reguPtr);
   	while ( (!feof(reroPtr)) && (!feof(reguPtr)) ){
      	fread(&rooms, sizeof(struct room), 1, reroPtr);
         fread(&guest, sizeof(struct reserve), 1, reguPtr);
         if ((rooms.guest_num ==  guest.guest_num) && (rooms.status == 2)){
         	found = 1;
                       /*Print to screen*/
         	printf("%-14d%-11d%-s\n",rooms.room_num, rooms.room_type, guest.full_name);
                       /*Write to file*/
         	fprintf(report2,"%-14%-11d%-s\n",rooms.room_num, rooms.room_type, guest.full_name);
         }
      }
      if(found == 0) {
   		printf("\n\n\n\aThere are no Reservation Available!");
         fprintf(report2,"\n\n\n%s","There are no Reservation Available!");
         Sleep(1000);
      }
      else {
      	printf("\n\nPlease wait while data is being stored to Reservation report file!\n");
			Sleep(1000); printf(">>>>."); Sleep(1000); printf(">>>>."); Sleep(1000); printf(">>>>."); Sleep(1000);
         printf("\nStored!\n\nData is stored in a file called \"Reservation Report\"");

         printf("\nPress Any Key...Main Menu!");
         getch();
      }

   }
   fclose(report2);
}



int main_menu()
{
   int opt;
   clrscr();
	printf("\t#############################################################\n"
          "\t#    **                   WELCOME                     **    # \n"
          "\t#  ******                   TO                      ******  #\n"
          "\t# ********      SOUTH COAST SERENITY INN (SSI)     ******** #\n"
          "\t#  |0  0|                  HOTEL                    |0  0|  #\n"
          "\t#  |    |                                           |    |  #\n"
          "\t#  |____|                                           |____|  #\n"
          "\t#                                                           #\n"
          "\t#       _____________________________________________       #\n"
          "\t#       )              MAIN MENU:                   (       #\n"
          "\t#      (                                             )      #\n"
          "\t#       )  a. Add Room Informaition                 (       #\n"
          "\t#      (   b. Add Reservations                       )      #\n"
          "\t#       )  c. Cancel Reservation                    (       #\n"
          "\t#      (   d. Check In Guest                         )      #\n"
          "\t#       )  e. Check Out Guest                       (       #\n"
          "\t#      (   f. Income Report                          )      #\n"
          "\t#       )  g. Report Avaible Smoking or Non-Smoking (       #\n"
          "\t#      (   h. Reservation Report                     )      #\n"
          "\t#       )                                           (       #\n"
          "\t#      (_____________________________________________)      #\n"
          "\t#                                                           #\n"
          "\t# Press X to exit!!!                                        #\n"
          "\t#############################################################\n");
   opt = getch();
   return opt;
}

