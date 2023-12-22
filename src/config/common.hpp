#pragma once

#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <vector>
#include <cstdarg>
#include <cstdlib>
#include <exception>
#include <set>
#include "TokenType.hpp"

#define USGERR 64

void    fatal(const std::string& msg, int exit_status);

#endif
