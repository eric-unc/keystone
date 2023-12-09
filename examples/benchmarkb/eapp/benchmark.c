#include <stdio.h>
#include <stdlib.h>

// This is going to depend wildly
#define SIZE_OF_TLB_IN_PAGES 1000
#define PAGE_SIZE 4096

int main(){
  char *start = malloc(SIZE_OF_TLB_IN_PAGES * PAGE_SIZE);
  char *end = start + (SIZE_OF_TLB_IN_PAGES * PAGE_SIZE);

  for(int i = 0; i < 1000; i++){
    for(char *page = start; page < end; page += PAGE_SIZE){
      *page++;
    }
  }

  return 0;
}
