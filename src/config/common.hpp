#pragma once

#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include "TokenType.hpp"
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#define USGERR 64

void fatal(const std::string& msg, int exit_status);

#endif
