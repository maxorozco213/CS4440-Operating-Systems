#include <stdio.h>

void myCompress(FILE *out, int sameCharCount, char lastRead) {
    if(sameCharCount >= 16) {
        if(lastRead == '0') {
            putc('-', out);
            fprintf(out, "%d", sameCharCount);
            putc('-', out);
        }

        else if(lastRead == '1'){
            putc('+', out);
            fprintf(out, "%d", sameCharCount);
            putc('+', out);
        }
    }
}

int main (int argc, char *argv[]) {
    FILE *file;
    FILE *output;
    int c;
    int count = 0;
    char buff[4096];
    char firstNum;
    char startFilePath[4096];
    char destFilePath[4096];
    char currentChar;
    char lastChar = ' ';

    //get path of file to be compressed
    printf("Enter starting file path: ");
    scanf("%s", startFilePath);

    //get path of file being written to
    printf("Enter destination file path: ");
    scanf("%s", destFilePath);

    //open the first file to read from it and second to write to it
    file = fopen(startFilePath, "r");
    output = fopen(destFilePath, "w");

    if (file) {
        //loop until EOF (or "End Of File"), each time setting current character
        while((c = fgetc(file)) != EOF) {
            currentChar = c;
            printf("%c", currentChar);

            //test current char
            if (currentChar != lastChar) {
                if (count >= 16) {
                    myCompress(output, count, lastChar);
                }


                //puts the character into the destination file
                else {
                    for (int i = 0; i < count; i++) {
                        putc(lastChar, output);
                    }
                }

                count = 0;
            }
            //increase the count if same
            count++;
            lastChar = currentChar;
        }

        if(count != 0) {
            if(count >= 16) {
                myCompress(output, count, lastChar);
            }

            else {
                for(int i = 0; i < count; i++) {
                    putc(lastChar, output);
                }
            }
        }


    }

    fclose(output);
}
