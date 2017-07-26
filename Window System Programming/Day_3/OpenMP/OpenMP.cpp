#include <stdio.h>
#include <stdlib.h>

#include <omp.h>
/*
 omp.h
 - OpenMP ���
 - ���ļ� �� ���ڼ��� Ȯ����
 - ����ȭ ����
 - ������Ʈ �������� OpenMP�� ����ؾ� �� : �ɼ� -> C/C++ -> ��� -> OpenMP ���
*/
int main() 
{
	int th_id, nthreads;

	// �ý��ۿ� ��ġ�� Core�� ������ �����
	printf("MAX THREAD : %d\n", omp_get_max_threads());

	// OpenMP ����ȭ ó��(th_id�� TLS�����)
	#pragma omp parallel private(th_id)
	{
		// �������� �������� '�������ȣ' ����
		th_id = omp_get_thread_num();
		printf("Hello World : ���� %d�� �������!\n", th_id);

		// ����ó���� ���� ������ ��� ��������� �۾��� ���������� ����ȭ
		#pragma omp barrier
		if(th_id == 0)
		{
			// ���� ������ ��������� ������ ����
			nthreads = omp_get_num_threads(); 
			printf("��� %d���� �����尡 �ֽ��ϴ�\n", nthreads);
		}
	}
	return 0;
}