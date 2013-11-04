#pragma once
#include "c_Globals.h"
#include "c_House1.h"
#include "c_House2.h"
#include "c_Store.h"
#include "c_Store_Extension.h"
#include "c_Manor.h"
#include "c_Manor_2F.h"
#include "c_gameOver.h"
#include "c_imgFunctions.h"
#include "c_States.h"

void initialize();
bool loadFiles();
void cleanUp();
void changeState();
