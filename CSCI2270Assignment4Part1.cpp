#include "CommunicationNetwork.cpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char * argv[]){

    //Will be passed when transmitting message
    char* inputFile = argv[1];

    bool continueNetwork = true;

    //Call an instance of CommunicationNetwork
    CommunicationNetwork myNetwork;

    while(continueNetwork){
        //Always start by printing all the menu options
        cout<<"======Main Menu======"<<endl;
        cout<<"1. Build Network"<<endl;
        cout<<"2. Print Network Path"<<endl;
        cout<<"3. Transmit Message Coast-To-Coast-To-Coast"<<endl;
        cout<<"4. Add City"<<endl;
        cout<<"5. Delete City"<<endl;
        cout<<"6. Clear Network"<<endl;
        cout<<"7. Quit"<<endl;

        //Get the user input on the action they want to take
        char userChoice;
        cin>>userChoice;

        if(userChoice == '1'){
            myNetwork.buildNetwork();

        }

        else if(userChoice == '2'){
            myNetwork.printNetwork();
        }

        else if(userChoice == '3'){
            myNetwork.transmitMsg(inputFile);
        }

        else if(userChoice == '4'){

            //This clears the stream
            cin.ignore();

            string cityNew = "";
            string cityPrevious = "";

            cout<<"Enter a city name:"<<endl;
            getline(cin, cityNew);

            cout<<"Enter a previous city name:"<<endl;
            getline(cin, cityPrevious);

            myNetwork.addCity(cityNew, cityPrevious);

        }

        else if(userChoice == '5'){

            //This clears the stream
            cin.ignore();

            string cityDelete = "";

            cout<<"Enter a city name:"<<endl;
            getline(cin, cityDelete);

            myNetwork.deleteCity(cityDelete);
        }

        else if(userChoice == '6'){
            myNetwork.deleteNetwork();
        }

        else if(userChoice == '7'){
            //Exit the menu loop
            cout<<"Goodbye!"<<endl;
            continueNetwork = false;
        }

        else{
            cout<<"Invalid choice!"<<endl;
        }
    }

}
