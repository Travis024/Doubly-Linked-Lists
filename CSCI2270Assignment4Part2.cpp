#include "CommunicationNetwork.h"

CommunicationNetwork::CommunicationNetwork(){
    //default constructor
}

/*
A function to build a network out of pre-determined cities
Pre-conditions: None
Post-conditions: A doubly linked list with a head and tail is build
*/
void CommunicationNetwork::buildNetwork(){

    //Store a default list of cities for initializing the network
    string cityList[10] =
    {
    "Los Angeles", "Phoenix", "Denver",
    "Dallas", "St. Louis", "Chicago",
    "Atlanta", "Washington, D.C.", "New York",
    "Boston"
    };

    //Loop through and initialize each city as a new node in a doubly linked list
    head = new City("Los Angeles", NULL, NULL, "");
    City * temp = head;

    for(int i = 1; i < 10; i++){
        City * newCity = new City(cityList[i], NULL, temp, "");
        temp -> next = newCity;
        temp = newCity;

        //set the tail
        if(i == 9){
            tail = newCity;
        }
    }

    printNetwork();
}

/*
A function to loop through every city and print its name
Pre-conditions: The network has been built
Post-conditions: The network path is printed to the terminal
*/
void CommunicationNetwork::printNetwork(){


    City * temp = head;

    cout<<"===CURRENT PATH==="<<endl;
    cout<<"NULL <- ";

    while(temp!=tail){
        cout<<temp -> cityName<<" <-> ";
        temp = temp -> next;
    }

    cout<<tail->cityName<<" -> ";
    cout<<"NULL"<<endl;
    cout<<"=================="<<endl;
}

/*
A function to read a file word by word and pass the word city by city
Pre-conditions: The network has been built, a file has been passed via the command line
Post-conditions: The word will travel through each city in the network and back again.
*/
void CommunicationNetwork::transmitMsg(char* filename){

    //If the network hasn't been built yet, head is NULL
    if(head -> next == NULL){
        cout<<"Empty list"<<endl;
        return;
    }

    ifstream in_stream(filename);

    //make sure the file opens properly
    if(in_stream.is_open()){

        string currentWord = "";

        //Starting at the head, the message goes through every city
        while(in_stream >> currentWord){

            City * temp = head;

            while(temp!=NULL){
                cout<<temp -> cityName<< " received "<<currentWord<<endl;
                temp = temp -> next;
            }

            //Now, starting at the city before the tail, the message travels back
            temp = tail -> previous;

            while(temp!=NULL){
                cout<<temp -> cityName<< " received "<<currentWord<<endl;
                temp = temp -> previous;
            }

        }

        in_stream.close();
    }

    //Opening the file didn't work.
    else{
        cout<<"Error opening file!"<<endl;
    }

}

/*
A function to add a new city to the network
Pre-conditions: Two strings are passed through
Post-conditions: A nw city is added as the head, as a tail, or after another city in the list
*/
void CommunicationNetwork::addCity(string cityNew, string cityPrevious){

    City * newCity = new City(cityNew, NULL, NULL, "");

    //If the network has not been built, the new city becomes the head
    if(head == NULL){
        head = newCity;
    }

    //If the user passes nothing as the previous city, the city they want to add becomes the tail
    else if(cityPrevious == ""){
        City * temp = head;

        while(temp -> next != NULL){
            temp = temp->next;
        }

        temp -> next = newCity;
        newCity -> previous = temp;
    }

    //If the user passes 'First' as the previous city, then the new city becomes the head
    else if(cityPrevious == "First"){
        City * temp = head;

        newCity -> next = head;
        head -> previous = newCity;
        head = newCity;
    }

    //Otherwise, it's a middle case. Find the city passed as previous city and insert the new city after it.
    else{
        City * temp = head;

        while(temp!=NULL){
            if(temp->cityName == cityPrevious){
                temp -> next -> previous = newCity;
                newCity -> next = temp -> next;
                newCity -> previous = temp;
                temp -> next = newCity;
            }

            temp = temp -> next;
        }
    }
}

/*
A function to delete a city from the network
Pre-conditions: The network has been built, a string is passed through
Post-conditions: If the city is in the network, it is deleted. if it is not in the network, a message is printed to the user.
*/
void CommunicationNetwork::deleteCity(string deleteCity){


    //If the user is deleting the head, move the head to the next city in the list
    if(head -> cityName == deleteCity){
        City * temp = head;

        head = temp -> next;
        temp -> next -> previous = NULL;
        delete temp;
    }

    //If the user is deleting the tail, move the tail to the next city in the list
    else if(tail -> cityName == deleteCity){
        City * temp = tail;

        temp -> previous -> next = NULL;
        tail = temp -> previous;
        delete temp;
    }

    //Otherwise, a middle case is being deleted
    else{
        City * temp = head;

        while(temp -> cityName != deleteCity){
            temp = temp -> next;

            //If we make it all the way through the while loop, the city is not in the list; don't delete anything.
            if(temp -> next == NULL){
                cout<<deleteCity<<" not found"<<endl;
                return;
            }
        }

        //re-direct the pointers so memory isn't lost
        temp -> previous -> next = temp -> next;
        temp -> next -> previous = temp -> previous;
        delete temp;
    }
}

/*
A function to delete every city in the network
Pre-conditions: A network ahs been built
Post-conditions: The entire network is cleared and head = NULL
*/
void CommunicationNetwork::deleteNetwork(){

    City * temp = head;

    //Go though and delete each city, starting at the head
    while(temp  != NULL){

        cout<<"deleting "<<head -> cityName<<endl;
        head = head -> next;
        delete temp;
        temp = head;
    }

}

//The destructor deletes the network and sets head and tail to NULL
CommunicationNetwork::~CommunicationNetwork(){
    deleteNetwork();
    head = NULL;
    tail = NULL;
}
