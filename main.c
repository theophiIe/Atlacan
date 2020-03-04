/******************************************************************************/
/*********** PROJET FAIT PAR : VINCENT XAVIER ET THEOPHILE MOLINATTI********** /
/******************************************************************************/
/************************ TD4 salle : JUNGLE DESCARTES ************************/
/******************************************************************************/

#include "atlacan.h"
#include <stdio.h>

void recherche_atlacan()
{
	//initialisation des varibles
	struct atl_stat as;
	char **path = NULL;
	int num_entry, data;
	
	atl_ls(&path,&num_entry);
	
	printf("lieu actuel : %s\n",atl_getpwd());
	
	for(int cmpt = 0; cmpt < num_entry; cmpt++)
	{
		atl_stat(path[cmpt], &as);
		
		//Affichage des caractérisques des éléments
		printf("choix : %s ", path[cmpt]);
		printf( (atl_is_dir(as.mode)) ? "est un chemin" : "");
		printf( (atl_is_file(as.mode)) ? "est un lieu" : "");
		printf( (atl_is_link(as.mode)) ? "est un piège" : "");
		printf("  |  uid = %d  |  gid = %d  |  taille : %d", as.uid, as.gid, as.size);
		printf("\n");
		
		//Teste si c'est un répertoire qui appartient au groupe ABITHAN ou EXPLORERS
		if(atl_is_dir(as.mode) && (as.gid == GID_ABITHAN || as.gid == GID_EXPLORERS))
		{
			printf("on rentre dans le chemin : %s  |  uid = %d  |  gid = %d\n\n", path[cmpt], as.uid, as.gid);
			atl_cd(path[cmpt]);
			recherche_atlacan();	//La fonction s'appelle elle-même, mais agit depuis un répertoir différent --> raisonnement récursif
		}
		
		//Teste si c'est un fichier et que sa taille est supérieur à un million
		else if(!atl_is_link(as.mode) && atl_is_file(as.mode) && as.size > 1000000)
		{
			printf("lecture du fichier : %s\n\n" ,path[cmpt]);
			atl_cat(path[cmpt], &data);			
		}
	}
	
	printf("cd..\n");
	atl_cd("..");
}

int main(int argc, char **argv) 
{
	printf("\n\n");	//Pour plus de visibilité
	atl_init();	
	recherche_atlacan();
	atl_fini();
	
	return 0;
}
