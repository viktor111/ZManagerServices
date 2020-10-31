#include<iostream>
#include<string>
#include<fstream> 
#include<sstream>
#include<vector>

using namespace std;

class Util{
    public:
        void tokenize(string const &str, const char delim,
			    vector<string> &out)
        {
	        size_t start;
	        size_t end = 0;

	        while ((start = str.find_first_not_of(delim, end)) != string::npos)
	        {
		        end = str.find(delim, start);
		        out.push_back(str.substr(start, end - start));
	        }
        }
};

class File{

    public:       

        inline bool file_exist_check (const string& name) {
            if (FILE *file = fopen(name.c_str(), "r")) {
                fclose(file);
                    return true;
            } 
            else {
                return false;
            }   
        }

        inline bool file_empty_check(const string name){
            ifstream file_read(name);

            string line;
            int count = 0;

            while(getline(file_read, line)){

                if(count == 1){
                    return true;

                }

                count++;

            }

            return false;

        }
};

class Personel{

    private:
        string file_name = "personel.csv";

    public:
        string name;
        int age;
        int payment;
        string adress;
    
        void save_person(){          

            bool file_exist, file_empty;

            File file_func;

            file_exist = file_func.file_exist_check(file_name);
            file_empty = file_func.file_empty_check(file_name);

            if(file_exist && file_empty){

                ofstream file(file_name, ofstream::app);

                vector<string> data = {name, to_string(age), to_string(payment), adress};

                for(int i = 0; i < data.size(); i++){
                    file << data[i] << ",";
                }

                file << "\n";
                file.close();

            }
            else if(!file_empty){

                ofstream file(file_name, ofstream::app);

                vector<string> data = {name, to_string(age), to_string(payment), adress};

                file << "Name," << "Personel," << "Owner," << "Adress,\n";   

                for(int i = 0; i < data.size(); i++){
                    file << data[i] << ",";
                }

                file << "\n";

                file.close();
            }
        }

        int all_month_payment(){

            Util util;
            bool file_exist;

            File file_func;

            file_exist = file_func.file_exist_check(file_name);

            if(file_exist){
                ifstream get_file(file_name);

                string line;
                int counter = 0;
                int output;
                while(getline(get_file, line)){
                    counter++;

                    vector<string> out;
                    if(counter > 1){  

                        util.tokenize(line, ',', out);
                        output += stoi(out[2]);               
                    }
                }

                return output;
            }

            else
            {
                return 0;
            }
            
        }
};

class Buisness{ 
    private:
        string file_name = "buisness.csv";
        string file_created_messege = "[+] File generated";          
 
    public:
        string name;
        string personel_count;
        string owner_name;
        string adress;
       
    void save_to_file(){

        bool file_exist, file_empty;

        File file_func;

        file_exist = file_func.file_exist_check(file_name);
        file_empty = file_func.file_empty_check(file_name);

        if(file_exist && file_empty){

            ofstream file(file_name, ofstream::app);

            vector<string> data = {name, personel_count, owner_name, adress};

            for(int i = 0; i < data.size(); i++){
                file << data[i] << ",";
            }

            file << "\n";
            file.close();

        }
        else if(!file_empty){

            ofstream file(file_name, ofstream::app);
            vector<string> data = {name, personel_count, owner_name, adress};

            file << "Name," << "Personel," << "Owner," << "Adress,\n";   

            for(int i = 0; i < data.size(); i++){
                file << data[i] << ",";
            }

            file << "\n";

            file.close();
        }
        
    }

    void list_buisnesses(){
        File file_func;

        bool file_exist = file_func.file_exist_check(file_name);

        if(file_exist){
            ifstream file_read(file_name);

            string line;

            while(getline(file_read, line)){
                
                cout << line << endl << "---- ------ ---- -----" << endl;
            }

        }
        else{
            cout << "[-] Create a buisness first!";
        }
    }
};

void main_menu(){
    cout << "0. Add buisness to list" << endl;
    cout << "1. List all buisness" << endl;
    cout << "2. Add worker" << endl;
    cout << "3. All payments for this month" << endl;
}

void help(){
    cout << "Press m for menu and choose different numbers to perform different actions!" << endl;
}

void add_buisness(){
    Buisness buisness;

    cout << "Buisness name: ";
    cin >> buisness.name;
    cout << "Personal count: ";
    cin >> buisness.personel_count;
    cout << "Owner name: ";
    cin >> buisness.owner_name;
    cout << "Adress: ";
    cin >> buisness.adress;

    buisness.save_to_file();
}

void add_person(){
    Personel personel;

    cout << "Person name: ";
    cin >> personel.name;
    cout << "Person age: ";
    cin >> personel.age;
    cout << "Persone adress: ";
    cin >> personel.adress;
    cout << "Person payment: ";
    cin >> personel.payment;

    personel.save_person();
}

void get_all_payment(){
    Personel persons; 
    int data = persons.all_month_payment();
    cout << data << " BGN" << endl;
}


int main(){

    Buisness buisness;
    Personel persons;

    
    main_menu();

    string input;
    while(1){
        cout << "> ";
        cin >> input;

        if(input == "m"){
            main_menu();
        }
        if(input == "0"){
            add_buisness();
        }
        if(input == "1"){
            buisness.list_buisnesses();
        }
        if(input == "2"){
            add_person();
        }
        if(input == "3"){
            persons.all_month_payment();
            get_all_payment();
        }

    }
}
