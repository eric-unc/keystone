#include <sched.h>
#include <stdio.h>

int main(){
  for(int i = 0; i < 100000; i++){
    sched_yield();
  }
  return 0;
}
