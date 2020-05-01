
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>



/*
* Abaixo seguem funções que fazem a escrita do binário em "stdout" (tela) pra poder ser comparado no run.codes.
*
* Funciona assim: você faz tudo o que tiver que fazer na funcionalidade no arquivo em disco, assim como ensinado nas aulas da disciplina.
* Ao fim da funcionalidade, use a função "binarioNaTela" e a função já cuida de tudo para você. É só chamar a função.
*
* Note que ao usar a binarioNaTela, o fclose no arquivo binário já deve ter sido feito anteriormente. Você passa o nome do arquivo binário ("arquivoTrabX.bin") pra ela e ela vai ler tudo e escrever na tela.
*
* Você pode colocar isso num módulo .h separado, ou incluir as funções no próprio código .c: como preferir.
* VOCÊ NÃO PRECISA ENTENDER ESSAS FUNÇÕES. É só usar elas da forma certa depois de acabar a funcionalidade.
* NÃO MODIFIQUE ESSAS FUNÇÕES. Da forma como elas estão aqui, já estão funcionando para o propósito delas.
*
* Tá tudo testado e funcionando, mas qualquer dúvida acerca dessas funções, falar com o monitor Matheus (mcarvalhor@usp.br).
*/



	// Se você for incluir no .h separado, tá abaixo:

	#ifndef H_BINARIONATELA_
	#define H_BINARIONATELA_

	void binarioNaTela(char *nomeArquivoBinario);
	void trim(char *str);
	void scan_quote_string(char *str);

	#endif

	// Acabou o código que vai no .h



// Abaixo vai em algum .c


void binarioNaTela(char *nomeArquivoBinario) {

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}




void trim(char *str) {

	/*
	*	Essa função arruma uma string de entrada "str".
	*	Manda pra ela uma string que tem '\r' e ela retorna sem.
	*	Ela remove do início e do fim da string todo tipo de espaçamento (\r, \n, \t, espaço, ...).
	*	Por exemplo:
	*
	*	char minhaString[] = "    \t TESTE  DE STRING COM BARRA R     \t  \r\n ";
	*	trim(minhaString);
	*	printf("[%s]", minhaString); // vai imprimir "[TESTE  DE STRING COM BARRA R]"
	*
	*/

	size_t len;
	char *p;

	// remove espaçamentos do fim
	for(len = strlen(str); len > 0 && isspace(str[len - 1]); len--);
	str[len] = '\0';
	
	// remove espaçamentos do começo
	for(p = str; *p != '\0' && isspace(*p); p++);
	len = strlen(p);
	
	memmove(str, p, sizeof(char) * (len + 1));
}




void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}


