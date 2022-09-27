#include <stdio.h>
#include <shadow.h>
#include <pwd.h>
#include <unistd.h>
#define _XOPEN_SOURCE
#include <crypt.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char *password; // password trong file shadow
    char *encrypted;
    char mkm[100];
    int len = 0;
        
    password = (char *) malloc(100 * sizeof(char));
    encrypted = (char *) malloc(100 * sizeof(char));

    struct passwd *pw;
    struct spwd *spwd;
        
    // tim username hien tai
    uid_t uid = getuid();
    pw = getpwuid(uid);
    // lay mat khau cua username trong file shadow
    spwd = getspnam(pw->pw_name);

    if(spwd == NULL)
        printf("Loi spwd\n");
        
    char *mkc;
    mkc = (char *) malloc(100 * sizeof(char));
        
    printf("Nhap mat khau cu: \n");
    scanf("%s",mkc);
    //hash mat khau nhap vao voi salt 
    encrypted = crypt(mkc,spwd->sp_pwdp);
    if  (!strcmp(spwd->sp_pwdp, encrypted))
    {
	    printf("Nhap mat khau moi: ");
        scanf("%s", mkm);
        FILE *fps;
        if(!(fps = fopen("/etc/shadow", "r+")))
            printf("Mo file loi\n");
        char *new = crypt(mkm, spwd->sp_pwdp);
        spwd->sp_pwdp = new;
        putspent(spwd, fps);
        fclose(fps);
    }
    else
        printf("Mat khau sai");        
    return 0;
}


