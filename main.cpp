// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include<vector>
using namespace std;
void calculatepermutations(vector<int> vec, int l, int r, int** graph);
int globalmin;
void createGraph(int argc,char* argv[])
{
	if (argc != 3)
	{
		cout << "Error: Incorrect number of arguments!!!" << endl;
		exit(EXIT_FAILURE);
		
	}
	fstream input(argv[1]);
	ofstream output(argv[2]);
	if (!input)
	{
		cout << "Error: Cannot open input file!!!" << endl;
		exit(EXIT_FAILURE);
	}

	if (!output)
	{
		cout << "Error: Cannot open output file (Permission issue?) !!!" << endl;
		exit(EXIT_FAILURE);
	}
	int numberofgraphs;
	int vertices, edges;
	int** graph;
	input >> numberofgraphs;

	for (int i = 0; i < numberofgraphs; i++)
	{
		globalmin = 111111;
		input >> vertices;
		input >> edges;
		vector<int> vec(vertices);
		
		for (int i = 0; i < vertices; i++)
		{
			vec[i] = i;
		}
	    graph = new int*[vertices];
		for (int i = 0; i < vertices; i++)
			graph[i] = new int[vertices];

		for (int i = 0; i < edges; i++)
		{
			int a, b, c;
			input >> a;
			input >> b;
			input >> c;
			graph[a][b]=c;
			graph[b][a]=c;
		}
		/*
		for (int i = 0; i < vertices; i++)
		{
			for (int j = 0; j < vertices; j++)
			{
				cout << "graph[" << i << "]" << "[" << j << "]=" << graph[i][j]<<endl;
				
			}
		
		}
		*/
     	calculatepermutations(vec,0,vec.size(),graph);
		output << globalmin<<endl;
	}
	
}
void swapfunction(int *temp1, int *temp2)
{
	int temp;
	temp = *temp1;
	*temp1 = *temp2;
	*temp2 = temp;
}
void calculatepermutations(vector<int> vec, int start,  int end,int** graph)
{
	int i;
	if (start == end)
	{
		int sum = 0;
		for (int j = 0; j< vec.size()-1; j++)
		{
			
			sum = sum + graph[vec[j]][vec[j + 1]];
			if (vec.size() - 2 == j)
			{
				sum = sum + graph[j+1][0];
			}
		}
		
		if (globalmin > sum)
		{
			globalmin = sum;

		}
	}
	else
	{
		for (i = start; i < end; i++)
		{
			swapfunction(&(vec[start]), &(vec[i]));
			calculatepermutations(vec, start+1, end,graph);
			swapfunction(&(vec[start]), &(vec[i]));
		}
	}
}


int main(int argc, char* argv[])
{
	cout << argc<<endl;
	createGraph(argc,argv);
	system("pause");
    return 0;
}

