#include <stdio.h>
#include <pwd.h>
#include <grp.h>

int main()
{
	gid_t groups[100];
	char name[100];
	int ngroups = 0;
	
	struct passwd *pwd;
	struct group *grp;
	
	printf("Nhap username: ");
	scanf("%s", name);
	pwd = getpwnam(name);
	
	if(pwd != NULL)
	{
		printf("Id: %d\n", pwd->pw_uid);
		printf("Username: %s\n", pwd->pw_name);
		printf("Thu muc home: %s\n", pwd->pw_dir);
		printf("Cac group cua user: ");
		
		getgrouplist(name, pwd->pw_gid, NULL, &ngroups); //lay gia tri cua ngroups
		getgrouplist(name, pwd->pw_gid, groups, &ngroups);
		
		for (int i = 0; i < ngroups; i++)
		{
			grp = getgrgid(groups[i]);
			if (grp != NULL)
			{
				printf("%s\n",grp->gr_name);
			}
		}
	}
	else
	{
		printf("Khong tim thay");
	}
	
}
