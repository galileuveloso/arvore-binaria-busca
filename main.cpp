#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
   int info;
   struct arvore *esq;
   struct arvore *dir;
} Arvore;

Arvore* cria_arv_vazia (void) {
   return NULL;
}

Arvore* arv_constroi (int c, Arvore* e, Arvore* d) {
  Arvore* a = (Arvore*)malloc(sizeof(Arvore));
  a->info = c;
  a->esq = e;
  a->dir = d;
  return a;
}

int verifica_arv_vazia (Arvore* a) {
  return (a == NULL);
}

Arvore* arv_libera (Arvore* a) {
  if (!verifica_arv_vazia(a)) {
    arv_libera (a->esq);
    arv_libera (a->dir);
    free(a);
  }
  return NULL;
}

int eh_espelho(Arvore * arv_a, Arvore * arv_b) {
	if(arv_a == NULL && arv_b == NULL)
		return 0;

	if(arv_a->info != arv_b->info)
		return 1;	

	if(eh_espelho(arv_a->esq, arv_b->dir) == 0 && eh_espelho(arv_a->dir, arv_b->esq) == 0)
		return 0;
	else
		return 1;
}

Arvore * cria_espelho(Arvore * arv_a) {
	if(arv_a == NULL)
		return cria_arv_vazia();

	if(arv_a->dir == NULL && arv_a->esq == NULL)
		return arv_a;
	
	Arvore * novo = (Arvore*)malloc(sizeof(Arvore));
	novo->info = arv_a->info;
	novo->dir = cria_espelho(arv_a->esq);
	novo->esq = cria_espelho(arv_a->dir);
	
	return novo;
}

int arv_bin_check(Arvore * a) {
	if(a == NULL)
		return 0;
		
	if((a->esq != NULL && a->esq->info > a->info) || (a->dir != NULL && a->info > a->dir->info))
		return 1;	
			
	if(arv_bin_check(a->esq) == 0 && arv_bin_check(a->dir) == 0)
		return 0;

	return 1;
}

int main(int argc, char** argv) {
	Arvore *a, *b, *c, *d, *e, *f;
	Arvore *a1, *b1, *c1, *d1, *e1, *f1;
	
	//criei uma arvore binaria de busca
	d = arv_constroi(1, cria_arv_vazia(), cria_arv_vazia());
	e = arv_constroi(4, cria_arv_vazia(), cria_arv_vazia());
	f = arv_constroi(6, cria_arv_vazia(), cria_arv_vazia());
	b = arv_constroi(2, d, cria_arv_vazia());
	c = arv_constroi(5, e, f);
	a = arv_constroi(3, b, c);
	
	//criei uma arvore nao binaria de busca
	f1 = arv_constroi(1, cria_arv_vazia(), cria_arv_vazia());
	e1 = arv_constroi(2, cria_arv_vazia(), cria_arv_vazia());
	d1 = arv_constroi(3, cria_arv_vazia(), cria_arv_vazia());
	c1 = arv_constroi(4, f1, e1);
	b1 = arv_constroi(5, cria_arv_vazia(), d1);
	a1 = arv_constroi(6, c1, b1);
		
	//verifico a primeira arvore
	if(arv_bin_check(a) == 0)
		printf("eh binaria de busca\n");
	else
		printf("nao eh binaria de busca\n");
		
	//verifico a segunda arvore
	if(arv_bin_check(a1) == 0)
		printf("eh binaria de busca\n");
	else
		printf("nao eh binaria de busca\n");
		
	
	arv_libera(a);
	arv_libera(a1);
	return 0;
}
