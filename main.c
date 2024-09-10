#include <stdio.h>
#include <stdlib.h>
#include "files.h"

int main(int argc, char *argv[])
{
    FILE *fpImgIni, *fpImgFin;
    Cabecalho c1, c2;
    Imagem imgIni, imgFin;
    int index = 0;

    abrir_arquivos(argv[1], argv[2], &fpImgIni, &fpImgFin);
    ler_cabecalho(fpImgIni, &c1);
    ler_cabecalho(fpImgFin, &c2); 
    
    imgIni = alocar_matriz_Imagem(c1.nlin, c1.ncol);
    imgFin = alocar_matriz_Imagem(c2.nlin, c2.ncol);

    ler_imagem(fpImgIni, c1.nlin, c1.ncol, imgIni);
    ler_imagem(fpImgFin, c2.nlin, c2.ncol, imgFin);

    fclose(fpImgIni);
    fclose(fpImgFin);

    for (double t = 0.0; t <= 1; t+=0.05)
    {
        gerar_imagem_intermediaria(imgIni, imgFin, c1, t, &index);
    }    

    return 0;
}