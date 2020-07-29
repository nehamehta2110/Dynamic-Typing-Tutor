#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

void userlogin(void);
char x[100];

struct user{
    char username[10];
    char password[10];
}*pUser;

int main()
{
    userlogin ( );

    return 0;
}

void userlogin(void){
		FILE *out;
		FILE *ot;
    FILE *fp;
    char uName[10], pwd[10];int i;char c;

    pUser=(struct user *)malloc(sizeof(struct user));

    printf("1. Login Through An Existing Account\n2. Create New account\n");
    scanf("%d",& i);
    //system("cls");
    switch(i){
        case 1:

            if ( ( fp=fopen("user.dat", "r+")) == NULL) {
                if ( ( fp=fopen("user.dat", "w+")) == NULL) {
                    printf ("Could not open file\n");
                    exit ( 1);
                }
            }
            printf("Username: ");
            scanf("%9s",uName);
            printf("Password: ");
            scanf("%9s",pwd);
            while ( fread (pUser, sizeof(struct user), 1, fp) == 1) {
                if( strcmp ( pUser->username, uName) == 0) {
                    printf ("Match username\n");
                    if( strcmp ( pUser->password, pwd) == 0) {
                        printf ("Match password\n");
                        //accessUser();
			out = fopen(uName, "w+");
                    }
                }
            }
            break;

        case 2:

            do
            {
                if ( ( fp=fopen("user.dat", "a+")) == NULL) {
                    if ( ( fp=fopen("user.dat", "w+")) == NULL) {
                        printf ("Could not open file\n");
                        exit ( 1);
                    }
                }
                printf("Choose A Username: ");
                scanf("%9s",pUser->username);
                printf("Choose A Password: ");
                scanf("%9s",pUser->password);
                fwrite (pUser, sizeof(struct user), 1, fp);
		
		char *x =  pUser ->username;
		
		ot = fopen(x, "w+");
                printf("Add another account? (Y/N): ");
                scanf(" %c",&c);//skip leading whitespace
		
            }while(c=='Y'||c=='y');
            break;
    }
    free ( pUser);//free allocated memory
    fclose(fp);
}
