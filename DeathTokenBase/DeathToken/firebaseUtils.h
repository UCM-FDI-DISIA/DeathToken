#pragma once
#include "firebase/app.h"
#include "firebase/database.h"
class FirebaseUtils
{
private:
	struct userData {
		std::string nombre;
		int fichas;
		int almas;
	};
public:
	static int currentId;
	static std::string name;
	static int chips;
	static int souls;
	static void StartFirebase();
	static void DeleteFirebaseUtils();
	static void RegisterUser(std::string name);
	void SaveState(int chipsN, int soulsN);
	std::vector<userData> getRanking();
};

