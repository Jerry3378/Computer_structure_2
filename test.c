/*this module is read bin code and convert hex into bin code*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hex_to_bin(char *hex_code ,char *bin);

int main() {
    FILE *file;
    const char *filename = "sum.bin";
    unsigned char buffer[4];
    size_t bytesRead;
    int i;

    char hex[9] = {0};

    char bin[33] = {0};

    int count = 0;

    // 파일 열기 (바이너리 모드로)
    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("파일을 열 수 없습니다");
        return EXIT_FAILURE;
    }

    /*
    fseek(file, 0, SEEK_END); // 파일 끝으로 이동
    long file_size = ftell(file); // 파일 크기 확인
    fseek(file, 0, SEEK_SET); // 파일의 처음으로 이동

    printf("%ld",file_size);

    */

    // 파일에서 바이트 읽기
    while(bytesRead = fread(buffer, sizeof(unsigned char), sizeof(buffer), file)){

        
        if (count == 4)
        {
            fseek(file,4,SEEK_CUR);
        }

        
    if (bytesRead == 0) {
        perror("파일에서 데이터를 읽을 수 없습니다");
        fclose(file);
        return EXIT_FAILURE;
    }

    // 읽어온 바이트 값 출력
    printf("읽어온 바이트 값: %d\n",count);
    
    for (i = 0; i < bytesRead; i++) {
        printf("%02x ", buffer[i]);
        sprintf(hex+i * 2,"%02x",buffer[i]);   //hex배열을 buffer에서 불러온 02x형태의 문자열로 저장
    }
    
    printf("\nhex is : %s\n",hex);

    for (i = 0; i < sizeof(hex)-1; i++) {
        hex_to_bin(hex+i,bin+i*4);
    }
    
    printf("hex to bin : %s\n",bin);
    printf("current location is : %#08x\n", count*4);

    memset(hex,0,sizeof(hex));
    memset(bin,0,sizeof(bin));

    count++;

    }
    
    // 파일 닫기
    fclose(file);

    return EXIT_SUCCESS;
}

void hex_to_bin(char *hex_code ,char* bin){

    switch(*hex_code) {
        case '0': strcpy(bin, "0000"); break;
        case '1': strcpy(bin, "0001"); break;
        case '2': strcpy(bin, "0010"); break;
        case '3': strcpy(bin, "0011"); break;
        case '4': strcpy(bin, "0100"); break;
        case '5': strcpy(bin, "0101"); break;
        case '6': strcpy(bin, "0110"); break;
        case '7': strcpy(bin, "0111"); break;
        case '8': strcpy(bin, "1000"); break;
        case '9': strcpy(bin, "1001"); break;
        case 'A': case 'a': strcpy(bin, "1010"); break;
        case 'B': case 'b': strcpy(bin, "1011"); break;
        case 'C': case 'c': strcpy(bin, "1100"); break;
        case 'D': case 'd': strcpy(bin, "1101"); break;
        case 'E': case 'e': strcpy(bin, "1110"); break;
        case 'F': case 'f': strcpy(bin, "1111"); break;
        case 0:  break;
        default: strcpy(bin, "????"); break; // 오류 처리
    }

}