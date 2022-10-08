#ifndef PARENT_H
#define PARENT_H

#include <vector>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <stdio.h>

int ParentRoutine(std::ifstream& s, char* PathToChild);

#endif