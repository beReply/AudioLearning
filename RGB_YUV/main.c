#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma region declare

// yuv420
void yuv420_split(char *url, int w, int h, int num);
void yuv420_gray(char *url, int w, int h, int num);
void yuv420_half_y(char *url, int w, int h, int num);
void yuv420_border(char *url, int w, int h, int border, int num);
int yuv420_gray_bar(int width, int height, int y_min, int y_max, int bar_num, char *url_out);

// yuv444
void yuv444_split(char *url, int w, int h,int num);

#pragma endregion


#pragma region YUV420P

/*
 * 如果视频帧的宽和高分别是w和h，
 * 那么一帧YUV420P像素数据一共占用w*h*3/2 byte数据。
 * 其中前 w * h byte存储Y,接着的 w * h * 1/4 byte存储U, 最后 w * h * 1/4 byte存储V
 */
void yuv420_split(char *url, int w, int h, int num){
    FILE *fp, *fp1, *fp2, *fp3;
    fopen_s(&fp, url, "rb+");
    fopen_s(&fp1, "output_420_y.y","wb+");
    fopen_s(&fp2, "output_420_u.y", "wb+");
    fopen_s(&fp3, "output_420_v.y","wb+");

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
 * 将YUV420P像素数据去掉颜色(变成灰度图)
 *
 */
void yuv420_gray(char *url, int w, int h, int num){
    FILE *fp, *fp1;
    fopen_s(&fp, url, "rb+");
    fopen_s(&fp1, "output_gray.yuv", "wb+");

    unsigned char *pic = (unsigned char *)malloc(w * h * 3/2);

    for (int i = 0; i < num; i++) {
        fread(pic, 1, w * h * 3/2, fp);
        // Gray
        memset(pic + w * h, 128, w * h / 2);
        fwrite(pic, 1, w * h * 3/2, fp1);
    }

    free(pic);
    fclose(fp);
    fclose(fp1);
}

/*
 * 将YUV420P像素数据亮度减半
 */
void yuv420_half_y(char *url, int w, int h, int num){
    FILE *fp, *fp1;
    fopen_s(&fp, url, "rb+");
    fopen_s(&fp1, "output_half_y.yuv", "wb+");

    unsigned char *pic = (unsigned char *)malloc(w * h * 3/2);

    for (int i = 0; i < num; i++) {
        fread(pic, 1, w * h * 3/2, fp);
        for (int j = 0; j < w * h; j++) {
            unsigned char temp = pic[j] / 2;
            pic[j] = temp;
        }
        fwrite(pic, 1, w * h * 3/2, fp1);
    }

    free(pic);
    fclose(fp);
    fclose(fp1);
}

/*
 * 将YUV420P像素的周围加上边框
 */
void yuv420_border(char *url, int w, int h, int border, int num){
    FILE *fp, *fp1;
    fopen_s(&fp, url, "rb+");
    fopen_s(&fp1, "output_border.yuv", "wb+");

    unsigned char *pic = (unsigned char *)malloc(w * h * 3/2);

    for (int i = 0; i < num; i++) {
        fread(pic, 1, w * h * 3/2, fp);
        // Y
        for (int j = 0; j < h; j++) {
            for (int k = 0; k < w; k++) {
                if (k < border || k > (w - border) || j < border || j > (h - border)){
                    pic[j * w + k] = 255;
                }
            }
        }
        fwrite(pic, 1, w * h * 3/2, fp1);
    }

    free(pic);
    fclose(fp);
    fclose(fp1);
}

/*
 * 生成YUV420P格式的灰阶测试图
 */
int yuv420_gray_bar(int width, int height, int y_min, int y_max, int bar_num, char *url_out){
    int bar_width;
    float lum_inc;
    unsigned char lum_temp;
    int uv_width, uv_height;
    FILE *fp;
    unsigned char *data_y, *data_u, *data_v;
    int t = 0, i = 0, j = 0;

    bar_width = width / bar_num;
    lum_inc = ( (float)(y_max - y_min) / (float)(bar_num - 1) );
    uv_width = width / 2;
    uv_height = height / 2;

    data_y = (unsigned char *)malloc(width * height);
    data_u = (unsigned char *)malloc(uv_width * uv_height);
    data_v = (unsigned char *)malloc(uv_width * uv_height);

    if (fopen_s(&fp, url_out, "wb+") != 0){
        printf("Error: Cannot create file!");
        return -1;
    }

    // Output Info
    printf("Y, U, V value from picture's left to right:\n");
    for (int t = 0; t < (width / bar_width); t++) {
        lum_temp = y_min + (char)(t * lum_inc);
        printf("%3d, 128, 128\n", lum_temp);
    }

    // Gen Data
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            t = i / bar_width;
            lum_temp = y_min + (char)(t * lum_inc);
            data_y[j * width + i] = lum_temp;
        }
    }

    for (int j = 0; j < uv_height; j++) {
        for (int i = 0; i < uv_width; i++) {
            data_u[j * uv_width + i] = 128;
        }
    }

    for (int j = 0; j < uv_height; j++) {
        for (int i = 0; i < uv_width; i++) {
            data_v[j * uv_width + i] = 128;
        }
    }

    fwrite(data_y, width * height, 1, fp);
    fwrite(data_u, uv_width * uv_height, 1, fp);
    fwrite(data_v, uv_width * uv_height, 1, fp);
    fclose(fp);
    free(data_y);
    free(data_u);
    free(data_v);
    return 0;
}

#pragma endregion


#pragma region YUV444P

/*
 * 如果视频帧的宽和高分别为w和h,
 * 那么一帧YUV444P像素数据一共占用w * h * 3 byte的数据。
 * 其中前 w * h byte存储Y,接着w * h byte存储U,最后 w * h byte存储V
 */
void yuv444_split(char *url, int w, int h,int num){
    FILE *fp, *fp1, *fp2, *fp3;
    fopen_s(&fp, url, "rb+");
    fopen_s(&fp1, "output_444_y.y","wb+");
    fopen_s(&fp2, "output_444_u.y","wb+");
    fopen_s(&fp3, "output_444_v.y","wb+");

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

#pragma endregion


int main() {
    printf("Hello, World!\n");
    yuv420_gray_bar(640, 360,0,255,10,"gray_bar_640x360.yuv");
    // yuv420_border("..\\TestFile\\tempete_cif.yuv",352,288, 10,1);

    return 0;
}
