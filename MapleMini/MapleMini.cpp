// MapleMini.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MapleMini.h"


int main(signed int argc, char* argv[])
{
	rang::setControlMode(rang::control::Auto);
	SetConsoleTitleA("MapleSeed Command Line");

	//TitleInfo::CreateDatabase();
	Decrypt((char*)argv[0]);
    return Decrypt::ret;
}

