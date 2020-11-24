#include <stdio.h>
#include <stdlib.h>

void yuv420_split(char *url, int w, int h, int num);

int main() {
    printf("Hello, World!\n");
    yuv420_split("testyuv.yuv",256,256,1);

    return 0;
}


/*
 * 如果视频帧的宽和高分别是w和h，
 * 那么一帧YUV420P像素数据一共占用w*h*3/2 byte数据。
 * 其中前 w * h byte存储Y,接着的 w * h * 1/4 byte存储U, 最后 w * h * 1/4 byte存储V
 */
void yuv420_split(char *url, int w, int h, int num){
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
}

/*
 * 如果视频帧的宽和高分别为w和h,
 * 那么一帧YUV444P像素数据一共占用w * h * 3 byte的数据。
 * 其中前 w * h byte存储Y,接着w * h byte存储U,最后 w * h byte存储V
 */
void yuv444_split(char *url, int w, int h,int num){
    // TODO :fopen过时，使用fopen_s替代
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("output_444_y.y","wb+");
    FILE *fp2 = fopen("output_444_u.y","wb+");
    FILE *fp3 = fopen("output_444_v.y","wb+");

    unsigned char *pic = (unsigned char *)malloc(w*h*3);

    for (int i = 0; i < num; i++) {
        fread(pic,1,w*h*3,fp);
        //Y
        fwrite(pic,1,w*h,fp1);
        //U
        fwrite(pic+w*h,1,w*h,fp2);
        //V
        fwrite(pic+w*h*2,1,w*h,fp3);
    }

    free(pic);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}

