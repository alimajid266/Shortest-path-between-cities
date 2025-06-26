

//M.Ali Majid, 22i-9874 sec B
//Ahmed Waqar, 22i-2217, sec B
//Created a weighted graph using a text file, made an adjlist and adjmatrix, used dijkstra to find shortestpath




#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#define INFINITY_CONST 1000000 // Defining  infinity distance for dijkstra 
using namespace std;

struct graphnode
{
	int adjcity;
	int distance;
};

class weightedgraph
{
private:
	list<graphnode>* grapharray;
	int* parent;
	int totalvertices;
	string* arr;

public:
	void creategraph()
	{
		arr = new string[40];
		ifstream read("graph.txt");
		read >> totalvertices;  //reads first line
		grapharray = new list<graphnode>[totalvertices];
		int i = 0;
		while (!read.eof())
		{
			graphnode currvertice;    
			int temp;    // to read the current vertice
			read >> temp;
			read >> currvertice.adjcity;    //reads adjacent city

			while (currvertice.adjcity != -999)
			{
				read >> currvertice.distance;   //reads adjacent city's distance
				grapharray[i].push_back(currvertice);
				read >> currvertice.adjcity;   //checks if adjacent city exists or not
			}
			i++;
		}
	}





	// Shortest path 
	void shortestPath(int startcity, int endcity, string arr[])
	{
		priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > cityqueue;
		int* distance = new int[totalvertices];      //for distance
		int* pred = new int[totalvertices];   //for node

		for (int i = 0; i < totalvertices; ++i)
		{
			distance[i] = INFINITY_CONST;
			pred[i] = -1;
		}
		cityqueue.push(make_pair(0, startcity));
		distance[startcity] = 0;

		while (!cityqueue.empty())
		{
			int currnode =cityqueue.top().second;    cityqueue.pop();


			for (list<graphnode>::iterator it = grapharray[currnode].begin(); it != grapharray[currnode].end(); it++)
			{
				int adjnode = it->adjcity;
				int distanceweight = it->distance;     //distance from currnode to adjnode

				if (distance[adjnode] > distance[currnode] + distanceweight)
				{
					distance[adjnode] = distance[currnode] + distanceweight;
					pred[adjnode] = currnode;
					cityqueue.push(make_pair(distance[adjnode], adjnode));
				}
			}
		}
		cout << "distance from " << arr[startcity] << " to " << arr[endcity] << " = ";
		if (distance[endcity] == INFINITY_CONST)
			cout << "No route found." << endl;
		else
			cout << distance[endcity] << " Kms  " << endl;  //prints distance

		cout << "Route: ";

		// Prints path
		int currentcity = endcity;
		while (currentcity != -1)
		{
			cout << arr[currentcity];
			currentcity = pred[currentcity];
			if (currentcity != -1)
				cout << " <- ";
		}

		cout << endl;
	}


	//failed attempt on shortestpath
/*	void shortestPath(int vertex)
	{
		for (int i = 0; i < gsize; i++)
		{
			smallestWeight[i] = wtdMat[vertex][i];
		}
		bool* weightfound;
		weightfound = new bool[gsize];
		pred = new int[gsize];
		for (int i = 0; i < gsize; i++)
		{
			weightfound[i] = false;
			pred[i] = -1;
		}
		weightfound[vertex] = true;
		smallestWeight[vertex] = 0;
		for (int i = 0; i < gsize - 1; i++)
		{
			double minweight = DBL_MAX;
			int v;
			for (int j = 0; j < gsize; j++)
			{
				if (!weightfound[j])
				{
					if (smallestWeight[j] < minweight)
					{
						v = j;
						minweight = smallestWeight[v];
					}
				}
			}
			weightfound[v] = true;
			for (int j = 0; j < gsize; j++)
			{
				if (!weightfound[j])
				{
					if (minweight + wtdMat[v][j] < smallestWeight[j])
					{
						smallestWeight[j] = minweight + wtdMat[v][j];
						pred[j] = v;
					}
				}
			}
		}
	}*/








	void printlist(string arr[])   //to check if file is working or not, implemented adj list
	{
		for (int i = 0; i < totalvertices; i++)
		{
			cout << "  " << i << " (" << arr[i] << "): ";
			list<graphnode>::iterator it;
			for (it = grapharray[i].begin(); it != grapharray[i].end(); ++it)
			{
				cout << it->adjcity << '\t' << "weight: " << it->distance << "  ";
			}
			cout << endl;
		}
	}

	int** matrixmaker()     //to create adjacency matrix
	{
		int** adjmatrix = new int* [totalvertices];

		for (int i = 0; i < totalvertices; i++)
		{
			adjmatrix[i] = new int[totalvertices];

			for (int j = 0; j < totalvertices; j++)
			{
				adjmatrix[i][j] = 0;
			}
		}

		for (int i = 0; i < totalvertices; i++)
		{
			list<graphnode>::iterator it;
			for (it = grapharray[i].begin(); it != grapharray[i].end(); ++it)
			{
				adjmatrix[i][it->adjcity] = it->distance;
			}
		}
		return adjmatrix;
	}
};

int main()
{
	string arr[40] = {     //hard coded city names in a string array
		"Glasgow", "Manchester", "Birmingham", "London", "Lille", "Brussels", "Paris", "Bordeaux",
		"Vitoria", "Amsterdam", "Hannover", "Nuremberg", "Mannheim", "Stuttgart", "Munich", "Verona",
		"Bologna", "Ancona", "Rome", "Naples", "Bari", "Palermo", "Berlin", "Rostock",
		"Poznan", "Warsaw", "Kaunas", "Riga", "Tallinn", "Wroclaw", "Ostrava", "Zilina",
		"Bratislava", "Budapest", "Arad", "Craiova", "Bucharest", "Sofia", "Thessaloniki", "Athens" };

	cout << "Start" << endl << endl << endl;
	weightedgraph gg;
	gg.creategraph();  //creates graph

	int option = 0;
	while (option < 4)
	{
		cout << "1) display data, 2) display matrix, 3) short path, 4) exit: ";
		cin >> option;
		if (option == 1)  //displays adj list
		{
			gg.printlist(arr);
		}
		else if (option == 2)  //displays adj matrix
		{
			int** matrix = gg.matrixmaker();
			cout << "\nAdjacency Matrix:\n";
			for (int i = 0; i < 40; i++)
			{
				cout << i << ":" << '\t';
				for (int j = 0; j < 40; j++)
				{
					cout << matrix[i][j] << " ";
				}
				cout << '\n';
			}
		}
		else if (option == 3)
		{
			string start, ending;
			cout << "Enter starting city: ";  //input of starting city
			cin >> start;
			cout << "Enter ending city: ";   //input of ending city
			cin >> ending;

			// Find the indices corresponding to the entered city names
			int startindex = -1, endindex = -1;
			for (int i = 0; i < 40; ++i)       //linear search
			{
				if (arr[i] == start)
					startindex = i;
				if (arr[i] == ending)
					endindex = i;
			}

			if (startindex == -1 || endindex == -1)  //if city not found
			{
				cout << "No such cities exists.\n";
			}
			else
			{
				gg.shortestPath(startindex, endindex, arr);
			}
		}
		else   // to exit program
		{
			break;
		}
	}
     return 0;
}
