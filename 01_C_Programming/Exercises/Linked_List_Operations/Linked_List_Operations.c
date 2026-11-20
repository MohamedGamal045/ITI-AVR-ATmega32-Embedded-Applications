// gcc Linked_list.c -o Linked_list.exe
// Linked_list.exe

#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"

typedef struct node{
    u8 Data;
    struct node * Next_node;
}Node_ty;

Node_ty * Head=NULL;

void AddAtFirst(u8 value)
{
    ///creat the new node
    Node_ty * ptr2NewNode= (Node_ty*)malloc(sizeof(Node_ty));
    
    ///Data
    ptr2NewNode->Data = value;
    //next --> head
    ptr2NewNode->Next_node = Head;
    //head --> new node 
    Head = ptr2NewNode;
}

void AddAtEnd(u8 value){
    
    if(Head == NULL)
    {
        AddAtFirst(value);
    }
    else
    {
        Node_ty* temp = Head;
        while(temp->Next_node != NULL)
        {
            temp = temp->Next_node;
        }
        //creat a new node  
        Node_ty* newNode =(Node_ty*)malloc(sizeof(Node_ty));
        
        ///last node ---> new node
        temp->Next_node = newNode;
        
        newNode->Data = value;
        newNode->Next_node = NULL;
        
    }
}

void DisplayTheList(void){
    if(Head == NULL)
    {
        printf("The list is empty \n");
    }
    else
    {
        Node_ty * temp = Head;
        do{
            printf("%d\n",temp->Data);
            temp = temp->Next_node;
        }while(temp != NULL);
    }
}

void DeleteFromFirst(void)
{
    if(Head == NULL)
    {
        ///Do nothing
    }
    else
    {
        Node_ty * temp = Head;
        Head = Head->Next_node;
        free(temp);
    }
}

void DeleteFromLast(void)
{
    // Task Implementation: DeleteFromLast
    if(Head == NULL)
    {
        // List is empty, do nothing
        return;
    }
    else if(Head->Next_node == NULL)
    {
        // Only one node in the list
        free(Head);
        Head = NULL;
    }
    else
    {
        // Traverse to the second last node
        Node_ty * temp = Head;
        while(temp->Next_node->Next_node != NULL)
        {
            temp = temp->Next_node;
        }
        
        // Delete the last node
        free(temp->Next_node);
        temp->Next_node = NULL;
    }
}

void DeleteByValue(u8 value)
{
    // Task Implementation: DeleteByValue
    if(Head == NULL)
    {
        // List is empty, do nothing
        return;
    }
    
    Node_ty * current = Head;
    Node_ty * previous = NULL;
    
    // Traverse the list to find the node with the value
    while(current != NULL)
    {
        if(current->Data == value)
        {
            // Found the node to delete
            if(previous == NULL)
            {
                // Node to delete is the head
                Head = current->Next_node;
                free(current);
                current = Head;
            }
            else
            {
                // Node to delete is in the middle or end
                previous->Next_node = current->Next_node;
                free(current);
                current = previous->Next_node;
            }
        }
        else
        {
            // Move to next node
            previous = current;
            current = current->Next_node;
        }
    }
}

int main()
{
    printf("Testing the linked list operations:\n\n");
    
    // Test AddAtEnd
    printf("Adding 30 at end:\n");
    AddAtEnd(30);
    DisplayTheList();
    printf("\n");
    
    printf("Adding 10 at end:\n");
    AddAtEnd(10);
    DisplayTheList();
    printf("\n");
    
    printf("Adding 40 at end:\n");
    AddAtEnd(40);
    DisplayTheList();
    printf("\n");
    
    // Test DeleteFromFirst
    printf("Deleting from first:\n");
    DeleteFromFirst();
    DisplayTheList();
    printf("\n");
    
    // Test DeleteFromLast
    printf("Adding more elements:\n");
    AddAtEnd(50);
    AddAtEnd(60);
    AddAtEnd(70);
    DisplayTheList();
    printf("\n");
    
    printf("Deleting from last:\n");
    DeleteFromLast();
    DisplayTheList();
    printf("\n");
    
    // Test DeleteByValue
    printf("Adding values 10, 20, 30, 10:\n");
    AddAtEnd(10);
    AddAtEnd(20);
    AddAtEnd(30);
    AddAtEnd(10);
    DisplayTheList();
    printf("\n");
    
    printf("Deleting all nodes with value 10:\n");
    DeleteByValue(10);
    DisplayTheList();
    printf("\n");
    
    printf("Deleting all nodes with value 30:\n");
    DeleteByValue(30);
    DisplayTheList();
    printf("\n");
    
    return 0;
}