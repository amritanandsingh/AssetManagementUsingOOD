#include<iostream>
#include"../headers/utility.h"
#include "../headers/log_In_Class.h"
#include "../headers/main_helper.h"
#include"../headers/AssetRequests.h"
#include "../headers/login.h"
using namespace std;

int main()
{ 
     
    //login obj;
    utlity utlity_obj;                              // utility class object is created 
    char ch;
    do{
        cout << "\033[2J\033[1;1H";
        utlity_obj.main_menu();                    // utility main_menu() function called .
        cin>>ch;
        if(ch=='1')
        {   //ch='2';
            string userID,password;
            cout<<"Enter UserID : ";
            cin>>userID;
            cout<<"Enter Password : ";
            cin>>password;
            //AssetDataOperations assetdataopration_object;
            Login obj;
            int status = obj.authenticate(userID,password);
            if(status==0 || status==1 )                                 // if credentials found than control move to if block.
            {   
                if(status==0)
                {    cout << "\033[2J\033[1;1H";
                    AssetRequestDataOpeations objOfRequest;             // this class belong from AssetRequests.h    
                    AssetTaggingDataOpeations  taggingObj;              //  this class defind in AssetTagging.h 
                    int choice;                                         // this variable used for taking user input at each itr..
                    do{
                        utlity_obj.employee_main_menu();                // this funtion is defind in utlity and only use to display menu.
                        cin>>choice;
                        switch (choice)                             //switch case for employee  
                        {   
                            
                            case 1:
                                taggingObj.EmployeeCanViewTaggedAsset(userID);     // this member funtion is used to view Asset tagged to employee.
                                break;
                            case 2:
                                {
                                    int f=taggingObj.taggedAsset(userID);           
                                    if(f==0)
                                    {
                                        int f=objOfRequest.RequestAssetHelper(userID);    // this member funtion used to Request for Asset.
                                        //cout<<"request is raised "<<endl;
                                        if(f==0)
                                        {
                                            cout<<"somthing went wrong !! "<<endl;
                                        }
                                    }
                                    else{
                                        
                                            try {
                                                    throw MyCustomException(f);
                                                }
                                            catch (MyCustomException mce) 
                                                {   
                                            
                                                    if(mce.what()==1)
                                                    {
                                                        cout<<"InvalidTaggingException"<<endl;
                                                    }
                                                    
                                                }

                                        }
                                }
                                break;
                            case 3:
                                objOfRequest.RequestStatus(userID);   // this fun. used to view status of request.
                                break;
                            case 4:
                              //  if(obj.Logout(userID))               // this funtion set active status to 0 in logIn.csv
                                    cout<<"Log Out Successful !"<<endl;
                                break;    
                            default:
                                cout<<"WRONG INPUT "<<endl;
                                break;
                        }
                    }while(choice!=4);
                }    
                else if(status==1)                          // admin switch menu
                {  
                    int choise;
                    do{ 
                        cout << "\033[2J\033[1;1H";
                        utlity_obj.admin_main_menu();       // this funtion used to show menu of admin
                        cin>>choise;
                        switch(choise)
                        {   cin>>choise;
                            case 1:
                                main_funtion_asset_caller();   // CRUD oprtion of Asset is done by this funtion
                                utlity_obj.getch();             // this funtion is used to hold screen
                                break;
                            case 2:
                                EmployeeAdminCaller();            // CRUD opration in Employee is done by calling this funtion.
                                utlity_obj.getch();
                                break;     
                            case 3:
                                AssetTggingCaller();                // tag , Detag, search by AssetID functiones implemented in this funtion
                                utlity_obj.getch();
                                break;
                            case 4:
                                ViewListAssetEmployeeDetails();              // this funtion used to view details of employee with asset tagged .
                                utlity_obj.getch();
                                break;
                            case 5:
                                EOLCaller();                            // this funtion is used to display EOL form Asset.csv
                                utlity_obj.getch();
                                break;
                            case 6:
                            {
                               // if(obj.Logout(userID))
                                    cout<<"Log Out Successful !"<<endl;
                            }
                                break; 
                            default:
                                cout<<"WRONG INPUT "<<endl;
                                utlity_obj.getch();
                        }
                    }while(choise!=6); 
                    
                }
                utlity_obj.getch();
            }
            else{
                cout<<"Wrong login credentials";
                utlity_obj.getch();
                }   
        }
    }while(ch!='2');
    return 0;
}