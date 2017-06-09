//SO2 IS1 210B LAB01
//Patryk Pazura
//ppazura@wi.zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <pwd.h>
#include <grp.h>
#include <stdbool.h>
int main(int argc, char **argv) {
setutent();
bool exist = false;
int j, ngroups = 1;
gid_t *groups;
struct passwd *p;
struct utmp *u;
struct group *g, *pw;
int ret;
groups = malloc(ngroups*sizeof(gid_t));
while((ret=getopt(argc, argv, "in")) != -1)
{
	switch(ret)
	{
	case 'i':
		exist = true;
		while((u = getutent()) != NULL)
	 	{
			if(u->ut_type == USER_PROCESS)
			{
			p = getpwnam(u->ut_user);
			printf("%d ", p->pw_uid);
			printf("%s \n", u->ut_user);

			}
		}
		break;
	case 'n':
		exist = true;
		while((u = getutent()) != NULL)
		{
		if(u->ut_type == USER_PROCESS)
			{
			p = getpwnam(u->ut_user);
			printf("%s ", u->ut_user);
			//printf("%d  ", p->pw_gid);
			//printf("%d ", p->pw_uid);
			if(getgrouplist(u->ut_user,p->pw_gid,groups,&ngroups) == -1)
			{
			free(groups);
			groups = malloc(ngroups*sizeof(gid_t));
			getgrouplist(u->ut_user,p->pw_gid,groups,&ngroups);
			}
			for(j=0;j<ngroups;j++)
			{
			g = getgrgid(groups[j]);
			printf("%s ", g->gr_name);
			}
			printf("\n");
			}
			}

		break;
		}
	}
		if(exist == false)
			while((u = getutent()) != NULL)
			{
			if(u->ut_type == USER_PROCESS) 
			{
			printf("%s\n",u->ut_user);
			}
			}
	
	
		
endutent();
return 0;
}
