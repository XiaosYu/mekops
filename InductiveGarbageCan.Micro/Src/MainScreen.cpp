/*
 * MainScreen.h
 *
 *  Created on: Mar 29, 2024
 *      Author: 纸鸢
 */

#include <MainScreen.h>



void MainScreen::DisplayOverTimeView()
{
	this->DisplayText("The cans is overtime,please put the garbage on the sensor");
}


void MainScreen::DisplayText(std::string text)
{
	this->Clear();
	this->PrintText(0, 0, text);
	this->Invoke();
}

