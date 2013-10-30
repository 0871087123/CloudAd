typedef struct fun_stub {
	unsigned char data[10];
	void * function;
} fun_stub;

void stub_set(fun_stub *tmp, void * func, void * func_stub);
void stub_reset(fun_stub *target);
