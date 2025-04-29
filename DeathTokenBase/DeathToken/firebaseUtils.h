#pragma once
#include "firebase/app.h"
#include "firebase/database.h"
class FirebaseUtils
{
private:

	

public:
	static int currentId;
	static std::string name;
	static int chips;
	static int souls;
	static void StartFirebase();
	static void DeleteFirebaseUtils();
	static void RegisterUser(std::string name);
	void GuardarProgreso(int chipsN, int soulsN);
};

