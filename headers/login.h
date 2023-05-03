#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
using namespace std;

class userData{
    string userId,password,type,status;
    public:
    userData(){}
    userData(string userId, string password , string type , string status)
    {
        this->userId = userId;
        this->password = password;
        this->type = type;
        this->status = status ;
    }
    string getUser(list<userData>::iterator obj)
    {
        return obj->userId;
    }
    string getPassword(list<userData>::iterator obj)
    {
        return obj->password;
    }
    string getType(list<userData>::iterator obj)
    {
        return obj->type;
    }
    void setStatus(list<userData>::iterator obj,string status)
    {
        obj->status=status;
    }
    string getStatus(list<userData>::iterator obj)
    {
        return obj->status;
    }  
};

class logIn :public userData
{
    private:
        list<userData> head;
        vector<string> makeItWord(string s)
        {
             vector<string> ans;
            string temp;
            for(int i=0 ; i <s.size() ; i++)
            {
                if(s[i]==',')
                {
                    ans.push_back(temp);
                    temp="";
                }
                else{
                    temp.push_back(s[i]);
                }
            }
            ans.push_back(temp);
            return ans;
        }
        void creatUserList()
        {
            fstream fobj;
            fobj.open("../csv/data.csv");
            string temp;
            while(fobj>>temp)
            {      
                vector<string> data = makeItWord(temp);
                head.push_back(userData(data[0],data[1],data[2],data[3]));
            }          
        }
        int isValid(string user , string password)
        {
            list<userData>::iterator itr=head.begin();
            for(; itr!=head.end();itr++)
            {
                
                if( getUser(itr)==user && getPassword(itr)==password)
                {   
                
                    setStatus(itr,"1");
                     
                    if(getType(itr)=="employee")
                    {
                        return 0;
                    }
                    if(getType(itr)=="admin")
                    {
                        return 1;
                    }
                    
                }
                
            }
            return -1;
        }
        void saveChnages()
        {
            fstream obj;
            obj.open("../csv/data2",ios::out);
            list<userData>::iterator itr;
            for(itr=head.begin();itr!=head.end();itr++)
            {
                setStatus(itr,"0");
            } 
        }
    public:
        logIn()
        {
            creatUserList();
        }
        int authentication(string user, string password )
        {
            return isValid(user, password);
        }
        ~logIn()
        {   
            void saveChnages();
            head.clear();
        }            
};
