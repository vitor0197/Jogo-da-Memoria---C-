/*
JOGO DA MEM�RIA EM C++
Desenvolvedor Vitor Alexandre Silveira
*/

#include <iostream> // entradas e sa�das
#include <locale.h> // acentos
#include <time.h> // function time
#include <windows.h>
#define TAM 4 // tamanho das matrizes
#define PAR TAM*TAM/2 // n�mero de pares

using namespace std;

int main()
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    int matPrinc[TAM][TAM],matModif[TAM][TAM]; // matriz principal e modificada
    int i, j; // linhas e colunas
    int nPcs[PAR]={0}, peca; // para consist�ncia da matriz do jogo (n� de pe�as e pe�a)
    int tipo; // tipo de jogo (s/ modifica��o, transposta, invertida p/ linha ou coluna)
    int nJogadas=0, lin1,col1,lin2,col2; // Intera��es com Jogador (n�mero de jogadas, linhas e colunas que o usu�rio inserir)
    int k=0; // auxiliar

    /// GERA MATRIZ
    for (i=0;i<TAM;i++){
        for (j=0;j<TAM;j++){
            matPrinc[i][j] = rand()%PAR+1;
            /// CONSIST�NCIA
            nPcs[matPrinc[i][j]-1]++; // indica quantas vezes apareceu na matriz
            if (nPcs[matPrinc[i][j]-1]>2) { // repetido +2 vezes
                for(peca=0;peca<PAR;peca++){
                    if (nPcs[peca]<2){ // verifica todas as pe�as que ainda n�o tem par
                        matPrinc[i][j] = peca+1; // armazena pe�a n�o repetida no lugar da repetida
                        //peca=PAR; // para sair do FOR
                    }
                }
                nPcs[matPrinc[i][j]-1]++;
            }

        }
    }
    tipo = rand()%4+1; // ESCOLHER QUAL VAI SER A MATRIZ JOGO

    switch (tipo){
        case 1: // SEM MODIFICA��O
            for (i=0;i<TAM;i++){
                for (j=0;j<TAM;j++){
                    matModif[i][j] = matPrinc[i][j];
                }
            }
            break;
        case 2: // TRANSPOSTA
            for (i=0;i<TAM;i++){
                for (j=0;j<TAM;j++){
                    matModif[i][j] = matPrinc[j][i];
                }
            }
            break;
        case 3: // INVERTIDA POR LINHA
            for (i=TAM-1;i>-1;i--){
                for (j=0;j<TAM;j++){
                    matModif[k][j] = matPrinc[i][j];
                }
                k++; // enquanto k sobe, i desce (matModif[3][0] == matPrinc[0][0])
            }
            break;
        default: // INVERTIDA POR COLUNA
            for (i=0;i<TAM;i++){
                k=0;
                for (j=TAM-1;j>-1;j--){
                    matModif[i][k] = matPrinc[i][j];
                    k++; // enquanto k sobe, j desce (matModif[0][3] == matPrinc[0][0])
                }
            }
    }
    // Zera as vari�veis
    k=0;
    for (i=0;i<TAM;i++){ // matriz zerada assim porque matPrinc[TAM][TAM] = {0} n�o funcionou
        for (j=0;j<TAM;j++) {
            matPrinc[i][j]=0;
        }
    }
    for (i=0;i<PAR;i++){ // vetor zerado assim porque nPcs[PAR] = {0} n�o funcionou
        nPcs[i]=0;
    }

    /// JOGABILIDADE
    while(nJogadas<PAR*3){
        cout<<"\t1\t2\t3\t4\t\n\n\n"; // cria��o de cen�rio (colunas)
        for (i=0;i<TAM;i++){
            cout<< i+1 << "\t";  // cria��o de cen�rio (linhas)
            for (j=0;j<TAM;j++) {
                cout<<matPrinc[i][j]<<"\t";
            }
            cout<< endl;
        }
        if (nJogadas>0){
            if (matPrinc[lin1][col1]==matPrinc[lin2][col2]){
                nPcs[matPrinc[lin1][col1]-1]++; // par encontrado
                cout << endl << "JOGADA OK" << endl;
                k++; // contador de pares achados
                if (k==PAR){ // contador igual ao n�mero de pares
                    system("cls");
                    cout << "\n\n\nVIT�RIA! Voc� achou todos os pares!\n\n\n";
                    return 0; // finaliza o jogo
                }
            } else {
                matPrinc[lin1][col1] =0;
                matPrinc[lin2][col2] =0;
                cout << endl << "JOGADA NOK" << endl;
            }
        }
        lin1=0;
        col1=0;
        lin2=0;
        col2=0;

        cout << "\n\nN�mero de jogadas: " << nJogadas << " de " << PAR*3 << endl;

        while(lin1<1 || lin1>TAM || col1<1 || col1>TAM){ // enquanto n�o inserir dados v�lidos
            cout << "\n\n1� Pe�a:\nInsira a linha: ";
            cin  >> lin1;
            cout << "Insira a coluna: ";
            cin  >> col1;
            if(lin1>0 && lin1<5 && col1>0 && col1<5 && nPcs[matModif[lin1-1][col1-1]-1]>0){ // se o par j� tenha sido encontrado
                cout << "\n\nPar j� encontrado! Insira outro valor.";
                lin1=0; // zera para exigir outra linha e coluna
                col1=0;
            }
        }
        lin1--;
        col1--;
        matPrinc[lin1][col1] = matModif[lin1][col1];

        while(lin2<1 || lin2>TAM || col2<1 || col2>TAM || /*exige coordenadas diferentes*/ col1==col2-1 && lin1==lin2-1){ // enquanto n�o inserir dados v�lidos
            cout << "\n\n2� Pe�a:\nInsira a linha: ";
            cin  >> lin2;
            cout << "Insira a coluna: ";
            cin  >> col2;
            if(lin2>0 && lin2<5 && col2>0 && col2<5 && nPcs[matModif[lin2-1][col2-1]-1]>0){
                cout << "\n\nPar j� encontrado! Insira outro valor.";
                lin1=0;
                col1=0;
            }
        }
        lin2--;
        col2--;
        matPrinc[lin2][col2] = matModif[lin2][col2];

        nJogadas++;
        system("cls");
    }
    cout << "\n\n\nDERROTA! Voc� excedeu seu limite de jogadas!\n\n\n";
    return 0;
}
