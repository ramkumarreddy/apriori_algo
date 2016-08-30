#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <set>
#include <tr1/unordered_map>
#include <bits/stdc++.h>
using namespace std;
using namespace tr1;



int n=0;
bool myfunction (int i, int j) {
  return (i==j);
}

typedef struct Node
{
	struct Node *child[20];
}node;

node *createnode(void)
{
	node *temp = NULL;
	temp = (node*)malloc(sizeof(node));
	if(temp)
	{
		int i;
		for(i = 0; i < 20; i++)
		{
			temp->child[i] = NULL;
		}
	}
	return temp;
};

// void insert(node *root, vector<int> x)
// {
// 	vector<int>::iterator introw;
// 	for(introw=x.begin(); introw != x.end(); introw++)
// 	{

// 	}
// }

int check(vector< vector <int> > data, vector<int> x)
{
	int occurences = 0, flag;
	vector<vector<int> >::iterator intRow;
	vector<int>::iterator intCol;
	vector<int>::iterator i;
	int len = x.size();
	for (intRow = data.begin(); intRow != data.end(); intRow++)
	{
		flag = 0;
		for(i = x.begin(); i != x.end(); i++)
		{
    		for (intCol = intRow->begin(); intCol != intRow->end(); intCol++) 
    		{
    			if(*i == *intCol)
    				flag++;
    		}
    	}
    	if(flag == len)
    	{
    		occurences++;
    	}
	}
	if(occurences>2)
		return 1;
	return 0;
	// cout << occurences;
	// cout << " ";
	// return occurences;
}



int main()
{
	unordered_map<string,int> set_index;
	vector<vector <string> > idata;
	vector<vector <int> > intdata;
	vector<vector <int> > fim;
	vector<vector <int> > dupfim;
	vector<string> tempvector;
	vector<int> inttempvector;

	set<string> mapp;

	vector<vector<string> >::iterator itRow;
	vector<string>::iterator itCol;
	vector<vector<int> >::iterator intRow;
	vector<vector<int> >::iterator intdRow;
	vector<int>::iterator intCol;
	vector<int>::iterator intdCol;
	vector<int>::iterator it;
	set<string>::iterator setiter;

	string line;
    int i=0,j=0,p,count,minsup=2,match=1;
    int toput=0;

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
		cout << *setiter+"\n";
		set_index[*setiter]=count++;
	}
	n=count-1;
    for (itRow = idata.begin(); itRow != idata.end(); itRow++)
	{
		inttempvector.clear();
    	for (itCol = itRow->begin(); itCol != itRow->end(); itCol++) 
    	{
    		inttempvector.push_back(set_index[*itCol]);
    	}
    	sort(inttempvector.begin(), inttempvector.end());
    	it = unique(inttempvector.begin(), inttempvector.end());
    	inttempvector.resize(distance(inttempvector.begin(),it));
    	unique (inttempvector.begin(), inttempvector.end(), myfunction);
    	intdata.push_back(inttempvector);
	}

	int occur[n+1]={0};
	for (intRow = intdata.begin(); intRow != intdata.end(); intRow++)
	{
    	for (intCol = intRow->begin(); intCol != intRow->end(); intCol++) 
    	{
    		occur[*intCol]+=1;
    	}
	}

	minsup = 2;
	for(i=1;i<=n;i++)
	{
		if(occur[i]>minsup)
		{
			inttempvector.clear();
			inttempvector.push_back(i);
			fim.push_back(inttempvector);
		}
	}
	
	for (intRow = fim.begin(); intRow != fim.end(); intRow++)
	{
		match=1;
		for(intdRow = intRow+1; intdRow != fim.end() && match==1; intdRow++)
		{
				match=1;
				j=0;
				intCol = intRow->begin();
				intdCol = intdRow->begin();
				inttempvector.clear();
				while(j!=0)
				{
					// cout << "hello";
					if(*intCol!=*intdCol)
					{
						match=0;
						break;
					}
					inttempvector.push_back(*intCol);
					intCol++;
					intdCol++;
					j--;
				}
				inttempvector.push_back(*intCol);
				inttempvector.push_back(*intdCol);
				toput = check(intdata, inttempvector);
				if(toput == 1)
					dupfim.push_back(inttempvector);				
		}
	}
	fim = dupfim;
	dupfim.clear();
	for (intRow = fim.begin(); intRow != fim.end(); intRow++)
	{
    	for (intCol = intRow->begin(); intCol != intRow->end(); intCol++) 
    	{
    		cout << *intCol;
    		cout << " ";
    	}
    	cout << "\n";
	}
	// node *root = createnode();
	// inttempvector.clear();
	// inttempvector.push_back(1);
	// inttempvector.push_back(11);
	// insert(root, inttempvector);

}