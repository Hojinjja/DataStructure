#include <stdio.h>
#include <stdlib.h>

typedef 
	struct {
		int exp ;
		double coef ;
	} 
	term_t ; //term_t(항) 정의 -> exp(지수) , coef(계수)

typedef 
	struct {
		int degree ; //
		int n_terms ;
		term_t * terms ; // a list of attached terms 
	} 
	poly_t ; // poly_t(다항식) 정의 -> degree(최고차항), n_terms(항 개수), terms(지수,계수) 



poly_t * poly_zero () // 다항식 초기화
{
	poly_t * p = (poly_t *) malloc(sizeof(poly_t)) ; // 다항식p에 poly_t 만큼 메모리 할당 
	
	//초기값 설정
	p->degree = 0 ; //최고차항 0 
	p->n_terms = 0 ; // 항의 개수 0 
	p->terms = NULL ; // 항의 지수/계수 NULL
	return p ; //초기값 설정된 다항식 p 반환
}




int poly_degree (poly_t * p) //최고차항 구하기
{
	return p->degree ; // 최고차항 정의된 degree 접근해서 return
}

double poly_coef (poly_t * p, int exp) // 지수의 계수 추출하기
{
	//이상한 값 거르기 -> 지수가 0또는 음수인 경우
	if (exp < 0) // 만약 지수가 0미만 이면 -> 0.0 반환 
		return 0.0 ;
	if (p->degree < exp) // 최고차항도 0 미만이면 -> 0.0 반환
		return 0.0 ;

	int i ;
	for (i = 0 ; i < p->n_terms ; i++) { // 항의 개수만큼 순회 (다항식 순회)
		if ((p->terms[i]).exp == exp) { //i번째 항의 지수가 입력한 지수와 같은 경우
			return (p->terms[i]).coef ; // 그 지수의 계수 반환
		}
	}
	return 0.0 ; // 만약 순회하면서 내가 파라미터로 넘긴 지수값이 항에 존재하지 않는다면, 0.0반환 
}	



poly_t * poly_attach (poly_t * p, double coef, int exp) // 지수,계수 입력해서 항 추가하기
{
	
	// 예외 처리- 만약 지수가 음수 , 계수가 0, 입력한 지수의 항이 존재하다면 NULL 반환
	if (exp < 0)
		return NULL ;
	if (coef == 0.0)
		return NULL ;
	if (poly_coef(p, exp) != 0.0)
		return NULL ;

	//만약 기존의 최고차항보다 큰 지수가 입력된다면, 입력된 지수를 최고차항으로 설정 
	if (p->degree < exp) {
		p->degree = exp ;
	}

	// terms(최고차항/항의 개수)를 1만큼 키워서 메모리 재할당
	p->terms = realloc(p->terms, sizeof(term_t) * (p->n_terms + 1)) ; 
	(p->terms[p->n_terms]).coef = coef ; // terms의 맨 끝에 계수 지수 집어넣어서 항 추가
	(p->terms[p->n_terms]).exp = exp ;
	p->n_terms += 1 ; // 항의 개수 +1

	return p ; // 추가작업 마친 p 반환
}

poly_t * poly_remove (poly_t * p, int exp) // 지수를 입력하고 그 지수의 항을 삭제
{
	//예외처리 - 만약 지수가 음수/ 최고차항보다 큰 지수 / 계수가 0인 지수가 입력되면 NULL 반환
	if (exp < 0)
		return NULL ;
	if (p->degree < exp)
		return NULL ;
	if (poly_coef(p, exp) == 0.0)
		return NULL ;


// i로 항을 순회하고 입력한 지수(exp)와 맞는 지수가 찾아질때 까지 i++
	int i = 0 ;
	while (p->terms[i].exp != exp) {
		i++ ;
	}
	// assert p->terms[i].exp == exp
	// i가 삭제하려는 지수에 도착하면 그 때의 i값을

//여기 for문에서 이용하여, 삭제하려는 지수보다 큰 지수들의 항을 한칸씩 앞으로 옮긴다
	for ( ; i < p->n_terms - 1 ; i++) {
		p->terms[i] = p->terms[i + 1] ;
	}
//앞으로 옮기고 난 후 메모리 크기 재할당하고 , 항의 개수도 1 줄인다.
	p->terms = realloc(p->terms, (p->n_terms - 1) * sizeof(term_t)) ;
	p->n_terms -= 1 ;

	int j ;
	p->degree = 0 ; // 최고차항도 초기화해서 
	for (j = 0 ; j < p->n_terms ; j++) { // j를 이용하여 항을 순회하고
		if (p->degree < p->terms[j].exp) { // 가장 큰 지수를 찾아내서 degree로 설정
			p->degree = p->terms[j].exp ;
		}
	}

	return p ;
}

void poly_show (poly_t * p)
{
	int i ;
	for (i = 0 ; i < p->n_terms ; i++) { // i를 이용하여 항의 개수만큼 순회
		printf("%lf", p->terms[i].coef) ; //지수 추출 long float
		if (p->terms[i].exp != 0) { // 만약 지수가 0이 아니라면
			printf("x^%d", p->terms[i].exp) ; // "x^exp"형으로 나타냄
		}
		if (i != p->n_terms - 1) { //만약 마지막 항까지 가지 않았다면
			printf("+") ; // +를 출력
		}
		printf(" ") ;//그리고 공백 출력 
	}
	printf("\n") ; // 줄바꿈으로 끝 
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
