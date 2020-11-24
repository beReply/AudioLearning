#include <stdio.h>
#include <stdlib.h>

int _split(char *url, int w, int h, int num);

int main() {
    printf("Hello, World!\n");
    int s = _split("testyuv.yuv",256,256,1);

    return 0;
}

int _split(char *url, int w, int h, int num){
    // TODO :fopen过时，使用fopen_s替代
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("output_420_y.y","wb+");
    FILE *fp2 = fopen("output_420_u.y","wb+");
    FILE *fp3 = fopen("output_420_v.y","wb+");

    unsigned char *pic = (unsigned char *)malloc(w*h*3/2);

    for (int i = 0; i < num; i++) {
        fread(pic, 1, w*h*3/2, fp);
        fwrite(pic, 1, w*h, fp1);
        fwrite(pic + w * h, 1, w*h/4, fp2);
        fwrite(pic + w * h * 5/4, 1, w*h/4, fp3);
    }

    free(pic);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    return 0;
}