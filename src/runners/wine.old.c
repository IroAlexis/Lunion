#include "wine.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>




int add_winedll (WINE* this, const char* dll, const char* load)
{
	char* path  = NULL;
	FILE* reg   = NULL;
	
	/**---------------------------------------------------------------------
	 * Concatene pour avoir le chemin du fichier de la base de registre Wine
	 *----------------------------------------------------------------------
	 **/
	path = strdup (this->prefix);
	if (NULL == path)
	{
		fprintf (stderr, "::ERROR (wine.add_winedll):: Probleme de copie \"%s\"\n", this->prefix);
		return EXIT_FAILURE;
	}
	
	path = (char*) realloc (path, (strlen(path) + strlen(USERREG) + 1) * sizeof (char));
	path = strcat (path, USERREG);
	
	
	
	/**---------------------------------------------
	 * Ouverture du fichier de base de registre Wine
	 *----------------------------------------------
	 **/
	reg = fopen (path, "a+");
	if (NULL == reg)
	{
		fprintf (stderr, "::ERROR (wine.wine_dll_add):: Ouverture impossible de \"%s\"\n", path);
		fprintf (stderr, "  -> \"%s\"\n", path);
		return EXIT_FAILURE;
	}
	//fprintf (stderr, "::DEBUG (wine.wine_dll_add):: Ouverture reussi de %s\n", path);
	
	
	
	/**----------------------------------------------------------
	 * Ecriture des dlls dans le fichier de base de registre Wine
	 *-----------------------------------------------------------
	 **/
	fprintf (reg, "\n%s\n\"%s\"=\"%s\"\n", REGDLLS, dll, load);
	
	fclose (reg);
	free (path);
	
	return EXIT_SUCCESS;
}




// TODO En cours de reflexion
int add_wineregvar (WINE* this, const char* regdir, const char* name, const char* value, const char* type)
{
	return EXIT_SUCCESS;
}




int add_varenvwine (WINE* this, const char* name, const char* value)
{
	assert (name  != NULL);
	assert (value != NULL);
	assert (this  != NULL);
	
	if (add_varenv (this->env, name, value) == EXIT_FAILURE)
	{
		fprintf (stderr, "::WARNING (wine.add_varenvwine):: Ajout impossible\n");
		fprintf (stderr, "  -> name: %s, value: %s\n", name, value);
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}




int config_winekeyboard (const WINE* this, const char* lang)
{
	return EXIT_FAILURE;
}




int control_varenvwine (const WINE* this, const char* name)
{
	assert (this != NULL);
	assert (name != NULL);
	
	if (search_varenv (this->env, name) == EXIT_FAILURE)
	{
		fprintf (stderr, ":: WARNING (wine.search_varenvwine):: Pas de presence de \"%s\"\n", name);
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}




void destroy_wine (WINE* this)
{
	assert (this != NULL);
	
	this->sys = -1;
	this->vk  =  0;
	destroy_env (this->env);
	free (this->prefix);
	free (this->dir);
	
	free (this);
}




void display_wine (const WINE* this)
{
	assert (this != NULL);
	
	fprintf (stdout, "::INFO:: Affichage de la configuration de Lunion Play\n");
	
	fprintf (stdout, "  -> DirectX %d\n", this->dx);
	
	if (this->vk == 1)
	{
		switch (this->dx)
		{
		case 9:
		case 10:
		case 11:
			fprintf (stdout, "  -> Utilisation de Vulkan - DXVK\n");
			break;
		case 12:
			fprintf (stdout, "  -> Utilisation de Vulkan - VKD3D\n");
			break;
		}
	}
	
	fprintf (stdout, "  -> Prefixe Wine: \"%s\"\n", this->prefix);
	
	switch (this->sys)
	{
		case 1:
			fprintf (stdout, "  -> Utilisation du paquet Wine\n");
			break;
		case 0:
			if (this->dir == NULL)
				fprintf (stdout, "  -> (ATTENTION: Pas de chemin Wine)\n");
			fprintf (stdout, "  -> Dossier Wine: \"%s\"\n", this->dir);
			break;
	}
	
	display_env (this->env);
}




void display_wine_debug (const WINE* this)
{
	assert (this != NULL);
	
	fprintf (stdout, "::DEBUG:: WINE\n");
	fprintf (stdout, "  -> vk: %d\n", this->vk);
	fprintf (stdout, "  -> sys: %d\n", this->sys);
	fprintf (stdout, "  -> prefix: %s\n", this->prefix);
	fprintf (stdout, "  -> dir: %s\n", this->dir);
	display_env_debug (this->env);
}




WINE* wine_new (const int dx, const int vk, const int sys, const char* prefix, const char* dir)
{
	assert (dx  >= 8 && dx  <= 12);
	assert (vk  >= 0 && vk  <= 1);
	assert (sys >= 0 && sys <= 1);
	assert (prefix != NULL);
	
	WINE* tmp = NULL;
	
	/**------------------------------
	 * Initialisation du pointeur tmp
	 *-------------------------------
	 **/
	tmp = (WINE*) calloc (1, sizeof (WINE));
	if (NULL == tmp)
	{
		fprintf (stderr, "::ERROR (wine.wine_new):: Allocation impossible\n");
		return NULL;
	}
	
	
	/**-------------------------------------
	 * Initialisation du pointeur env de tmp
	 *--------------------------------------
	 **/
	tmp->env = init_env ();
	if (NULL == tmp->env)
	{
		free(tmp);
		return NULL;
	}
	
	
	/**-----------------------------------
	 * Copie des données dans l'objet cree
	 *------------------------------------
	 **/
	tmp->dx = dx;
	tmp->vk = vk;
	tmp->sys = sys;
	
	
	/**------------------------------------------------
	 * Copie des chaines de caractere dans l'objet cree
	 *-------------------------------------------------
	 **/
	tmp->prefix = strdup (prefix);
	if (NULL == tmp->prefix)
	{
		fprintf (stderr, "::ERROR (wine.wine_new):: Probleme de copie \"%s\"\n", prefix);
		free (tmp->env);
		free (tmp);
		
		return NULL;
	}
	
	if (sys == 0 && dir != NULL)
	{
		tmp->dir = strdup (dir);
		if (NULL == tmp->dir)
		{
			fprintf (stderr, "::ERROR (wine.wine_new):: Probleme de copie \"%s\"\n", dir);
			free (tmp->prefix);
			free (tmp->env);
			free (tmp);
			
			return NULL;
		}
	}
	
	
	
	return tmp;
}




int install_wineprefix (WINE* this)
{
	assert (this != NULL);
	
	/**-------------------------------------------
	 * Verification au moins les prerequis remplis
	 *--------------------------------------------
	 **/
	if (NULL == this->prefix)
	{
		fprintf (stderr, "::ERROR (wine.install_wineprefix):: Pas de chemin precise\n");
		return 1;
	}
	
	/**-------------------------------------------------------------------
	 * Empeche la demande d'installation de Mono & Gecko (si pas installe)
	 *--------------------------------------------------------------------
	 **/
	add_varenvwine (this, WINEDLL, "\"mscoree,mshtml=d\"");
	
	/**----------------------------------------------------------
	 * Lancement de exec dans un thread/fork et attente de la fin
	 *-----------------------------------------------------------
	 **/
	
	/**---------------------------------------------------------------------
	 * Capturer le retour du thread ou de la commande exec
	 * 
	 * Attente tant que le prefix n'a pas ete creee (ecriture sur le disque)
	 *----------------------------------------------------------------------
	 **/
	
	
	
	
	return EXIT_SUCCESS;
}




int main ()
{
	WINE* run = NULL;
	
	run = wine_new (12, 1, 1, "/home/iroalexis/Games/uplay/windata/", NULL);
	if (NULL == run)
		return EXIT_FAILURE;
	
	add_winedll (run, "mscvp140", "native");
	display_wine (run);
	
	destroy_wine (run);
	fprintf (stdout, "%d\n", EXIT_SUCCESS);
	
	return EXIT_SUCCESS;
}

