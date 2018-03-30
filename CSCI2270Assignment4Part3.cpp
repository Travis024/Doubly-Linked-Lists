#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//A structure for the City object

struct City{

    string cityName = "";
    City * next = NULL;
    City * previous = NULL;
    string message = "";

    //default
    City(){};

    //initialized
    City(string initName, City * initNext, City * initPrevious, string initMessage){
        cityName = initName;
        next = initNext;
        previous = initPrevious;
        message = initMessage;
    }
};

class CommunicationNetwork{

    public:

        //default constructor and destructor
        CommunicationNetwork();
        ~CommunicationNetwork();

        void addCity(string, string);
        void buildNetwork();
        void transmitMsg(char *);
        void printNetwork();
        void deleteCity(string);
        void deleteNetwork();

        private:
            City *head;
            City *tail;

};

