#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <fstream>
#include <chrono>         // std::chrono::seconds
#include <mutex>

using namespace std;
using namespace std::chrono;
std::mutex mapWrMtx;

class UDPMsg
{
    char msg; //‘A’
    unsigned long int seqNumber; // 329231
    char side; //‘B’
    unsigned long int size; // 2000
    string ticker; // “ABC”
    double price; //23.23

    public :
        friend istream & operator >> (istream &in,  UDPMsg &obj)
        {
            in >> obj.msg;
            in >> obj.seqNumber;
            in >> obj.side;
            in >> obj.size;
            in >> obj.ticker;
            in >> obj.price;
            return in;
        }

        friend ostream & operator << (ostream &out, const UDPMsg & obj)
        {
            out << obj.msg << "\t" << obj.seqNumber << "\t" << "\t"<<obj.side <<"\t"<< obj.size << "\t" << obj.ticker << "\t" << obj.price;
            return out;
        }
        unsigned long int getSeqNumber(){return seqNumber;}
};

map<unsigned long int, UDPMsg> outmap;

/*****************************************
 void readUDPMsgFromFile(char* filename, map<unsigned long int, UDPMsg> &m)
    Read UDP messages from input files
 input  :   filename
 output :   map<unsigned long int, UDPMsg> &m
 return :   -1 error in reading
            n(>-1) number of UDP messages read
*****************************************/
void readUDPMsgFromFile(char* filename, map<unsigned long int, UDPMsg> &m)
{
    cout<<"readUDPMsgFromFile() :: reading file "<<filename<<endl;
    std::ifstream in(filename);
    UDPMsg msg;
    //std::this_thread::sleep_for (std::chrono::milliseconds(500));

    while (in>>msg)
    {
        if ( m.find(msg.getSeqNumber()) == m.end() )
        {
            // not found
            m[msg.getSeqNumber()]=msg;
        }
        else
        {
            //cout<<"Duplicate message with sequence number "<< msg.getSeqNumber() << "in file "<<filename<<endl;
        }
        // mark duplicate
    }
    in.close();

    cout<<"read "<<m.size()<<" UDP messages"<<endl;

    mapWrMtx.lock();
    //critical section
    outmap.insert(m.begin(),m.end());
    mapWrMtx.unlock();

}

/*****************************************
 void printUDPMsgMap(map<unsigned long int, UDPMsg> &m)
    Print contents of the UDP Message map
 input  :   map
 output :   -
 return :   -
*****************************************/
void printUDPMsgMap(map<unsigned long int, UDPMsg> &m)
{
    cout<<"printUDPMsgMap() :: ------------------------------------------"<<endl;
    cout <<"msg"<<"\t"<<"seqNumber"<<"\t"<<"side"<<"\t"<<"size"<<"\t"<<"ticker"<<"\t"<<"price"<<endl;
    for (auto const &x : m)
    {
        cout<<x.second<<endl;
    }
}

/*****************************************
 void printUDPMsgMap(map<unsigned long int, UDPMsg> &m)
    Print contents of the UDP Message map
    and write it into file
 input  :   map
 output :   written into file "outfile"
 return :   none
*****************************************/
void printUDPMsgMap(map<unsigned long int, UDPMsg> &outmap, char* outfile)
{
    ofstream outdata;
    outdata.open(outfile);
    // TODO : Error handle : If file exists ask before overwrite

    if( !outdata ) {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    cout<<"printUDPMsgMap(outmap) :: ------------------------------"<<endl;
    cout <<"msg"<<"\t"<<"seqNumber"<<"\t"<<"side"<<"\t"<<"size"<<"\t"<<"ticker"<<"\t"<<"price"<<endl;

    for (auto const &x : outmap)
    {
        cout<<x.second<<endl;
        outdata<<x.second;
    }

    cout<<outmap.size()<<" unique UDP messages in total"<<endl;

    outdata.close();
}

int main(int argc, char** argv)
{
    int count,i;
    auto start = high_resolution_clock::now();

    cout << "Message Processor reading files "<<endl;
    cout << "--------------------------------------------------------"<<endl;

    std::vector<std::thread> ThreadVector;
    ThreadVector.resize(argc-2);
    // first arg prog name, last arg output file name.
    // thus argc-2 input files.
    // We are creating same number of threads to handle them.

    for (i=1; i<argc-1; i++){
        map<unsigned long int, UDPMsg> m;

        //readUDPMsgFromFile(argv[i], m);
        ThreadVector.push_back(std::thread(readUDPMsgFromFile, argv[i], std::ref(m)));
        //if(size ==-1){continue;}
        //printUDPMsgMap(m);
        cout << "--------------------------------------------------------"<<endl;
        //std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    for (std::thread & th : ThreadVector)
    {
        if (th.joinable())
            th.join();
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;


    cout << "--------------------------------------------------------"<<endl;
    cout << "Output Map : (duplicates removed)"<<endl;

    printUDPMsgMap(outmap, argv[argc-1]);

    return 0;

}
