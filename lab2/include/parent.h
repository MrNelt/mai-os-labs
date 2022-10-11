#ifndef PARENT_H
#define PARENT_H

#include <istream>
#include <vector>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <sys/wait.h>


void ParentRoutine(std::istream& stream, char* PathToChild);

#endif