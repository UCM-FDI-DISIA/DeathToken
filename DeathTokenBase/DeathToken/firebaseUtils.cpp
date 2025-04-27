#include "FirebaseUtils.h"
#include <SDL_timer.h>
static firebase::App* app;
static firebase::database::Database* db;
static firebase::database::DatabaseReference dbref;
void FirebaseUtils::StartFirebase()
{
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
        db = nullptr;
    }

    if (app != nullptr) {
        delete app;
        app = nullptr;
    }
}

void FirebaseUtils::RegisterUser(std::string name, int chips, int souls)
{
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
	
	int maxId = 0;

	//recorre todos los id para luego asignar id+1 al usuario nuevo
	for (auto& child : snapshot.children()) {
		int id = (int)child.key();
		if (id > maxId) {
			maxId = id;
		}
	}
	int newId = maxId + 1;

	//Mapa con los datos del usuario
	firebase::Variant usuario = firebase::Variant::EmptyMap();
	usuario.map()["nombre"] = name;
	usuario.map()["fichas"] = chips;
	usuario.map()["almas"] = souls;

	//añadir datos a la base de datos
	dbref.Child("usuarios").Child(std::to_string(newId)).SetValue(usuario);
}


