/*
 * MainScreen.h
 *
 *  Created on: Mar 29, 2024
 *      Author: 纸鸢
 */

#ifndef INC_MAINSCREEN_H_
#define INC_MAINSCREEN_H_

#include <Screen.h>
#include <cstring>

class MainScreen: public Screen {
public:
	void DisplayOverfilledView();
	void DisplayOverTimeView();
	void DisplayText(std::string text);
};

#endif /* INC_MAINSCREEN_H_ */
