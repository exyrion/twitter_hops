//Justin Liang
//CS130A
//Due: 12/11/12
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <queue>
using namespace std;

//Vertex class for the graph
//Each vertex has information about its name,
//its neighboring vertexes (adjList),
//and its distance from source
class Vertex
{
	public:
	string name;
	vector<Vertex *> adjList;
	int distance;
	
	Vertex(string s)
	{
		name = s;
	}
};

//Construct a new map called graph and an iterator "it" for traversals
map <string, Vertex *> graph;
map <string, Vertex *>::iterator it;

//Computes the shortest path between a source and destination
//Returns an int
int computeShortestPath(Vertex *source, Vertex *destination)
{
	//Initially, set all vertex distance from source to be -1
	for(it = graph.begin(); it != graph.end(); it++)
	{
		(it->second)->distance = -1; //Set distance of each vertex to a large number
	}
	
	//Construct a queue and insert the source
	queue<Vertex *> q;
	q.push(source);
	source->distance = 0;
	
	//While the queue is not empty, process the source's distance from source first
	//Then process the neighboring vertex's distance from source
	//then its neighboring neighbors, and so on...
	//Computes the shortest distance path from every vertex in the graph to its source
	while(!q.empty())
	{
		Vertex *v = q.front();
		q.pop();
		
		for(int i = 0; i < v->adjList.size(); i++)
		{
			if(v->adjList[i]->distance == -1)
			{
				v->adjList[i]->distance = v->distance + 1;
				q.push(v->adjList[i]);
			}
		}
	}
	
	//However, we only need the shortest distance path from a specified destination
	//Therefore, we search the graph for the specified destination and return its shortest distance path
	for(it = graph.begin(); it != graph.end(); it++)
	{
		if(destination == it->second)
		{
			return it->second->distance;
		}
	}
}

//Main function
int main()
{
	string str;
	int numOfPeople, numOfEdges, numOfQueries;	
	
	//First process the number of vertexes (people) in the network
	//and assign them to the keys in the graph
	cin >> numOfPeople;
	for(int i = 0; i < numOfPeople; i++)
	{
		cin >> str;
		Vertex *s = new Vertex(str);
		graph.insert(pair<string, Vertex *>(str, s));
	}
	
	//Next, assign edges or followers and followed relationship between vertexes
	cin >> numOfEdges;
	for(int i = 0; i < numOfEdges; i++)
	{
		string follower;
		string followed;
		
		cin >> follower;
		cin >> str; //temporary holds the word "follows"
		cin >> followed;
		
		//Traverse through the graph and assign follower relationship
		//In code, assign each key value in the map a certain vertex
		for(it = graph.begin(); it != graph.end(); it++)
		{
			if((it->first).compare(followed) == 0)
			{
				((it->second)->adjList).push_back(graph.find(follower)->second);
			}
		}
	}
	
	//Lastly, process the queries
	//Format is as follows: i.e. "dennis andres"
	//means that dennis is the source and andres is the destination
	//Use computeShortestPath(source, destination) to find shortest path between two vertexes
	cin >> numOfQueries;
	for(int i = 0; i < numOfQueries; i++)
	{
		string source;
		string destination;
		cin >> source;
		cin >> destination;
		cout << computeShortestPath(graph.find(source)->second, graph.find(destination)->second) << endl;;
	}	
}

