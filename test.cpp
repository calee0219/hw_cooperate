#include<cstdio>
#include<iostream>

int main(){
  FILE *fin, *fout;
  int a;
  char b;
  fin = fopen("test.in", "rb");
  fout = fopen("test.out", "wb");
  while(fscanf(fin, "%d", &a) == 1){
    fprintf(fout, "%d\n", a);
    if(fscanf(fin, "%c", &b) == 1 && b == ' ');
    else
      break;
  }


  fclose(fin);
  fclose(fout);
  return 0;
}
