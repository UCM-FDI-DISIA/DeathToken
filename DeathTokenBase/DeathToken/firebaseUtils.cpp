#include "FirebaseUtils.h"
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

