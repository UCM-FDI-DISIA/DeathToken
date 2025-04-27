#pragma once
#include "firebase/app.h"
#include "firebase/database.h"
class FirebaseUtils
{
private:
	struct Usuario {
		std::string name;
		int chips;
		int souls;
	};

public:
	static void StartFirebase();
	static void DeleteFirebaseUtils();
	static void RegisterUser(std::string name,int chips, int souls);
};

