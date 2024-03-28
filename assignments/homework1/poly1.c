#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef 
	struct {
		int exp ; // ���� 
		double coef ; //��� 
	} 
	term_t ;

typedef 
	struct {
		int degree ; // ���׽��� ����
		int n_terms ; // ���׽��� ����
		term_t * terms ; // �׵��� �迭 ex)2x+1 = (����,���) (1,2),(0,1) 
	} 
	poly_t ;

poly_t * poly_zero () // ���ο� ���׽� ����, �ʱ�ȭ ���·� ��ȯ
{
	poly_t * p = (poly_t *) malloc(sizeof(poly_t)) ; 
	// malloc(sizeof(poly_t)) - > poly_t ����ü�� ũ�⸸ŭ �޸� �����Ҵ�.
		//(poly_t *) ->malloc�� void*(void ������)�� return�Ѵ�. �ٵ� (poly_t *)�� ĳ�����ؼ� 
		// ->malloc�� ��ȯ�� �޸� �ּҸ� p��� ������ ������ �Ҵ��Ѵٴ� �� 
		// ->��, p�� �������� �Ҵ�� poly_t ����ü�� ����Ű�� �ȴ�.
	
	p->degree = 0 ;
	p->n_terms = 0 ;
	p->terms = NULL ;
	return p ; 
}

int poly_degree (poly_t * p) // �־��� ���׽��� ������ ��ȯ�Ѵ�. 
{
	return p->degree ;
	// -> ȭ��ǥ�� .(��)�� ���� �ǹ̸� ���µ�, ȭ��ǥ�� p�� ����ü�� ����Ű�� �������� ��� ���.
	// .(��)�� p�� ����ü �����϶� ���
}

double poly_coef (poly_t * p, int exp) // �־��� ���׽� Ư�� "������ ���" ��ȯ
{
	if (exp < 0) // ���� ������ �������, ���� �������� �����Ƿ� 0.0 ��ȯ
		return 0.0 ;
	if (p->degree < exp) //���� ������ ���׽��� �ְ� �������� ũ�ٸ�, ������ ���� �������� �����Ƿ� 0.0��ȯ
		return 0.0 ;

	int i ; 
	for (i = 0 ; i < p->n_terms ; i++) { // i< p->n_terms �� �� ���� ��ȸ
		if ((p->terms[i]).exp == exp) { // ���� �˻����� ������, �Ķ���ͷ� �Ѿ�� ������ ������
			return (p->terms[i]).coef ; // �� ������ ����� ��ȯ
		}         
	}                                                                  
	return 0.0 ;                                                                                                                                                                                                                  
}	                                                           
                                                                           
poly_t * poly_attach (poly_t * p, double coef, int exp) // ���ο� �� �߰� (������, �߰��� ���� ���, �߰��� ���� ����)
{
	if (exp < 0) // ���� ������ ������ �� �߰� x -> NULL
		return NULL ;
	if (coef == 0.0) // ���� ����� 0�̸� �� �߰� x -> NULL 
		return NULL ;
	if (poly_coef(p, exp) != 0.0) // ���� ����� 0�� �ƴ϶�� (�̹� �����ϴ� ���̶��), �ߺ��ǹǷ� NULL
		return NULL ;

	if (p->degree < exp) { // ���� �߰��Ϸ��� ���� ������ ���� ���׽��� �ְ����׺��� ũ�� 
		p->degree = exp ; // �ְ����� ������Ʈ
	}
	p->terms = realloc(p->terms, sizeof(term_t) * (p->n_terms + 1)) ; // �� �ϳ��� �߰������Ƿ� �޸� ���Ҵ�.
	// realloc���� ���ο� �޸� �ּҸ� �Ҵ��ϸ�, ���� �����ʹ� ���ο� �޸� �ּҸ� ����Ŵ
	(p->terms[p->n_terms]).coef = coef ; // �� ���ο� �ּҿ� ������ ����� �������. 
	(p->terms[p->n_terms]).exp = exp ;
	p->n_terms += 1 ; // ���� ���������� ���׽��� ���� ������ ������Ű�� �۾��� �������Ƿ� ���� ���� ī��Ʈ��+1 ����. 

	return p ;
}

poly_t * poly_remove (poly_t * p, int exp) //�־��� ������ �ش��ϴ� ���� ���� �� ����� ���׽� ��ȯ.
{
	if (exp < 0) // ������ ���� -> NULL
		return NULL ;
	if (p->degree < exp) // �ְ����׺��� ������ ū ��� -> ���� ���̹Ƿ� NULL
		return NULL ;
	if (poly_coef(p, exp) == 0.0) // ����� 0�� ��� -> ���� ���̹Ƿ� NULL
		return NULL ;

	int i = 0 ;
	while (p->terms[i].exp != exp) { // �ش� ������ ���ö����� �ݺ��ϰ�, �ش� �� �ε��� ã��.
		i++ ;
	}
	// assert p->terms[i].exp == exp

	for ( ; i < p->n_terms - 1 ; i++) { // ã�� ���� �����ϱ� ���� �ش� �� ������ ��� ���� �������� �о�ֱ�. 
		p->terms[i] = p->terms[i + 1] ;
	}
	p->terms = realloc(p->terms, (p->n_terms - 1) * sizeof(term_t)) ; // �� �ϳ��� ���� �Ǿ����Ƿ�, (n_terms-1)��ŭ�� �޸𸮷� ���Ҵ�
	p->n_terms -= 1 ; //���� �ϳ� ���������Ƿ�, ī��Ʈ�� -1

	int j ; 
	p->degree = 0 ; //���ŵ� ���� �ְ������̾��� ���� �����Ƿ�, �ְ����� �ٽ� ����� ���� degree= 0���� �ʱⰪ ����
	for (j = 0 ; j < p->n_terms ; j++) { // ��� ���� ��ȸ
		if (p->degree < p->terms[j].exp) { // 
			p->degree = p->terms[j].exp ;
		}
	}

	return p ;
}


void poly_delete (poly_t * p) //���׽İ� ���õ� �޸� ����  
{
	if (p->terms != NULL) { // ���� terms�� null�� �ƴ� ��� -> �޸𸮰� �Ҵ�Ǿ� �ִ� ���
		free(p->terms) ; // �� �ϳ��ϳ��� ���� �޸𸮸� free
	}
	free(p) ; // ��ü���� �κ�(����ü ��ü)�� ���� �޸� free
}


//homework


poly_t * poly_scale (poly_t * p, double s) // s ���� �� ����� ���ؼ� ��ȯ
{
	poly_t *result = poly_zero(); // ���ο� ���׽� ����

	int i;
	for (i = 0 ; i < p->n_terms ; i++){// ��ü �� ��ȸ 
		if (poly_coef(p, i) != 0.0) // ���� ����� 0�� �ƴ϶�� (�̹� �����ϴ� ���̶��)
			p->terms[i].coef*=s;
	}
	return result;
}

poly_t * poly_add (poly_t * p1, poly_t * p2) // �� ���׽� ���ϱ�
{
	poly_t *p3 = poly_zero();  
	p3->n_terms = 0;
	p3->degree = (p1->degree > p2->degree) ? p1->degree : p2->degree;
	//���� p1.degree > p2.degree �̸� p1->degree�� ������, �ƴϸ� p2->degree�� ����
	p3->terms = (term_t *)malloc(sizeof(term_t) * (p3->degree + 1));
	// 0������ �����ؼ� degre+1 ���� �����Ҵ�

	int i;
	for (i=0; i<= p3->degree; i++){ // p3 �ְ����ױ��� �� ���׽� ��ȸ
		double coef1 = 0.0 , coef2 = 0.0; // ���� ��� ���� ����

		if(i<= p1->degree){ // ���� �˻��ϰ� �ִ� �������� p1�� �ְ������� �� ũ�ٸ�, ���� ������ ���ɼ��� �����Ƿ� �˻�. 
			for (int j = 0; j< p1->n_terms; j++){ // ù ��° ���׽� ��ȸ
				if (p1->terms[j].exp == i){ // ���� ������ ���� �˻��ϰ� �ִ� ������ ���� ���� ���
					coef1 = p1->terms[j].coef; // coef�� ���� ��Ƴ��� �ϴ� �ݺ� ���߱�
					break;
				}
			}
		}

		if(i<=p2->degree){ // �� ��° ���׽� �ְ����ױ��� ��ȸ
			for (int j = 0; j< p2->n_terms; j++){ 
				if(p2->terms[j].exp == i){ 
					coef2 = p2->terms[j].coef;
					break;
				}
			}
			double sum = coef1+coef2; // ������ ��� ���ϱ�
			if(sum!= 0.0){ // ���� ����� ���� 0�� �ƴ϶��
				p3->terms[p3->degree-i].exp=i; // �˻��ϰ� �ִ� ���� 
				p3->terms[p3->degree-i].coef=sum; // �˻� ���� ������ ��� ���� ��
				// ����� �ְ����� - i�� �����ؾ� ���������� ��µȴ�.  
				p3->n_terms++; // ���ο� ���׽� p3�� ���׽� ���� �� �� ī��Ʈ
			}
		}
		
	}
	return p3;
}



poly_t * poly_sub (poly_t * p1, poly_t * p2) // �� ���׽� ����
{
	 poly_t *p3 = poly_zero();  
	p3->n_terms = 0;
	p3->degree = (p1->degree > p2->degree) ? p1->degree : p2->degree;
	//���� p1.degree > p2.degree �̸� p1->degree�� ������, �ƴϸ� p2->degree�� ����
	p3->terms = (term_t *)malloc(sizeof(term_t) * (p3->degree + 1));
	// 0������ �����ؼ� degre+1 ���� �����Ҵ�

	int i;
	for (i=0; i<= p3->degree; i++){ // p3 �ְ����ױ��� �� ���׽� ��ȸ
		double coef1 = 0.0 , coef2 = 0.0; // ���� ��� ���� ����

		if(i<= p1->degree){ // ���� �˻��ϰ� �ִ� �������� p1�� �ְ������� �� ũ�ٸ�, ���� ������ ���ɼ��� �����Ƿ� �˻�. 
			for (int j = 0; j< p1->n_terms; j++){ // ù ��° ���׽� ��ȸ
				if (p1->terms[j].exp == i){ // ���� ������ ���� �˻��ϰ� �ִ� ������ ���� ���� ���
					coef1 = p1->terms[j].coef; // coef�� ���� ��Ƴ��� �ϴ� �ݺ� ���߱�
					break;
				}
			}
		}

		if(i<=p2->degree){ // �� ��° ���׽� �ְ����ױ��� ��ȸ
			for (int j = 0; j< p2->n_terms; j++){ 
				if(p2->terms[j].exp == i){ 
					coef2 = p2->terms[j].coef;
					break;
				}
			}
			double sub = coef1-coef2; // ������ ��� ���ϱ�
			if(sub!= 0.0){ // ���� ����� ���� 0�� �ƴ϶��
				p3->terms[p3->degree-i].exp=i; // �˻��ϰ� �ִ� ���� 
				p3->terms[p3->degree-i].coef=sub; // �˻� ���� ������ ��� ���� ��
				// ����� �ְ����� - i�� �����ؾ� ���������� ��µȴ�.  
				p3->n_terms++; // ���ο� ���׽� p3�� ���׽� ���� �� �� ī��Ʈ
			}
		}
		
	}
	return p3;
}

poly_t * poly_mult (poly_t * p1, poly_t * p2) // �� ���׽� ���ϱ�
{
    poly_t *p3 = poly_zero();

    for (int i = 0; i <= p1->degree; i++) {
        for (int j = 0; j <= p2->degree; j++) {
            double coef1 = p1->terms[i].coef;
            double coef2 = p2->terms[j].coef;
            int exp1 = p1->terms[i].exp;   //������(��)
            int exp2 = p2->terms[j].exp;
            double coef_p3 = coef1 * coef2;  //�����
            int exp_p3 = exp1 + exp2;

            // ���ο� �� �߰�
            int n = 0;
            for (int k = 0; k < p3->n_terms; k++) {
                if (p3->terms[k].exp == exp_p3) {
                    p3->terms[k].coef += coef_p3;
                    n = 1;
                    break;
                }
            }
            if (n == 0) {
                poly_attach(p3, coef_p3, exp_p3);
            }
        }
    }

    return p3; 

}


double poly_eval (poly_t * p, double x) // �־��� �� x�� ���� ���׽� �� ���
{
	double result = 0.0; // ����� ���� �� ����

	int i =0;
	for (i=0; i<p->n_terms ; i++){ // ��ü �� ��ȸ
		int exp2= p->terms[i].exp; // �˻��ϴ� ���� ���� ����
		double coef2= poly_coef(p,i); // �˻��ϴ� ���� ��� ���� 
		
		double value = 1.0; // �������� �� �̹Ƿ� "1"�� �ؾ���
		
		int j;
		for(j=0; j<exp2; j++){ // ������ŭ x�� ���ؼ� value�� ����
			value *= x;
		}
		
		result += coef2*value; // ����� 
	}
	return result; 
}



void poly_show (poly_t * p) // ���׽� ���
{
	int i ;
	for (i = 0 ; i < p->n_terms ; i++) {
		printf("%lf", p->terms[i].coef) ;
		if (p->terms[i].exp != 0) {
			printf("x^%d", p->terms[i].exp) ;
		}
		if (i != p->n_terms - 1) {
			if (p->terms[i + 1].coef >= 0.0) {
				printf("+") ;
			}
		}
	}
	printf("\n") ;
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

//remove
	printf("%d\n", p == poly_remove(p, 1)) ;

//delete
	poly_delete(p) ;
	poly_show(p) ;



// TODO
//scale_test = 4x^3 + 2x^2+ 5x +3 
	poly_t * scale_test = poly_zero();
	poly_attach(scale_test,4.0,3);
	poly_attach(scale_test,2.0,2);
	poly_attach(scale_test,5.0,1);
	poly_attach(scale_test,3.0,0);
	printf("scale_test-->");
	poly_show(scale_test);

//p1 = x^2 + 2x+ 1
	poly_t * p1 = poly_zero();
	poly_attach(p1,1.0,2);
	poly_attach(p1,2.0,1);
	poly_attach(p1,1.0,0);
	printf("p1-->");
	poly_show(p1);

//p2 = 3x^2+1
	poly_t * p2 = poly_zero();
	poly_attach(p2,3.0,2);
	poly_attach(p2,0.0,1);
	poly_attach(p2,1.0,0);
	printf("p2-->");
	poly_show(p2);	

//scale
	printf("poly_scale-->");
	poly_scale(scale_test ,2);
	poly_show(scale_test);
//add
	poly_t * add_result = poly_add(p1,p2);
	printf("poly_add result-->");
	poly_show(add_result);

//sub
	 poly_t *sub_result = poly_sub(p1, p2);
    printf("poly_sub result--> ");
    poly_show(sub_result);

//mult
    poly_t *mult_result = poly_mult(p1, p2);
    printf("poly_mult result--> ");
    poly_show(mult_result);

//eval 
	double eval_result = poly_eval(p1,3);
	printf("poly_eval result-->%f\n", eval_result);
	

    poly_delete(p1);
    poly_delete(p2);
	poly_delete(add_result);
	poly_delete(sub_result);
	poly_delete(scale_test);
    poly_delete(mult_result);



	return EXIT_SUCCESS ;
}
