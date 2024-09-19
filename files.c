#include "files.h"

void abrir_arquivos(char* img1, char* img2, FILE **fpImgIni, FILE **fpImgFin)
{
    if(((*fpImgIni) = fopen(img1, "r"))==NULL)
    {
        printf("Erro ao abrir imagem Inicial.\n");
        exit(1);
    }
    if(((*fpImgFin)=fopen(img2, "r"))==NULL)
    {
        printf("Erro ao abrir imagem Final.\n");
        exit(1);
    }
}

FILE* criar_arquivo(char* newImage)
{
    FILE *fp;
    if((fp=fopen(newImage, "w"))==NULL)
    {
        printf("Erro ao gerar imagem intermediaria.\n");
        exit(1);
    }
    return fp;
}

void ler_cabecalho(FILE *fp, Cabecalho *cabecalho)
{
    char tipo[4];
    fscanf(fp, "%s\n", tipo);
    fscanf(fp, "%d %d\n", &cabecalho->nlin, &cabecalho->ncol);
    fscanf(fp, "%d\n", &cabecalho->quantizacao);
}

void ler_imagem(FILE *fp, int nlin, int ncol, Imagem img)
{
    for(int lin = 0; lin<nlin; lin++)
    {
        for(int col = 0; col<ncol; col++)
        {
            fscanf(fp, "%d\n", &img[lin][col].red);
            fscanf(fp, "%d\n", &img[lin][col].green);
            fscanf(fp, "%d\n", &img[lin][col].blue);
        }
    }
}
void gravar_cabecalho(FILE *fpNewImage, Cabecalho cabecalho)
{
    fprintf(fpNewImage, "%s\n", "P3");
    fprintf(fpNewImage, "%d %d\n", cabecalho.nlin, cabecalho.ncol);
    fprintf(fpNewImage, "%d\n", cabecalho.quantizacao);
}

void gravar_imagem(FILE *fpNewImage, Imagem imgIn, int nlin, int ncol)
{
    int lin = 0, col = 0;
    for(lin = 0; lin<nlin; lin++)
    {
        for(col = 0; col<ncol; col++)
        {
            fprintf(fpNewImage, "%d\n", imgIn[lin][col].red);
            fprintf(fpNewImage, "%d\n", imgIn[lin][col].green);
            fprintf(fpNewImage, "%d\n", imgIn[lin][col].blue);
        }
    }
}

void gerar_imagens_intermediarias(Imagem imgIni, Imagem imgFin, Cabecalho cabecalho, int *index)
{
    Imagem newImage = alocar_matriz_Imagem(cabecalho.nlin, cabecalho.ncol);

    for (double t = 0.0; t < 1.01; t+=0.05)
    {
        for (int lin = 0; lin < cabecalho.nlin; lin++)
        {
            for (int col = 0; col < cabecalho.ncol; col++)
            {
                newImage[lin][col].red = ((1 - t)*imgIni[lin][col].red + t*imgFin[lin][col].red);
                newImage[lin][col].green = ((1 - t)*imgIni[lin][col].green + t*imgFin[lin][col].green);
                newImage[lin][col].blue = ((1 - t)*imgIni[lin][col].blue + t*imgFin[lin][col].blue);
            }
        }

        salvar_imagem_intermediaria(newImage, cabecalho, ++(*index));
    }

    for (int lin = 0; lin < cabecalho.nlin; lin++) {
        free(newImage[lin]);
    }
    free(newImage);
}

void salvar_imagem_intermediaria(Imagem intermediaria, Cabecalho cabecalho, int index)
{
    FILE *fp;
    char imageIndex[10], fileName[30];
    sprintf(imageIndex, "%d", index);
    sprintf(fileName, "%s.ppm", imageIndex);

    fp = criar_arquivo(fileName);
    gravar_cabecalho(fp, cabecalho);
    gravar_imagem(fp, intermediaria, cabecalho.nlin, cabecalho.ncol);
    fclose(fp);
}

Imagem alocar_matriz_Imagem(int nlin, int ncol)
{
    Imagem newImage = (Imagem)malloc((nlin + 1) * sizeof(ImgagemP));
    for (int col = 0; col < nlin; col++)
    {
        newImage[col] = (ImgagemP)malloc((ncol+1)*sizeof(ImagemF));
        if(newImage[col] == NULL)
        {
            printf("Erro ao alocar nova Imagem.\n");
            exit(1);
        }
    }

    return newImage;
}