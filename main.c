#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000000

#if(defined CREATE_TEXT || defined CREATE_BIN)
int create_file(const char * path){
	FILE *file; //file pointer
	file = fopen(path,"w");
	if (!file) return 1;
	for (int i=0;i<SIZE;i++){
		fprintf(file,"%d\n", i);
	
	}
	fclose(file);

}
#endif
#ifdef TEXT
int text2text(const char * path1, const char * path2, const char * path3 ){
	FILE *fp1;
	FILE *fp2;
	FILE *fp3;
	fp1 =fopen(path1,"r");
	fp2 =fopen(path2,"r");
	fp3 = fopen(path3,"w");
	int result;	
	int buff_len =7;
	char buff1[buff_len];
	char buff2[buff_len];
	while((fgets(buff1,buff_len,fp1))&&(fgets(buff2,buff_len,fp2))){
		result =atoi(buff1)+atoi(buff2);	
		fprintf(fp3,"%d\n",result);
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	



}
#endif
#ifdef BIN
int bin2bin(const char * path1, const char * path2, const char * path3 ){
        FILE *fp1;
        FILE *fp2;
        FILE *fp3;
        fp1 =fopen(path1,"r");
        fp2 =fopen(path2,"r");
        fp3 = fopen(path3,"w");
        int result;
        int buff_len =7;
        char buff1[buff_len];
        char buff2[buff_len];
        while((fgets(buff1,buff_len,fp1))&&(fgets(buff2,buff_len,fp2))){
                result =atoi(buff1)+atoi(buff2);
                fprintf(fp3,"%d\n",result);
        }
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);

	


}
#endif
#ifdef MEM
int  mem2mem(){
	    // Allocate memory for the arrays
	int *arr1 = (int *)malloc(SIZE * sizeof(int));
   	int *arr2 = (int *)malloc(SIZE * sizeof(int));
   	int *arr3 = (int *)malloc(SIZE * sizeof(int));

   	if (arr1 == NULL || arr2 == NULL || arr3 == NULL) {
       		printf( "Memory allocation failed\n");
	return 1;
    }
	int i;
	for (i=0; i<SIZE;i++){
                arr1[i]=i;
		arr2[i]=i;
        }

	for ( i=0; i<SIZE;i++){
		arr3[i]=arr1[i]+arr2[i];
		//printf("%d\n",arr3[i]);
	}	
	


}
#endif
int main(){
#ifdef CREATE_TEXT	
	create_file("text1.txt");
	create_file("text2.txt");
#endif
#ifdef CREATE_BIN
	create_file("binary1.bin");
	create_file("binary2.bin");
#endif	
#ifdef TEXT
	text2text("text1.txt","text2.txt", "result_text.txt");
#elif BIN
	bin2bin("binary1.bin","binary2.bin","result_bin.bin");
#elif MEM
	mem2mem();
#endif

	return 0;
}
