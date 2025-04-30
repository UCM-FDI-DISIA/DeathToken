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
	static long long chips;
	static long long souls;
	static bool insanity;
	static void StartFirebase();
	static void DeleteFirebaseUtils();
	static void RegisterUser(std::string name);
	static void SaveState(int chipsN, int soulsN);
	static std::vector<userData> getRanking();
};

