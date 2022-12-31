﻿#include "Manager.h"

Manager::Manager()
{
	getNumOfRoadsAndActions();
	_roads = new Road[_numOfRoads];
	_heapArray = new pair<float, int>[_numOfRoads];
}

void Manager::Run()
{

	for (int i = 0; i < _numOfActions; i++)
	{
		char action;
		int res;
		float bridgeHeight = 0;
		int road = 0;
		float truckHeight = 0;

		cin >> action;
		getParameters(action, &bridgeHeight, &road, &truckHeight);


		switch (action)
		{
		case 'a':
			Init();
			break;
		case 'b':
			AddBridge(bridgeHeight, road);
			break;
		case 'c':
			res = WhichRoad(truckHeight);
			cout << "Heighest road the truck can go under is road index: " << res << endl << endl;
			break;
		case 'd':
			Print(road);
			break;
		default:
			break;
		}
	}
}

void Manager::Init()
{
	for (int i = 0; i < _numOfRoads; i++)
	{
		_heapArray[i].first = 100;	// key 
		_heapArray[i].second = i;	// value

		_roads[i].getList()->setHead(NULL);
		_roads[i].setMaxHeapIndex(i);
	}
}

void Manager::AddBridge(float bridgeHeight, int roadIndex)
{
	MaxHeap Heap(_heapArray, _numOfRoads, _roads);

	_roads[roadIndex - 1].getList()->insertAtBeginning(bridgeHeight);

	int index = _roads[roadIndex - 1].getMaxHeapIndex();

	if (bridgeHeight < _heapArray[index].first)
	{
		_heapArray[index].first = bridgeHeight;
		Heap.FixHeap(index, _roads);
	}

	cout << "_heapArray: ";
	for (int i = 0; i < 5; i++)
		cout << " " << _heapArray[i].first;

	cout << endl;
}


int Manager::WhichRoad(float truckHeight)
{
	int max = _heapArray[0].first;

	if (truckHeight < max)
		return _heapArray[0].second + 1;
	else return 0;
}


void Manager::Print(int road)
{
	_roads[road - 1].getList()->printList();
}




void Manager::getNumOfRoadsAndActions()
{
	cin >> _numOfRoads;
	cin >> _numOfActions;
}

void Manager::getParameters(char action, float* bridgeHeight, int* road, float* truckHeight)
{
	switch (action)
	{
	case 'b':
		cin >> *bridgeHeight;
		cin >> *road;
		break;
	case 'c':
		cin >> *truckHeight;
		break;
	case 'd':
		cin >> *road;
		break;
	default:
		break;
	}
}