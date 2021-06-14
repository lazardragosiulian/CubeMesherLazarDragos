// CubeMesher.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include "Mesh.h"
#include "Cube.h"


// Exercise: fill in the method CreateMesh.
// This method must mesh a cube. There are a couple rules underlying the meshing:
// - You may only use shell elements with a connectivity of 4 (QUAD element)
// - Only the outside of the cube has to be meshed. There may not be any interior nodes or elements
// - Of course, nodes have to be shared when needed, also on the corners and edges of the cube
// - Specifying 1000 nodes in x,y and z direction, should execute within a 10 seconds on a 2GHZ computer in optimized compilation
// Additionally, there are some rules to follow:
// - You may not modify the code in Mesh.h , Mesh.cpp, Cube.h and Cube.cpp
// - It is allowed to add new files
// - The _tmain method should stay like it is, except that you may change the parameters for the cube and the mesh for experimentation purposes
// This method takes a input:
//  - a Cube with certain dimensions
//  - the number of nodes to create in x/y/z direction
//  - An object that represents the mesh
// You have to call methods on the ioMesh object, such that the ioMesh is a correct representation
// of the meshed cube. Please see the header file of the mesh to see which methods it supports and how 
// the nodes and elements are represented in the mesh.
void CreateMesh(const Cube& iCube, int iNbrNodesX, int iNbrNodesY, int iNbrNodesZ, Mesh& ioMesh)
{
    ioMesh.SetNumberNodes (iNbrNodesX * iNbrNodesY * iNbrNodesZ - ((iNbrNodesX-2)*(iNbrNodesY-2)*(iNbrNodesZ-2)));
    ioMesh.SetNumberQUADs((iNbrNodesX-1)*(iNbrNodesY-1)*6);
  
    //calculates the distance between nodes for each direction
    double sizeX = iCube.GetX() / (iNbrNodesX - 1);
    double sizeY = iCube.GetY() / (iNbrNodesY - 1);
    double sizeZ = iCube.GetZ() / (iNbrNodesZ - 1);

    std::cout << "The distance between two nodes is = " << sizeX << std::endl;
    int index = 0;
    int indexQ = 0;

    //generates the nodes and the QUADs

    //face1 of the cube
    for (int indexX = 0; indexX < iNbrNodesX; indexX++)
        for (int indexY = 0; indexY < iNbrNodesY; indexY++)
        {
                ioMesh.SetNode(index, indexX * sizeX, indexY * sizeY, 0.0);
                
                if (indexX < (iNbrNodesX - 1) && indexY < (iNbrNodesY - 1))
                {
                    ioMesh.SetQUAD(indexQ, index, index + 1, index + iNbrNodesX, index + iNbrNodesX + 1);
                    indexQ++;
                }
                index++;   
        }
    
    //face 2 of the cube
    for (int indexY = 0; indexY < iNbrNodesY; indexY++)
        for (int indexZ = 1; indexZ < iNbrNodesZ; indexZ++)
        {
                
                ioMesh.SetNode(index, 0.0, indexY * sizeY, indexZ * sizeZ);
                if (indexY < (iNbrNodesY - 1) && indexZ < (iNbrNodesZ - 1))
                {
                    ioMesh.SetQUAD(indexQ, index, index + 1, index + iNbrNodesX, index + iNbrNodesX + 1);
                    indexQ++;
                }
                index++;
        }

    //face 3 of the cube
    for (int indexX = 1; indexX < iNbrNodesX; indexX++)
        for (int indexZ = 1; indexZ < iNbrNodesZ; indexZ++)
        {          
                ioMesh.SetNode(index, indexX * sizeX, 0.0, indexZ * sizeZ);
                if (indexX < (iNbrNodesX - 1) && indexZ < (iNbrNodesZ - 1))
                {
                    ioMesh.SetQUAD(indexQ, index, index + 1, index + iNbrNodesX, index + iNbrNodesX + 1);
                    indexQ++;
                }
                index++;           
        }

    //face 4 of the cube
    for (int indexX = 1; indexX < iNbrNodesX; indexX++)
        for (int indexY = 1; indexY < iNbrNodesY; indexY++)
        {
            ioMesh.SetNode(index, indexX * sizeX, indexY * sizeY, iCube.GetZ());
            if (indexX < (iNbrNodesX - 1) && indexY < (iNbrNodesY - 1))
            {
                ioMesh.SetQUAD(indexQ, index, index + 1, index + iNbrNodesX, index + iNbrNodesX + 1);
                indexQ++;
            }
            index++;
        }

    //face 5 of the cube
    for (int indexY = 1; indexY < iNbrNodesY; indexY++)
        for (int indexZ = 1; indexZ < (iNbrNodesZ - 1); indexZ++)
        {
            ioMesh.SetNode(index, iCube.GetX(), indexY * sizeY, indexZ * sizeZ);
            if (indexY < (iNbrNodesY - 1) && indexZ < (iNbrNodesZ - 1))
            {
                ioMesh.SetQUAD(indexQ, index, index + 1, index + iNbrNodesX, index + iNbrNodesX + 1);
                indexQ++;
            }
            index++;
        }

    //face 6 of the cube
    for (int indexX = 1; indexX < (iNbrNodesX - 1); indexX++)
        for (int indexZ = 1; indexZ < (iNbrNodesZ - 1); indexZ++)
        {
            ioMesh.SetNode(index, indexX * sizeX, iCube.GetY(), indexZ * sizeZ);
            if (indexX < (iNbrNodesX - 1) && indexZ < (iNbrNodesZ - 1) && index < ioMesh.GetNumberNodes() - iNbrNodesX)
            {
                ioMesh.SetQUAD(indexQ, index, index + 1, index + iNbrNodesX, index + iNbrNodesX + 1);
                indexQ++;
            }
            index++;
        }

}

int _tmain(int argc, _TCHAR* argv[])
{
    // This represents the design of a cube with dimensions 1x1x1 meter
    Cube lCube (3, 3, 3); 

    // This object will hold the mesh
    Mesh lMesh; 

    // Create the mesh
    CreateMesh(lCube, 4, 4, 4, lMesh);

    // Print the Mesh
    // The output of the Print method will be limited to 100 elements and 100 nodes, because
    // otherwise it might take an hour before the output is printed
    lMesh.Print();

	return 0;
}


