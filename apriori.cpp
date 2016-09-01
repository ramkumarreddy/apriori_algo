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
	struct Node **child;
	int occur;
	int value;
}node;

node *createnode(int x)
{
	node *temp = NULL;
	temp = (node*)malloc(sizeof(node));
	if(temp)
	{
		int i;
		temp->occur = 0;
		temp->value = 0;
		temp->child = (node**)malloc((x+1)*sizeof(node*));
		for(i = 0; i <= x; i++)
		{
			temp->child[i] = NULL;
		}
	}
	return temp;
};

node insert(node *root, vector<vector <int> > x, vector<int> y, int p)
{
	node *temp;
	vector< vector <int> >::iterator introw;
	vector<int>::iterator intcol;
	vector<int>::iterator occurite;
	occurite = y.begin();
	for(introw=x.begin(); introw != x.end(); introw++)
	{
		temp = root;
		for(intcol = introw->begin(); intcol != introw->end(); intcol++)
		{
			if(!temp->child[*intcol])
			{
				temp->child[*intcol] = createnode(p);
			}
			temp = temp->child[*intcol];
			temp->value = *intcol;
		}
		temp->occur += *occurite;
		occurite++;
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
    		occurences++;
	}
	return occurences;
	if(occurences>=mincount)
		return 1;
	return 0;
}

int binary(vector<int> data,int x)
{
	int i,start=0;
	int end = data.size()-1;
	int mid=(start+end)/2;
	while(1)
	{
		if(start>end)
			return 0;
		else if(data[mid]==x)
			return 1;
		else if(data[mid]<x)
		{
			start = mid+1;
			mid = (start+end)/2;
		}
		else if(data[mid]>x)
		{
			end = mid-1;
			mid = (start+end)/2;
		}
	}
}

int checkb(vector< vector <int> > data, vector<int> x)
{
	int lendata = data.size(),occurences=0;
	int len = x.size(), i, j, flag=0,z;
	for(i=0; i < lendata; i++)
	{
		flag=0;
		for(j = 0; j < len; j++)
		{
			z = binary(data[i],x[j]);
			if(z == 1)
				flag++;
		}
		if(flag == len)
			occurences++;
	}
	return occurences;
}


int search(node *root, vector<int> x)
{
	int occur=1;
	node *temp = root;
	vector<int>::iterator i;
	for(i = x.begin(); i != x.end() && occur==1; i++)
	{
		if(temp->child[*i]!=NULL)
			temp = temp->child[*i];
		else
			occur=0;
	}
	return occur;
}

int pri_tree(node *root)
{
	node *temp = root;
	cout << temp->value;
	cout << " ";
	cout << temp->occur;
	cout << "\n";
	for(int i=1;i<=n;i++)
	{
		if(temp->child[i]!=NULL)
			pri_tree(temp->child[i]);
	}	
}

int main()
{
	unordered_map<string,int> set_index;
	unordered_map<int,string> reverse_mapping;
	vector<vector <string> > idata;
	vector<vector <int> > intdata;
	vector<vector <int> > fim;
	vector<vector <int> > dupfim;
	vector<string> tempvector;
	vector<int> inttempvector;
	vector<int> intdupvector;
	vector<int> intduplicatevector;

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
    int i=0,j=0,p,count,match=1,found,w;
    int toput=0,total_itemsets=0;
    float minsup=0.01;

	// ifstream  data("TextbookInput.csv");
	ifstream  data("inp.csv");
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
		set_index[*setiter] = count;
		reverse_mapping[count] = *setiter;
		count++;
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
	node *root = createnode(n);
	intduplicatevector.clear();
	for(i=1;i<=n;i++)
	{
		if(occur[i]>=mincount)
		{
			intduplicatevector.push_back(occur[i]);
			inttempvector.clear();
			inttempvector.push_back(i);
			fim.push_back(inttempvector);
		}
	}
	*root = insert(root, fim, intduplicatevector, n);
	for (intRow = fim.begin(); intRow != fim.end(); intRow++)
	{
    	for (intCol = intRow->begin(); intCol != intRow->end(); intCol++) 
    	{
    		cout << reverse_mapping[*intCol];
    		// cout << " ";
    	}
    	cout << "\n";
	}

	vector< vector <int> > twodimen;
	vector<int> onetwodimen;
	for(int qqq=0;qqq<=n;qqq++)
	{
		onetwodimen.push_back(0);
	}
	for(int ppp=0;ppp<=n;ppp++)
	{
		twodimen.push_back(onetwodimen);
	}
	for (intRow = intdata.begin(); intRow != intdata.end(); intRow++)
	{
    	for (intCol = intRow->begin(); intCol != intRow->end(); intCol++) 
    	{
			for(intdCol = intCol+1; intdCol !=intRow->end(); intdCol++)
			{    		
    			twodimen[*intCol][*intdCol]++;
    		}
    	}
	}
	onetwodimen.clear();
	dupfim.clear();
	intduplicatevector.clear();
	for (intRow = fim.begin(); intRow != fim.end(); intRow++)
	{
		for(intdRow = intRow+1; intdRow != fim.end() && match==1; intdRow++)
		{
			if(twodimen[*intRow->begin()][*intdRow->begin()]>=mincount)
			{
				onetwodimen.push_back(*intRow->begin());
				onetwodimen.push_back(*intdRow->begin());
				dupfim.push_back(onetwodimen);
				intduplicatevector.push_back(twodimen[*intRow->begin()][*intdRow->begin()]);
				onetwodimen.clear();
				cout << reverse_mapping[*intRow->begin()];
				cout << ",";
				cout << reverse_mapping[*intdRow->begin()];
				cout << "\n";
			}
		}
	}
	fim = dupfim;
	*root = insert(root, fim, intduplicatevector, n);
	dupfim.clear();

	w=1;
	while(1)
	{
		intduplicatevector.clear();
		for (intRow = fim.begin(); intRow != fim.end(); intRow++)
		{
			match=1;
			for(intdRow = intRow+1; intdRow != fim.end() && match==1; intdRow++)
			{
					match=1;
					j=w;
					intCol = intRow->begin();
					intdCol = intdRow->begin();
					inttempvector.clear();
					while(j!=0)
					{
						// cout << "hello resr";
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
					if(match == 0)
						continue;
					inttempvector.push_back(*intCol);
					inttempvector.push_back(*intdCol);
					toput = 1;
					found = 1;
					for(int z=0; z<inttempvector.size() && found == 1; z++)
					{
						intdupvector = inttempvector;
						intdupvector.erase(intdupvector.begin()+z);
						found = search(root,intdupvector);
					}
					if(found == 0)
						continue;
					toput = checkb(intdata, inttempvector);
					if(toput >= mincount)
					{
						dupfim.push_back(inttempvector);
						intduplicatevector.push_back(toput);
					}
			}
		}
		fim = dupfim;
		*root = insert(root, fim, intduplicatevector, n);
		dupfim.clear();
		if(fim.empty())
		{
			// cout << "empty\n";
			break;
		}
		for (intRow = fim.begin(); intRow != fim.end(); intRow++)
		{
	    	for (intCol = intRow->begin(); intCol != intRow->end(); intCol++) 
	    	{
	    		cout << reverse_mapping[*intCol];
	    		if(intCol!=(intRow->end()-1))
	    			cout << ",";
	    	}
	    	cout << "\n";
		}
		w++;
	}
	// cout << "skdh\n";
	// pri_tree(root);
}