#include <stdio.h>

int main (int argc, char *argv[]) {
  int c;
  FILE *fp;
  char buff[4096];
  char firstNum;
  char filePath[4096];

  printf("Enter a file path: ");
  scanf("%s", filePath);

  fp = fopen(filePath, "r");
  if (fp) {
    while((c = getc(fp)) != EOF){
      putchar();
    }

    // firstNum = &buff[0];
    // printf("\n");
    // printf("%c", firstNum);
    // printf("\n");
    fclose(fp);

  }
}


// Set switch = firstNum
// Iterate through characters until file.length
//
// If switch == currentNum,
// 	count++,
// 	continue to..print?
//
// Else if switch == ""
// 	continue to..print?,
// 	counter == 0?
//
// If count >= 16,
// 	compressed == "-" + count + "-"
//
// If switch != currentNum,
// 	switch == currentNum,
// 	count == 0
