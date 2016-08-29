#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <set>
#include <tr1/unordered_map>
#include <bits/stdc++.h>
using namespace std;
using namespace tr1;

int main()
{
	unordered_map<string,int> set_index;
	vector<vector <string> > idata;
	vector<vector <int> > intdata;
	vector<string> tempvector;
	vector<int> inttempvector;

	set<string> mapp;

	vector<vector<string> >::iterator itRow;
	vector<string>::iterator itCol;
	vector<vector<int> >::iterator intRow;
	vector<int>::iterator intCol;
	set<string>::iterator setiter;

	string line;
    int i=0,j=0,p,count;

	ifstream  data("TextbookInput.csv");
    while(getline(data,line))
    {
        stringstream lineStream(line);
        string cell;
        j=0;
        while(getline(lineStream,cell,','))
        {
        	if(cell.length()>0)
        	{
            	tempvector.push_back(cell);
            	mapp.insert(cell);
            }
        }
        idata.push_back(tempvector);
        tempvector.clear();
    }

    count=1;
	for (setiter=mapp.begin(); setiter != mapp.end(); setiter++)
	{
		set_index[*setiter]=count++;
	}

    for (itRow = idata.begin(); itRow != idata.end(); itRow++)
	{
		inttempvector.clear();
    	for (itCol = itRow->begin(); itCol != itRow->end(); itCol++) 
    	{
    		inttempvector.push_back(set_index[*itCol]);
    	}
    	intdata.push_back(inttempvector);
	}	

 //    for (intRow = intdata.begin(); intRow != intdata.end(); intRow++)
	// {
 //    	for (intCol = intRow->begin(); intCol != intRow->end(); intCol++) 
 //    	{
 //    		cout << *intCol;
 //    		cout << " ";
 //    	}
 //    	cout << "\n";
	// }
}