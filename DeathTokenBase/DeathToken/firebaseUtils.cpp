#include "FirebaseUtils.h"
#include <SDL_timer.h>
#include "PlayerEconomy.h"
static firebase::App* app;
static firebase::database::Database* db;
static firebase::database::DatabaseReference dbref;

int FirebaseUtils::currentId = -1;
std::string FirebaseUtils::name = "";
long long FirebaseUtils::chips = 0;
long long FirebaseUtils::souls = 0;
int FirebaseUtils::insanity = 0;

void FirebaseUtils::StartFirebase()
{
	//leer usuarios y ponerlos en una tabla
	firebase::AppOptions options; 

	options.set_api_key("AIzaSyBTKNWi5Tjs-TfjGKrIxzH8M6zL_xljtKY");
	options.set_app_id("1:136166131440:web:2308c20429e96e49c76435");
	options.set_project_id("deathtoken");
	options.set_database_url("https://deathtoken-default-rtdb.firebaseio.com");

	app = firebase::App::Create(options);
	if (app == nullptr) { return ; }

	db = firebase::database::Database::GetInstance(app);
	dbref = db->GetReference();
}

void FirebaseUtils::DeleteFirebaseUtils()
{

	if (db != nullptr) {
		delete db;
    }

    if (app != nullptr) {
		delete app;
	}
}

void FirebaseUtils::RegisterUser(std::string name)
{
	//Hago esto porque si se borra un usuario desde firebase, desde el vs lo guarda en cache o 
	/*if (db != nullptr) {
		db->GoOffline();
		SDL_Delay(5000);
		db->GoOnline();
	}*/
	//referencia a la tabla "usuarios"
	firebase::database::DatabaseReference usuariosRef = dbref.Child("usuarios");

	//se guarda toda la informacion que tiene esa tabla
	firebase::Future<firebase::database::DataSnapshot> future = usuariosRef.GetValue();
	//se espera a que se carge todo en future
	while (future.status() == firebase::kFutureStatusPending) {
		SDL_Delay(10);
	}

	//todos los resultado se guardan en una captura
	const firebase::database::DataSnapshot& snapshot = *future.result();
	

	currentId = -1;
	//Buscar que el usuario ya existe
	for (const auto& child : snapshot.children()) {
		auto data = child.value().map();
		std::string nomrbeeq = data["nombre"].string_value();
		if (nomrbeeq == name) {
			currentId = std::stoi(child.key());
			chips = data["fichas"].int64_value();
			if (chips == 0) {
				chips = 2000;
			}
			souls = data["almas"].int64_value();
			insanity = data["locura"].int64_value();
			return;
		}
	}
	
	//recorre todos los id para luego asignar id+1 al usuario nuevo
	int idLibre = 0;
	bool idEncontrado = false;

	while (!idEncontrado) {
		idEncontrado = true;
		for (const auto& child : snapshot.children()) {
			int idExistente = std::stoi(child.key());
			if (idExistente == idLibre) {
				idLibre++;
				idEncontrado = false;
				break;
			}
		}
	}
	currentId = idLibre;
	chips = 2000;
	souls = 0;
	insanity = 0;

	//Mapa con los datos del usuario
	firebase::Variant usuario = firebase::Variant::EmptyMap();
	usuario.map()["nombre"] = name;
	usuario.map()["fichas"] = chips;
	usuario.map()["almas"] = souls;
	usuario.map()["locura"] = insanity;

	//añadir datos a la base de datos
	firebase::Future<void> result = dbref.Child("usuarios").Child(std::to_string(currentId)).SetValue(usuario);
	while (result.status() == firebase::kFutureStatusPending) {
		SDL_Delay(10);
	}
	PlayerEconomy::setBlueSouls(chips);
	PlayerEconomy::setRedSouls(souls);
	PlayerEconomy::setInsanity(insanity);
}

void FirebaseUtils::SaveState(int chipsN, int soulsN, int insanityN)
{
	firebase::Variant usuarioU = firebase::Variant::EmptyMap();
	usuarioU.map()["fichas"] = chipsN;
	usuarioU.map()["almas"] = soulsN;
	usuarioU.map()["locura"] = insanityN;

	firebase::Future<void> result = dbref.Child("usuarios").Child(std::to_string(currentId)).UpdateChildren(usuarioU);
	while (result.status() == firebase::kFutureStatusPending) {
		SDL_Delay(10);
	}
}

std::vector<FirebaseUtils::userData> FirebaseUtils::getRanking()
{
	std::vector<userData> ranking;

	firebase::database::DatabaseReference usuariosRef = dbref.Child("usuarios");
	firebase::Future<firebase::database::DataSnapshot> future = usuariosRef.GetValue();
	while (future.status() == firebase::kFutureStatusPending) {
		SDL_Delay(10);
	}

	const firebase::database::DataSnapshot& snapshot = *future.result();

	//recorre cada hijo de la captura(osea cada id)
	for (const auto& child : snapshot.children()) {
		auto usuarioR = child.value().map();
		userData nuevo;
		nuevo.nombre = usuarioR["nombre"].string_value();
		nuevo.fichas = usuarioR["fichas"].int64_value();
		nuevo.almas = usuarioR["almas"].int64_value();

		std::vector<userData> vectorPrueba;
		bool insertado = false;

		// recorre el vector ranking y pone en orden dependiendo del numero de almas
		for (int i = 0; i < ranking.size(); ++i) {
			if (!insertado && nuevo.fichas > ranking[i].fichas) {
				vectorPrueba.push_back(nuevo);
				insertado = true;
			}
			vectorPrueba.push_back(ranking[i]);
		}

		if (!insertado) {
			vectorPrueba.push_back(nuevo);
		}

		ranking = vectorPrueba;
	}
	

	return ranking;

}

void FirebaseUtils::CleanFirebase()
{
	if (db == nullptr) return;

	firebase::database::DatabaseReference usuariosRef = dbref.Child("usuarios");
	firebase::Future<firebase::database::DataSnapshot> future = usuariosRef.GetValue();

	while (future.status() == firebase::kFutureStatusPending) {
		SDL_Delay(10);
	}

	const firebase::database::DataSnapshot& snapshot = *future.result();

	for (const auto& child : snapshot.children()) {
		std::string key = child.key();
		auto datos = child.value().map();

		bool nombreB = datos["nombre"].is_string();
		bool fichasB = datos["fichas"].is_int64();
		bool almasB = datos["almas"].is_int64();
		bool locuraB = datos["locura"].is_int64();

		if (!(nombreB && fichasB && almasB && locuraB)) {
			dbref.Child("usuarios").Child(key).RemoveValue();
		}
	}
}


