/*
 * & File   : ThomasMcDonnell.c
 * Author   : Thomas McDonnell
 * Purpose  : Programming Algoritms & Data Structures Assignment 2 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// employee boiler plate
typedef struct employee
{
    char    *name;
    char    *position;   
    int     employee_id;
    float   hourly_rate;
    struct  employee *next;  
}employee;

// callback function definition for struct manipulation (pointer to a function)
typedef void (*function_ptr)(employee* data);

// function creates a new employee and returns it
employee* create(char *name, char *position, int employee_id, float hourly_rate, employee* next)
{
    employee* new_employee = (employee*)malloc(sizeof(employee));
    if(new_employee == NULL)
    {
        printf("Error creating a new employee.\n");
        exit(0);
    }
    
    new_employee->name = (char *)malloc(strlen(name) + 1);  // Allocate memory for the string
    strcpy(new_employee->name, name);   // copy string into the member
    new_employee->position = (char *)malloc(strlen(position) + 1);   // Allocate memory for the string
    strcpy(new_employee->position, position);   // Copy string into the member
    new_employee->employee_id = employee_id;
    new_employee->hourly_rate = hourly_rate;
    new_employee->next = next;

    return new_employee;
}

// function inserts new employee into the linked list via the head (start of the linked list)
employee* insert(employee* head, char *name, char *position, int employee_id, float hourly_rate)
{
    employee* new_employee = create(name, position, employee_id, hourly_rate, head);
    head = new_employee;

    return head;
}

// display employee data` 
void display_employee(employee* employee)
{
    if(employee != NULL)
    {
        printf("Empolyee Name : %s\n", employee->name);
        printf("Empolyee Position : %s\n", employee->position);
        printf("Employee ID : %d\n", employee->employee_id);
        printf("Employee Pay Rate (hourly) : %.2f\n"
                "=================================\n",      // pretty formating 
                employee->hourly_rate);
    }
}

// move through a linked list and perform operation in steps 
// function takes a starting point (head)
// walks through the linked list for the number of steps given
// applies a function to each structure along the way
void walk(employee* head, function_ptr func, int steps)
{
    int counter = 0;

    employee* ptr = head;
    while((ptr != NULL) && (counter < steps))
    {
        counter++;
        func(ptr);
        ptr = ptr->next;
    }
}

// iterates through a struct in the desired number of steps and calculates 
// the average pay rate 
void average_rate(employee* head, int steps)
{
    int counter = 0;
    float sum = 0.0;

    employee* ptr = head;
    while((ptr != NULL) && (counter < steps))
    {
        counter++;
        sum += ptr->hourly_rate;
        ptr = ptr->next;
    }
    float average = sum/steps;
    printf("*********************************\n"
            "The average hourly rate is: %.2f\n"
            "********************************\n", average);
}

// find an employee by id
void find_id(employee* head, int id)
{   
    int found = 0;  // initalize found variable for switch case
    employee* ptr = head;   
    while(ptr !=NULL)
    {
        if(ptr->employee_id == id)
             display_employee(ptr);
             found++;   
        ptr = ptr->next;
    }
    if(found == 0)  // if found FALSE 
        printf("No such employee in the system\n");

}

// find an employee by name
void find_name(employee* head, const char *name)
{   
    int found = 0;   // initalize found variable for switch case
    employee* ptr = head;   
    while(ptr !=NULL)
    {
        if(strcmp( ptr->name, name ) == 0 )     // string comparision 
             display_employee(ptr);
             found++;   
        ptr = ptr->next;
    }
    if(found == 0)  // if found FALSE
        printf("No such employee in the system\n");

}


int main()
{   
    /* Question 1, 2, 3
     * 
     * Kept together and tested with two employee structures
     *
     */
     

    employee* head = NULL;
    
    head = insert(head, "Thomas", "barista", 3989, 10.50);
    head = insert(head, "Samara", "barista", 8879, 10.50);
    walk(head, display_employee);
    

    /* Question 4 & 5 
     *
     */

    /*
     *
     * Initalize empty variables for  struct members
     * These will be dymanically updated and passed into our structs
     *
     */

    char randChar = ' ';
    int counter = 0;
    int randNum = 0;
    float randFloat = 5.0;
    
    employee* head = NULL;

    srand(time(NULL));

    for(counter = 0; counter < 1000; counter++)
    {
        randNum =  rand() %26;
        randChar = (char) (randNum + 97);
        randFloat = (((float)rand()/(float)(RAND_MAX)) * randFloat);

        head = insert(head, &randChar, &randChar, randNum, randFloat); // create struct employee
    }

    walk(head, display_employee, 10);

    average_rate(head, 100);
    
    find_id(head, 20);
    
    find_name(head, "f");
    


}

