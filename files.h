#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
/**
 * @brief Estrutura que representa um pixel
 */
struct pixels{
    int red;
    int green;
    int blue;
};
/**
 * @brief Definição de tipo de um ponteiro para ponteira da estrutura pixels 
 */
typedef struct pixels **Imagem;

/**
 * @brief Definição de tipo para cabeçalho
 */
typedef struct
{
    int nlin, ncol, quantizacao;
}Cabecalho;

/**
 * @brief Abre os arquivos das imagens iniciais e finais
 * 
 * @param img1 Nome da imagem inicial
 * @param img2 Nome da imagem final
 * @param fpImgIni Ponteiro para a imagem de inicio
 * @param fpImgFin Ponteiro para a imagem de saida
 */
void abrir_arquivos(char* img1, char* img2, FILE **fpImgIni, FILE **fpImgFin);

/**
 * @brief Abre um arquivo para uma imagem intermediária
 * 
 * @param newImage Nome do arquivo a ser criado/sobrescrito
 * 
 * @return O ponteiro para o arquivo
 */
FILE* criar_arquivo(char* newImage);

/**
 * @brief Lê as informações de cabeçalho da imagem
 * 
 * @param fp Ponteiro para a imagem
 * @param cabecalho Onde as informações de cabeçalho serão armazendas 
 */
void ler_cabecalho(FILE *fp, Cabecalho *cabecalho);

/**
 * @brief Lê as informações da imagem e as armazena em uma matriz do tipo Imagem
 * 
 * @param fp Ponteiro para o arquivo 
 * @param nlin Numero de linhas da imagem (altura)
 * @param ncol Numero de colunas da imagem (largura)
 * @param img Onde os pixels da imagem vão ser armazenados
 */
void ler_imagem(FILE *fp, int nlin, int ncol, Imagem img);

/**
 * @brief Grava o cabeçalho de uma imagem
 * 
 * @param fpNewImage Ponteiro para o arquivo da imagem
 * @param cabecalho Onde estão as informações do cabeçalho
 */
void gravar_cabecalho(FILE *fpNewImage, Cabecalho cabecalho);

/**
 * @brief Grava os pixels da imagem no arquivo
 * 
 * @param fpNewImage Ponteiro para o arquivo da imagem
 * @param imgIn Pixels a serem gravados no arquivo
 * @param nlin Altura da imagem
 * @param ncol Largura da imagem
 */
void gravar_imagem(FILE *fpNewImage, Imagem imgIn, int nlin, int ncol);

/**
 * @brief Função que gera os pixels das imagens intermediárias
 * 
 * Os pixels das imagens intermediárias são criados sempre que o for mais externo
 * varia; ele inicia em 0 e vai até 1, com incremento de 0.01 a cada volta, gerando no fim
 * 100 imagens. 
 * 
 * Ao gerar os pixels da imagem intermediáriam uma função auxiliar é chamada para que a 
 * imagem seja salva.
 * 
 * @param imgIni Pixels da imagem de inicio
 * @param imgFin Pixels da imagem final
 * @param cabecalho Informações a serem gravadas no cabeçalho das imagens
 * @param index Um inteiro usado para nomear cada imagem intermediária de maneira crescente 
 */
void gerar_imagens_intermediarias(Imagem imgIni, Imagem imgFin, Cabecalho cabecalho, int *index);

/**
 * @brief Salva em arquivos as imagens geradas pela função geradora de imagens intermediárias
 * 
 * @param intermediaria Pixels da imagem a ser salva
 * @param cabecalho Informações de cabecalho da imagem
 * @param index Numero da imagem usado para nomear o arquivo 
 */
void salvar_imagem_intermediaria(Imagem intermediaria, Cabecalho cabecalho, int index);  

/**
 * @brief Aloca espaço para uma matriz de Pixels
 * 
 * @param nlin Numero de linhas da matriz (Altura da imagem)
 * @param ncol Numero de colunas da matriz (Largura da imagem)
 * 
 * @return O ponteiro para a matriz alocada
 */
Imagem alocar_matriz_Imagem(int nlin, int ncol);

#endif //FILES_H_INCLUDED