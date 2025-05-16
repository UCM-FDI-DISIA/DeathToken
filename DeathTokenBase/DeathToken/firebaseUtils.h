#pragma once
#include "firebase/app.h"
#include "firebase/database.h"
class FirebaseUtils
{

public:
	struct userData {
		std::string nombre;
		int fichas;
		int almas;
		int locura;
	};
	static int currentId;
	static std::string name;
	static long long chips;
	static long long souls;
	static int insanity;
	static void StartFirebase();
	static void DeleteFirebaseUtils();
	static void RegisterUser(std::string name);
	static void SaveState(int chipsN, int soulsN, int insanityN);
	static std::vector<userData> getRanking();
	static void CleanFirebase();
private:
	static firebase::App* app;
	static firebase::database::Database* db;
	static firebase::database::DatabaseReference dbref;
	static bool initialized;
};

