#include <stdio.h>
#include <stdlib.h>

#include <omp.h>
/*
 omp.h
 - OpenMP 헤더
 - 병렬성 및 원자성이 확보됨
 - 동기화 지원
 - 프로젝트 설정에서 OpenMP를 허용해야 함 : 옵션 -> C/C++ -> 언어 -> OpenMP 사용
*/
int main() 
{
	int th_id, nthreads;

	// 시스템에 설치된 Core의 갯수를 출력함
	printf("MAX THREAD : %d\n", omp_get_max_threads());

	// OpenMP 병렬화 처리(th_id는 TLS적용됨)
	#pragma omp parallel private(th_id)
	{
		// 실행중인 스레드의 '스레드번호' 구함
		th_id = omp_get_thread_num();
		printf("Hello World : 나는 %d번 스레드야!\n", th_id);

		// 병렬처리를 위해 생성된 모든 스레드들의 작업이 끝날때까지 동기화
		#pragma omp barrier
		if(th_id == 0)
		{
			// 현재 생성된 스레드들의 갯수를 구함
			nthreads = omp_get_num_threads(); 
			printf("모두 %d개의 스레드가 있습니다\n", nthreads);
		}
	}
	return 0;
}