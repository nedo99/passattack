#include<stdio.h>
#include<stdlib.h>
#define _XOPEN_SOURCE      
#include <unistd.h>
#include <crypt.h>
#include<string.h>
#include<malloc.h>

struct usr{
	char username[7], name[21], surname[21], hash[29];
};

struct dictionary{
	char word[25], h[29];
};


struct dictionary addmore[1472942];
struct dictionary addmore1[4157];
struct dictionary dates[227760];

int main(int argc, char *argv[]){
	FILE *f,*f1,*dict; 
	struct dictionary words[8468];
	struct usr users[8196];
	int k=0;
	int p;
	char salt[7];
	char line[100];
	char username1[7], d[2], rest[13], rest1[14];
	int len=0, s1=0, s=0;
	int j, top=0, dict_count=0, cain=0, dates_count=0;
	int i=0;
	int count=0;
	f=fopen(argv[1], "r");
	if( f==NULL){
		printf("\nError while reading the file pass and shadow files\n");
		exit(1);
	}
	
	while(fscanf(f,"%6s%13s %[^\n]s \n", username1, rest1, line)!=EOF){
		len=0;
		s1=0;
		s=0;
		
		for(j=0; j<100; j++){
			if(line[j]==' ')
				len++;
			if(line[j]==',')
				len++;
			if(len==0 && line[j]>64 && line[j]<123){ 
				users[i].name[s]=line[j];
				s++;
			}
		
			if(len==1 && line[j]>64 && line[j]<123){
				users[i].surname[s1]=line[j];
				s1++;
			}
		}
		users[i].name[s]='\0';
		users[i].surname[s1]='\0';
		i++;
	}
	fclose(f);
	f1=fopen(argv[2], "r");
	if(f1==NULL || f==NULL){
		printf("\nError while reading the file pass and shadow files\n");
		exit(1);
	}
	i=0;
	while(fscanf(f1,"%6s%1s%28s%12s\n",users[i].username, d, users[i].hash, rest)!=EOF){
		i++;
	}
	fclose(f1);
	int size=i;
	for(k=0;k<6;k++) salt[k]=users[0].hash[k];
	salt[6]='\0';		
	
	k=0;
	dict=fopen("top250more.txt", "r");
	if(dict==NULL){
		printf("\nError while reading the file\n");
		exit(1);
	}
	while(fscanf(dict,"%s\n", words[k].word) != EOF ){
			if(k>=8468) break;
			char *pass;
			pass=crypt(words[k].word, salt);
			int s=strlen(pass);
			for(p=0; p<=s; p++){
				words[k].h[p]=pass[p];
			}
			
			k++;
	}
	fclose(dict); 
	top=k;
	dict=fopen("dictionary.txt", "r");
	k=0;
	while(fscanf(dict,"%s\n", addmore[k].word) != EOF ){
			if(k>=1472942) break;
			char *pass;
			pass=crypt(addmore[k].word, salt);
			int s=strlen(pass);
			for(p=0; p<=s; p++){
				addmore[k].h[p]=pass[p];
			}
			
			k++;
	}
	dict_count=k;
	fclose(dict);
	dict=fopen("dates.txt", "r");
	k=0;
	while(fscanf(dict,"%s\n", dates[k].word) != EOF ){
			if(k>=227760) break;
			char *pass;
			pass=crypt(dates[k].word, salt);
			int s=strlen(pass);
			for(p=0; p<=s; p++){
				dates[k].h[p]=pass[p];
			}
			
			k++;
	}
	fclose(dict);
	dates_count=k;
	dict=fopen("cain.txt", "r");
	k=0;
	while(fscanf(dict,"%s\n", addmore1[k].word) != EOF ){
			if(k>=4157) break;
			char *pass;
			pass=crypt(addmore1[k].word, salt);
			int s=strlen(pass);
			for(p=0; p<=s; p++){
				addmore1[k].h[p]=pass[p];
			}
			
			k++;
	}
	fclose(dict);
	
	cain=k;
	
	for(i=0; i<size; i++){
		
		
		for(k=0; k<top; k++){
			
			if(strcmp(words[k].h, users[i].hash)==0){
				count++;
				printf("%-6s%-1s%-s\n", users[i].username, ":", words[k].word);
				fflush(stdout);
				users[i]=users[size-1];
				size--; i--;
				
				break;
			}
		}
	
		
		
	}
	
	for(i=0; i<size; i++){
		for(k=0; k<dates_count; k++){
			
			if(strcmp(dates[k].h, users[i].hash)==0){
				count++;
				printf("%-6s%-1s%-s\n", users[i].username, ":", dates[k].word);
				fflush(stdout);
				users[i]=users[size-1];
				size--; i--;
				break;
			}
		}
	}
	for(i=0; i<size; i++){
		for(k=0; k<dict_count; k++){
			
			if(strcmp(addmore[k].h, users[i].hash)==0){
				count++;
				printf("%-6s%-1s%-s\n", users[i].username, ":", addmore[k].word);
				fflush(stdout);
				
				users[i]=users[size-1];
				size--; i--;
				break;
			}
		}
	}
	for(i=0; i<size; i++){
		for(k=0; k<cain; k++){
			
			if(strcmp(addmore1[k].h, users[i].hash)==0){
				count++;
				printf("%-6s%-1s%-s\n", users[i].username, ":", addmore1[k].word);
				fflush(stdout);
				
				users[i]=users[size-1];
				size--; i--;
				break;
			}
		}
	}
	
	
	
	for(i=0; i<size; i++){
		
		char *pass;
		int v=0,p,hit;
		char lowern[21], uppern[21],lowers[21], uppers[21];
		strcpy(lowern, users[i].name);
		lowern[0]=lowern[0]+32;
		v=strlen(lowern);
		for(p=0; p<v; p++){
			uppern[p]=lowern[p]-32;
		}
		uppern[v]='\0';
		strcpy(lowers, users[i].surname);
		lowers[0]=lowers[0]+32;
		v=strlen(lowers);
		for(p=0; p<v; p++){
			uppers[p]=lowers[p]-32;
		}
		hit=0;
		uppers[v]='\0';
		pass=crypt(users[i].name, salt);
		if(strcmp(pass,users[i].hash)==0){
			count++;
			printf("%-6s%-1s%-s\n", users[i].username, ":", users[i].name);
			fflush(stdout);
			hit++;
			users[i]=users[size-1];
				size--; i--;
			
		}
		pass=crypt(lowern, salt);
		if(strcmp(pass,users[i].hash)==0){
			count++;
			printf("%-6s%-1s%-s\n", users[i].username, ":", lowern);
			fflush(stdout);
			hit++;
			
		}		

		pass=crypt(uppern, salt);
		if(strcmp(pass,users[i].hash)==0){
			count++;
			printf("%-6s%-1s%-s\n", users[i].username, ":", uppern);
			fflush(stdout);
			hit++;
			
		}
		pass=crypt(users[i].surname, salt);
		if(strcmp(pass,users[i].hash)==0){
			count++;
			printf("%-6s%-1s%-s\n", users[i].username, ":", users[i].surname);
			fflush(stdout);
			hit++;
			
		}
		pass=crypt(lowers, salt);
		if(strcmp(pass,users[i].hash)==0){
			count++;
			printf("%-6s%-1s%-s\n", users[i].username, ":", lowers);
			fflush(stdout);
			hit++;
			
		}
		pass=crypt(uppers, salt);
		if(strcmp(pass,users[i].hash)==0){
			count++;
			printf("%-6s%-1s%-s\n", users[i].username, ":", uppers);
			fflush(stdout);
			hit++;
			
		}
	
		if(hit==0){
			char num[5];
			int k;
			for(k=60; k<=2000; k++){
				if(k==100)
					k=1970;
				sprintf(num, "%d", k);
				char *c = malloc(strlen(lowern)+strlen(num)+1);
				strcat(c,lowern);
				strcat(c,num);
				pass=crypt(c, salt);
				if(strcmp(pass,users[i].hash)==0){
					count++;
					printf("%-6s%-1s%-s\n", users[i].username, ":", c);
					fflush(stdout);
					
					break;
				}
			
			}
		}
	}
	return 0;
}
