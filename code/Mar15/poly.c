#include <stdio.h>
#include <stdlib.h>

typedef 
	struct {
		int exp ;
		double coef ;
	} 
	term_t ; //term_t(��) ���� -> exp(����) , coef(���)

typedef 
	struct {
		int degree ; //
		int n_terms ;
		term_t * terms ; // a list of attached terms 
	} 
	poly_t ; // poly_t(���׽�) ���� -> degree(�ְ�����), n_terms(�� ����), terms(����,���) 



poly_t * poly_zero () // ���׽� �ʱ�ȭ
{
	poly_t * p = (poly_t *) malloc(sizeof(poly_t)) ; // ���׽�p�� poly_t ��ŭ �޸� �Ҵ� 
	
	//�ʱⰪ ����
	p->degree = 0 ; //�ְ����� 0 
	p->n_terms = 0 ; // ���� ���� 0 
	p->terms = NULL ; // ���� ����/��� NULL
	return p ; //�ʱⰪ ������ ���׽� p ��ȯ
}




int poly_degree (poly_t * p) //�ְ����� ���ϱ�
{
	return p->degree ; // �ְ����� ���ǵ� degree �����ؼ� return
}

double poly_coef (poly_t * p, int exp) // ������ ��� �����ϱ�
{
	//�̻��� �� �Ÿ��� -> ������ 0�Ǵ� ������ ���
	if (exp < 0) // ���� ������ 0�̸� �̸� -> 0.0 ��ȯ 
		return 0.0 ;
	if (p->degree < exp) // �ְ����׵� 0 �̸��̸� -> 0.0 ��ȯ
		return 0.0 ;

	int i ;
	for (i = 0 ; i < p->n_terms ; i++) { // ���� ������ŭ ��ȸ (���׽� ��ȸ)
		if ((p->terms[i]).exp == exp) { //i��° ���� ������ �Է��� ������ ���� ���
			return (p->terms[i]).coef ; // �� ������ ��� ��ȯ
		}
	}
	return 0.0 ; // ���� ��ȸ�ϸ鼭 ���� �Ķ���ͷ� �ѱ� �������� �׿� �������� �ʴ´ٸ�, 0.0��ȯ 
}	



poly_t * poly_attach (poly_t * p, double coef, int exp) // ����,��� �Է��ؼ� �� �߰��ϱ�
{
	
	// ���� ó��- ���� ������ ���� , ����� 0, �Է��� ������ ���� �����ϴٸ� NULL ��ȯ
	if (exp < 0)
		return NULL ;
	if (coef == 0.0)
		return NULL ;
	if (poly_coef(p, exp) != 0.0)
		return NULL ;

	//���� ������ �ְ����׺��� ū ������ �Էµȴٸ�, �Էµ� ������ �ְ��������� ���� 
	if (p->degree < exp) {
		p->degree = exp ;
	}

	// terms(�ְ�����/���� ����)�� 1��ŭ Ű���� �޸� ���Ҵ�
	p->terms = realloc(p->terms, sizeof(term_t) * (p->n_terms + 1)) ; 
	(p->terms[p->n_terms]).coef = coef ; // terms�� �� ���� ��� ���� ����־ �� �߰�
	(p->terms[p->n_terms]).exp = exp ;
	p->n_terms += 1 ; // ���� ���� +1

	return p ; // �߰��۾� ��ģ p ��ȯ
}

poly_t * poly_remove (poly_t * p, int exp) // ������ �Է��ϰ� �� ������ ���� ����
{
	//����ó�� - ���� ������ ����/ �ְ����׺��� ū ���� / ����� 0�� ������ �ԷµǸ� NULL ��ȯ
	if (exp < 0)
		return NULL ;
	if (p->degree < exp)
		return NULL ;
	if (poly_coef(p, exp) == 0.0)
		return NULL ;


// i�� ���� ��ȸ�ϰ� �Է��� ����(exp)�� �´� ������ ã������ ���� i++
	int i = 0 ;
	while (p->terms[i].exp != exp) {
		i++ ;
	}
	// assert p->terms[i].exp == exp
	// i�� �����Ϸ��� ������ �����ϸ� �� ���� i����

//���� for������ �̿��Ͽ�, �����Ϸ��� �������� ū �������� ���� ��ĭ�� ������ �ű��
	for ( ; i < p->n_terms - 1 ; i++) {
		p->terms[i] = p->terms[i + 1] ;
	}
//������ �ű�� �� �� �޸� ũ�� ���Ҵ��ϰ� , ���� ������ 1 ���δ�.
	p->terms = realloc(p->terms, (p->n_terms - 1) * sizeof(term_t)) ;
	p->n_terms -= 1 ;

	int j ;
	p->degree = 0 ; // �ְ����׵� �ʱ�ȭ�ؼ� 
	for (j = 0 ; j < p->n_terms ; j++) { // j�� �̿��Ͽ� ���� ��ȸ�ϰ�
		if (p->degree < p->terms[j].exp) { // ���� ū ������ ã�Ƴ��� degree�� ����
			p->degree = p->terms[j].exp ;
		}
	}

	return p ;
}

void poly_show (poly_t * p)
{
	int i ;
	for (i = 0 ; i < p->n_terms ; i++) { // i�� �̿��Ͽ� ���� ������ŭ ��ȸ
		printf("%lf", p->terms[i].coef) ; //���� ���� long float
		if (p->terms[i].exp != 0) { // ���� ������ 0�� �ƴ϶��
			printf("x^%d", p->terms[i].exp) ; // "x^exp"������ ��Ÿ��
		}
		if (i != p->n_terms - 1) { //���� ������ �ױ��� ���� �ʾҴٸ�
			printf("+") ; // +�� ���
		}
		printf(" ") ;//�׸��� ���� ��� 
	}
	printf("\n") ; // �ٹٲ����� �� 
}

int main ()
{
	//1.0x^2 + 2.0x+ 1.0 
	poly_t * p = poly_zero() ;
	printf("%d\n", p == poly_attach(p, 1.0, 2)) ;
	printf("%d\n", p == poly_attach(p, 2.0, 1)) ;
	printf("%d\n", p == poly_attach(p, 1.0, 0)) ;
	printf("%d\n", p == poly_attach(p, 2.0, 2)) ;
	poly_show(p) ;

	printf("%d\n", p == poly_remove(p, 1)) ;
	poly_show(p) ;

	return EXIT_SUCCESS ;
}
