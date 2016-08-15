/*
 * main.cpp
 *
 *  Created on: Jul 21, 2015
 *      Author: root
 */

#include "inifile.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;
int LoadDaConfig() //loadTcpInifile()
{
	char g_inifile[512];
	strcpy(g_inifile, "./CfgFile/Mode.ini");
	int mode = 0;
	time_t lt;
	time(&lt);

#if 0
	//daserver port
	read_profile_string("MODE","GPSMODE",temp,sizeof(temp),"./",g_inifile);
	if(strlen(temp) > 0 )
	{
		cout << "GPSMODE:" << temp << endl;

	} else {

		perror("read GPSMODE error \n");
		return -1;
	}
#endif
	mode = read_profile_int("MODE", "GPSMODE", 0, g_inifile);

	if (!mode) {

		perror("load mode error\n");
		return -1;
	}

	return mode;

}

int main() {

	int mode;
	mode = LoadDaConfig();

	cout << mode <<endl;

}
