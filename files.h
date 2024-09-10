#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

struct files{
    int red;
    int green;
    int blue;
};
typedef struct files **Imagem;
typedef struct files *ImgagemP;
typedef struct files ImagemF;

typedef struct
{
    int nlin, ncol, quantizacao;
}Cabecalho;


void abrir_arquivos(char* img1, char* img2, FILE **fpImgIni, FILE **fpImgFin);
FILE* criar_arquivo(char* newImage);
void ler_cabecalho(FILE *fp, Cabecalho *cabecalho);
void ler_imagem(FILE *fp, int nlin, int ncol, Imagem img);
void gravar_cabecalho(FILE *fpNewImage, Cabecalho cabecalho);
void gravar_imagem(FILE *fpNewImage, Imagem imgIn, int nlin, int ncol);
void gerar_imagem_intermediaria(Imagem imgIni, Imagem imgFin, Cabecalho cabecalho, double t, int *index); 
void salvar_imagem_intermediaria(Imagem intermediaria, Cabecalho cabecalho, int index);  

Imagem alocar_matriz_Imagem(int nlin, int ncol);
#endif //FILES_H_INCLUDED