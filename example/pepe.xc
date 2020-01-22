#include <stdio.h>

/*__LAMBDA__*/

void transform (int const* first, int const* last, int* out, int(*f)(int)) {
	for(; first != last; ++first)
		*out++ = f(*first);
}

void for_each (int const* first, int const* last, void(*f)(int)) {
	for(; first != last; ++first)
		f(*first);
}

int main () {
	int arr[10] = {0,1,2,3,4,5,6,7,8,9};
	int result[10];

	for_each(arr, arr+10, (fn void(int x) => (void)printf("%d ", x)));
	putchar('\n');

	transform(arr, arr+10, result, (fn int(int x) => x*2));

	for_each(result, result+10, (fn void(int x) => (void)printf("%d ", x)));
	putchar('\n');
	
}

