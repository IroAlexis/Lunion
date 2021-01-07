#ifndef __LUNION_WINE__
#define __LUNION_WINE__

#include "../utils/system.h"


/** ----------------------------
 * Variable d'environnement Wine
 * -----------------------------
 **/
#define WINEPREFIX "WINEPREFIX"
#define WINEDLL    "WINEDLLOVERRIDES"
#define WINEESYNC  "WINEESYNC"
#define WINEFSYNC  "WINEFSYNC"
#define WINEDEBUG  "WINEDEBUG"


/** ---------------------------------------------------
 * Variable globale pour gerer la base de registre Wine
 * _____________________________________
 * Fichier commun de la base de registre
 * -------------------------------------
 * ----------------------------------------------------
 **/
#define SYSTEMREG "system.reg"
#define USERREG   "user.reg"

/** _____________________________
 * Section de la base de registre
 * ------------------------------
 **/
#define REGDLLS   "[Software\\\\Wine\\\\DllOverrides]"




typedef struct _wine_
{
	/// TODO Donnees du jeu ? GAME* gm; ?
	int   dx;     /// @brief Indique la version DirectX utilisee
	int   vk;     /// @brief Utilisation de l'API Vulkan
	char* prefix; /// @brief Prefix Wine
	int   sys;    /// @brief Utilise le paquet Wine (1) ou telecharge Wine TkG (0)
	char* dir;    /// @brief Chemin du paquet Wine si sys = 0
	ENV*  env;    /// @brief Ensemble des variables d'environnement utiles
} WINE;




/**
 * @brief Ajoute une dll au prefix Wine
 * @param this Objet Wine
 * @param dll  Nom de la dll
 * @param load Type de chargement de la dll
 **/
int wine_dll_add (WINE* this, const char* dll, const char* load);


/**
 * @brief Ajoute une variable dans la base de registre Wine
 **/
int wine_regvar_add (WINE* this, const char* regdir, const char* name, const char* value, const char* type);


/**
 * @brief  Ajoute une variable d'environnement dans l'objet WINE
 * @param  name  Name de la variable d'environnement
 * @param  value Valeur de la variable d'environnement
 * @param  env   Environnement de l'objet WINE
 * @return true si la variable d'environnement a ete ajoute et false sinon
 **/
int add_varenvwine (WINE* this, const char* name, const char* value);


/**
 * @brief  Controle la presence de la variable d'environnement
 * @param  env  Environnement d'un objet WINE alloue
 * @param  name Nom de la variable dont la presence est a verifier
 * @return -1  si l'environnement est vide
 *          0  si la variable n'a pas ete trouve
 *         >=0 la place de la variable dans le tableau
 **/
int control_varenvwine (const WINE* this, const char* name);


/**
 * @brief Detruit les informations du runner Wine
 * @param this Objet Wine a detruire
 **/
void destroy_wine (WINE* this);


/**
 * @brief Affiche le contenu du runner Wine en parametre
 * @param this Objet Wine
 **/ 
void display_wine (const WINE* this);


/**
 * @brief Affiche le contenu du runner Wine en parametre pour du debug
 * @param this Objet Wine
 **/ 
void display_wine_debug (const WINE* this);


/**
 * @brief  Initialise le runner Wine pour un jeu
 * @param vk     Activiation de Vulkan
 * @param prefix Prefixe Wine
 * @param sys    Pour savoir si utilise le paquet Wine
 * @param dir    Chemin de Wine (si sys = 0)
 * @return Objet alloue, NULL sinon
 **/
WINE* wine_new (const int sys, const int dx, const int vk, const char* prefix, const char* dir);


/**
 * @brief Installation du prefix Wine (wineboot)
 * @param
 * @return 0 si tout se passe bien
 *         1 si le prefix n'est pas alloue ou non present
 *         2 si 
 **/
int install_wineprefix (WINE* this);


#endif

