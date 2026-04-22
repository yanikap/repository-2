#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure to store road details
struct Road {
    char name[20];
    int count;      // number of cars
    int emergency;  // 1 means yes ambulance, 0 means no
};

// defining functions
void input(struct Road r[]);
int findGreenRoad(struct Road r[]);
int getTime(int count);
void showSignal(struct Road r[], int greenIndex, int time);

int main() {
    struct Road r[4]; 
    int choice;

    //names of the roads 
    strcpy(r[0].name, "NORTH");
    strcpy(r[1].name, "EAST");
    strcpy(r[2].name, "SOUTH");
    strcpy(r[3].name, "WEST");

    while(1) {
        // clear the screen (cls is for windows)
        system("cls"); 

        printf("\n TRAFFIC SIGNAL PROJECT \n");

        // 1. calling input function
        input(r);

        // 2. logic to find which road will be green
        int greenIndex = findGreenRoad(r);

        // 3. getting the time duration
        int time = getTime(r[greenIndex].count);
        
        // if ambulance is there, full 60 seconds directly
        if(r[greenIndex].emergency == 1) {
            time = 60;
        }

        // 4. print the final signal table
        showSignal(r, greenIndex, time);

        printf("\nCheck again? (1 = Yes, 0 = Exit): ");
        scanf("%d", &choice);
        
        // if user types 0 then loop stops
        if(choice == 0) {
            break;
        }
    }

    return 0;
}

// function to take user input for all 4 roads
void input(struct Road r[]) {
    int i;
    // loop running 4 times for each road
    for(i = 0; i < 4; i++) {
        printf("\n %s Road \n", r[i].name);
        printf("Vehicles: ");
        scanf("%d", &r[i].count);
        
        // if user enters negative number make it 0
        if(r[i].count < 0) r[i].count = 0; 

        printf("Emergency (1=Yes, 0=No): ");
        scanf("%d", &r[i].emergency);
    }
}

// logic to find road with max traffic
int findGreenRoad(struct Road r[]) {
    int i;
    int maxIndex = 0;
    int maxVal = -1;

    // checking if any emergency vehicle is there first
    for(i = 0; i < 4; i++) {
        if(r[i].emergency == 1) {
            return i; // if yes then return this road index
        }
    }

    // if no emergency check normal traffic count
    for(i = 0; i < 4; i++) {
        if(r[i].count > maxVal) {
            maxVal = r[i].count;
            maxIndex = i;
        }
    }
    return maxIndex;
}

// loop to decide time based on cars
int getTime(int count) {
    if(count > 20) {
        return 60; // heavy traffic
    } else if(count >= 10) {
        return 40; // medium traffic
    } else {
        return 20; // low traffic
    }
}

// the output table
void showSignal(struct Road r[], int greenIndex, int time) {
    int i;
    printf("       SIGNAL STATUS        \n");

    // warning for emergency 
    if(r[greenIndex].emergency == 1) {
        printf(" !! EMERGENCY VEHICLE !! \n");
    }

    // green for one road and red for others
    for(i = 0; i < 4; i++) {
        if(i == greenIndex) {
            printf(" %s: \tGREEN (%d sec) \t[Cars: %d]\n", r[i].name, time, r[i].count);
        } else {
            printf(" %s: \tRED \t\t[Cars: %d]\n", r[i].name, r[i].count);
        }
    }
}