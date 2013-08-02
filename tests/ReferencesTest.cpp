/**
 * Copyright 2013 Felix Schmitt
 *
 * This file is part of libSplash. 
 * 
 * libSplash is free software: you can redistribute it and/or modify 
 * it under the terms of of either the GNU General Public License or 
 * the GNU Lesser General Public License as published by 
 * the Free Software Foundation, either version 3 of the License, or 
 * (at your option) any later version. 
 * libSplash is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License and the GNU Lesser General Public License 
 * for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * and the GNU Lesser General Public License along with libSplash. 
 * If not, see <http://www.gnu.org/licenses/>. 
 */ 
 


#include <time.h>
#include <stdlib.h>

#include "ReferencesTest.h"
#include "SerialDataCollector.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ReferencesTest);

#define HDF5_FILE "h5/testReferences"

using namespace DCollector;

ReferencesTest::ReferencesTest() :
ctInt()
{
    dataCollector = new SerialDataCollector(10);
    srand(time(NULL));
}

ReferencesTest::~ReferencesTest()
{
    if (dataCollector != NULL)
    {
        delete dataCollector;
        dataCollector = NULL;
    }
}

void ReferencesTest::testCreateReference()
{
    Dimensions gridSize(10, 17, 22);
    size_t bufferSize = gridSize[0] * gridSize[1] * gridSize[2];

    // write data to file
    DataCollector::FileCreationAttr fileCAttr;
    DataCollector::initFileCreationAttr(fileCAttr);
    dataCollector->open(HDF5_FILE, fileCAttr);

    int *dataWrite = new int[bufferSize];

    for (uint32_t i = 0; i < bufferSize; i++)
        dataWrite[i] = i;

    dataCollector->write(0, ctInt, 3, gridSize, "data", dataWrite);
    
    dataCollector->createReference(0, "data", ctInt, 0, "ref", 
            Dimensions(5, 10, 10), Dimensions(1, 1, 1), Dimensions(1, 1, 1));
    
    dataCollector->createReference(0, "data", ctInt, 1, "ref2", 
            Dimensions(2, 2, 10), Dimensions(1, 1, 1), Dimensions(2, 1, 1));
    
    delete[] dataWrite;
    dataWrite = NULL;

    dataCollector->close();
    
    CPPUNIT_ASSERT(true);
}