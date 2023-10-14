#include <stdio.h>
#include <stdlib.h>
//defines size_t unsinged int
#include <string.h>
//limits.h has limits for each var
//ctype.h has funs for info about vars
//stdint.h has exact types for int types, e.g. 24 bits, 32 bits...

#include <assert.h>

/********************************************************************************/

/* ---------------------------- scanf vs fgets -------------------------------- */

void scanfvsfgets()
{
  char buffer[5]; // +1 for NULL
  char a;
  fgets(buffer, 5, stdin); //in stdio.h
  
  //buffer[4] = 'a'; seg if not null at last pos in buff from printf
  //char *fgets(char *str, int n, FILE *stream) 

  printf("%s\n", buffer);
  printf("%c\n", a);
}

/********************************************************************************/

/* ------------------------------- string.h ----------------------------------- */

void stringhfuns() {
  char stra[50] = "helloworlda";
  const char *strb = "helloworldb";

  const char* test = "world";

   
  /*if(!strcmp(stra, strb))
  {
    printf("same\n");
  }*/

  /*if(!strcmp(test, strchr(stra, 'w')))
  {
    printf("peos\n");
  }*/

  /*if(!strncmp(stra, strb, 11))
  {
    printf("peos\n");
  }*/

  printf("%p\n", stra);
  printf("%p", strchr(stra, 'o'));

  // printf("A -> %lu %lu\n", strlen(stra), sizeof stra);

  // printf("B -> %lu %lu\n", strlen(strb), sizeof strb);
  
  // char *strcat(char *dest, const char *src)
  // char *strncat(char *dest, const char *src, size_t n)
  // to kollaei sto \0
  // char *strchr(const char *str, int c)
  // c is char, searches for the first occurence of a char in a str
  // int strcmp(const char *str1, const char *str2)
  // strcmp returns negative if str1 is smaller, pos if str2 is bigger, 0 if same
  // int strncmp(const char *str1, const char *str2, size_t n)
  // char *strcpy(char *dest, const char *src)
  // char *strncpy(char *dest, const char *src, size_t n)
  // copies str, not safe from overlapping
  // char *strstr(const char *haystack, const char *needle)
  // substr
  // char *strtok(char *str, const char *delim)
  // https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
  // tokenizer

  /*
  SAFE FOR OVERLAPPING:
  void *memchr(const void *str, int c, size_t n)
  int memcmp(const void *str1, const void *str2, size_t n)
  void *memcpy(void *dest, const void *src, size_t n)
  void *memmove(void *dest, const void *src, size_t n)
  void *memset(void *str, int c, size_t n)
  */

}

/********************************************************************************/

/* ---------------------- POINTERS & DOUBLE POINTERS -------------------------- */

void bar(int la[])
{
  (*la)++;

  printf("%d\n", *la);

  return;
}

void foo(int *la)
{
  (*la)++;

  printf("%d\n", *la);

  return;
}

void printLibTable(int *table, int len2d)
{
 int i, j;
 for(i=0; i<5; i++) {
    for(j=0; j<5; j++) {
      printf("%3d ", table[i * len2d + j]);
    }

    printf("\n");
  }
}

void printTable(int table[5][5])
{
 int i, j;
 for(i=0; i<5; i++) {
    for(j=0; j<5; j++) {
      printf("%3d ", table[i][j]);
    }

    printf("\n");
  }
}

void setStrategy(int **strat, int *newstrat) {
  *strat = newstrat;
}

void pointerGang() {
  int i, j;
  int B[5][5] = {0};

  //setXY(2, 2, 25);
  int a = 5, b = 6;
  int *strategy = &a;

  setStrategy(&strategy, &a);

  printTable(B);
  printf("\n");

  // int a = 9, b = 8;
  // int *p;
  // char *p2;
  // void *vp;
  // p = &a;
  // vp = &a;
  // *(int *)vp = 4;
  // (*p)++;  

  /*
  p2 = (char*) &a;

  *((int*)(p2-4)) = 80;*/
  
  // p[-1] = 70;
  // printf("%p %p %p\n", &a, &b, p);
  // printf("%d %d %d", a, b, *p);

}

/************************************************************************************/

/* --------------------------------- STRUCTS 1 ------------------------------------ */

typedef struct test
{
  int data[99999];
} Test;

//typedef struct test Test;

void doSomething(Test *tdata)
{
  (*tdata).data[0] = 1;

  tdata->data[0] = 2;
}


void byref()
{
Test tt;  
  int i;

  for(i=0; i < 10000; i++)
  {
    if(!(i % 100))printf("%d\n", i);

    doSomething(&tt);
  }

}

/************************************************************************************/

/* --------------------------------- STRUCTS 2 ------------------------------------ */

typedef struct string
{
  char *data;
  size_t len;
  size_t cap;
  //kati eidiko
} String;

//#define malloc(a) malloc_int(a, __FILE__, __LINE__);

void reallocateString(String *str, const size_t newSize)
{

  assert(str->cap < newSize);

  str->data = realloc(str->data, newSize * sizeof(char));
  if (str->data == NULL) {
    printf("Goodbye cruel world 2");
    exit(-1);
  }

  str->cap = newSize;
  
  return;
}

void appendToString(String *str, const char *data)
{
  size_t datalen = strlen(data);
  size_t newTotalLen = datalen + str->len;
  size_t prevSize = str->cap;

  if(prevSize < newTotalLen + 1)
  {
    while(prevSize < newTotalLen + 1) prevSize *= 2;

    reallocateString(str, prevSize);  
  }
 

  strcpy(str->data + str->len, data);

  str->len = newTotalLen;

  return;
}

void destroyString(String *str)
{
  free(str->data);
  str->data = NULL;
  str->cap = 0;
  str->len = 0;
}


String createString()
{
  const size_t initCap = 10;
  String str;
  /*
  str.data = malloc(initCap * sizeof (char));
  if (str.data == NULL) {
    printf("Goodbye cruel world");
    exit(-1);
  }
  */
  str.data = NULL;
  str.cap = 0;

  reallocateString(&str, initCap);

  str.len = 0;

  return str;
}

void strtest() {
  int i;
  String test = createString();

  appendToString(&test, "gayshit ");

  printf("%s\n", test.data);

  appendToString(&test, "very very gayshit");

  printf("%s\n", test.data);

  for(i=0; i < 10000; i++)
    appendToString(&test, "asdfasjdgfjkasdgfaisdfiasdfljkagsdkfgasoufasdf");
  
  printf("%s\n", test.data);

  destroyString(&test);
}

/* ---------------------------- FUNCTION POINTERS ------------------------------- */

int min(const void * a, const void * b)
{
  return *(int*)b - *(int*)a;
}

int max(const void * a, const void * b)
{
  return *(int*)a - *(int*)b;
}

void structtest() {
  int arr[] = { 4, 2, 4, 6, 12, 43, 1, 4, 6}; //gamw th poutana moy
  const size_t size = sizeof arr / sizeof arr[0];
  int i;


  /* Functions are nothing more really than pointers: with the declaration 
   * int (*var)(typeX1 a1, typeX2 a2, ...) you can save them into variables.
   * You can obviously, store pointers to pointers, and onwards and so forth.
   * For example: qsort takes the pointer to an array, the number of elements,
   * size of each element in bytes, and a comparison function pointer, that returns
   * pos if greater, 0 if same, neg if lower. */
  int (**KEKO)(const void*, const void*);
  int (*choice)(const void*, const void*) = max;

  KEKO = &choice;

  *KEKO = max;

  //qsort(arr, size, sizeof (int), *KEKO);
  qsort(arr, size, sizeof (int), choice);

  for(i=0; i < size; i++) printf("%d ", arr[i]);
  
  printf("\n");
}

/*********************************************************************************/

/* --------------------------------- UNIONS ------------------------------------ */

/*unions store the same value in different representations e.g:
 * if I store in peos.a = 3, then the same value would be used in peos.b and peos.c
 * in different representations. for example, see unions().
 * This could be useful in situations where I need to store the same thing in different
 * forms for some use case; for example, char ASCII values, where an int from -127 to 
 * +127 (0-255) has a meaningful value for a character representation. Ofcourse, the 
 * aforementioned example is rudementary.
 */
union 
{
  int a;
  long int b;
  char c[8];
} peos;

void unions() {
  int arr[] = { 4, 2, 4, 6, 12, 43, 1, 4, 6}; 
  const size_t size = sizeof arr / sizeof arr[0];
  int i;

  peos.b = 2345233456512341234l;
  strcpy(peos.c, "GTPKXS");
  printf("%d\t %0x\n", peos.a, *( int*)&peos.a);
  printf("%ld\t %0lx\n", peos.b, *(long int*)&peos.b);
  printf("%s\t %0lx\n", peos.c, *(long int*)&peos.c);
}

/*********************************************************************************/

/* ----------------------------- EXTERN & STATIC -------------------------------- */

//b.c
/* 
static int b = 5;

extern int getB()
{
  return b;
}
*/

//extern int b; //extern is used to access things on other files 
//static on the other hand will make it unavailable to access from a global scope -- meaning other files

int getB(); //inside a header


char* test(int b)
{
  //static is defined once, on the first function call
  static int a = 3; 
  static char tok[33];
  //if I want to return an array from a function defined in a function, i have to make it static otherwise it'll get freed (and ill get a seg eventually)
  if(!b) a = b; 
  
  return tok;
}


int asdf() {printf("dfg"); return 0;}; //any function can be used instead of main.c


int main(int argc, char **argv)
{
  int i;

  for(i=0; i < argc; i++) printf("%s\n", argv[i]);
  
  return 0;
}

/* ----------------------------- Getting dynamic input from C -------------------------------- */
//https://brennan.io/2015/01/16/write-a-shell-in-c/
/*The meat of the function is within the (apparently infinite) 
 * while (1) loop. In the loop, we read a character 
 * (and store it as an int, not a char, that’s important! 
 * EOF is an integer, not a character, and if you want to check for 
 * it, you need to use an int. This is a common beginner 
 * C mistake.). If it’s the newline, or EOF, we null 
 * terminate our current string and return it. Otherwise, 
 * we add the character to our existing string. 
 */

#define LSH_RL_BUFSIZE 1024
char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

/*********************************************************************************/
// https://nullprogram.com/blog/2023/10/08/
// For GCC and Clang, my favorite assert macro now looks like this:

#define assert(c)  while (!(c)) __builtin_unreachable()
/*
* It has useful properties beyond the usual benefits:
*   It does not require separate definitions for debug and release builds. Instead it’s controlled by the presence of Undefined Behavior Sanitizer (UBSan), which is already present/absent in these circumstances. That includes fuzz testing.
*   libubsan provides a diagnostic printout with a file and line number.
*   In release builds it turns into a practical optimization hint.
*/

// Next, my “standard” set of macros:
#define sizeof(x)    (size)sizeof(x)
#define alignof(x)   (size)_Alignof(x)
#define countof(a)   (sizeof(a) / sizeof(*(a)))
#define lengthof(s)  (countof(s) - 1)
// While I still prefer ALL_CAPS for constants, I’ve adopted lowercase for function-like macros because it’s nicer to read. 
//  Author note: i disagree with lowercase for macros, this can lead to accidental bugs

