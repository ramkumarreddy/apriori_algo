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
float mincount;

bool myfunction (int i, int j) {
  return (i==j);
}

typedef struct Node
{
	struct Node *child[20];
	int occur;
	int value;
}node;

node *createnode(void)
{
	node *temp = NULL;
	temp = (node*)malloc(sizeof(node));
	if(temp)
	{
		int i;
		temp->occur = 0;
		temp->value = 0;
		for(i = 0; i < 20; i++)
		{
			temp->child[i] = NULL;
		}
	}
	return temp;
};

node insert(node *root, vector<vector <int> > x)
{
	node *temp;
	vector< vector <int> >::iterator introw;
	vector<int>::iterator intcol;
	for(introw=x.begin(); introw != x.end(); introw++)
	{
		temp = root;
		for(intcol = introw->begin(); intcol != introw->end(); intcol++)
		{
			if(!temp->child[*intcol])
			{
				temp->child[*intcol] = createnode();
				temp->value = *intcol;
			}
			else
			{
				temp->occur++;
			}
			temp = temp->child[*intcol];
		}

	}
	return *root;
}

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
	if(occurences>mincount)
		return 1;
	return 0;
}

int search(node *root, vector<int> x)
{
	int occur=1;
	node *temp = root;
	vector<int>::iterator i;
	for(i = x.begin(); i != x.end() && occur==1; i++)
	{
		if(temp->child[*i]!=NULL)
		{
			temp = temp->child[*i];
		}
		else
		{
			occur=0;
		}
	}
	return occur;
}

int pri_tree(node *root)
{
	node *temp = root;
	for(int i=1;i<=16;i++)
	{
		if(temp->child[i]!=NULL)
		{
			cout << i;
			cout << " ";
			pri_tree(temp->child[i]);
		}
	}	
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
	vector<int> intdupvector;

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
    int i=0,j=0,p,count,match=1,found;
    int toput=0,total_itemsets=0;
    float minsup=0.4;

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
		// cout << *setiter+"\n";
		set_index[*setiter]=count++;
	}
	n=count-1;

    for (itRow = idata.begin(); itRow != idata.end(); itRow++)
	{
		inttempvector.clear();
		total_itemsets++;
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
	mincount=minsup*total_itemsets;
	node *root = createnode();
	for(i=1;i<=n;i++)
	{
		if(occur[i]>mincount)
		{
			inttempvector.clear();
			inttempvector.push_back(i);
			fim.push_back(inttempvector);
		}
	}
	*root = insert(root, fim);

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
				if(match==0)
					continue;
				inttempvector.push_back(*intCol);
				inttempvector.push_back(*intdCol);
				toput = 1;
				found = 1;
				for(int z=0;z<inttempvector.size() && found==1;z++)
				{
					intdupvector = inttempvector;
					intdupvector.erase(intdupvector.begin()+z);
					found = search(root,intdupvector);
				}
				if(found==0)
					continue;
				toput = check(intdata, inttempvector);
				if(toput == 1 && found==1)
					dupfim.push_back(inttempvector);
		}
	}
	fim = dupfim;
	*root = insert(root, fim);
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
	cout << "hello\n";
	pri_tree(root);
	cout << "hello\n";

	// search working
	// inttempvector.clear();
	// inttempvector.push_back(6);
	// inttempvector.push_back(16);
	// cout << search(root, inttempvector);
	// cout << "hello\n";


	// node *root = createnode();
	// inttempvector.clear();
	// inttempvector.push_back(1);
	// inttempvector.push_back(11);
	// insert(root, inttempvector);

}